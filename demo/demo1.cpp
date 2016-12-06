////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/demo1.cpp
/// @brief   The demo code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <mcnla.hpp>
#include "statistics_set.hpp"

using ScalarType = double;

ScalarType tolerance = 1e-4;
mcnla::index_t maxiter = 256;

void create( mcnla::matrix::DenseMatrix<ScalarType> &matrix_a,
             const mcnla::index_t rank, mcnla::index_t seed[4] ) noexcept;

template <mcnla::Layout _layout>
void check( const mcnla::matrix::DenseMatrix<ScalarType, _layout> &matrix_a,
            const mcnla::matrix::DenseMatrix<ScalarType, _layout> &matrix_u,
            const mcnla::matrix::DenseMatrix<ScalarType, _layout> &matrix_vt,
            const mcnla::matrix::DenseVector<ScalarType> &vector_s,
            ScalarType &frerr ) noexcept;

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
              << MCNLA_MAJOR_VERSION << "."
              << MCNLA_MINOR_VERSION << "."
              << MCNLA_PATCH_VERSION << " demo" << std::endl << std::endl;
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
  mcnla::index_t k        = ( argc > ++argi ) ? atoi(argv[argi]) : 100;
  mcnla::index_t p        = ( argc > ++argi ) ? atoi(argv[argi]) : 0;
  mcnla::index_t num_test = ( argc > ++argi ) ? atoi(argv[argi]) : 100;
  assert(k <= m && m <= n);
  if ( mpi_rank == mpi_root ) {
    std::cout << "m = " << m
            << ", n = " << n
            << ", k = " << k
            << ", p = " << p
            << ", N = " << Nj*mpi_size
            << ", K = " << mpi_size << std::endl
            << "tolerance = " << tolerance
            << ", maxiter = " << maxiter << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Create statistics collector
  StatisticsSet set_frerr(num_test), set_iter(num_test),
                set_time(num_test), set_time_s(num_test), set_time_i(num_test), set_time_r(num_test);

  // ====================================================================================================================== //
  // Initialize solver
  mcnla::matrix::DenseMatrix<ScalarType> matrix_a(m, n);
  mcnla::isvd::Solver<mcnla::matrix::DenseMatrix<ScalarType>,
                      mcnla::isvd::GaussianProjectionSketcher<mcnla::matrix::DenseMatrix<ScalarType>>,
                      mcnla::isvd::KolmogorovNagumoIntegrator<mcnla::matrix::DenseMatrix<ScalarType>>,
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
    std::cout << "A = Uk Sk Vk' + E; E~N(0, 1/(k+p))." << std::endl << std::endl;
    create(matrix_a, k, seed);
  }
  mcnla::mpi::bcast(matrix_a, mpi_root, MPI_COMM_WORLD);

  // ====================================================================================================================== //
  // Run MCNLA
  if ( mpi_rank == mpi_root ) {
    std::cout << "Start iSVD." << std::endl << std::endl;
    std::cout << std::fixed << std::setprecision(6);
  }

  for ( mcnla::index_t t = 0; t < num_test; ++t ) {

    // Run solver
    MPI_Barrier(MPI_COMM_WORLD);
    solver.compute(matrix_a);
    MPI_Barrier(MPI_COMM_WORLD);

    // Check result
    if ( mpi_rank == mpi_root ) {
      ScalarType frerr;
      check(matrix_a, solver.getLeftSingularVectors(), solver.getRightSingularVectors(), solver.getSingularValues(), frerr);
      auto iter    = solver.getIntegratorIter();
      auto maxiter = solver.getParameters().getMaxIteration();
      auto time_s = solver.getSketcherTime();
      auto time_i = solver.getIntegratorTime();
      auto time_r = solver.getReconstructorTime();
      auto time = time_s + time_i + time_r;
      std::cout << std::setw(log10(num_test)+1) << t
                << " | error: " << frerr
                << " | iter: " << std::setw(log10(maxiter)+1) << iter
                << " | time: " << time << " (" << time_s << " / " << time_i << " / " << time_r << ")" << std::endl;
      set_frerr(frerr); set_iter(iter); set_time(time); set_time_s(time_s); set_time_r(time_r); set_time_i(time_i);
    }
  }

  // Display statistics results
  if ( mpi_rank == mpi_root ) {
    std::cout << std::endl;
    std::cout << "Average total computing time: " << set_time.mean()   << " seconds." << std::endl;
    std::cout << "Average sketching time:       " << set_time_s.mean() << " seconds." << std::endl;
    std::cout << "Average integrating time:     " << set_time_i.mean() << " seconds." << std::endl;
    std::cout << "Average reconstructing time:  " << set_time_r.mean() << " seconds." << std::endl;
    std::cout << "error: \tmean = " << set_frerr.mean() << ", \tsd = " << set_frerr.sd() << std::endl;
    std::cout << "iter:  \tmean = " << set_iter.mean()  << ", \tsd = " << set_iter.sd() << std::endl;
    std::cout << std::endl;
    std::cout << "error = norm(A-USV')_F/norm(A)_F" << std::endl;
  }

  MPI_Finalize();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Create matrix A
