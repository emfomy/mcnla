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

  isvd::DenseCube<double> mat(5, 6, 7);

  int i = 0;
  for ( auto &value : mat ) {
    value = ++i;
  }
  std::cout << mat << std::endl;
  std::cout << mat(3, 4, 5) << std::endl << std::endl;
  std::cout << mat.find(3, 4, 5) << std::endl << std::endl;
  std::cout << mat.getCube({1, 3}, {2, 4}, {3, 5}) << std::endl;

}
