////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <mcnla.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {
  std::cout << "MCNLA "
            << MCNLA_VERSION_MAJOR << "."
            << MCNLA_VERSION_MINOR << "."
            << MCNLA_VERSION_PATCH << " test" << std::endl << std::endl;

  mcnla::matrix::DenseMatrix<double> mat;
  mcnla::io::loadMatrixMarket(mat, "test.mtx");
  std::cout << mat << std::endl;

  return 0;
}
