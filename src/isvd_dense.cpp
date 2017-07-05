////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    src/isvd.cpp
/// @brief   The iSVD driver for dense matrix
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <mcnla.hpp>
#include <omp.h>

void check( const mcnla::matrix::DenseMatrixRowMajor<double> &matrix_a,
            const mcnla::matrix::DenseMatrixColMajor<double> &matrix_u,
            const mcnla::matrix::DenseMatrixColMajor<double> &matrix_vt,
            const mcnla::matrix::DenseVector<double> &vector_s,
            double &frerr ) noexcept;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {

  // ====================================================================================================================== //
  // Initialize MCNLA
  mcnla::init(argc, argv);
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
              << MCNLA_PATCH_VERSION << " iSVD driver for DenseMatrix" << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Check input
  if ( argc < 5 && mpi_rank == mpi_root ) {
    std::cout << "Usage: " << argv[0]
              << " <A-mtx-file> <S-mtx-file> <U-mtx-file> <V-mtx-file>"
                 " [#sketch-per-node] [rank] [over-sampling-rank] [tolerance] [maxiter]"
              << std::endl << std::endl;
    MPI_Abort(mpi_comm, 1);
  }

  // ====================================================================================================================== //
  // Load matrix
  mcnla::matrix::DenseMatrixRowMajor<double> matrix_a;
  mcnla::io::loadMatrixMarket(matrix_a, argv[1]);

  // ====================================================================================================================== //
  // Initialize random seed
  srand(time(NULL));

  // ====================================================================================================================== //
  // Load parameters
  int argi = 4;
  mcnla::index_t Nj      = ( argc > ++argi ) ? atof(argv[argi]) : 4;
  mcnla::index_t m       = matrix_a.nrow();
  mcnla::index_t n       = matrix_a.ncol();
  mcnla::index_t k       = ( argc > ++argi ) ? atof(argv[argi]) : 20;
  mcnla::index_t p       = ( argc > ++argi ) ? atof(argv[argi]) : 12;
  double         tol     = ( argc > ++argi ) ? atof(argv[argi]) : 1e-4;
  mcnla::index_t maxiter = ( argc > ++argi ) ? atof(argv[argi]) : 256;
  if ( mpi_rank == mpi_root ) {
    std::cout << "m = " << m
            << ", n = " << n
            << ", k = " << k
            << ", p = " << p
            << ", N = " << Nj*mpi_size
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
  }
  assert((k+p) <= m && m <= n);

  // ====================================================================================================================== //
  // Initialize parameters
  mcnla::isvd::Parameters<double> parameters(mpi_root, mpi_comm);
  parameters.setSize(matrix_a).setRank(k).setOverRank(p).setNumSketchEach(Nj);
  parameters.sync();

  // ====================================================================================================================== //
  // Allocate stages
  mcnla::isvd::RowBlockGaussianProjectionSketcher<double> sketcher(parameters);
  mcnla::isvd::RowBlockGramianOrthogonalizer<double> orthogonalizer(parameters);
  mcnla::isvd::RowBlockKolmogorovNagumoIntegrator<double> integrator(parameters);
  mcnla::isvd::SvdFormer<double> former(parameters);
  mcnla::isvd::MatrixFromRowBlockConverter<double> if_converter(parameters);

  // ====================================================================================================================== //
  // Initialize stages
  sketcher.setSeed(rand());
  integrator.setMaxIteration(maxiter).setTolerance(tol);
  sketcher.initialize();
  orthogonalizer.initialize();
  integrator.initialize();
  former.initialize();
  if_converter.initialize();

  // Allocate variables
  auto matrix_aj     = matrix_a(parameters.rowrange(), ""_);
  auto collection_qj = parameters.createCollectionQj();
  auto matrix_qj     = parameters.createMatrixQbarj();
  auto matrix_q      = parameters.createMatrixQbar();

  // ====================================================================================================================== //
  // Display stage names
  if ( mpi_rank == mpi_root ) {
    std::cout << "Uses " << sketcher << "." << std::endl;
    std::cout << "Uses " << orthogonalizer << "." << std::endl;
    std::cout << "Uses " << integrator << "." << std::endl;
    std::cout << "Uses " << former << "." << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Run iSVD
  if ( mpi_rank == mpi_root ) {
    std::cout << "Start iSVD." << std::endl << std::endl;
    std::cout << std::fixed << std::setprecision(6);
  }

  sketcher(matrix_aj, collection_qj);
  orthogonalizer(collection_qj);
  integrator(collection_qj, matrix_qj);
  if_converter(matrix_qj, matrix_q);
  former(matrix_a, matrix_q);

  // ====================================================================================================================== //
  // Display results
  if ( mpi_rank == mpi_root ) {
    double frerr;
    check(matrix_a, former.matrixU(), former.matrixV(), former.vectorS(), frerr);
    auto time_s  = sketcher.time();
    auto time_o  = orthogonalizer.time();
    auto time_i  = integrator.time();
    auto time_f  = former.time();
    auto time    = time_s + time_o + time_i + time_f;
    auto iter    = integrator.iteration();

    std::cout << "Total computing time: " << time   << " seconds." << std::endl;
    std::cout << "Sketching time:       " << time_s << " seconds." << std::endl;
    std::cout << "Orthogonalizing time: " << time_o << " seconds." << std::endl;
    std::cout << "Integrating time:     " << time_i << " seconds." << std::endl;
    std::cout << "Forming time:         " << time_f << " seconds." << std::endl;
    std::cout << std::endl;
    std::cout << "Iteration = " << iter << std::endl;
    std::cout << "Error     = " << frerr << std::endl;
    std::cout << std::endl;
    std::cout << "Error := norm(A - Uk Sk Vk')_F / norm(A)_F" << std::endl;
    std::cout << std::endl;
  }

  // ====================================================================================================================== //
  // Save matrices
  if ( mpi_rank == mpi_root ) {
    std::cout << "Save S into "  << argv[2] << "." << std::endl;
    mcnla::io::saveMatrixMarket(former.vectorS(), argv[2]);

    std::cout << "Save U into "  << argv[3] << "." << std::endl;
    mcnla::io::saveMatrixMarket(former.matrixU(), argv[3]);

    std::cout << "Save V into " << argv[4] << "." << std::endl;
    mcnla::io::saveMatrixMarket(former.matrixV(), argv[4]);

    std::cout << std::endl;
  }

  // ====================================================================================================================== //
  // Finalize MCNLA
  mcnla::finalize();

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Check the result (A)
///
void check(
    const mcnla::matrix::DenseMatrixRowMajor<double> &matrix_a,
    const mcnla::matrix::DenseMatrixColMajor<double> &matrix_u,
    const mcnla::matrix::DenseMatrixColMajor<double> &matrix_vt,
    const mcnla::matrix::DenseVector<double> &vector_s,
          double &frerr
) noexcept {
  mcnla::matrix::DenseMatrixColMajor<double> matrix_a_tmp(matrix_a.sizes());
  mcnla::matrix::DenseMatrixColMajor<double> matrix_u_tmp(matrix_u.sizes());

  // A_tmp := A, U_tmp = U
  mcnla::la::copy(matrix_a, matrix_a_tmp);
  mcnla::la::copy(matrix_u, matrix_u_tmp);

  // A_tmp -= U * S * V'
  mcnla::la::mm(""_, vector_s.diag(), matrix_u_tmp);
  mcnla::la::mm(matrix_u_tmp, matrix_vt, matrix_a_tmp, -1.0, 1.0);

  // frerr := norm(A_tmp)_F / norm(A)_F
  frerr = mcnla::la::nrmf(matrix_a_tmp) / mcnla::la::nrmf(matrix_a);
}
