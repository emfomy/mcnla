////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    src/isvd.cpp
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

using ValType = double;
using AType = mcnla::matrix::ATYPE<ValType>;

void check( const AType &matrix_a,
            const mcnla::matrix::DenseMatrixColMajor<ValType> &matrix_u,
            const mcnla::matrix::DenseMatrixColMajor<ValType> &matrix_vt,
            const mcnla::matrix::DenseVector<ValType> &vector_s,
            ValType &frerr ) noexcept;

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
              << " <A-mtx-file> <S-mtx-file> <U-mtx-file> <Vt-mtx-file>"
                 " [#sketch-per-node] [rank] [over-sampling-rank] [tolerance] [maxiter]"
              << std::endl << std::endl;
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  // ====================================================================================================================== //
  // Load matrix
  AType matrix_a;
  if ( mpi_rank == mpi_root ) {
    std::cout << "Load A from " << argv[1] << "." << std::endl << std::endl;
  }
  mcnla::io::loadMatrixMarket(matrix_a, argv[1]);
  if ( mpi_rank == mpi_root ) {
    std::cout << "Loaded A." << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Initialize random seed
  srand(time(NULL));

  // ====================================================================================================================== //
  // Set parameters
  int argi = 4;
  mcnla::index_t Nj      = ( argc > ++argi ) ? atof(argv[argi]) : 4;
  mcnla::index_t m       = matrix_a.nrow();
  mcnla::index_t n       = matrix_a.ncol();
  mcnla::index_t k       = ( argc > ++argi ) ? atof(argv[argi]) : 10;
  mcnla::index_t p       = ( argc > ++argi ) ? atof(argv[argi]) : 12;
  ValType        tol     = ( argc > ++argi ) ? atof(argv[argi]) : 1e-4;
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
              << omp_get_max_threads() << " threads per node" << std::endl << std::endl;
  }
  assert((k+p) <= m && m <= n);

  // ====================================================================================================================== //
  // Initialize driver
  mcnla::isvd::Driver<ValType,
                      mcnla::isvd::SKETCHER,
                      mcnla::isvd::ORTHOGONALIZER,
                      mcnla::isvd::INTEGRATOR,
                      mcnla::isvd::FORMER> driver(MPI_COMM_WORLD);
  driver.setSize(matrix_a).setRank(k).setOverRank(p).setNumSketchEach(Nj).setSeeds(rand());
  driver.setTolerance(tol).setMaxIteration(maxiter);
  driver.initialize();
  if ( mpi_rank == mpi_root ) {
    std::cout << "Uses " << driver.sketcher() << "." << std::endl;
    std::cout << "Uses " << driver.orthogonalizer() << "." << std::endl;
    std::cout << "Uses " << driver.integrator() << "." << std::endl;
    std::cout << "Uses " << driver.former() << "." << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Run iSVD
  if ( mpi_rank == mpi_root ) {
    std::cout << "Start iSVD." << std::endl << std::endl;
    std::cout << std::fixed << std::setprecision(6);
  }

  MPI_Barrier(MPI_COMM_WORLD);
  driver.compute(matrix_a);
  MPI_Barrier(MPI_COMM_WORLD);

  // ====================================================================================================================== //
  // Display results
  if ( mpi_rank == mpi_root ) {
    ValType frerr;
    check(matrix_a, driver.leftSingularVectors(), driver.rightSingularVectors(), driver.singularValues(), frerr);
    auto iter   = driver.integratorIteration();
    auto time_s = driver.sketcherTime();
    auto time_i = driver.integratorTime();
    auto time_o = driver.orthogonalizerTime();
    auto time_f = driver.formerTime();
    auto time = time_s + time_o + time_i + time_f;

    std::cout << "Total computing time: " << time   << " seconds." << std::endl;
    std::cout << "Sketching time:       " << time_s << " seconds." << std::endl;
    std::cout << "Orthogonalizing time: " << time_o << " seconds." << std::endl;
    std::cout << "Integrating time:     " << time_i << " seconds." << std::endl;
    std::cout << "Forming time:         " << time_f << " seconds." << std::endl;
    std::cout << std::endl;
    std::cout << "Iteration = " << iter << std::endl;
    std::cout << "Error     = " << frerr << std::endl;
    std::cout << std::endl;
    std::cout << "Error := norm(A-USV')_F/norm(A)_F" << std::endl;
    std::cout << std::endl;
  }

  // ====================================================================================================================== //
  // Save matrix
  if ( mpi_rank == mpi_root ) {
    std::cout << "Save S  into "  << argv[2] << "." << std::endl;
    mcnla::io::saveMatrixMarket(driver.singularValues(), argv[2]);

    std::cout << "Save U  into "  << argv[3] << "." << std::endl;
    mcnla::io::saveMatrixMarket(driver.leftSingularVectors(), argv[3]);

    std::cout << "Save Vt into " << argv[4] << "." << std::endl;
    mcnla::io::saveMatrixMarket(driver.rightSingularVectors(), argv[4]);

    std::cout << std::endl;
  }

  // ====================================================================================================================== //
  // Finalize MPI
  MPI_Finalize();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Check the result (A)
///
void check(
    const AType &matrix_a,
    const mcnla::matrix::DenseMatrixColMajor<ValType> &matrix_u,
    const mcnla::matrix::DenseMatrixColMajor<ValType> &matrix_vt,
    const mcnla::matrix::DenseVector<ValType> &vector_s,
          ValType &frerr
) noexcept {
  // A_tmp := A, U_tmp = U
  auto matrix_a_tmp = matrix_a.copy();
  auto matrix_u_tmp = matrix_u.copy();

  // A_tmp -= U * S * V'
  mcnla::la::mm("", vector_s.viewDiagonal(), matrix_u_tmp);
  mcnla::la::mm(matrix_u_tmp, matrix_vt, matrix_a_tmp, -1.0, 1.0);

  // frerr := norm(A_tmp)_F / norm(A)_F
  frerr = mcnla::la::nrmf(matrix_a_tmp) / mcnla::la::nrmf(matrix_a);
}
