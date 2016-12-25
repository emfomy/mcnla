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
  std::cout << "MCNLA "
            << MCNLA_MAJOR_VERSION << "."
            << MCNLA_MINOR_VERSION << "."
            << MCNLA_PATCH_VERSION << " test" << std::endl << std::endl;

  mcnla::matrix::DenseVector<double> vec(3);

  std::cout << vec << std::endl;

  auto i = 0;
  for ( auto &v : vec ) {
    v = ++i;
  }

  std::cout << vec << std::endl;

  vec.resize(2);

  std::cout << vec << std::endl;

  vec.reconstruct(2);

  std::cout << vec << std::endl;

  return 0;
}
