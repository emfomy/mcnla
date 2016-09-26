////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/isvd.cpp
/// @brief   The iSVD algorithm
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#include <cmath>
#include <iostream>
#include <algorithm>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <isvd/utility.hpp>
#include <mpi.h>
#include <mkl.h>

using namespace std;
using namespace boost::accumulators;
using namespace isvd;

int mpi_size;
int mpi_rank;

double tolorance = 1e-4;

void createA( const int m0, const int n, const int k, double *matrix_a, double *matrix_u_true, int seed[4] );
void sketch( const int Nj, const int m, const int m0, const int n, const int k,
             const double *matrix_a, double *matrices_qjt, int seed[4] );
void integrate( const int N, const int mj, const int k, const double *matrices_qjt, double *matrix_qjt );
void reconstruct( const int m0, const int n, const int k,
                  const double *matrix_a, const double *matrix_qt, double *matrix_u, double *matrix_vt, double *vector_s );
void check( const int m0, const int k, const double *matrix_u_true, const double *matrix_u,
            double &smax, double &smin, double &smean );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {
  double start_time = 0.0, total_time = 0.0, smax, smin, smean;

  // ====================================================================================================================== //
  // Initialize MPI
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);

  if ( mpi_rank == 0 ) {
    cout << "iSVD "
         << ISVD_VERSION_MAJOR << "."
         << ISVD_VERSION_MINOR << "."
         << ISVD_VERSION_PATCH << " old demo" << endl << endl;
  }

  int Nj       = ( argc > 1 ) ? atoi(argv[1]) : 4;
  int m0       = ( argc > 2 ) ? atoi(argv[2]) : 1000;
  int n        = ( argc > 3 ) ? atoi(argv[3]) : 10000;
  int k        = ( argc > 4 ) ? atoi(argv[4]) : 10;
  int num_test = ( argc > 5 ) ? atoi(argv[5]) : 100;

  // ====================================================================================================================== //
  // Initialize random seed
  srand(time(NULL) ^ mpi_rank);
  srand(rand());
  int seed[4] = {rand()%4096, rand()%4096, rand()%4096, (rand()%2048)*2+1};

  // ====================================================================================================================== //
  // Set parameters
  bool verbose = false;
  int N = Nj * mpi_size;
  int mj = (m0-1) / mpi_size + 1;
  int m = mj * mpi_size;
  assert(k <= m && m <= n);

  if ( mpi_rank == 0 ) { printf("m = %d, n = %d, k = %d, N = %d, K = %d\n\n", m, n, k, N, mpi_size); }

  // ====================================================================================================================== //
  // Allocate memory
  auto matrix_a      = malloc<double>(m0 * n);
  auto matrix_u_true = malloc<double>(m0 * k);
  auto matrix_qt     = malloc<double>(k * m);
  auto matrix_u      = malloc<double>(m0 * k);
  auto matrix_vt     = malloc<double>(k  * n);
  auto vector_s      = malloc<double>(k);
  auto matrix_qjt    = malloc<double>(k * mj);
  auto matrices_qjt  = malloc<double>(k * mj * N);
  accumulator_set<double, stats<tag::variance>> acc_max, acc_min, acc_mean;

  // ====================================================================================================================== //
  // Generate matrix
  if ( verbose && mpi_rank == 0 )  {cout << "Generating matrix .............. " << flush; }
  if ( mpi_rank == 0 ) {
    createA(m0, n, k, matrix_a, matrix_u_true, seed);
  }
  MPI_Bcast(matrix_a, m0*n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  if ( verbose && mpi_rank == 0 ) { cout << "done" << endl << endl; }

  // ====================================================================================================================== //
  // Run iSVD
  if ( mpi_rank == 0 ) {
    cout << "Start iSVD." << endl;
  }

  for ( auto t = 0; t < num_test; ++t ) {
    MPI_Barrier(MPI_COMM_WORLD);
    if ( mpi_rank == 0 ) {
      start_time = dsecnd();
    }

    // ================================================================================================================== //
    // Random sketch
    if ( verbose && mpi_rank == 0 ) { cout << "Sketching ...................... " << flush; }
    fill(matrices_qjt, matrices_qjt+k*mj*N, 0.0);
    sketch(Nj, m, m0, n, k, matrix_a, matrices_qjt, seed);
    for ( auto i = 0; i < Nj; ++i ) {
      MPI_Alltoall(MPI_IN_PLACE, k*mj, MPI_DOUBLE, matrices_qjt+i*k*m, k*mj, MPI_DOUBLE, MPI_COMM_WORLD);
    }
    if ( verbose && mpi_rank == 0 ) { cout << "done" << endl; }

    // ================================================================================================================== //
    // Integrate
    if ( verbose && mpi_rank == 0 ) { cout << "Integrating .................... " << flush; }
    integrate(N, mj, k, matrices_qjt, matrix_qjt);
    MPI_Gather(matrix_qjt, k*mj, MPI_DOUBLE, matrix_qt, k*mj, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    if ( verbose && mpi_rank == 0 ) { cout << "done" << endl; }

    // ================================================================================================================== //
    // Reconstruct SVD
    if ( verbose && mpi_rank == 0 ) { cout << "Reconstructing ................. " << flush; }
    if ( mpi_rank == 0 ) {
      reconstruct(m0, n, k, matrix_a, matrix_qt, matrix_u, matrix_vt, vector_s);
    }
    if ( verbose && mpi_rank == 0 ) { cout << "done" << endl; }

    // ================================================================================================================== //
    // Check time
    MPI_Barrier(MPI_COMM_WORLD);
    if ( mpi_rank == 0 ) {
      total_time += dsecnd() - start_time;
    }

    // ================================================================================================================== //
    // Check result
    if ( mpi_rank == 0 ) {
      check(m0, k, matrix_u_true, matrix_u, smax, smin, smean);
    }
    if ( verbose && mpi_rank == 0 ) {
      printf("\nS: "); for ( auto xx = 0; xx < k; ++xx ) { printf("%12.6f", vector_s[xx]); } printf("\n");
      printf("svd(U_true' * U): max = %.4f, min = %.4f, mean = %.4f\n", smax, smin, smean); fflush(stdout);
    }
    if ( mpi_rank == 0 ) { printf("%4d: max = %.4f, min = %.4f, mean = %.4f\n", t, smax, smin, smean); }
    if ( mpi_rank == 0 ) { acc_min(smin); acc_max(smax); acc_mean(smean); }
  }

  if ( mpi_rank == 0 ) {
    cout << "Used " << total_time / num_test << " seconds averagely." << endl;
    cout << "mean(max(svd(U_true' * U)))  = " << mean(acc_max) << endl;
    cout << "mean(min(svd(U_true' * U)))  = " << mean(acc_min) << endl;
    cout << "mean(mean(svd(U_true' * U))) = " << mean(acc_mean) << endl;
    cout << "sd(max(svd(U_true' * U)))    = " << sqrt(variance(acc_max)) << endl;
    cout << "sd(min(svd(U_true' * U)))    = " << sqrt(variance(acc_min)) << endl;
    cout << "sd(mean(svd(U_true' * U)))   = " << sqrt(variance(acc_mean)) << endl;
  }

  // ====================================================================================================================== //
  // Free memory
  free(matrix_a);
  free(matrix_u_true);
  free(matrix_qt);
  free(matrix_u);
  free(matrix_vt);
  free(vector_s);
  free(matrix_qjt);
  free(matrices_qjt);

  // Finalize MPI
  MPI_Finalize();

  return 0;
}

void createA( const int m0, const int n, const int k, double *matrix_a, double *matrix_u_true, int seed[4] ) {
  auto matrix_u     = malloc<double>(m0 * m0);
  auto matrix_v     = malloc<double>(n  * m0);
  auto vector_tmp_s = malloc<double>(m0);
  auto vector_tmp_b = malloc<double>(m0);

  // Generate U & V using normal random
  LAPACKE_dlarnv(3, seed, m0*m0, matrix_u);
  LAPACKE_dlarnv(3, seed, n*m0,  matrix_v);

  // Orthogonalize U & V
  LAPACKE_dgesvd(LAPACK_COL_MAJOR, 'O', 'N', m0, m0, matrix_u, m0, vector_tmp_s, nullptr, 1, nullptr, 1, vector_tmp_b);
  LAPACKE_dgesvd(LAPACK_COL_MAJOR, 'O', 'N', n,  m0, matrix_v, n,  vector_tmp_s, nullptr, 1, nullptr, 1, vector_tmp_b);

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
  free(matrix_u);
  free(matrix_v);
  free(vector_tmp_s);
  free(vector_tmp_b);
}

void sketch( const int Nj, const int m, const int m0, const int n, const int k,
             const double *matrix_a, double *matrices_qjt, int seed[4] ) {
  auto matrix_oit = malloc<double>(k * n);
  auto vector_tmp_s = malloc<double>(k);
  auto vector_tmp_b = malloc<double>(k);

  for ( auto i = 0; i < Nj; ++i ) {
    LAPACKE_dlarnv(3, seed, k*n, matrix_oit);
    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasTrans,
                k, m0, n, 1.0, matrix_oit, k, matrix_a, m0, 0.0, matrices_qjt+i*k*m, k);


    LAPACKE_dgesvd(LAPACK_COL_MAJOR, 'N', 'O', k, m0, matrices_qjt+i*k*m, k,
                   vector_tmp_s, nullptr, 1, nullptr, 1, vector_tmp_b);
  }

  // Free memory
  free(matrix_oit);
  free(vector_tmp_s);
  free(vector_tmp_b);
}

