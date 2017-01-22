////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/isvd.cpp
/// @brief   The iSVD driver
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <mcnla.hpp>

#ifndef ATYPE
#define ATYPE DenseMatrix
#endif  // ATYPE

#ifndef SKETCHER
#define SKETCHER GaussianProjectionSketcherTag<0>
#endif  // SKETCHER

#ifndef ORTHOGONALIZER
#define ORTHOGONALIZER SvdOrthogonalizerTag
#endif  // ORTHOGONALIZER

#ifndef INTEGRATOR
#define INTEGRATOR KolmogorovNagumoIntegratorTag
#endif  // INTEGRATOR

#ifndef FORMER
#define FORMER SvdFormerTag
#endif  // FORMER

#define QUOTE(str) #str
#define MACROSTR(str) QUOTE(str)

using ScalarType = double;
using AType = mcnla::matrix::ATYPE<ScalarType>;

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
  mcnla::mpi_int_t mpi_size = mcnla::mpi::commSize(MPI_COMM_WORLD);
  mcnla::mpi_int_t mpi_rank = mcnla::mpi::commRank(MPI_COMM_WORLD);

  // ====================================================================================================================== //
  // Display program information
  if ( mpi_rank == mpi_root ) {
    std::cout << "MCNLA "
              << MCNLA_MAJOR_VERSION << "."
              << MCNLA_MINOR_VERSION << "."
              << MCNLA_PATCH_VERSION << " iSVD driver for " << MACROSTR(ATYPE) << std::endl << std::endl;
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
  AType matrix_a;
  auto sizes = matrix_a.sizes();
  if ( mpi_rank == mpi_root ) {
    std::cout << "Load A from " << argv[1] << "." << std::endl << std::endl;
    mcnla::io::loadMatrixMarket(matrix_a, argv[1]);
    sizes = matrix_a.sizes();
  }
  MPI_Bcast(&sizes, 2, MPI_INT, mpi_root, MPI_COMM_WORLD);
  if ( mpi_rank != mpi_root ) {
    matrix_a.reconstruct(sizes);
  }
  mcnla::mpi::bcast(matrix_a, mpi_root, MPI_COMM_WORLD);

  // ====================================================================================================================== //
  // Initialize random seed
  srand(time(NULL));

  // ====================================================================================================================== //
  // Set parameters
  int argi = 4;
  mcnla::index_t Nj = ( argc > ++argi ) ? atoi(argv[argi]) : 4;
  mcnla::index_t m  = matrix_a.nrow();
  mcnla::index_t n  = matrix_a.ncol();
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
  mcnla::isvd::Solver<ScalarType,
                      mcnla::isvd::SKETCHER,
                      mcnla::isvd::ORTHOGONALIZER,
                      mcnla::isvd::INTEGRATOR,
                      mcnla::isvd::FORMER> solver(MPI_COMM_WORLD);
  solver.setSize(matrix_a).setRank(k).setOverRank(p).setNumSketchEach(Nj).setSeeds(rand());
  solver.setTolerance(tolerance).setMaxIteration(maxiter);
  solver.initialize();
  if ( mpi_rank == mpi_root ) {
    std::cout << "Uses " << solver.sketcher() << "." << std::endl;
    std::cout << "Uses " << solver.orthogonalizer() << "." << std::endl;
    std::cout << "Uses " << solver.integrator() << "." << std::endl;
    std::cout << "Uses " << solver.former() << "." << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Run iSVD
  if ( mpi_rank == mpi_root ) {
    std::cout << "Start iSVD." << std::endl << std::endl;
    std::cout << std::fixed << std::setprecision(6);
  }

  MPI_Barrier(MPI_COMM_WORLD);
  solver.compute(matrix_a);
  MPI_Barrier(MPI_COMM_WORLD);

  // ====================================================================================================================== //
  // Display executing time
  if ( mpi_rank == mpi_root ) {
    auto time_s = solver.sketcherTime();
    auto time_i = solver.integratorTime();
    auto time_o = solver.orthogonalizerTime();
    auto time_f = solver.formerTime();
    auto time = time_s + time_o + time_i + time_f;

    std::cout << "Average total computing time: " << time   << " seconds." << std::endl;
    std::cout << "Average sketching time:       " << time_s << " seconds." << std::endl;
    std::cout << "Average orthogonalizing time: " << time_o << " seconds." << std::endl;
    std::cout << "Average integrating time:     " << time_i << " seconds." << std::endl;
    std::cout << "Average forming time:         " << time_f << " seconds." << std::endl;
    std::cout << std::endl;
  }

  // ====================================================================================================================== //
  // Save matrix
  if ( mpi_rank == mpi_root ) {
    std::cout << "Save S  into "  << argv[2] << "." << std::endl;
    mcnla::io::saveMatrixMarket(solver.singularValues(), argv[2]);

    std::cout << "Save U  into "  << argv[3] << "." << std::endl;
    mcnla::io::saveMatrixMarket(solver.leftSingularVectors(), argv[3]);

    std::cout << "Save Vt into " << argv[4] << "." << std::endl;
    mcnla::io::saveMatrixMarket(solver.rightSingularVectors(), argv[4]);

    std::cout << std::endl;
  }

  // ====================================================================================================================== //
  // Finalize MPI
  MPI_Finalize();
}
