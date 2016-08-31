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

  MPI_Init(&argc, &argv);

  isvd::Solver<isvd::DenseMatrix<double>,
               isvd::GaussianProjectionSketcher<isvd::DenseMatrix<double>>,
               isvd::GaussianProjectionSketcher<isvd::DenseMatrix<double>>,
               isvd::GaussianProjectionSketcher<isvd::DenseMatrix<double>>> solver(MPI_COMM_WORLD);

  solver.setSize(10, 20).setRank(5).setOverRank(2).setNumSketch(8);

  solver.initialize();

  MPI_Finalize();
}