///
void create(
          mcnla::matrix::DenseMatrix<ScalarType> &matrix_a,
    const mcnla::index_t rank,
          mcnla::index_t seed[4]
) noexcept {
  mcnla::matrix::DenseMatrix<ScalarType> matrix_u(matrix_a.getNrow(), rank);
  mcnla::matrix::DenseMatrix<ScalarType> matrix_v(matrix_a.getNcol(), rank);
  mcnla::matrix::DenseMatrix<ScalarType> matrix_empty;
  mcnla::matrix::DenseVector<ScalarType> vector_s(rank);

  // Generate A & U & V using normal random
  mcnla::lapack::larnv<3>(matrix_a.vectorize(), seed);
  mcnla::lapack::larnv<3>(matrix_u.vectorize(), seed);
  mcnla::lapack::larnv<3>(matrix_v.vectorize(), seed);

  // Orthogonalize U & V
  mcnla::lapack::gesvd<'O', 'N'>(matrix_u, vector_s, matrix_empty, matrix_empty);
  mcnla::lapack::gesvd<'O', 'N'>(matrix_v, vector_s, matrix_empty, matrix_empty);

  // A := U * S * V'
  for ( mcnla::index_t i = 0; i < rank; ++i ) {
    mcnla::blas::scal(1.0/(i+1), matrix_u.getCol(i));
  }
  ScalarType tmp = 1.0 / rank / mcnla::blas::nrm2(matrix_a.vectorize());
  mcnla::blas::gemm<mcnla::TransOption::NORMAL, mcnla::TransOption::TRANS>(1.0, matrix_u, matrix_v, tmp, matrix_a);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Check the result
///
template <mcnla::Layout _layout>
void check(
    const mcnla::matrix::DenseMatrix<ScalarType, _layout> &matrix_a,
    const mcnla::matrix::DenseMatrix<ScalarType, _layout> &matrix_u,
    const mcnla::matrix::DenseMatrix<ScalarType, _layout> &matrix_vt,
    const mcnla::matrix::DenseVector<ScalarType>          &vector_s,
          ScalarType &frerr
) noexcept {
  mcnla::matrix::DenseMatrix<ScalarType, _layout> matrix_a_tmp(matrix_a.getSizes());
  mcnla::matrix::DenseMatrix<ScalarType, _layout> matrix_u_tmp(matrix_u.getSizes());

  // A_tmp := A, U_tmp = U
  mcnla::blas::copy(matrix_a, matrix_a_tmp);
  mcnla::blas::copy(matrix_u, matrix_u_tmp);

  // A_tmp -= U * S * V'
  for ( auto i = 0; i < vector_s.getLength(); ++i ) {
    mcnla::blas::scal(vector_s(i), matrix_u_tmp.getCol(i));
  }
  mcnla::blas::gemm<mcnla::TransOption::NORMAL, mcnla::TransOption::NORMAL>(-1.0, matrix_u_tmp, matrix_vt, 1.0, matrix_a_tmp);

  // frerr := norm(A_tmp)_F / norm(A)_F
  frerr = mcnla::blas::nrm2(matrix_a_tmp.vectorize()) / mcnla::blas::nrm2(matrix_a.vectorize());
}
