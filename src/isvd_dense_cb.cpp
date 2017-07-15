////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    src/isvd_dense_cb.cpp
/// @brief   The iSVD driver for dense matrix (column-block version)
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <mcnla.hpp>
#include <omp.h>

#ifndef FILETYPE
#define FILETYPE MatrixMarket
#endif  // FILETYPE
#define MAKE_FN_NAME(prefix, name, suffix)  prefix ## name ## suffix
#define FUNCTION_NAME(prefix, name, suffix) MAKE_FN_NAME(prefix, name, suffix)
#define IO_LOAD_SIZE      FUNCTION_NAME(load, FILETYPE, Size)
#define IO_LOAD_COL_BLOCK FUNCTION_NAME(load, FILETYPE, ColBlock)

#ifndef STYPE
#define STYPE ColBlockGaussianProjectionSketcher
#endif  // STYPE

#ifndef OTYPE
#define OTYPE RowBlockGramianOrthogonalizer
#endif  // OTYPE

#ifndef ITYPE
#define ITYPE RowBlockWenYinIntegrator
#endif  // ITYPE

#ifndef FTYPE
#define FTYPE RowBlockGramianFormer
#endif  // FTYPE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {

  // ====================================================================================================================== //
  // Initialize MCNLA
  mcnla::init(argc, argv, MPI_COMM_WORLD);
  auto mpi_comm = MPI_COMM_WORLD;
  auto mpi_size = mcnla::mpi::commSize(mpi_comm);
  auto mpi_rank = mcnla::mpi::commRank(mpi_comm);
  auto mpi_root = 0;

  // ====================================================================================================================== //
  // Display program information
  if ( mpi_rank == mpi_root ) {
    std::cout << "MCNLA "
              << MCNLA_MAJOR_VERSION << "."
              << MCNLA_MINOR_VERSION << "."
              << MCNLA_PATCH_VERSION << " iSVD driver for DenseMatrix (column-block version)" << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Check input
  if ( argc < 5 ) {
    if ( mpi_rank == mpi_root ) {
      std::cout << "Usage: " << argv[0]
                << " <A-mtx-file> <S-mtx-file> <U-mtx-file> <skip>"
                   " [#sketch] [rank] [over-sampling-rank] [tolerance] [maxiter]"
                << std::endl << std::endl;
      MPI_Abort(mpi_comm, 1);
    }
    MPI_Barrier(mpi_comm);
  }

  // ====================================================================================================================== //
  // Load matrix size
  mcnla::index_t m, n;
  mcnla::io::IO_LOAD_SIZE<mcnla::Trans::NORMAL>(m, n, argv[1]);

  // ====================================================================================================================== //
  // Initialize random seed
  srand(time(NULL));

  // ====================================================================================================================== //
  // Load parameters
  int argi = 4;
  mcnla::index_t N       = ( argc > ++argi ) ? atof(argv[argi]) : 16;
  mcnla::index_t k       = ( argc > ++argi ) ? atof(argv[argi]) : 20;
  mcnla::index_t p       = ( argc > ++argi ) ? atof(argv[argi]) : 12;
  double         tol     = ( argc > ++argi ) ? atof(argv[argi]) : 1e-3;
  mcnla::index_t maxiter = ( argc > ++argi ) ? atof(argv[argi]) : 256;
  if ( mpi_rank == mpi_root ) {
    std::cout << "m = " << m
            << ", n = " << n
            << ", k = " << k
            << ", p = " << p
            << ", N = " << N
            << ", tol = " << tol
            << ", maxiter = " << maxiter << std::endl;
    std::cout << mpi_size << " nodes / "
#ifdef _OPENMP
              << omp_get_max_threads()
#else  // _OPENMP
              << 1
#endif  // _OPENMP
              << " threads per node" << std::endl;
    std::cout << sizeof(mcnla::index_t)*8 << "bit integer" << std::endl << std::endl;

    mcnla::printEnvironment();
  }
  assert((k+p) <= m && m <= n);

  // ====================================================================================================================== //
  // Initialize parameters
  mcnla::isvd::Parameters<double> parameters(mpi_root, mpi_comm);
  parameters.setSize(m, n).setRank(k).setOverRank(p).setNumSketch(N);
  parameters.sync();

  // ====================================================================================================================== //
  // Allocate stages
  mcnla::isvd::STYPE<double> sketcher(parameters);
  mcnla::isvd::OTYPE<double> orthogonalizer(parameters);
  mcnla::isvd::ITYPE<double> integrator(parameters);
  mcnla::isvd::FTYPE<double, false> former(parameters);
  mcnla::isvd::CollectionFromPartialSumToRowBlockConverter<double> so_converter(parameters);
  mcnla::isvd::MatrixFromRowBlockToAllConverter<double> if_converter(parameters);

  // ====================================================================================================================== //
  // Initialize stages
  sketcher.setSeed(rand());
  integrator.setMaxIteration(maxiter).setTolerance(tol);
  sketcher.initialize();
  orthogonalizer.initialize();
  integrator.initialize();
  former.initialize();
  so_converter.initialize();
  if_converter.initialize();

  // ====================================================================================================================== //
  // Display stage names
  if ( mpi_rank == mpi_root ) {
    std::cout << "Uses " << sketcher << "." << std::endl;
    std::cout << "Uses " << orthogonalizer << "." << std::endl;
    std::cout << "Uses " << integrator << "." << std::endl;
    std::cout << "Uses " << former << "." << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Load matrix
  if ( mpi_rank == mpi_root ) {
    std::cout << "Reading data from " << argv[1] << "." << std::endl;
  }
  mcnla::matrix::DenseMatrixColMajor<double> matrix_ajc;
  {
    double timer = 0;
    if ( mpi_rank == mpi_root ) {
      mcnla::utility::tic(timer);
    }
    mcnla::io::IO_LOAD_COL_BLOCK(matrix_ajc, argv[1], parameters.rowrange());
    if ( mpi_rank == mpi_root ) {
      mcnla::utility::dispToc(timer); std::cout << std::endl;
    }
  }

  // Allocate variables
  auto collection_qjp = parameters.createCollectionQ();
  auto collection_qj  = parameters.createCollectionQj();
  auto matrix_q       = parameters.createMatrixQbar();
  auto matrix_qj      = parameters.createMatrixQbarj();

  // ====================================================================================================================== //
  // Run iSVD
  if ( mpi_rank == mpi_root ) {
    std::cout << "Start iSVD." << std::endl << std::endl;
    std::cout << std::fixed << std::setprecision(6);
  }

  if ( mpi_rank == mpi_root ) { std::cout << "Sketching ............................. " << std::flush; }
  sketcher(matrix_ajc, collection_qj);
  if ( mpi_rank == mpi_root ) { std::cout << "Done!" << std::endl; }

  if ( mpi_rank == mpi_root ) { std::cout << "Scattering ............................ " << std::flush; }
  so_converter(collection_qjp, collection_qj);
  if ( mpi_rank == mpi_root ) { std::cout << "Done!" << std::endl; }

  if ( mpi_rank == mpi_root ) { std::cout << "Orthogonalization ..................... " << std::flush; }
  orthogonalizer(collection_qj);
  if ( mpi_rank == mpi_root ) { std::cout << "Done!" << std::endl; }

  if ( mpi_rank == mpi_root ) { std::cout << "Integration ........................... " << std::flush; }
  integrator(collection_qj, matrix_qj);
  if ( mpi_rank == mpi_root ) { std::cout << "Done!" << std::endl; }

  if ( mpi_rank == mpi_root ) { std::cout << "Gathering ............................. " << std::flush; }
  if_converter(matrix_qj, matrix_q);
  if ( mpi_rank == mpi_root ) { std::cout << "Done!" << std::endl; }

  if ( mpi_rank == mpi_root ) { std::cout << "Forming ............................... " << std::flush; }
  former(matrix_ajc, matrix_q);
  if ( mpi_rank == mpi_root ) { std::cout << "Done!" << std::endl; }

  auto &&vector_s = former.vectorS();
  // auto &&matrix_u = former.matrixU();
#pragma warning
  auto &&matrix_u = former.matrixUj();

  // ====================================================================================================================== //
  // Display results
  if ( mpi_rank == mpi_root ) {
    auto iter    = integrator.iteration();
    auto time_s  = sketcher.time();
    auto time_o  = orthogonalizer.time();
    auto time_i  = integrator.time();
    auto time_f  = former.time();
    auto time_so = so_converter.time();
    auto time_oi = 0.0;
    auto time_if = if_converter.time();
    auto time_fe = 0.0;
    auto time    = time_s + time_o + time_i + time_if + time_f + time_fe;
    std::cout << "Average total computing time:   " << time    << " seconds." << std::endl;
    std::cout << "Average sketching time:         " << time_s  << " seconds." << std::endl;
    std::cout << "Average orthogonalizing time:   " << time_o  << " seconds." << std::endl;
    std::cout << "Average integrating time:       " << time_i  << " seconds." << std::endl;
    std::cout << "Average forming time:           " << time_f  << " seconds." << std::endl;
    std::cout << "Average converting time (S->O): " << time_so << " seconds." << std::endl;
    std::cout << "Average converting time (O->I): " << time_oi << " seconds." << std::endl;
    std::cout << "Average converting time (I->F): " << time_if << " seconds." << std::endl;
    std::cout << "Average converting time (F->@): " << time_if << " seconds." << std::endl;
    std::cout << std::endl;
    std::cout << "Iteration = " << iter << std::endl;
    std::cout << std::endl;
  }

  // ====================================================================================================================== //
  // Save matrices
  if ( mpi_rank == mpi_root ) {
    std::cout << "Write S into " << argv[2] << "." << std::endl;
    mcnla::io::saveMatrixMarket(vector_s, argv[2]);

    std::cout << "Write U into " << argv[3] << "." << std::endl;
    mcnla::io::saveMatrixMarket(matrix_u, argv[3]);

    mcnla::matrix::DenseMatrixRowMajor<double> matrix_v;
    std::cout << "Write V into " << argv[4] << "." << std::endl;
    mcnla::io::saveMatrixMarket(matrix_v, argv[4]);

    std::cout << std::endl;
  }

  // ====================================================================================================================== //
  // Finalize MCNLA
  mcnla::finalize();

}