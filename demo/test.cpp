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

  isvd::CooVector<double> mat(10, 3, 5);

  int i = 0;
  for ( auto tuple : mat ) {
    ++i;
    tuple(i, 7-i*2);
  }

  std::cout << mat << std::endl;
  mat.sort();
  std::cout << mat << std::endl;
  std::cout << mat(3) << std::endl;

}
