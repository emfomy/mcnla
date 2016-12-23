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

  mcnla::matrix::DenseVector<double> vec(10, 2, 48);

  std::cout << vec << std::endl;

  auto i = 0;
  for ( auto &v : vec ) {
    v = ++i;
  }

  std::cout << vec << std::endl;

  for ( auto &v : vec ) {
    std::cout << v << '\t';
  }
  std::cout << std::endl;

  return 0;
}
