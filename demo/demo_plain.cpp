////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/demo_plain.cpp
/// @brief   The plain demo code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <cmath>
#include <cassert>
#include <iostream>
#include <mcnla/config.hpp>
#include "statistics_set.hpp"
#include <mpi.h>
#include <mkl.h>
#include <omp.h>

using namespace std;

int mpi_size;
int mpi_rank;

double tol = 1e-4;
int maxiter = 256;

void createA( const int m0, const int n, const int k, double *matrix_a, double *matrix_u_true, int seed[4] );
void sketch( const int Nj, const int m, const int m0, const int n, const int k, const int q,
             const double *matrix_a, double *matrices_qjt, int seed[4] );
void integrate( const int N, const int mj, const int k, const double *matrices_qjt, double *matrix_qjt, int &iter );
void form( const int m0, const int n, const int k,
           const double *matrix_a, const double *matrix_qt, double *matrix_u, double *matrix_vt, double *vector_s );
void check_u( const int m0, const int k, const double *matrix_u_true, const double *matrix_u,
              double &smax, double &smin, double &smean );
void check( const int m0, const int n, const int k, const double *matrix_a,
            const double *matrix_u, const double *matrix_vt, const double *vector_s, double &frerr );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {

  // ====================================================================================================================== //
  // Initialize MPI
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);

  if ( mpi_rank == 0 ) {
    cout << "iSVD "
         << MCNLA_MAJOR_VERSION << "."
         << MCNLA_MINOR_VERSION << "."
         << MCNLA_PATCH_VERSION << " plain demo" << endl << endl;
  }

  int argi = 0;
  int Nj        = ( argc > ++argi ) ? atof(argv[argi]) : 4;
  int m0        = ( argc > ++argi ) ? atof(argv[argi]) : 1000;
  int n         = ( argc > ++argi ) ? atof(argv[argi]) : 10000;
  int k         = ( argc > ++argi ) ? atof(argv[argi]) : 100;
  int q         = ( argc > ++argi ) ? atof(argv[argi]) : 0;
  int num_test  = ( argc > ++argi ) ? atof(argv[argi]) : 10;
  int skip_test = ( argc > ++argi ) ? atof(argv[argi]) : 5;

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

  if ( mpi_rank == 0 ) {
    cout << "m = " << m
         << ", n = " << n
         << ", k = " << k
         << ", p = " << 0
         << ", q = " << q
         << ", N = " << Nj*mpi_size
         << ", tol = " << tol
         << ", maxiter = " << maxiter << endl;
    cout << mpi_size << " nodes / "
         << omp_get_max_threads() << " threads per node" << endl << endl;
  }

  // ====================================================================================================================== //
  // Allocate memory
  auto matrix_a      = static_cast<double*>(malloc(m0 * n      * sizeof(double)));
  auto matrix_u_true = static_cast<double*>(malloc(m0 * k      * sizeof(double)));
  auto matrix_qt     = static_cast<double*>(malloc(k  * m      * sizeof(double)));
  auto matrix_u      = static_cast<double*>(malloc(m0 * k      * sizeof(double)));
  auto matrix_vt     = static_cast<double*>(malloc(k  * n      * sizeof(double)));
  auto vector_s      = static_cast<double*>(malloc(k           * sizeof(double)));
  auto matrix_qjt    = static_cast<double*>(malloc(k  * mj     * sizeof(double)));
  auto matrices_qjt  = static_cast<double*>(malloc(k  * mj * N * sizeof(double)));

  // ====================================================================================================================== //
  // Create statistics collector
  StatisticsSet set_smax(num_test), set_smean(num_test),  set_smin(num_test),   set_frerr(num_test),
                set_time(num_test), set_time_s(num_test), set_time_i(num_test), set_time_f(num_test), set_iter(num_test);

  // ====================================================================================================================== //
  // Generate matrix
  if ( verbose && mpi_rank == 0 )  {cout << "Generating matrix .............. " << flush; }
  if ( mpi_rank == 0 ) {
    createA(m0, n, k, matrix_a, matrix_u_true, seed);
  }
  MPI_Bcast(matrix_a, m0*n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  if ( verbose && mpi_rank == 0 ) { cout << "done" << endl << endl; }

  // ====================================================================================================================== //
  // Run MCNLA
  if ( mpi_rank == 0 ) {
    cout << "Start iSVD." << endl;
    cout << fixed << setprecision(6);
  }

  for ( auto t = -skip_test; t < num_test; ++t ) {
    double smax, smin, smean, frerr, time, time_s = 0.0, time_i = 0.0, time_f = 0.0; int iter;

    MPI_Barrier(MPI_COMM_WORLD);

    // ================================================================================================================== //
    // Random sketch
    if ( verbose && mpi_rank == 0 ) { cout << "Sketching ...................... " << flush; }
    if ( mpi_rank == 0 ) { time_s = MPI_Wtime(); }
    fill(matrices_qjt, matrices_qjt+k*mj*N, 0.0);
    sketch(Nj, m, m0, n, k, q, matrix_a, matrices_qjt, seed);
    for ( auto i = 0; i < Nj; ++i ) {
      MPI_Alltoall(MPI_IN_PLACE, k*mj, MPI_DOUBLE, matrices_qjt+i*k*m, k*mj, MPI_DOUBLE, MPI_COMM_WORLD);
    }
    if ( mpi_rank == 0 ) { time_s = MPI_Wtime() - time_s; }
    if ( verbose && mpi_rank == 0 ) { cout << "done" << endl; }

    // ================================================================================================================== //
    // Integrate
    if ( verbose && mpi_rank == 0 ) { cout << "Integrating .................... " << flush; }
    if ( mpi_rank == 0 ) { time_i = MPI_Wtime(); }
    integrate(N, mj, k, matrices_qjt, matrix_qjt, iter);
    MPI_Gather(matrix_qjt, k*mj, MPI_DOUBLE, matrix_qt, k*mj, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    if ( mpi_rank == 0 ) { time_i = MPI_Wtime() - time_i; }
    if ( verbose && mpi_rank == 0 ) { cout << "done" << endl; }

    // ================================================================================================================== //
    // Reconstruct SVD
    if ( verbose && mpi_rank == 0 ) { cout << "Forming ................. " << flush; }
    if ( mpi_rank == 0 ) {
      time_f = MPI_Wtime();
      form(m0, n, k, matrix_a, matrix_qt, matrix_u, matrix_vt, vector_s);
      time_f = MPI_Wtime() - time_f;
    }
    if ( verbose && mpi_rank == 0 ) { cout << "done" << endl; }

    MPI_Barrier(MPI_COMM_WORLD);

    // ================================================================================================================== //
    // Check result
    if ( mpi_rank == 0  ) {
      check_u(m0, k, matrix_u_true, matrix_u, smax, smin, smean);
      check(m0, n, k, matrix_a, matrix_u, matrix_vt, vector_s, frerr);

      time = time_s + time_i + time_f;
      cout << setw(log10(num_test)+1) << t
                << " | validity: " << smax << " / " << smean << " / " << smin
                << " | error: " << frerr
                << " | time: " << time << " (" << time_s << " / " << time_i << " / " << time_f << ")"
                << " | iter: " << setw(log10(maxiter)+1) << iter << endl;
      if ( t >= 0 ) {
        set_smax(smax); set_smean(smean);   set_smin(smin);     set_frerr(frerr);
        set_time(time); set_time_s(time_s); set_time_f(time_f); set_time_i(time_i); set_iter(iter);
      }
    }
  }

  // Display statistics results
  if ( mpi_rank == 0 ) {
    cout << endl;
    cout << "Average total computing time: " << set_time.mean()   << " seconds." << endl;
    cout << "Average sketching time:       " << set_time_s.mean() << " seconds." << endl;
    cout << "Average integrating time:     " << set_time_i.mean() << " seconds." << endl;
    cout << "Average forming time:         " << set_time_f.mean() << " seconds." << endl;
    cout << "mean(validity): max = " << set_smax.mean()
                      << ", mean = " << set_smean.mean()
                       << ", min = " << set_smin.mean() << endl;
    cout << "sd(validity):   max = " << set_smax.sd()
                      << ", mean = " << set_smean.sd()
                       << ", min = " << set_smin.sd() << endl;
    cout << "mean(error) = " << set_frerr.mean() << endl;
    cout << "sd(error)   = " << set_frerr.sd() << endl;
    cout << "mean(iter) = " << set_iter.mean() << endl;
    cout << "sd(iter)   = " << set_iter.sd() << endl;
    cout << endl;
    cout << "validity = svd(U_true' U)_2" << endl;
    cout << "error    = norm(A-USV')_F/norm(A)_F" << endl;
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
  auto matrix_u     = static_cast<double*>(malloc(m0 * m0 * sizeof(double)));
  auto matrix_v     = static_cast<double*>(malloc(n  * m0 * sizeof(double)));
  auto vector_tmp_s = static_cast<double*>(malloc(m0      * sizeof(double)));
  auto vector_tmp_b = static_cast<double*>(malloc(m0      * sizeof(double)));

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
    cblas_dscal(m0, 1e-2 / (i+1), matrix_u+i*m0, 1);
  }
  cblas_dgemm(CblasColMajor, CblasNoTrans, CblasTrans, m0, n, m0, 1.0, matrix_u, m0, matrix_v, n, 0.0, matrix_a, m0);

  // Free memory
  free(matrix_u);
  free(matrix_v);
  free(vector_tmp_s);
  free(vector_tmp_b);
}

void sketch( const int Nj, const int m, const int m0, const int n, const int k, const int q,
             const double *matrix_a, double *matrices_qjt, int seed[4] ) {
  auto matrix_oit   = static_cast<double*>(malloc(k * n * sizeof(double)));
  auto vector_tmp_s = static_cast<double*>(malloc(k     * sizeof(double)));
  auto vector_tmp_b = static_cast<double*>(malloc(k     * sizeof(double)));

  for ( auto i = 0; i < Nj; ++i ) {
    LAPACKE_dlarnv(3, seed, k*n, matrix_oit);
    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasTrans,
                k, m0, n, 1.0, matrix_oit, k, matrix_a, m0, 0.0, matrices_qjt+i*k*m, k);
    for ( auto j = 0; j < q; ++j ) {
      cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans,
                  k, n, m0, 1.0, matrices_qjt+i*k*m, k, matrix_a, m0, 0.0, matrix_oit, k);
      cblas_dgemm(CblasColMajor, CblasNoTrans, CblasTrans,
                  k, m0, n, 1.0, matrix_oit, k, matrix_a, m0, 0.0, matrices_qjt+i*k*m, k);
    }

    LAPACKE_dgesvd(LAPACK_COL_MAJOR, 'N', 'O', k, m0, matrices_qjt+i*k*m, k,
                   vector_tmp_s, nullptr, 1, nullptr, 1, vector_tmp_b);
  }

  // Free memory
  free(matrix_oit);
  free(vector_tmp_s);
  free(vector_tmp_b);
}

