////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    main/demo.cpp
/// @brief   The demo code
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#include <cmath>
#include <iostream>
#include <algorithm>
#include <isvd.hpp>
#include <mkl.h>

using namespace std;
using namespace isvd;

void createA( int m, int n, int k, double *matrix_a, int iseed[4] );
void sketch( int N, int m, int n, int k, double *matrix_a, double *matrices_q[], int iseed[4] );
void integrate( int N, int m, int k, double *matrices_q[], double *matrix_q );
void reconstruct( int m, int n, int k, double *matrix_a, double *matrix_q,
                  double *matrix_u, double *matrix_v, double *vector_s );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main() {
  cout << "iSVD "
       << ISVD_VERSION_MAJOR << "."
       << ISVD_VERSION_MINOR << "."
       << ISVD_VERSION_PATCH << " demo" << endl << endl;

  // Initialize random generator
  #pragma warning
  // srand(time(NULL));
  // int iseed[4] = {rand()%4096, rand()%4096, rand()%4096, (rand()%2048)*2+1};
  int iseed[4] = {0, 0, 0, 1};

  // Set parameters
  int N = 8;
  int m = 100;
  int n = 1000;
  int k = 10;
  assert(k <= m && m <= n);

  // ====================================================================================================================== //
  // Matrix generating

  auto matrix_a = static_cast<double*>(mkl_malloc(m * n * sizeof(double), 64));
  createA(m, n, k, matrix_a, iseed);

  // ====================================================================================================================== //
  // Random sketching

  auto matrices_q = new double*[N];
  for ( auto i = 0; i < N; ++i ) {
    matrices_q[i] = static_cast<double*>(mkl_malloc(m * k * sizeof(double), 64));
  }
  sketch(N, m, n, k, matrix_a, matrices_q, iseed);

  // ====================================================================================================================== //
  // Integration

  auto matrix_q = static_cast<double*>(mkl_malloc(m * k * sizeof(double), 64));
  integrate(N, m, k, matrices_q, matrix_q);

  // ====================================================================================================================== //
  // Reconstruct SVD

  auto matrix_u = static_cast<double*>(mkl_malloc(m * k * sizeof(double), 64));
  auto matrix_v = static_cast<double*>(mkl_malloc(n * k * sizeof(double), 64));
  auto vector_s = static_cast<double*>(mkl_malloc(k *     sizeof(double), 64));
  reconstruct(m, n, k, matrix_a, matrix_q, matrix_u, matrix_v, vector_s);

  // ====================================================================================================================== //
  // Check result

  auto vector_tmp1 = static_cast<double*>(mkl_malloc(m * sizeof(double), 64));
  auto vector_tmp2 = static_cast<double*>(mkl_malloc(m * sizeof(double), 64));

  // A -= U * S * V
  for ( auto i = 0; i < k; ++i ) {
    cblas_dscal(m, vector_s[i], matrix_u+i*m, 1);
  }
  cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, m, n, k, -1.0, matrix_u, m, matrix_v, k, 1.0, matrix_a, m);

  // Compute the SVD of A (S := singular values)
  LAPACKE_dgesvd(LAPACK_COL_MAJOR, 'N', 'N', m, n, matrix_a, m, vector_tmp1, nullptr, 1, nullptr, 1, vector_tmp2);
  cout << "norm(A - USV') = " << abs(vector_tmp1[cblas_idamax(m, vector_tmp1, 1)]) << endl;

  mkl_free(vector_tmp1);
  mkl_free(vector_tmp2);

  // ====================================================================================================================== //
  // Free memory

  mkl_free(matrix_a);
  mkl_free(matrix_q);
  mkl_free(matrix_u);
  mkl_free(matrix_v);
  // mkl_free(vector_s);
  for ( auto i = 0; i < N; ++i ) {
    mkl_free(matrices_q[i]);
  }
  delete[] matrices_q;

  return 0;
}

