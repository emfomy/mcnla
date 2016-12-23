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
            << MCNLA_MAJOR_VERSION << "."
            << MCNLA_MINOR_VERSION << "."
            << MCNLA_PATCH_VERSION << " test" << std::endl << std::endl;

  mcnla::matrix::DenseMatrix<double> mat(3, 5);

  std::cout << mat << std::endl;

  auto i = 0;
  for ( auto &v : mat ) {
    v = ++i;
  }

  std::cout << mat << std::endl;

  std::cout << mat({1, 2}, "") << std::endl;

  return 0;
}
