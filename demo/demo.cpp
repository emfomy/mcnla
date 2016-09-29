////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/demo.cpp
/// @brief   The demo code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <iomanip>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <mcnla.hpp>

using ScalarType = double;

void create( mcnla::DenseMatrix<ScalarType> &matrix_a, mcnla::DenseMatrix<ScalarType> &matrix_u_true,
             const mcnla::index_t rank, mcnla::index_t seed[4] ) noexcept;
template <mcnla::Layout _layout>
void check( const mcnla::DenseMatrix<ScalarType, _layout> &matrix_u, const mcnla::DenseMatrix<ScalarType> &matrix_u_true,
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
  // Initialize solver
  mcnla::DenseMatrix<ScalarType> matrix_a(m, n), matrix_u_true;
  mcnla::Solver<mcnla::DenseMatrix<ScalarType>,
               mcnla::GaussianProjectionSketcher<mcnla::DenseMatrix<ScalarType>>,
               mcnla::KolmogorovNagumoTypeIntegrator<mcnla::DenseMatrix<ScalarType>>,
               mcnla::StandardReconstructor<mcnla::DenseMatrix<ScalarType>>> solver(MPI_COMM_WORLD);
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
  mcnla::mpi::bcast(matrix_a, mpi_root, MPI_COMM_WORLD);

  // ====================================================================================================================== //
  // Create statistics collector
  boost::accumulators::accumulator_set<double, boost::accumulators::stats<boost::accumulators::tag::variance>> acc_max;
  boost::accumulators::accumulator_set<double, boost::accumulators::stats<boost::accumulators::tag::variance>> acc_min;
  boost::accumulators::accumulator_set<double, boost::accumulators::stats<boost::accumulators::tag::variance>> acc_mean;

  // ====================================================================================================================== //
  // Run MCNLA
  if ( mpi_rank == mpi_root ) {
    std::cout << "Start MCNLA." << std::endl;
    std::cout << std::fixed << std::setprecision(6);
  }

  for ( mcnla::index_t t = 0; t < num_test; ++t ) {
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
      std::cout << std::setw(log10(num_test)+1) << t
                << ": max = " << smax << ", min = " << smin << ", mean = " << smean << std::endl;
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
          mcnla::DenseMatrix<ScalarType> &matrix_a,
          mcnla::DenseMatrix<ScalarType> &matrix_u_true,
    const mcnla::index_t rank,
          mcnla::index_t seed[4]
) noexcept {
  matrix_u_true = mcnla::DenseMatrix<ScalarType>(matrix_a.getNrow(), rank);

  mcnla::DenseMatrix<ScalarType> matrix_u(matrix_a.getNrow(), matrix_a.getNrow());
  mcnla::DenseMatrix<ScalarType> matrix_v(matrix_a.getNcol(), matrix_a.getNrow());
  mcnla::DenseMatrix<ScalarType> matrix_empty;
  mcnla::DenseVector<ScalarType> vector_s(matrix_a.getNrow());

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
    const mcnla::DenseMatrix<ScalarType, _layout> &matrix_u,
    const mcnla::DenseMatrix<ScalarType> &matrix_u_true,
          ScalarType &smax,
          ScalarType &smin,
          ScalarType &smean
) noexcept {
  mcnla::DenseMatrix<ScalarType> matrix_u2(matrix_u.getNcol(), matrix_u.getNcol());
  mcnla::DenseVector<ScalarType> vector_s(matrix_u.getNcol());
  mcnla::DenseMatrix<ScalarType> matrix_empty;

  // U2 := Utrue' * U
  mcnla::blas::gemm<mcnla::TransOption::TRANS, mcnla::TransOption::NORMAL>(1.0, matrix_u_true, matrix_u, 0.0, matrix_u2);

  // Compute the SVD of U2
  mcnla::lapack::gesvd<'N', 'N'>(matrix_u2, vector_s, matrix_empty, matrix_empty);
  smax  = mcnla::blas::amax(vector_s);
  smin  = mcnla::blas::amin(vector_s);
  smean = mcnla::blas::asum(vector_s) / vector_s.getLength();
}