void createA( int m, int n, int k, double *matrix_a, int iseed[4] ) {
  auto matrix_u     = static_cast<double*>(mkl_malloc(m * m * sizeof(double), 64));
  auto matrix_v     = static_cast<double*>(mkl_malloc(n * n * sizeof(double), 64));
  auto vector_tau_u = static_cast<double*>(mkl_malloc(m *     sizeof(double), 64));
  auto vector_tau_v = static_cast<double*>(mkl_malloc(n *     sizeof(double), 64));

  // Fill A by diagonal
  fill(matrix_a, matrix_a+m*n, 0.0);
  for ( auto i = 0; i < k; ++i ) {
    matrix_a[i+i*m] = 1.0 / (i+1);
  }
  for ( auto i = k; i < m; ++i ) {
    matrix_a[i+i*m] = 1e-2 / (i+1);
  }

  // Generate U & V using normal random
  LAPACKE_dlarnv(3, iseed, m*m, matrix_u);
  LAPACKE_dlarnv(3, iseed, n*n, matrix_v);

  // Orthogonalize U & V
  LAPACKE_dgeqrf(LAPACK_COL_MAJOR, m, m, matrix_u, m, vector_tau_u);
  LAPACKE_dgeqrf(LAPACK_COL_MAJOR, n, n, matrix_v, n, vector_tau_v);

  // A := U * S * V'
  LAPACKE_dormqr(LAPACK_COL_MAJOR, 'L', 'N', m, n, m, matrix_u, m, vector_tau_u, matrix_a, m);
  LAPACKE_dormqr(LAPACK_COL_MAJOR, 'R', 'T', m, n, n, matrix_v, n, vector_tau_v, matrix_a, m);

  // Free memory
  mkl_free(matrix_u);
  mkl_free(matrix_v);
  mkl_free(vector_tau_u);
  mkl_free(vector_tau_v);
}

void sketch( int N, int m, int n, int k, double *matrix_a, double *matrices_q[], int iseed[4] ) {
  auto matrix_omega = static_cast<double*>(mkl_malloc(n * k * sizeof(double), 64));
  auto vector_tau   = static_cast<double*>(mkl_malloc(k * sizeof(double), 64));

  for ( auto i = 0; i < N; ++i ) {
    LAPACKE_dlarnv(3, iseed, n*k, matrix_omega);
    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, m, k, n, 1.0, matrix_a, m, matrix_omega, n, 0.0, matrices_q[i], m);
    LAPACKE_dgeqrf(LAPACK_COL_MAJOR, m, k, matrices_q[i], m, vector_tau);
    LAPACKE_dorgqr(LAPACK_COL_MAJOR, m, k, k, matrices_q[i], m, vector_tau);
  }

  // Free memory
  mkl_free(matrix_omega);
  mkl_free(vector_tau);
}