void integrate( const int N, const int mj, const int k, const double *matrices_qjt, double *matrix_qjt, int &iter ) {
  auto matrix_b   = static_cast<double*>(malloc(k * k * N * sizeof(double)));
  auto matrix_d   = static_cast<double*>(malloc(k * k     * sizeof(double)));
  auto matrix_c   = static_cast<double*>(malloc(k * k     * sizeof(double)));
  auto matrix_xjt = static_cast<double*>(malloc(k * mj    * sizeof(double)));
  auto matrix_tmp = static_cast<double*>(malloc(mj * k    * sizeof(double)));
  auto vector_e   = static_cast<double*>(malloc(k         * sizeof(double)));

  bool is_converged = false;

  // Qj' := Q0'
  cblas_dcopy(k*mj, matrices_qjt, 1, matrix_qjt, 1);

  for ( iter = 0; iter < maxiter && !is_converged; ++iter ) {

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

    // D := sum( Xj'*Xj )
    cblas_dsyrk(CblasColMajor, CblasLower, CblasNoTrans, k, mj, 1.0, matrix_xjt, k, 0.0, matrix_d, k);
    MPI_Allreduce(MPI_IN_PLACE, matrix_d, k*k, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    // Compute the eigen-decomposition of D (E := eigenvalues, D := eigenvectors)
    LAPACKE_dsyev(LAPACK_COL_MAJOR, 'V', 'L', k, matrix_d, k, vector_e);

    // E := sqrt( I/2 - sqrt( I/4 - E ) )
    for ( auto i = 0; i < k; ++i ) {
      vector_e[i] = sqrt(0.5 + sqrt(0.25 - vector_e[i]));
    }

    // ================================================================================================================== //
    // Q := Q * C + X * inv(C)
    // C      = D * diag(E)      * D'
    // inv(C) = D * inv(diag(E)) * D'

    // Tmp := Qj * D
    cblas_dgemm(CblasColMajor, CblasTrans, CblasNoTrans, mj, k, k, 1.0, matrix_qjt, k, matrix_d, k, 0.0, matrix_tmp, mj);

    // Tmp *= E
    for ( auto i = 0; i < k; ++i ) {
      cblas_dscal(mj, vector_e[i], matrix_tmp+i*mj, 1);
    }

    // Qj' := D * Tmp'
    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasTrans, k, mj, k, 1.0, matrix_d, k, matrix_tmp, mj, 0.0, matrix_qjt, k);

    // Tmp := Xj * D
    cblas_dgemm(CblasColMajor, CblasTrans, CblasNoTrans, mj, k, k, 1.0, matrix_xjt, k, matrix_d, k, 0.0, matrix_tmp, mj);

    // Tmp /= E
    for ( auto i = 0; i < k; ++i ) {
      cblas_dscal(mj, 1/vector_e[i], matrix_tmp+i*mj, 1);
    }

    // Qj' += D * Tmp'
    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasTrans, k, mj, k, 1.0, matrix_d, k, matrix_tmp, mj, 1.0, matrix_qjt, k);

    // ================================================================================================================== //
    // Check convergence
    for ( auto i = 0; i < k; ++i ) {
      vector_e[i] = vector_e[i] - 1.0;
    }
    is_converged = !(cblas_dnrm2(k, vector_e, 1) / sqrt(k) > tol);
  }

  // Free memory
  free(matrix_b);
  free(matrix_d);
  free(matrix_c);
  free(matrix_xjt);
  free(matrix_tmp);
  free(vector_e);
}

