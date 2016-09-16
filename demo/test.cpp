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

  isvd::CooVector<double> mat(3, 5);
  int i = 0;
  for ( auto it = mat.begin(); it != mat.end(); ++it ) {
    *it = ++i;
    it.getIdx() = 3*i;
  }
  std::cout << mat << std::endl;
  std::cout << mat(2) << std::endl;

}
