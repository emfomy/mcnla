////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/mcnla.cpp
/// @brief   The iSVD algorithm
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <valarray>
#include <mcnla/config.hpp>
#include <mpi.h>
#include <mkl.h>

using namespace std;

int mpi_size;
int mpi_rank;

double tolerance = 1e-4;
int maxiter = 256;

void createA( const int m0, const int n, const int k, double *matrix_a, double *matrix_u_true, int seed[4] );
void sketch( const int Nj, const int m, const int m0, const int n, const int k,
             const double *matrix_a, double *matrices_qjt, int seed[4] );
void integrate( const int N, const int mj, const int k, const double *matrices_qjt, double *matrix_qjt, int &iter );
void reconstruct( const int m0, const int n, const int k,
                  const double *matrix_a, const double *matrix_qt, double *matrix_u, double *matrix_vt, double *vector_s );
void check( const int m0, const int k, const double *matrix_u_true, const double *matrix_u,
            double &smax, double &smin, double &smean );

class StatisticsSet {
 private:
  valarray<double> set_;
  valarray<double> diff_;
  size_t size_;

 public:
  StatisticsSet( const int capacity ) : set_(capacity), diff_(capacity), size_(0) {};
  void operator()( const double value ) { assert(size_ < set_.size()); set_[size_++] = value; }
  double mean() { return set_.sum() / set_.size(); }
  double var() { diff_ = set_ - mean(); diff_ *= diff_; return diff_.sum() / diff_.size(); };
  double sd() { return sqrt(var()); };
};

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

  if ( mpi_rank == 0 ) {
    cout << "m = " << m
       << ", n = " << n
       << ", k = " << k
       << ", p = " << 0
       << ", N = " << Nj*mpi_size
       << ", K = " << mpi_size << endl << endl;
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
  StatisticsSet set_max(num_test),  set_mean(num_test),   set_min(num_test),
                set_time(num_test), set_time_s(num_test), set_time_i(num_test), set_time_r(num_test), set_iter(num_test);

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
    std::cout << std::fixed << std::setprecision(6);
  }

  for ( auto t = 0; t < num_test; ++t ) {
    double smax, smin, smean, time, time_s = 0.0, time_i = 0.0, time_r = 0.0; int iter;

    MPI_Barrier(MPI_COMM_WORLD);

    // ================================================================================================================== //
    // Random sketch
    if ( verbose && mpi_rank == 0 ) { cout << "Sketching ...................... " << flush; }
    if ( mpi_rank == 0 ) { time_s = MPI_Wtime(); }
    fill(matrices_qjt, matrices_qjt+k*mj*N, 0.0);
    sketch(Nj, m, m0, n, k, matrix_a, matrices_qjt, seed);
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
    if ( verbose && mpi_rank == 0 ) { cout << "Reconstructing ................. " << flush; }
    if ( mpi_rank == 0 ) {
      time_r = MPI_Wtime();
      reconstruct(m0, n, k, matrix_a, matrix_qt, matrix_u, matrix_vt, vector_s);
      time_r = MPI_Wtime() - time_r;
    }
    if ( verbose && mpi_rank == 0 ) { cout << "done" << endl; }

    MPI_Barrier(MPI_COMM_WORLD);

    // ================================================================================================================== //
    // Check result
    if ( mpi_rank == 0 ) {
      check(m0, k, matrix_u_true, matrix_u, smax, smin, smean);
      time = time_s + time_i + time_r;
      cout << setw(log10(num_test)+1) << t
                << " | svd(U_true' * U): " << smax << " / " << smean << " / " << smin
                << " | time: " << time << " (" << time_s << " / " << time_i << " / " << time_r << ")"
                << " | iter: " << setw(log10(maxiter)+1) << iter << endl;
      set_min(smin); set_max(smax); set_mean(smean);
      set_time(time); set_time_s(time_s); set_time_r(time_r); set_time_i(time_i); set_iter(iter);
    }
  }

  // Display statistics results
  if ( mpi_rank == 0 ) {
    cout << endl;
    cout << "Average total computing time: " << set_time.mean() << " seconds." << endl;
    cout << "Average sketching time:       " << set_time_s.mean() << " seconds." << endl;
    cout << "Average integrating time:     " << set_time_i.mean() << " seconds." << endl;
    cout << "Average reconstructing time:  " << set_time_r.mean() << " seconds." << endl;
    cout << "mean(svd(U_true' * U)): max = " << set_max.mean()
                              << ", mean = " << set_mean.mean()
                               << ", min = " << set_min.mean() << endl;
    cout << "sd(svd(U_true' * U)):   max = " << set_max.sd()
                              << ", mean = " << set_mean.sd()
                               << ", min = " << set_min.sd() << endl;
    cout << "mean(iter) = " << set_iter.mean() << endl;
    cout << "sd(iter)   = " << set_iter.sd() << endl;
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
  auto matrix_oit   = static_cast<double*>(malloc(k * n * sizeof(double)));
  auto vector_tmp_s = static_cast<double*>(malloc(k     * sizeof(double)));
  auto vector_tmp_b = static_cast<double*>(malloc(k     * sizeof(double)));

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

void integrate( const int N, const int mj, const int k, const double *matrices_qjt, double *matrix_qjt, int &iter ) {
  auto matrix_b   = static_cast<double*>(malloc(k * k * N * sizeof(double)));
  auto matrix_d   = static_cast<double*>(malloc(k * k     * sizeof(double)));
  auto matrix_c   = static_cast<double*>(malloc(k * k     * sizeof(double)));
  auto matrix_xjt = static_cast<double*>(malloc(k * mj    * sizeof(double)));
  auto matrix_tmp = static_cast<double*>(malloc(k * mj    * sizeof(double)));
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

    // C *= D * D'
    cblas_dsyrk(CblasColMajor, CblasLower, CblasNoTrans, k, k, 1.0, matrix_d, k, 0.0, matrix_c, k);

    // inv(C) := B * B'
    cblas_dsyrk(CblasColMajor, CblasLower, CblasNoTrans, k, k, 1.0, matrix_b, k, 0.0, matrix_d, k);

    // ================================================================================================================== //
    // Q := Q * C + X * inv(C)

    // Qj' := C * Qj'
    cblas_dsymm(CblasColMajor, CblasLeft, CblasLower, k, mj, 1.0, matrix_c, k, matrix_qjt, k, 0.0, matrix_tmp, k);
    cblas_dcopy(k*mj, matrix_tmp, 1, matrix_qjt, 1);

    // Qj' += inv(C) * Xj'
    cblas_dsymm(CblasColMajor, CblasLeft, CblasLower, k, mj, 1.0, matrix_d, k, matrix_xjt, k, 1.0, matrix_qjt, k);

    // ================================================================================================================== //
    // Check convergence
    if ( mpi_rank == 0 ) {
      for ( auto i = 0; i < k; ++i ) {
        vector_e[i] = sqrt(vector_e) - 1.0;
      }
      is_converged = !(cblas_dnrm2(k, vector_e, 1) / sqrt(k) > tolerance);
    }
    MPI_Bcast(&is_converged, 1, MPI_CHAR, 0, MPI_COMM_WORLD);
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

void check( const int m0, const int k, const double *matrix_u_true, const double *matrix_u,
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
