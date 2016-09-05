////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    main/demo.cpp
/// @brief   The demo code
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#include <iostream>
#include <algorithm>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <isvd.hpp>

void create( isvd::DenseMatrix<double> &matrix_a, isvd::DenseMatrix<double> &matrix_u_true,
             const isvd::index_t rank, isvd::index_t seed[4] ) noexcept;
void check( const isvd::DenseMatrix<double> &matrix_u, const isvd::DenseMatrix<double> &matrix_u_true,
            double &smax, double &smin ) noexcept;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {
  double start_time = 0.0, total_time = 0.0, smax, smin;

  // ====================================================================================================================== //
  // Initialize MPI
  MPI_Init(&argc, &argv);
  isvd::index_t mpi_root = 0;
  isvd::index_t mpi_size = isvd::mpi::getCommSize(MPI_COMM_WORLD);
  isvd::index_t mpi_rank = isvd::mpi::getCommRank(MPI_COMM_WORLD);

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
    printf("m = %d, n = %d, k = %d, p = %d, N = %d, K = %d\n\n", m, n, k, p, Nj*mpi_size, mpi_size);
  }

  // ====================================================================================================================== //
  // Initialize solver
  isvd::DenseMatrix<double> matrix_a(m, n), matrix_u_true;
  isvd::Solver<isvd::DenseMatrix<double>,
               isvd::GaussianProjectionSketcher<isvd::DenseMatrix<double>>,
               isvd::KolmogorovNagumoTypeIntegrator<isvd::DenseMatrix<double>>,
               isvd::StandardReconstructor<isvd::DenseMatrix<double>>> solver(MPI_COMM_WORLD);
  solver.setSize(matrix_a).setRank(k).setOverRank(p).setNumSketch(Nj).setSeed(seed);
  solver.initialize();

  // ====================================================================================================================== //
  // Generate matrix
  if ( mpi_rank == mpi_root ) {
    create(matrix_a, matrix_u_true, k, seed);
  }
  isvd::mpi::bcast(matrix_a, mpi_root, MPI_COMM_WORLD);

  // ====================================================================================================================== //
  // Create statistics collector
  boost::accumulators::accumulator_set<double, boost::accumulators::stats<boost::accumulators::tag::variance>> acc;

  // ====================================================================================================================== //
  // Run iSVD
  if ( mpi_rank == mpi_root ) {
    std::cout << "Start iSVD." << std::endl;
  }

  for ( isvd::index_t t = 0; t < num_test; ++t ) {
    MPI_Barrier(MPI_COMM_WORLD);
    if ( mpi_rank == mpi_root ) {
      start_time = isvd::lapack::secnd();
    }

    // Run solver
    solver.compute(matrix_a);

    // Check time
    MPI_Barrier(MPI_COMM_WORLD);
    if ( mpi_rank == mpi_root ) {
      total_time += isvd::lapack::secnd() - start_time;
    }

    // Check result
    if ( mpi_rank == mpi_root ) {
      check(solver.getLeftSingularVectors(), matrix_u_true, smax, smin);
      printf("%4d: %.4f\n", t, smin);
      acc(smin);
    }
  }

  // Display statistics results
  if ( mpi_rank == mpi_root ) {
    std::cout << "Using " << total_time / num_test << " seconds averagely." << std::endl;
    std::cout << "mean(min(svd(U_true' * U))) = " << boost::accumulators::mean(acc) << std::endl;
    std::cout << "sd(min(svd(U_true' * U)))   = " << std::sqrt(boost::accumulators::variance(acc)) << std::endl;
  }

  MPI_Finalize();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Create matrix A
///
void create(
          isvd::DenseMatrix<double> &matrix_a,
          isvd::DenseMatrix<double> &matrix_u_true,
    const isvd::index_t rank,
          isvd::index_t seed[4]
) noexcept {
  matrix_u_true = isvd::DenseMatrix<double>(matrix_a.getNrow(), rank);

  isvd::DenseMatrix<double> matrix_u(matrix_a.getNrow(), matrix_a.getNrow());
  isvd::DenseMatrix<double> matrix_v(matrix_a.getNcol(), matrix_a.getNrow());
  isvd::DenseMatrix<double> matrix_empty;
  isvd::DenseVector<double> vector_s(matrix_a.getNrow());

  isvd::lapack::GesvdDriver<isvd::DenseMatrix<double>, 'O', 'N'> driver_u(matrix_u);
  isvd::lapack::GesvdDriver<isvd::DenseMatrix<double>, 'O', 'N'> driver_v(matrix_v);

  // Generate U & V using normal random
  isvd::lapack::larnv<3>(matrix_u.vectorize(), seed);
  isvd::lapack::larnv<3>(matrix_v.vectorize(), seed);

  // Orthogonalize U & V
  driver_u(matrix_u, vector_s, matrix_empty, matrix_empty);
  driver_v(matrix_v, vector_s, matrix_empty, matrix_empty);

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
void check(
    const isvd::DenseMatrix<double> &matrix_u,
    const isvd::DenseMatrix<double> &matrix_u_true,
          double &smax,
          double &smin
) noexcept {
  isvd::DenseMatrix<double> matrix_u2(matrix_u.getNcol(), matrix_u.getNcol());
  isvd::DenseVector<double> vector_s(matrix_u.getNcol());
  isvd::DenseMatrix<double> matrix_empty;

  // U2 := Utrue' * U
  isvd::blas::gemm<isvd::TransOption::TRANS, isvd::TransOption::NORMAL>(1.0, matrix_u_true, matrix_u, 0.0, matrix_u2);

  // Compute the SVD of U2
  isvd::lapack::GesvdDriver<isvd::DenseMatrix<double>, 'N', 'N'> driver(matrix_u2);
  driver(matrix_u2, vector_s, matrix_empty, matrix_empty);
  smax = isvd::blas::amax(vector_s);
  smin = isvd::blas::amin(vector_s);
}
