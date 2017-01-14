////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/isvd.cpp
/// @brief   The isvd code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <mcnla.hpp>
#include "statistics_set.hpp"

using ScalarType = double;

ScalarType tolerance = 1e-4;
mcnla::index_t maxiter = 256;

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
  mcnla::mpi_int_t mpi_size = mcnla::mpi::commSize(MPI_COMM_WORLD);
  mcnla::mpi_int_t mpi_rank = mcnla::mpi::commRank(MPI_COMM_WORLD);

  // ====================================================================================================================== //
  // Display program information
  if ( mpi_rank == mpi_root ) {
    std::cout << "MCNLA "
              << MCNLA_MAJOR_VERSION << "."
              << MCNLA_MINOR_VERSION << "."
              << MCNLA_PATCH_VERSION << " isvd demo" << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Check input
  if ( argc < 2 && mpi_rank == mpi_root ) {
    std::cout << "Usage: " << argv[0]
              << " <mtx-file> <#sketch-per-node> <rank> <over-sampling-rank> <#test>"
              << std::endl << std::endl;
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  // ====================================================================================================================== //
  // Load matrix
  mcnla::matrix::DenseMatrix<ScalarType> matrix_a;
  mcnla::index_t anrow, ancol;
  if ( mpi_rank == mpi_root ) {
    std::cout << "Load A from " << argv[1] << "." << std::endl << std::endl;
    mcnla::io::loadMatrixMarket(matrix_a, argv[1]);
    anrow = matrix_a.nrow();
    ancol = matrix_a.ncol();
  }
  MPI_Bcast(&anrow, 1, MPI_INT, mpi_root, MPI_COMM_WORLD);
  MPI_Bcast(&ancol, 1, MPI_INT, mpi_root, MPI_COMM_WORLD);
  if ( mpi_rank != mpi_root ) {
    matrix_a = mcnla::matrix::DenseMatrix<ScalarType>(anrow, ancol);
  }
  mcnla::mpi::bcast(matrix_a, mpi_root, MPI_COMM_WORLD);


  // ====================================================================================================================== //
  // Initialize random seed
  srand(time(NULL) ^ mpi_rank);
  srand(rand());
  mcnla::index_t seed[4] = {rand()%4096, rand()%4096, rand()%4096, (rand()%2048)*2+1};

  // ====================================================================================================================== //
  // Set parameters
  int argi = 1;
  mcnla::index_t Nj        = ( argc > ++argi ) ? atoi(argv[argi]) : 4;
  mcnla::index_t m         = matrix_a.nrow();
  mcnla::index_t n         = matrix_a.ncol();
  mcnla::index_t k         = ( argc > ++argi ) ? atoi(argv[argi]) : 10;
  mcnla::index_t p         = ( argc > ++argi ) ? atoi(argv[argi]) : 12;
  mcnla::index_t num_test  = ( argc > ++argi ) ? atoi(argv[argi]) : 10;
  mcnla::index_t skip_test = ( argc > ++argi ) ? atoi(argv[argi]) : 5;
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
  StatisticsSet set_frerr(num_test), set_iter(num_test),
                set_time(num_test), set_time_s(num_test), set_time_i(num_test), set_time_f(num_test);

  // ====================================================================================================================== //
  // Initialize solver
  mcnla::isvd::Solver<mcnla::matrix::DenseMatrix<ScalarType>,
                      mcnla::isvd::GaussianProjectionSketcher<mcnla::matrix::DenseMatrix<ScalarType>>,
                      mcnla::isvd::KolmogorovNagumoIntegrator<mcnla::matrix::DenseMatrix<ScalarType>>,
                      mcnla::isvd::SvdFormer<mcnla::matrix::DenseMatrix<ScalarType>>> solver(MPI_COMM_WORLD);
  solver.setSize(matrix_a).setRank(k).setOverRank(p).setNumSketchEach(Nj).setSeed(seed);
  solver.setTolerance(tolerance).setMaxIteration(maxiter);
  solver.initialize();
  if ( mpi_rank == mpi_root ) {
    std::cout << "Uses " << solver.getSketcherName() << "." << std::endl;
    std::cout << "Uses " << solver.getIntegratorName() << "." << std::endl;
    std::cout << "Uses " << solver.getFormerName() << "." << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Run MCNLA
  if ( mpi_rank == mpi_root ) {
    std::cout << "Start iSVD." << std::endl << std::endl;
    std::cout << std::fixed << std::setprecision(6);
  }

  for ( int t = -skip_test; t < num_test; ++t ) {

    // Run solver
    MPI_Barrier(MPI_COMM_WORLD);
    solver.compute(matrix_a);
    MPI_Barrier(MPI_COMM_WORLD);

    // Check result
    if ( mpi_rank == mpi_root  ) {
      ScalarType frerr;
      check(matrix_a, solver.getLeftSingularVectors(), solver.getRightSingularVectors(), solver.getSingularValues(), frerr);
      auto iter    = solver.getIntegratorIter();
      auto maxiter = solver.getParameters().getMaxIteration();
      auto time_s = solver.getSketcherTime();
      auto time_i = solver.getIntegratorTime();
      auto time_f = solver.getFormerTime();
      auto time = time_s + time_i + time_f;
      std::cout << std::setw(log10(num_test)+1) << t
                << " | error: " << frerr
                << " | iter: " << std::setw(log10(maxiter)+1) << iter
                << " | time: " << time << " (" << time_s << " / " << time_i << " / " << time_f << ")" << std::endl;
      if ( t >= 0 ) {
        set_frerr(frerr); set_iter(iter); set_time(time); set_time_s(time_s); set_time_f(time_f); set_time_i(time_i);
      }
    }
  }

  // Display statistics results
  if ( mpi_rank == mpi_root ) {
    std::cout << std::endl;
    std::cout << "Average total computing time: " << set_time.mean()   << " seconds." << std::endl;
    std::cout << "Average sketching time:       " << set_time_s.mean() << " seconds." << std::endl;
    std::cout << "Average integrating time:     " << set_time_i.mean() << " seconds." << std::endl;
    std::cout << "Average forming time:         " << set_time_f.mean() << " seconds." << std::endl;
    std::cout << "error: \tmean = " << set_frerr.mean() << ", \tsd = " << set_frerr.sd() << std::endl;
    std::cout << "iter:  \tmean = " << set_iter.mean()  << ", \tsd = " << set_iter.sd() << std::endl;
    std::cout << std::endl;
    std::cout << "error = norm(A-USV')_F/norm(A)_F" << std::endl;
  }

  MPI_Finalize();
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
  mcnla::matrix::DenseMatrix<ScalarType, _layout> matrix_a_tmp(matrix_a.sizes());
  mcnla::matrix::DenseMatrix<ScalarType, _layout> matrix_u_tmp(matrix_u.sizes());

  // A_tmp := A, U_tmp = U
  mcnla::blas::copy(matrix_a, matrix_a_tmp);
  mcnla::blas::copy(matrix_u, matrix_u_tmp);

  // A_tmp -= U * S * V'
  for ( auto i = 0; i < vector_s.length(); ++i ) {
    mcnla::blas::scal(vector_s(i), matrix_u_tmp.getCol(i));
  }
  mcnla::blas::gemm<mcnla::Trans::NORMAL, mcnla::Trans::NORMAL>(-1.0, matrix_u_tmp, matrix_vt, 1.0, matrix_a_tmp);

  // frerr := norm(A_tmp)_F / norm(A)_F
  frerr = mcnla::blas::nrm2(matrix_a_tmp.vectorize()) / mcnla::blas::nrm2(matrix_a.vectorize());
}