void form( const int m0, const int n, const int k,
           const double *matrix_a, const double *matrix_qt, double *matrix_u, double *matrix_vt, double *vector_s ) {
  auto matrix_w   = static_cast<double*>(malloc(k * k * sizeof(double)));
  auto vector_tmp = static_cast<double*>(malloc(k     * sizeof(double)));

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

void check_u( const int m0, const int k, const double *matrix_u_true, const double *matrix_u,
              double &smax, double &smin, double &smean ) {
  auto matrix_tmp  = static_cast<double*>(malloc(k * k * sizeof(double)));
  auto vector_tmp1 = static_cast<double*>(malloc(k     * sizeof(double)));
  auto vector_tmp2 = static_cast<double*>(malloc(k     * sizeof(double)));

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

void check( const int m0, const int n, const int k, const double *matrix_a,
            const double *matrix_u, const double *matrix_vt, const double *vector_s, double &frerr ) {
  auto matrix_a_tmp = static_cast<double*>(malloc(m0 * n * sizeof(double)));
  auto matrix_u_tmp = static_cast<double*>(malloc(m0 * k * sizeof(double)));

  // A_tmp := A, U_tmp := U
  cblas_dcopy(m0*n, matrix_a, 1, matrix_a_tmp, 1);
  cblas_dcopy(m0*k, matrix_u, 1, matrix_u_tmp, 1);

  // A_tmp -= U * S * V'
  for ( auto i = 0; i < k; ++i ) {
    cblas_dscal(m0, vector_s[i], matrix_u_tmp+i*m0, 1);
  }
  cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, m0, n, k,
              -1.0, matrix_u_tmp, m0, matrix_vt, k, 1.0, matrix_a_tmp, m0);

  // frerr := norm(A_tmp)_F / norm(A)_F
  frerr = cblas_dnrm2(m0*n, matrix_a_tmp, 1) / cblas_dnrm2(m0*n, matrix_a, 1);

  // Free memory
  free(matrix_a_tmp);
  free(matrix_u_tmp);
}
