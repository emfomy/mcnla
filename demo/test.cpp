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

  isvd::CooVector<double> coovec(10, 5, std::shared_ptr<double>(new double[5]),
                                 std::shared_ptr<isvd::index_t>(new isvd::index_t[5]));

  int i = 0;
  for ( auto &v : coovec ) {
    v = ++i;
  }

  std::cout << coovec << std::endl;
}
