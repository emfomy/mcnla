////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/demo.cpp
/// @brief   The demo code
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#include <iostream>
#include <iomanip>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <isvd.hpp>

using ScalarType = double;

void create( isvd::DenseMatrix<ScalarType> &matrix_a, isvd::DenseMatrix<ScalarType> &matrix_u_true,
             const isvd::index_t rank, isvd::index_t seed[4] ) noexcept;
template <isvd::Layout _layout>
void check( const isvd::DenseMatrix<ScalarType, _layout> &matrix_u, const isvd::DenseMatrix<ScalarType> &matrix_u_true,
            ScalarType &smax, ScalarType &smin, ScalarType &smean ) noexcept;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {
  double start_time = 0.0, total_time = 0.0;
  ScalarType smax, smin, smean;

  // ====================================================================================================================== //
  // Initialize MPI
  MPI_Init(&argc, &argv);
  isvd::mpi_int_t mpi_root = 0;
  isvd::mpi_int_t mpi_size = isvd::mpi::getCommSize(MPI_COMM_WORLD);
  isvd::mpi_int_t mpi_rank = isvd::mpi::getCommRank(MPI_COMM_WORLD);

  // ====================================================================================================================== //
  // Display program information
  if ( mpi_rank == mpi_root ) {
    std::cout << "iSVD "
              << ISVD_VERSION_MAJOR << "."
              << ISVD_VERSION_MINOR << "."
              << ISVD_VERSION_PATCH << " demo" << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Initialize random seed
  srand(time(NULL) ^ mpi_rank);
  srand(rand());
  isvd::index_t seed[4] = {rand()%4096, rand()%4096, rand()%4096, (rand()%2048)*2+1};

  // ====================================================================================================================== //
  // Set parameters
  int argi = 0;
  isvd::index_t Nj       = ( argc > ++argi ) ? atoi(argv[argi]) : 4;
  isvd::index_t m        = ( argc > ++argi ) ? atoi(argv[argi]) : 1000;
  isvd::index_t n        = ( argc > ++argi ) ? atoi(argv[argi]) : 10000;
  isvd::index_t k        = ( argc > ++argi ) ? atoi(argv[argi]) : 10;
  isvd::index_t p        = ( argc > ++argi ) ? atoi(argv[argi]) : 0;
  isvd::index_t num_test = ( argc > ++argi ) ? atoi(argv[argi]) : 100;
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
  // Initialize solver
  isvd::DenseMatrix<ScalarType> matrix_a(m, n), matrix_u_true;
  isvd::Solver<isvd::DenseMatrix<ScalarType>,
               isvd::GaussianProjectionSketcher<isvd::DenseMatrix<ScalarType>>,
               isvd::KolmogorovNagumoTypeIntegrator<isvd::DenseMatrix<ScalarType>>,
               isvd::StandardReconstructor<isvd::DenseMatrix<ScalarType>>> solver(MPI_COMM_WORLD);
  solver.setSize(matrix_a).setRank(k).setOverRank(p).setNumSketch(Nj).setSeed(seed);
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
  isvd::mpi::bcast(matrix_a, mpi_root, MPI_COMM_WORLD);

  // ====================================================================================================================== //
  // Create statistics collector
  boost::accumulators::accumulator_set<double, boost::accumulators::stats<boost::accumulators::tag::variance>> acc_max;
  boost::accumulators::accumulator_set<double, boost::accumulators::stats<boost::accumulators::tag::variance>> acc_min;
  boost::accumulators::accumulator_set<double, boost::accumulators::stats<boost::accumulators::tag::variance>> acc_mean;

  // ====================================================================================================================== //
  // Run iSVD
  if ( mpi_rank == mpi_root ) {
    std::cout << "Start iSVD." << std::endl;
    std::cout << std::fixed << std::setprecision(4);
  }

  for ( isvd::index_t t = 0; t < num_test; ++t ) {
    MPI_Barrier(MPI_COMM_WORLD);
    if ( mpi_rank == mpi_root ) {
      start_time = MPI_Wtime();
    }

    // Run solver
    solver.compute(matrix_a);

    // Check time
    MPI_Barrier(MPI_COMM_WORLD);
    if ( mpi_rank == mpi_root ) {
      total_time += MPI_Wtime() - start_time;
    }

    // Check result
    if ( mpi_rank == mpi_root ) {
      check(solver.getLeftSingularVectors(), matrix_u_true, smax, smin, smean);
      std::cout << std::setw(4) << t << ": max = " << smax << ", min = " << smin << ", mean = " << smean << std::endl;
      acc_min(smin); acc_max(smax); acc_mean(smean);
    }
  }

  // Display statistics results
  if ( mpi_rank == mpi_root ) {
    std::cout << "Used " << total_time / num_test << " seconds averagely." << std::endl;
    std::cout << "mean(op(svd(U_true' * U))): max = " << boost::accumulators::mean(acc_max)
                                        << ", min = " << boost::accumulators::mean(acc_min)
                                       << ", mean = " << boost::accumulators::mean(acc_mean) << std::endl;
    std::cout << "sd(op(svd(U_true' * U))):   max = " << std::sqrt(boost::accumulators::variance(acc_max))
                                        << ", min = " << std::sqrt(boost::accumulators::variance(acc_min))
                                       << ", mean = " << std::sqrt(boost::accumulators::variance(acc_mean)) << std::endl;
  }

  MPI_Finalize();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Create matrix A
///
void create(
          isvd::DenseMatrix<ScalarType> &matrix_a,
          isvd::DenseMatrix<ScalarType> &matrix_u_true,
    const isvd::index_t rank,
          isvd::index_t seed[4]
) noexcept {
  matrix_u_true = isvd::DenseMatrix<ScalarType>(matrix_a.getNrow(), rank);

  isvd::DenseMatrix<ScalarType> matrix_u(matrix_a.getNrow(), matrix_a.getNrow());
  isvd::DenseMatrix<ScalarType> matrix_v(matrix_a.getNcol(), matrix_a.getNrow());
  isvd::DenseMatrix<ScalarType> matrix_empty;
  isvd::DenseVector<ScalarType> vector_s(matrix_a.getNrow());

  // Generate U & V using normal random
  isvd::lapack::larnv<3>(matrix_u.vectorize(), seed);
  isvd::lapack::larnv<3>(matrix_v.vectorize(), seed);

  // Orthogonalize U & V
  isvd::lapack::gesvd<'O', 'N'>(matrix_u, vector_s, matrix_empty, matrix_empty);
  isvd::lapack::gesvd<'O', 'N'>(matrix_v, vector_s, matrix_empty, matrix_empty);

  // Copy U
  isvd::blas::copy(matrix_u.getCols({0, rank}), matrix_u_true);

  // A := U * S * V'
  for ( isvd::index_t i = 0; i < rank; ++i ) {
    isvd::blas::scal(1.0/(i+1), matrix_u.getCol(i));
  }
  for ( isvd::index_t i = rank; i < matrix_a.getNrow(); ++i ) {
    isvd::blas::scal(1e-2/(i-rank+1), matrix_u.getCol(i));
  }
  isvd::blas::gemm<isvd::TransOption::NORMAL, isvd::TransOption::TRANS>(1.0, matrix_u, matrix_v, 0.0, matrix_a);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Check the result
///
template <isvd::Layout _layout>
void check(
    const isvd::DenseMatrix<ScalarType, _layout> &matrix_u,
    const isvd::DenseMatrix<ScalarType> &matrix_u_true,
          ScalarType &smax,
          ScalarType &smin,
          ScalarType &smean
) noexcept {
  isvd::DenseMatrix<ScalarType> matrix_u2(matrix_u.getNcol(), matrix_u.getNcol());
  isvd::DenseVector<ScalarType> vector_s(matrix_u.getNcol());
  isvd::DenseMatrix<ScalarType> matrix_empty;

  // U2 := Utrue' * U
  isvd::blas::gemm<isvd::TransOption::TRANS, isvd::TransOption::NORMAL>(1.0, matrix_u_true, matrix_u, 0.0, matrix_u2);

  // Compute the SVD of U2
  isvd::lapack::gesvd<'N', 'N'>(matrix_u2, vector_s, matrix_empty, matrix_empty);
  smax  = isvd::blas::amax(vector_s);
  smin  = isvd::blas::amin(vector_s);
  smean = isvd::blas::asum(vector_s) / vector_s.getLength();
}
