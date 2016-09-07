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
  srand(time(NULL));

  isvd::DenseCube<double> cube(5, 5, 5);
  int i = 1;
  for ( auto& v : cube ) {
    v = i++;
  }
  for ( auto v : cube ) {
    std::cout << std::setw(4) << v;
  }
  std::cout << std::endl;
  std::cout << cube.unfold().transpose() << std::endl;
}
