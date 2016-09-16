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

  isvd::DenseCube<double> mat(3, 5, 7, 9, 11);
  int i = 0;
  for ( auto& v : mat ) {
    v = ++i;
  }
  for ( auto i = 0; i < mat.getNpage(); ++i ) {
    std::cout << mat.getPage(i) << std::endl;
  }
  auto it = std::lower_bound(mat.cibegin(), mat.ciend(), isvd::makeIdxTuple(1, 3, 5));
  std::cout << it << std::endl;

}
