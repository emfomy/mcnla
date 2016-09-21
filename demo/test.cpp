////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/test.cpp
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

  isvd::CooMatrix<double> mat(10, 8, 3, 5);

  int i = 0;
  for ( auto tuple : mat ) {
    ++i;
    tuple(i, i+2, 7-i*2);
  }

  std::cout << mat << std::endl;
  mat.sort();
  std::cout << mat << std::endl;
  std::cout << mat(3, 2) << std::endl;
  std::cout << mat(4, 3) << std::endl << std::endl;
  std::cout << mat.getCols({0, 3}) << std::endl;

}
