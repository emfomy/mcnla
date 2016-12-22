////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/isvd_driver.cpp
/// @brief   The isvd driver
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <mcnla.hpp>

using ScalarType = double;

ScalarType tolerance = 1e-4;
mcnla::index_t maxiter = 256;

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
              << MCNLA_PATCH_VERSION << " isvd driver" << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Check input
  if ( argc < 5 && mpi_rank == mpi_root ) {
    std::cout << "Usage: " << argv[0]
              << " <A-mtx-file> <S-mtx-file> <U-mtx-file> <Vt-mtx-file> [#sketch-per-node] [rank] [over-sampling-rank]"
              << std::endl << std::endl;
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  // ====================================================================================================================== //
  // Load matrix
  mcnla::matrix::DenseMatrix<ScalarType> matrix_a;
  mcnla::index_t asize0, asize1;
  if ( mpi_rank == mpi_root ) {
    std::cout << "Load A from " << argv[1] << "." << std::endl << std::endl;
    mcnla::io::loadMatrixMarket(matrix_a, argv[1]);
    asize0 = matrix_a.getNrow();
    asize1 = matrix_a.getNcol();
  }
  MPI_Bcast(&asize0, 1, MPI_INT, mpi_root, MPI_COMM_WORLD);
  MPI_Bcast(&asize1, 1, MPI_INT, mpi_root, MPI_COMM_WORLD);
  if ( mpi_rank != mpi_root ) {
    matrix_a = mcnla::matrix::DenseMatrix<ScalarType>(asize0, asize1);
  }
  mcnla::mpi::bcast(matrix_a, mpi_root, MPI_COMM_WORLD);

  // ====================================================================================================================== //
  // Initialize random seed
  srand(time(NULL) ^ mpi_rank);
  srand(rand());
  mcnla::index_t seed[4] = {rand()%4096, rand()%4096, rand()%4096, (rand()%2048)*2+1};

  // ====================================================================================================================== //
  // Set parameters
  int argi = 4;
  mcnla::index_t Nj = ( argc > ++argi ) ? atoi(argv[argi]) : 4;
  mcnla::index_t m  = matrix_a.getNrow();
  mcnla::index_t n  = matrix_a.getNcol();
  mcnla::index_t k  = ( argc > ++argi ) ? atoi(argv[argi]) : 10;
  mcnla::index_t p  = ( argc > ++argi ) ? atoi(argv[argi]) : 12;
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
  // Run MCNLA
  if ( mpi_rank == mpi_root ) {
    std::cout << "Start iSVD." << std::endl << std::endl;
    std::cout << std::fixed << std::setprecision(6);
  }

  // Run solver
  MPI_Barrier(MPI_COMM_WORLD);
  solver.compute(matrix_a);
  MPI_Barrier(MPI_COMM_WORLD);

  // Display statistics results
  if ( mpi_rank == mpi_root ) {
    auto time_s = solver.getSketcherTime();
    auto time_i = solver.getIntegratorTime();
    auto time_r = solver.getReconstructorTime();
    auto time = time_s + time_i + time_r;

    std::cout << "Average total computing time: " << time   << " seconds." << std::endl;
    std::cout << "Average sketching time:       " << time_s << " seconds." << std::endl;
    std::cout << "Average integrating time:     " << time_i << " seconds." << std::endl;
    std::cout << "Average reconstructing time:  " << time_r << " seconds." << std::endl;
    std::cout << std::endl;
  }

  // ====================================================================================================================== //
  // Save matrix
  if ( mpi_rank == mpi_root ) {
    std::cout << "Save S into "  << argv[2] << "." << std::endl;
    mcnla::io::saveMatrixMarket(solver.getSingularValues(), argv[2]);

    std::cout << "Save U into "  << argv[3] << "." << std::endl;
    mcnla::io::saveMatrixMarket(solver.getLeftSingularVectors(), argv[3]);

    std::cout << "Save Vt into " << argv[4] << "." << std::endl;
    mcnla::io::saveMatrixMarket(solver.getRightSingularVectors(), argv[4]);

    std::cout << std::endl;
  }

  MPI_Finalize();
}
