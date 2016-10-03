////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <mcnla.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {
  mcnla::index_t seed[4] = {0, 0, 0, 1};

  mcnla::DenseVector<double> vec(5, 3);

  mcnla::lapack::larnv<1>(vec, seed);
  std::cout << vec << std::endl;

  mcnla::blas::memset0(vec);
  std::cout << vec << std::endl;
  std::cout << vec.expand() << std::endl;
}
