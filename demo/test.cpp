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
  isvd::index_t seed[4] = {rand()%4096, rand()%4096, rand()%4096, (rand()%2048)*2+1};

  isvd::DenseVector<double> vec(100);
  isvd::lapack::larnv<3>(vec, seed);
  for ( auto& v : vec ) {
    std::cout << std::setw(12) << v;
  }
  std::cout << std::endl;
}
