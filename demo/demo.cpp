////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/demo.cpp
/// @brief   The demo code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <iomanip>
#include <valarray>
#include <mcnla.hpp>

using ScalarType = double;

ScalarType tolerance = 1e-4;
mcnla::index_t maxiter = 256;

void create( mcnla::matrix::DenseMatrix<ScalarType> &matrix_a,
             mcnla::matrix::DenseMatrix<ScalarType> &matrix_u_true,
             const mcnla::index_t rank, mcnla::index_t seed[4] ) noexcept;
template <mcnla::Layout _layout>
void check( const mcnla::matrix::DenseMatrix<ScalarType, _layout> &matrix_u,
            const mcnla::matrix::DenseMatrix<ScalarType> &matrix_u_true,
            ScalarType &smax, ScalarType &smin, ScalarType &smean ) noexcept;

class StatisticsSet {
 private:
  std::valarray<double> set_;
  std::valarray<double> diff_;
  size_t size_;

 public:
  StatisticsSet( const int capacity ) : set_(capacity), diff_(capacity), size_(0) {};
  void operator()( const double value ) { assert(size_ < set_.size()); set_[size_++] = value; }
  double mean() { return set_.sum() / set_.size(); }
  double var() { diff_ = set_ - mean(); diff_ *= diff_; return diff_.sum() / diff_.size(); };
  double sd() { return std::sqrt(var()); };
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {

  // ====================================================================================================================== //
  // Initialize MPI
  MPI_Init(&argc, &argv);
  mcnla::mpi_int_t mpi_root = 0;
  mcnla::mpi_int_t mpi_size = mcnla::mpi::getCommSize(MPI_COMM_WORLD);
  mcnla::mpi_int_t mpi_rank = mcnla::mpi::getCommRank(MPI_COMM_WORLD);

  // ====================================================================================================================== //
  // Display program information
  if ( mpi_rank == mpi_root ) {
    std::cout << "MCNLA "
              << MCNLA_VERSION_MAJOR << "."
              << MCNLA_VERSION_MINOR << "."
              << MCNLA_VERSION_PATCH << " demo" << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Initialize random seed
  srand(time(NULL) ^ mpi_rank);
  srand(rand());
  mcnla::index_t seed[4] = {rand()%4096, rand()%4096, rand()%4096, (rand()%2048)*2+1};

  // ====================================================================================================================== //
  // Set parameters
  int argi = 0;
  mcnla::index_t Nj       = ( argc > ++argi ) ? atoi(argv[argi]) : 4;
  mcnla::index_t m        = ( argc > ++argi ) ? atoi(argv[argi]) : 1000;
  mcnla::index_t n        = ( argc > ++argi ) ? atoi(argv[argi]) : 10000;
  mcnla::index_t k        = ( argc > ++argi ) ? atoi(argv[argi]) : 10;
  mcnla::index_t p        = ( argc > ++argi ) ? atoi(argv[argi]) : 0;
  mcnla::index_t num_test = ( argc > ++argi ) ? atoi(argv[argi]) : 100;
  assert(k <= m && m <= n);
  if ( mpi_rank == mpi_root ) {
    std::cout << "m = " << m
            << ", n = " << n
            << ", k = " << k
            << ", p = " << p
            << ", N = " << Nj*mpi_size
            << ", K = " << mpi_size << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Create statistics collector
  StatisticsSet set_max(num_test),  set_mean(num_test),   set_min(num_test),
                set_time(num_test), set_time_s(num_test), set_time_i(num_test), set_time_r(num_test), set_iter(num_test);

  // ====================================================================================================================== //
  // Initialize solver
  mcnla::matrix::DenseMatrix<ScalarType> matrix_a(m, n), matrix_u_true;
  mcnla::isvd::Solver<mcnla::matrix::DenseMatrix<ScalarType>,
                      mcnla::isvd::GaussianProjectionSketcher<mcnla::matrix::DenseMatrix<ScalarType>>,
                      mcnla::isvd::KolmogorovNagumoTypeIntegrator<mcnla::matrix::DenseMatrix<ScalarType>>,
                      mcnla::isvd::StandardReconstructor<mcnla::matrix::DenseMatrix<ScalarType>>> solver(MPI_COMM_WORLD);
  solver.setSize(matrix_a).setRank(k).setOverRank(p).setNumSketchEach(Nj).setSeed(seed);
  solver.setTolerance(tolerance).setMaxIteration(maxiter);
  solver.initialize();
  if ( mpi_rank == mpi_root ) {
    std::cout << "Uses " << solver.getSketcherName() << "." << std::endl;
    std::cout << "Uses " << solver.getIntegratorName() << "." << std::endl;
    std::cout << "Uses " << solver.getReconstructorName() << "." << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Generate matrix
  if ( mpi_rank == mpi_root ) {
    create(matrix_a, matrix_u_true, k, seed);
  }
  mcnla::mpi::bcast(matrix_a, mpi_root, MPI_COMM_WORLD);

  // ====================================================================================================================== //
  // Run MCNLA
  if ( mpi_rank == mpi_root ) {
    std::cout << "Start MCNLA." << std::endl;
    std::cout << std::fixed << std::setprecision(6);
  }

  for ( mcnla::index_t t = 0; t < num_test; ++t ) {

    // Run solver
    MPI_Barrier(MPI_COMM_WORLD);
    solver.compute(matrix_a);
    MPI_Barrier(MPI_COMM_WORLD);

    // Check result
    if ( mpi_rank == mpi_root ) {
      ScalarType smax, smin, smean;
      check(solver.getLeftSingularVectors(), matrix_u_true, smax, smin, smean);
      auto iter    = solver.getIntegratorIter();
      auto maxiter = solver.getParameters().getMaxIteration();
      auto time_s = solver.getSketcherTime();
      auto time_i = solver.getIntegratorTime();
      auto time_r = solver.getReconstructorTime();
      auto time = time_s + time_i + time_r;
      std::cout << std::setw(log10(num_test)+1) << t
                << " | svd(U_true' * U): " << smax << " / " << smean << " / " << smin
                << " | time: " << time << " (" << time_s << " / " << time_i << " / " << time_r << ")"
                << " | iter: " << std::setw(log10(maxiter)+1) << iter << std::endl;
      set_min(smin); set_max(smax); set_mean(smean);
      set_time(time); set_time_s(time_s); set_time_r(time_r); set_time_i(time_i); set_iter(iter);
    }
  }

  // Display statistics results
  if ( mpi_rank == mpi_root ) {
    std::cout << std::endl;
    std::cout << "Average total computing time: " << set_time.mean() << " seconds." << std::endl;
    std::cout << "Average sketching time:       " << set_time_s.mean() << " seconds." << std::endl;
    std::cout << "Average integrating time:     " << set_time_i.mean() << " seconds." << std::endl;
    std::cout << "Average reconstructing time:  " << set_time_r.mean() << " seconds." << std::endl;
    std::cout << "mean(svd(U_true' * U)): max = " << set_max.mean()
                                   << ", mean = " << set_mean.mean()
                                    << ", min = " << set_min.mean() << std::endl;
    std::cout << "sd(svd(U_true' * U)):   max = " << set_max.sd()
                                   << ", mean = " << set_mean.sd()
                                    << ", min = " << set_min.sd() << std::endl;
    std::cout << "mean(iter) = " << set_iter.mean() << std::endl;
    std::cout << "sd(iter)   = " << set_iter.sd() << std::endl;
  }

  MPI_Finalize();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Create matrix A
///
void create(
          mcnla::matrix::DenseMatrix<ScalarType> &matrix_a,
          mcnla::matrix::DenseMatrix<ScalarType> &matrix_u_true,
    const mcnla::index_t rank,
          mcnla::index_t seed[4]
) noexcept {
  matrix_u_true = mcnla::matrix::DenseMatrix<ScalarType>(matrix_a.getNrow(), rank);

  mcnla::matrix::DenseMatrix<ScalarType> matrix_u(matrix_a.getNrow(), matrix_a.getNrow());
  mcnla::matrix::DenseMatrix<ScalarType> matrix_v(matrix_a.getNcol(), matrix_a.getNrow());
  mcnla::matrix::DenseMatrix<ScalarType> matrix_empty;
  mcnla::matrix::DenseVector<ScalarType> vector_s(matrix_a.getNrow());

  // Generate U & V using normal random
  mcnla::lapack::larnv<3>(matrix_u.vectorize(), seed);
  mcnla::lapack::larnv<3>(matrix_v.vectorize(), seed);

  // Orthogonalize U & V
  mcnla::lapack::gesvd<'O', 'N'>(matrix_u, vector_s, matrix_empty, matrix_empty);
  mcnla::lapack::gesvd<'O', 'N'>(matrix_v, vector_s, matrix_empty, matrix_empty);

  // Copy U
  mcnla::blas::copy(matrix_u.getCols({0, rank}), matrix_u_true);

  // A := U * S * V'
  for ( mcnla::index_t i = 0; i < rank; ++i ) {
    mcnla::blas::scal(1.0/(i+1), matrix_u.getCol(i));
  }
  for ( mcnla::index_t i = rank; i < matrix_a.getNrow(); ++i ) {
    mcnla::blas::scal(1e-2/(i-rank+1), matrix_u.getCol(i));
  }
  mcnla::blas::gemm<mcnla::TransOption::NORMAL, mcnla::TransOption::TRANS>(1.0, matrix_u, matrix_v, 0.0, matrix_a);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Check the result
///
template <mcnla::Layout _layout>
void check(
    const mcnla::matrix::DenseMatrix<ScalarType, _layout> &matrix_u,
    const mcnla::matrix::DenseMatrix<ScalarType> &matrix_u_true,
          ScalarType &smax,
          ScalarType &smin,
          ScalarType &smean
) noexcept {
  mcnla::matrix::DenseMatrix<ScalarType> matrix_u2(matrix_u.getNcol(), matrix_u.getNcol());
  mcnla::matrix::DenseVector<ScalarType> vector_s(matrix_u.getNcol());
  mcnla::matrix::DenseMatrix<ScalarType> matrix_empty;

  // U2 := Utrue' * U
  mcnla::blas::gemm<mcnla::TransOption::TRANS, mcnla::TransOption::NORMAL>(1.0, matrix_u_true, matrix_u, 0.0, matrix_u2);

  // Compute the SVD of U2
  mcnla::lapack::gesvd<'N', 'N'>(matrix_u2, vector_s, matrix_empty, matrix_empty);
  smax  = mcnla::blas::amax(vector_s);
  smin  = mcnla::blas::amin(vector_s);
  smean = mcnla::blas::asum(vector_s) / vector_s.getLength();
}
