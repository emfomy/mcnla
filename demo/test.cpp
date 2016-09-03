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
  std::cout << "iSVD "
            << ISVD_VERSION_MAJOR << "."
            << ISVD_VERSION_MINOR << "."
            << ISVD_VERSION_PATCH << " test" << std::endl << std::endl;

  isvd::DenseMatrix<double> matA(4, 3);
  isvd::DenseMatrix<double, isvd::Layout::ROWMAJOR> matB(6, 3), matC(4, 6);

  isvd::blas::gemm<isvd::TransOption::NORMAL, isvd::TransOption::TRANS>(1.0, matA, matB, 2.0, matC);


  // MPI_Init(&argc, &argv);

  // isvd::Solver<isvd::DenseMatrix<double, isvd::Layout::ROWMAJOR>,
  //              isvd::GaussianProjectionSketcher<isvd::DenseMatrix<double, isvd::Layout::ROWMAJOR>>,
  //              isvd::GaussianProjectionSketcher<isvd::DenseMatrix<double, isvd::Layout::ROWMAJOR>>,
  //              isvd::GaussianProjectionSketcher<isvd::DenseMatrix<double, isvd::Layout::ROWMAJOR>>> solver(MPI_COMM_WORLD, 0);

  // isvd::index_t iseed[4] = {rand()%4096, rand()%4096, rand()%4096, (rand()%2048)*2+1};
  // isvd::index_t m = 5, n = 10;

  // // Generate A
  // isvd::DenseMatrix<double, isvd::Layout::ROWMAJOR> matrix_a(m, n);
  // isvd::lapack::larnv<3>(matrix_a.vectorize(), iseed);
  // std::cout << "A:\n" << matrix_a << std::endl;

  // solver.setSize(matrix_a).setRank(2).setOverRank(2).setNumSketch(8).setSeed(iseed);

  // solver.initialize();

  // solver.compute(matrix_a);

  // MPI_Finalize();
}