void integrate( const int N, const int mj, const int k, const double *matrices_qjt, double *matrix_qjt ) {
  auto matrix_b   = malloc<double>(k * k * N);
  auto matrix_d   = malloc<double>(k * k);
  auto matrix_c   = malloc<double>(k * k);
  auto matrix_xjt = malloc<double>(k * mj);
  auto matrix_tmp = malloc<double>(k * mj);
  auto vector_e   = malloc<double>(k);

  bool is_converged = false;

  // Qj' := Q0'
  cblas_dcopy(k*mj, matrices_qjt, 1, matrix_qjt, 1);

  while ( !is_converged ) {

    // ================================================================================================================== //
    // X = (I - Q * Q') * sum( Qi * Qi' )/N * Q

    // Bi := sum( Qij' * Qj )
    for ( auto i = 0; i < N; ++i ) {
      cblas_dgemm(CblasColMajor, CblasNoTrans, CblasTrans,
                  k, k, mj, 1.0, matrices_qjt+i*k*mj, k, matrix_qjt, k, 0.0, matrix_b+i*k*k, k);
    }
    MPI_Allreduce(MPI_IN_PLACE, matrix_b, k*k*N, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

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
    cblas_dsyrk(CblasColMajor, CblasLower, CblasNoTrans, k, mj, -1.0, matrix_xjt, k, 0.0, matrix_b, k);
    MPI_Allreduce(MPI_IN_PLACE, matrix_b, k*k, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
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

    // C *= D * D'
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
      is_converged = !(abs(vector_e[cblas_idamax(k, vector_e, 1)]) > tolorance);
    }
    MPI_Bcast(&is_converged, 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    // inv(C) := B*B'
    cblas_dsyrk(CblasColMajor, CblasLower, CblasNoTrans, k, k, 1.0, matrix_b, k, 0.0, matrix_c, k);

    // Qj' += inv(C) * Xj'
    cblas_dsymm(CblasColMajor, CblasLeft, CblasLower, k, mj, 1.0, matrix_c, k, matrix_xjt, k, 1.0, matrix_qjt, k);
  }

  // Free memory
  free(matrix_b);
  free(matrix_d);
  free(matrix_c);
  free(matrix_xjt);
  free(matrix_tmp);
  free(vector_e);
}

void reconstruct( const int m0, const int n, const int k,
                  const double *matrix_a, const double *matrix_qt, double *matrix_u, double *matrix_vt, double *vector_s ) {
  auto matrix_w   = malloc<double>(k * k);
  auto vector_tmp = malloc<double>(k);

  // V := Q' * A
  cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, k, n, m0, 1.0, matrix_qt, k, matrix_a, m0, 0.0, matrix_vt, k);

  // Compute the SVD of V (W := left singular vectors, V := right singular vectors, S := singular values)
  LAPACKE_dgesvd(LAPACK_COL_MAJOR, 'S', 'O', k, n, matrix_vt, k, vector_s, matrix_w, k, nullptr, 1, vector_tmp);

  // U := Q * W
  cblas_dgemm(CblasColMajor, CblasTrans, CblasNoTrans, m0, k, k, 1.0, matrix_qt, k, matrix_w, k, 0.0, matrix_u, m0);

  // Free memory
  free(matrix_w);
  free(vector_tmp);
}

void check( const int m0, const int k, const double *matrix_u_true, const double *matrix_u,
            double &smax, double &smin, double &smean ) {
  auto matrix_tmp  = malloc<double>(k * k);
  auto vector_tmp1 = malloc<double>(k);
  auto vector_tmp2 = malloc<double>(k);

  // TMP := Utrue' * U
  cblas_dgemm(CblasColMajor, CblasTrans, CblasNoTrans, k, k, m0, 1.0, matrix_u_true, m0, matrix_u, m0, 0.0, matrix_tmp, k);

  // Compute the SVD of TMP
  LAPACKE_dgesvd(LAPACK_COL_MAJOR, 'N', 'N', k, k, matrix_tmp, k, vector_tmp1, nullptr, 1, nullptr, 1, vector_tmp2);
  smax = abs(vector_tmp1[cblas_idamax(k, vector_tmp1, 1)]);
  smin = abs(vector_tmp1[cblas_idamin(k, vector_tmp1, 1)]);
  smean = cblas_dasum(k, vector_tmp1, 1) / k;

  // Free memory
  free(matrix_tmp);
  free(vector_tmp1);
  free(vector_tmp2);
}
