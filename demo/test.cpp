////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    main/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#include <iostream>
#include <isvd.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {

  MPI_Init(&argc, &argv);

  int mpi_rank = isvd::mpi::getCommRank(MPI_COMM_WORLD), mpi_root = 0;

  srand(time(NULL) ^ mpi_rank);
  srand(rand());

  if ( mpi_rank == mpi_root ) {
    std::cout << "iSVD "
              << ISVD_VERSION_MAJOR << "."
              << ISVD_VERSION_MINOR << "."
              << ISVD_VERSION_PATCH << " test" << std::endl << std::endl;
  }

  isvd::DenseMatrix<double> matA(4, 3);
  isvd::DenseMatrix<double, isvd::Layout::ROWMAJOR> matB(6, 3), matC(4, 6);

  isvd::blas::gemm<isvd::TransOption::NORMAL, isvd::TransOption::TRANS>(1.0, matA, matB, 2.0, matC);

  isvd::Solver<isvd::DenseMatrix<double>,
               isvd::GaussianProjectionSketcher<isvd::DenseMatrix<double>>,
               isvd::KolmogorovNagumoTypeIntegrator<isvd::DenseMatrix<double>>,
               isvd::StandardReconstructor<isvd::DenseMatrix<double>>> solver(MPI_COMM_WORLD);

  isvd::index_t seed[4] = {rand()%4096, rand()%4096, rand()%4096, (rand()%2048)*2+1};
  isvd::index_t m = 7, n = 10, k = 2, p = 1, Nj = 2;

  // Generate A
  isvd::DenseMatrix<double> matrix_a(m, n);
  if ( mpi_rank == mpi_root ) {
    isvd::lapack::larnv<3>(matrix_a.vectorize(), seed);
  }
  isvd::mpi::Bcast(matrix_a, mpi_root, MPI_COMM_WORLD);
  if ( mpi_rank == mpi_root ) {
    std::cout << "A:\n" << matrix_a << std::endl;
  }

  solver.setSize(matrix_a).setRank(k).setOverRank(p).setNumSketch(Nj).setSeed(seed);

  solver.initialize();

  solver.compute(matrix_a);

  // if ( mpi_rank == mpi_root ) {
  //   std::cout << "S:\n"  << solver.getSingularValues() << std::endl;
  //   std::cout << "U:\n"  << solver.getLeftSingularVectors() << std::endl;
  //   std::cout << "Vt:\n" << solver.getRightSingularVectors() << std::endl;
  // }

  MPI_Finalize();
}
