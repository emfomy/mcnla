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

  mcnla::matrix::DenseMatrix<double> a(5, 6), b(5, 6);

  int i = 0;
  for ( auto &v : a ) {
    v = ++i;
  }
  std::cout << a << std::endl;

  mcnla::blas::omatcopy(1.0, a.getRows({0, 3}), b.getRows({0, 3}));

  std::cout << b << std::endl;


  return 0;
}
