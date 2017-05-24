////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/example.cpp
/// @brief   The example code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <mcnla.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {

  /// [init-mcnla]
  // Initialize MCNLA
  mcnla::init(argc, argv);
  mcnla::mpi_int_t mpi_root = 0;

  // Initialize random seed
  srand(time(NULL));

  // Check input
  if ( argc < 5 && mcnla::mpi::isCommRoot(mpi_root, MPI_COMM_WORLD) ) {
    std::cout << "Usage: " << argv[0]
              << " <A-mtx-file> <S-mtx-file> <U-mtx-file> <Vt-mtx-file>"
              << std::endl << std::endl;
    MPI_Abort(MPI_COMM_WORLD, 1);
  }
  /// [init-mcnla]

  /// [load-data]
  // Load matrix
  mcnla::matrix::DenseMatrix<double> matrix_a;
  mcnla::io::loadMatrixMarket(matrix_a, argv[1]);
  /// [load-data]

  /// [init-param]
  // Set parameters
  mcnla::index_t k = 20, p = 12, Nj = 4;
  mcnla::isvd::Parameters<double> parameters(mpi_root, MPI_COMM_WORLD);
  parameters.setSize(matrix_a).setRank(k).setOverRank(p).setNumSketchEach(Nj);
  parameters.sync();
  /// [init-param]

  /// [alloc-stage]
  // Allocate stages
  mcnla::isvd::RowBlockColumnSamplingSketcher<double> sketcher(parameters);
  mcnla::isvd::RowBlockGramianOrthogonalizer<double> orthogonalizer(parameters);
  mcnla::isvd::RowBlockKolmogorovNagumoIntegrator<double> integrator(parameters);
  mcnla::isvd::SvdFormer<double> former(parameters);
  mcnla::isvd::MatrixFromRowBlockConverter<double> if_converter(parameters);

  // Initialize stages
  mcnla::index_t maxiter = 256;
  double tol = 1e-4;
  sketcher.setSeed(rand());
  integrator.setMaxIteration(maxiter).setTolerance(tol);
  sketcher.initialize();
  orthogonalizer.initialize();
  integrator.initialize();
  former.initialize();
  if_converter.initialize();
  /// [alloc-stage]

  /// [alloc-var]
  // Allocate variables
  auto matrix_aj     = matrix_a(parameters.rowrange(), ""_);
  auto collection_qj = parameters.createCollectionQj();
  auto matrix_qj     = parameters.createMatrixQj();
  auto matrix_q      = parameters.createMatrixQ();
  /// [alloc-var]

  /// [disp-stage]
  // Display stage names
  if ( mcnla::mpi::isCommRoot(mpi_root, MPI_COMM_WORLD) ) {
    std::cout << "Uses " << sketcher << "." << std::endl;
    std::cout << "Uses " << orthogonalizer << "." << std::endl;
    std::cout << "Uses " << integrator << "." << std::endl;
    std::cout << "Uses " << former << "." << std::endl << std::endl;
  }
  /// [disp-stage]

  /// [run-isvd]
  // Run iSVD
  sketcher(matrix_aj, collection_qj);
  orthogonalizer(collection_qj);
  integrator(collection_qj, matrix_qj);
  if_converter(matrix_qj, matrix_q);
  former(matrix_a, matrix_q);
  /// [run-isvd]

  /// [disp-time]
  // Display executing time
  if ( mcnla::mpi::isCommRoot(mpi_root, MPI_COMM_WORLD) ) {
    auto time_s  = sketcher.time();
    auto time_o  = orthogonalizer.time();
    auto time_i  = integrator.time();
    auto time_f  = former.time();
    auto time_so = 0.0;
    auto time_oi = 0.0;
    auto time_if = if_converter.time();
    auto time    = time_s + time_o + time_i + time_if + time_f;
    std::cout << "Average total computing time:   " << time    << " seconds." << std::endl;
    std::cout << "Average sketching time:         " << time_s  << " seconds." << std::endl;
    std::cout << "Average orthogonalizing time:   " << time_o  << " seconds." << std::endl;
    std::cout << "Average integrating time:       " << time_i  << " seconds." << std::endl;
    std::cout << "Average forming time:           " << time_f  << " seconds." << std::endl;
    std::cout << "Average converting time (S->O): " << time_so << " seconds." << std::endl;
    std::cout << "Average converting time (O->I): " << time_oi << " seconds." << std::endl;
    std::cout << "Average converting time (I->F): " << time_if << " seconds." << std::endl;
  }
  /// [disp-time]

  /// [save-data]
  // Save matrix
  if ( mcnla::mpi::isCommRoot(mpi_root, MPI_COMM_WORLD) ) {
    mcnla::io::saveMatrixMarket(former.vectorS(),  argv[2]);
    mcnla::io::saveMatrixMarket(former.matrixU(),  argv[3]);
    mcnla::io::saveMatrixMarket(former.matrixVt(), argv[4]);
  }
  /// [save-data]

  /// [final-mcnla]
  // Finalize MCNLA
  mcnla::finalize();
  /// [final-mcnla]

}
