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
#include <mpi.h>
#include <mkl.h>

using namespace std;
using namespace isvd;

int mpi_size;
int mpi_rank;

void createA( int m0, int n, int k, double *matrix_a, double *matrix_u_true, int iseed[4] );
void sketch( int Nj, int m, int m0, int n, int k, double *matrix_a, double *matrices_qjt, int iseed[4] );
void integrate( int N, int mj, int k, double *matrices_qjt, double *matrix_qjt );
void reconstruct( int m0, int n, int k, double *matrix_a, double *matrix_qt,
                  double *matrix_u, double *matrix_vt, double *vector_s );
void check( int m0, int k, double *matrix_u_true, double *matrix_u );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {
  double start_time = 0.0, total_time;

  // Initialize MPI
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);

  if ( mpi_rank == 0 ) {
    cout << "iSVD "
         << ISVD_VERSION_MAJOR << "."
         << ISVD_VERSION_MINOR << "."
         << ISVD_VERSION_PATCH << " demo" << endl << endl;
  }

  // Initialize random seed
  srand(time(NULL) ^ mpi_rank);
  srand(rand());
  int iseed[4] = {rand()%4096, rand()%4096, rand()%4096, (rand()%2048)*2+1};

  // Set parameters
  int Nj = 4;
  int m0 = 100;
  int n = 10000;
  int k = 10;
  int N = Nj * mpi_size;
  int mj = (m0-1) / mpi_size + 1;
  int m = mj * mpi_size;
  assert(k <= m && m <= n);

  if ( mpi_rank == 0 ) { printf("m = %d, n = %d, k = %d, N = %d, K = %d\n\n", m, n, k, N, mpi_size); }

  // ====================================================================================================================== //
  // Matrix generating

  if ( mpi_rank == 0 )  {cout << "Generating matrix .............. " << flush; }

  double *matrix_a      = Malloc<double>(m0 * n);
  double *matrix_u_true = Malloc<double>(m0 * k);
  if ( mpi_rank == 0 ) {
    createA(m0, n, k, matrix_a, matrix_u_true, iseed);
  }
  MPI_Bcast(matrix_a, m0*n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  if ( mpi_rank == 0 ) { cout << "done" << endl << endl; }

  MPI_Barrier(MPI_COMM_WORLD);
  if ( mpi_rank == 0 ) {
    cout << "Start iSVD." << endl;
    start_time = dsecnd();
  }

  // ====================================================================================================================== //
  // Random sketching

  if ( mpi_rank == 0 ) { cout << "Sketching ...................... " << flush; }

  double *matrices_qit = Calloc<double>(k * mj * N);
  double *matrices_qjt = Malloc<double>(k * mj * N);
  sketch(Nj, m, m0, n, k, matrix_a, matrices_qit, iseed);
  for ( auto i = 0; i < Nj; ++i ) {
    MPI_Alltoall(matrices_qit+i*k*m, k*mj, MPI_DOUBLE, matrices_qjt+i*k*m, k*mj, MPI_DOUBLE, MPI_COMM_WORLD);
  }

  if ( mpi_rank == 0 ) { cout << "done" << endl; }

  // ====================================================================================================================== //
  // Integration

  if ( mpi_rank == 0 ) { cout << "Integrating .................... " << flush; }

  double *matrix_qt = nullptr;
  if ( mpi_rank == 0 ) {
    matrix_qt        = Malloc<double>(k * m);
  }
  double *matrix_qjt = Malloc<double>(k * mj);
  integrate(N, mj, k, matrices_qjt, matrix_qjt);
  MPI_Gather(matrix_qjt, k*mj, MPI_DOUBLE, matrix_qt, k*mj, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  if ( mpi_rank == 0 ) { cout << "done" << endl; }

  // ====================================================================================================================== //
  // SVD reconstruction

  if ( mpi_rank == 0 ) { cout << "Reconstructing ................. " << flush; }

  double *matrix_u  = nullptr;
  double *matrix_vt = nullptr;
  double *vector_s  = nullptr;
  if ( mpi_rank == 0 ) {
    matrix_u  = Malloc<double>(m0 * k);
    matrix_vt = Malloc<double>(k  * n);
    vector_s  = Malloc<double>(k);
    reconstruct(m0, n, k, matrix_a, matrix_qt, matrix_u, matrix_vt, vector_s);
  }

  if ( mpi_rank == 0 ) { cout << "done" << endl; }

  MPI_Barrier(MPI_COMM_WORLD);
  if ( mpi_rank == 0 ) {
    total_time = dsecnd() - start_time;
  }

  if ( mpi_rank == 0 ) { cout << "Using " << total_time << " seconds." << endl; }

  // ====================================================================================================================== //
  // Check result

  if ( mpi_rank == 0 ) {
    printf("\nS: ");
    for ( auto xx = 0; xx < k; ++xx ) {
      printf("%12.6f", vector_s[xx]);
    }
    printf("\n");
    check(m0, k, matrix_u_true, matrix_u);
  }

  // ====================================================================================================================== //
  // Free memory

  Free(matrix_a);
  Free(matrix_u_true);
  Free(matrix_qt);
  Free(matrix_u);
  Free(matrix_vt);
  Free(matrix_qjt);
  Free(matrices_qjt);
  Free(matrices_qit);

  // Finalize MPI
  MPI_Finalize();

  return 0;
}

void createA( int m0, int n, int k, double *matrix_a, double *matrix_u_true, int iseed[4] ) {
  auto matrix_u     = Malloc<double>(m0 * m0);
  auto matrix_v     = Malloc<double>(n  * m0);
  auto vector_tau_u = Malloc<double>(m0);
  auto vector_tau_v = Malloc<double>(m0);

  // Generate U & V using normal random
  LAPACKE_dlarnv(3, iseed, m0*m0, matrix_u);
  LAPACKE_dlarnv(3, iseed, n*m0,  matrix_v);

  // Orthogonalize U & V
  LAPACKE_dgeqrf(LAPACK_COL_MAJOR, m0, m0, matrix_u, m0, vector_tau_u);
  LAPACKE_dgeqrf(LAPACK_COL_MAJOR, n,  m0, matrix_v, n,  vector_tau_v);

  // Construct U & V
  LAPACKE_dorgqr(LAPACK_COL_MAJOR, m0, m0, m0, matrix_u, m0, vector_tau_u);
  LAPACKE_dorgqr(LAPACK_COL_MAJOR, n,  m0, m0, matrix_v, n,  vector_tau_v);

  // Copy U
  cblas_dcopy(m0*k, matrix_u, 1, matrix_u_true, 1);

  // A := U * S * V'
  for ( auto i = 0; i < k; ++i ) {
    cblas_dscal(m0, 1.0  / (i+1), matrix_u+i*m0, 1);
  }
  for ( auto i = k; i < m0; ++i ) {
    cblas_dscal(m0, 1e-2 / (i-k+1), matrix_u+i*m0, 1);
  }
  cblas_dgemm(CblasColMajor, CblasNoTrans, CblasTrans, m0, n, m0, 1.0, matrix_u, m0, matrix_v, n, 0.0, matrix_a, m0);

  // Free memory
  Free(matrix_u);
  Free(matrix_v);
  Free(vector_tau_u);
  Free(vector_tau_v);
}

void sketch( int Nj, int m, int m0, int n, int k, double *matrix_a, double *matrices_qjt, int iseed[4] ) {
  auto matrix_oit = Malloc<double>(k * n);
  auto vector_tau = Malloc<double>(k);

  for ( auto i = 0; i < Nj; ++i ) {
    LAPACKE_dlarnv(3, iseed, k*n, matrix_oit);
    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasTrans,
                k, m0, n, 1.0, matrix_oit, k, matrix_a, m0, 0.0, matrices_qjt+i*k*m, k);
    LAPACKE_dgeqrf(LAPACK_ROW_MAJOR, m0, k, matrices_qjt+i*k*m, k, vector_tau);
    LAPACKE_dorgqr(LAPACK_ROW_MAJOR, m0, k, k, matrices_qjt+i*k*m, k, vector_tau);
  }

  // Free memory
  Free(matrix_oit);
  Free(vector_tau);
}

