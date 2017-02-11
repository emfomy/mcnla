////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#define MCNLA_TEST

#include <iostream>
#include <mcnla.hpp>

#define MTX_PATH MCNLA_DATA_PATH "/../demo/test.mtx"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {
  std::cout << "MCNLA "
            << MCNLA_MAJOR_VERSION << "."
            << MCNLA_MINOR_VERSION << "."
            << MCNLA_PATCH_VERSION << " test" << std::endl << std::endl;

  mcnla::matrix::CooMatrixColMajor<double> mat(10, 3, 5);
  int i = 0, j = 2;
  double v = 1;
  for ( auto tuple : mat ) {
    tuple.operator()(v, ++i, j);
    v /= 2;
    ++j;
    j %= 3;
  }
  for ( auto it = mat.begin(); it != mat.end(); ++it ) {
    std::cout << *it << std::endl;
  }
  std::cout << mat << std::endl;

  return 0;
}
