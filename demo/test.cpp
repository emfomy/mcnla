////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#include <iostream>
#include <isvd.hpp>

template class isvd::CooVector<double>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {

  // isvd::CooVector<double> vec(10, 5, std::shared_ptr<double>(new double[5]),
  //                                std::shared_ptr<isvd::index_t>(new isvd::index_t[5]));
  isvd::DenseVector<double> vec(10);

  int i = 0;
  for ( auto &v : vec ) {
    v = ++i;
  }

  std::cout << vec << std::endl;
}
