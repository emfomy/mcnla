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

  mcnla::matrix::DenseMatrixSet120<double> set(5, 2, 4);
  int i = 0;
  for ( auto &v : set ) {
    v = ++i;
  }
  std::cout << set.unfold() << std::endl << std::endl;

  for ( auto i = 0; i < set.getNmat(); ++i ) {
    std::cout << set(i) << std::endl << std::endl;
  }

  std::cout << set.getRows({1, 3}).unfold() << std::endl << std::endl;

  auto subset = set.getRows({1, 3});

  std::cout << subset.unfold() << std::endl << std::endl;

  for ( auto i = 0; i < subset.getNmat(); ++i ) {
    std::cout << subset(i) << std::endl << std::endl;
  }

  return 0;
}
