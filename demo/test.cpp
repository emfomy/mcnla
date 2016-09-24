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

  isvd::CooVector<double> coovec(10, 3, 5);
  std::cout << coovec << std::endl;

  int i = 0;
  for ( auto tuple : coovec ) {
    ++i;
    tuple(i, 7-i*2);
  }
  std::cout << coovec << std::endl;

  coovec.sort();
  std::cout << coovec << std::endl;

  isvd::DenseVector<double> denvec(10);
  std::cout << denvec << std::endl;

  for ( auto &value : denvec ) {
    value = ++i;
  }
  std::cout << denvec << std::endl;

  isvd::blas::copy(coovec, denvec);
  std::cout << denvec << std::endl;

}