void integrate( int N, int mj, int k, double *matrices_qjt, double *matrix_qjt ) {
  auto matrix_b   = Malloc<double>(k * k * N);
  auto matrix_d   = Malloc<double>(k * k * N);
  auto matrix_c   = Malloc<double>(k * k);
  auto matrix_xjt = Malloc<double>(k * mj);
  auto matrix_tmp = Malloc<double>(k * mj);
  auto vector_e   = Malloc<double>(k);

  bool is_converged = false;

  // Qj' := Q0'
  cblas_dcopy(k*mj, matrices_qjt, 1, matrix_qjt, 1);

  while ( !is_converged ) {

    // ================================================================================================================== //
    // X = (I - Q * Q') * sum( Qi * Qi' )/N * Q

    // Bi := sum( Qij' * Qj )
    for ( auto i = 0; i < N; ++i ) {
      cblas_dgemm(CblasColMajor, CblasNoTrans, CblasTrans,
                  k, k, mj, 1.0, matrices_qjt+i*k*mj, k, matrix_qjt, k, 0.0, matrix_d+i*k*k, k);
    }
    MPI_Allreduce(matrix_d, matrix_b, k*k*N, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    // Xj' := 0, D := 0
    fill(matrix_xjt, matrix_xjt+k*mj, 0.0);
    fill(matrix_d,   matrix_d+k*k,   0.0);

    for ( auto i = 0; i < N; ++i ) {
      // Di := Bi' * Bi
      cblas_dsyrk(CblasColMajor, CblasLower, CblasTrans, k, k, 1.0, matrix_b+i*k*k, k, 1.0, matrix_d, k);

      // Xj' += Bi' * Qij'
      cblas_dgemm(CblasColMajor, CblasTrans, CblasNoTrans,
                  k, mj, k, 1.0, matrix_b+i*k*k, k, matrices_qjt+i*k*mj, k, 1.0, matrix_xjt, k);
    }

    // Xj' -= D * Qj'
    cblas_dsymm(CblasColMajor, CblasLeft, CblasLower, k, mj, -1.0, matrix_d, k, matrix_qjt, k, 1.0, matrix_xjt, k);

    // Xj' /= N
    cblas_dscal(k*mj, 1.0/N, matrix_xjt, 1);

    // ================================================================================================================== //
    // C := sqrt( I/2 + sqrt( I/4 - X' * X ) )

    // B := I/4 - sum( Xj'*Xj )
    cblas_dsyrk(CblasColMajor, CblasLower, CblasNoTrans, k, mj, -1.0, matrix_xjt, k, 0.0, matrix_d, k);
    MPI_Allreduce(matrix_d, matrix_b, k*k, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
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

    // Qj' := C * Qj'
    cblas_dsymm(CblasColMajor, CblasLeft, CblasLower, k, mj, 1.0, matrix_c, k, matrix_qjt, k, 0.0, matrix_tmp, k);
    cblas_dcopy(k*mj, matrix_tmp, 1, matrix_qjt, 1);

    // Check convergence
    if ( mpi_rank == 0 ) {
      for ( auto i = 0; i < k; ++i ) {
        matrix_c[i+i*k] -= 1.0;
      }
      LAPACKE_dsyev(LAPACK_COL_MAJOR, 'N', 'L', k, matrix_c, k, vector_e);
      is_converged = !(abs(vector_e[cblas_idamax(k, vector_e, 1)]) > 1e-6);
    }
    MPI_Bcast(&is_converged, 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    // inv(C) := B*B'
    cblas_dsyrk(CblasColMajor, CblasLower, CblasNoTrans, k, k, 1.0, matrix_b, k, 0.0, matrix_c, k);

    // Qj' += inv(C) * Xj'
    cblas_dsymm(CblasColMajor, CblasLeft, CblasLower, k, mj, 1.0, matrix_c, k, matrix_xjt, k, 1.0, matrix_qjt, k);
  }

  // Free memory
  Free(matrix_b);
  Free(matrix_d);
  Free(matrix_c);
  Free(matrix_xjt);
  Free(matrix_tmp);
  Free(vector_e);
}

void reconstruct( int m0, int n, int k, double *matrix_a, double *matrix_qt,
                  double *matrix_u, double *matrix_vt, double *vector_s ) {
  auto matrix_w   = Malloc<double>(k * k);
  auto vector_tmp = Malloc<double>(k);

  // V := Q' * A
  cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, k, n, m0, 1.0, matrix_qt, k, matrix_a, m0, 0.0, matrix_vt, k);

  // Compute the SVD of V (W := left singular vectors, V := right singular vectors, S := singular values)
  LAPACKE_dgesvd(LAPACK_COL_MAJOR, 'S', 'O', k, n, matrix_vt, k, vector_s, matrix_w, k, nullptr, 1, vector_tmp);

  // U := Q * W
  cblas_dgemm(CblasColMajor, CblasTrans, CblasNoTrans, m0, k, k, 1.0, matrix_qt, k, matrix_w, k, 0.0, matrix_u, m0);

  // Free memory
  Free(matrix_w);
  Free(vector_tmp);
}

void check( int m0, int k, double *matrix_u_true, double *matrix_u ) {
  auto matrix_tmp = Malloc<double>(k * k);
  auto vector_tmp1 = Malloc<double>(k);
  auto vector_tmp2 = Malloc<double>(k);

  // TMP := Utrue' * U
  cblas_dgemm(CblasColMajor, CblasTrans, CblasNoTrans, k, k, m0, 1.0, matrix_u_true, m0, matrix_u, m0, 0.0, matrix_tmp, k);

  // Compute the SVD of TMP
  LAPACKE_dgesvd(LAPACK_COL_MAJOR, 'N', 'N', k, k, matrix_tmp, k, vector_tmp1, nullptr, 1, nullptr, 1, vector_tmp2);
  cout << "s_max(U_true' * U) = " << abs(vector_tmp1[cblas_idamax(k, vector_tmp1, 1)]) << endl;
  cout << "s_min(U_true' * U) = " << abs(vector_tmp1[cblas_idamin(k, vector_tmp1, 1)]) << endl;

  Free(matrix_tmp);
  Free(vector_tmp1);
  Free(vector_tmp2);
}