void integrate( int N, int m, int k, double *matrices_q[], double *matrix_q ) {
  auto matrix_c = static_cast<double*>(mkl_malloc(k * k * sizeof(double), 64));
  auto matrix_b = static_cast<double*>(mkl_malloc(k * k * sizeof(double), 64));
  auto matrix_d = static_cast<double*>(mkl_malloc(k * k * sizeof(double), 64));
  auto matrix_x = static_cast<double*>(mkl_malloc(m * k * sizeof(double), 64));
  auto matrix_y = static_cast<double*>(mkl_malloc(m * k * sizeof(double), 64));
  auto vector_e = static_cast<double*>(mkl_malloc(k     * sizeof(double), 64));

  bool is_converged = false;

  // Q := Q0
  cblas_dcopy(m*k, matrices_q[0], 1, matrix_q, 1);

  while ( !is_converged ) {

    // ================================================================================================================== //
    // X = (I - Q * Q') * sum( Qi * Qi' )/N * Q

    // X := 0, C := 0
    fill(matrix_x, matrix_x+m*k, 0.0);
    fill(matrix_d, matrix_d+k*k, 0.0);

    for ( auto i = 0; i < N; ++i ) {
      // B := Qi' * Q
      cblas_dgemm(CblasColMajor, CblasTrans, CblasNoTrans, k, k, m, 1.0, matrices_q[i], m, matrix_q, m, 0.0, matrix_b, k);

      // D += B' * B
      cblas_dsyrk(CblasColMajor, CblasLower, CblasTrans, k, k, 1.0, matrix_b, k, 1.0, matrix_d, k);

      // X += Qi * B
      cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, m, k, k, 1.0, matrices_q[i], m, matrix_b, k, 1.0, matrix_x, m);
    }

    // X -= Q * D
    cblas_dsymm(CblasColMajor, CblasRight, CblasLower, m, k, -1.0, matrix_d, k, matrix_q, m, 1.0, matrix_x, m);

    // X /= N
    cblas_dscal(m*k, 1.0/N, matrix_x, 1);

    // ================================================================================================================== //
    // C := sqrt( I/2 + sqrt( I/4 - X' * X ) )

    // B := I/4 - X'*X
    cblas_dsyrk(CblasColMajor, CblasLower, CblasTrans, k, m, -1.0, matrix_x, m, 0.0, matrix_b, k);
    for ( auto i = 0; i < k; ++i ) {
      matrix_b[i+i*k] += 0.25;
    }

    // Compute the eigen-decomposition of B (E := eigenvalues, B := eigenvectors)
    LAPACKE_dsyev(LAPACK_COL_MAJOR, 'V', 'L', k, matrix_b, k, vector_e);

    // B *= E^(1/4)
    for ( auto i = 0; i < k; ++i ) {
      cblas_dscal(k, pow(vector_e[i], 0.25), matrix_b+i*k, 1);
    }

    // D := I/2 + B*B'
    cblas_dsyrk(CblasColMajor, CblasLower, CblasNoTrans, k, k, 1.0, matrix_b, k, 0.0, matrix_d, k);
    for ( auto i = 0; i < k; ++i ) {
      matrix_d[i+i*k] += 0.5;
    }

    // Compute the eigen-decomposition of D (E := eigenvalues, D := eigenvectors)
    LAPACKE_dsyev(LAPACK_COL_MAJOR, 'V', 'L', k, matrix_d, k, vector_e);

    // B := D
    cblas_dcopy(k*k, matrix_d, 1, matrix_b, 1);

    // D *= E^(1/4)
    for ( auto i = 0; i < k; ++i ) {
      cblas_dscal(k, pow(vector_e[i], 0.25), matrix_d+i*k, 1);
    }

    // B /= E^(1/4)
    for ( auto i = 0; i < k; ++i ) {
      cblas_dscal(k, pow(vector_e[i], -0.25), matrix_b+i*k, 1);
    }

    // C *= D*D'
    cblas_dsyrk(CblasColMajor, CblasLower, CblasNoTrans, k, k, 1.0, matrix_d, k, 0.0, matrix_c, k);

    // ================================================================================================================== //
    // Q := Q * C + X * inv(C)

    // Q *= C
    cblas_dsymm(CblasColMajor, CblasRight, CblasLower, m, k, 1.0, matrix_c, k, matrix_q, m, 0.0, matrix_y, m);
    cblas_dcopy(m*k, matrix_y, 1, matrix_q, 1);

    // Check convergence
    for ( auto i = 0; i < k; ++i ) {
      matrix_c[i+i*k] -= 1.0;
    }
    LAPACKE_dsyev(LAPACK_COL_MAJOR, 'N', 'L', k, matrix_c, k, vector_e);
    is_converged = !(abs(vector_e[cblas_idamax(k, vector_e, 1)]) > 1e-6);

    // inv(C) := B*B'
    cblas_dsyrk(CblasColMajor, CblasLower, CblasNoTrans, k, k, 1.0, matrix_b, k, 0.0, matrix_c, k);

    // Q += X * inv(C)
    cblas_dsymm(CblasColMajor, CblasRight, CblasLower, m, k, 1.0, matrix_c, k, matrix_x, m, 1.0, matrix_q, m);
  }

  // Free memory
  mkl_free(matrix_b);
  mkl_free(matrix_d);
  mkl_free(matrix_c);
  mkl_free(matrix_x);
  mkl_free(matrix_y);
  mkl_free(vector_e);
}
void reconstruct( int m, int n, int k, double *matrix_a, double *matrix_q,
                  double *matrix_u, double *matrix_v, double *vector_s ) {
  auto matrix_w   = static_cast<double*>(mkl_malloc(k * k * sizeof(double), 64));
  auto vector_tmp = static_cast<double*>(mkl_malloc(k * sizeof(double), 64));

  // V := Q' * A
  cblas_dgemm(CblasColMajor, CblasTrans, CblasNoTrans, k, n, m, 1.0, matrix_q, m, matrix_a, m, 0.0, matrix_v, k);

  // Compute the SVD of V (W := left singular vectors, V := right singular vectors, S := singular values)
  LAPACKE_dgesvd(LAPACK_COL_MAJOR, 'S', 'O', k, n, matrix_v, k, vector_s, matrix_w, k, nullptr, 1, vector_tmp);

  // U := Q * W
  cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, m, k, k, 1.0, matrix_q, m, matrix_w, k, 0.0, matrix_u, m);

  // Free memory
  mkl_free(matrix_w);
  mkl_free(vector_tmp);
}
