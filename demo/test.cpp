////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <mcnla.hpp>
#include <unistd.h>

#define MTX_PATH MCNLA_DATA_PATH "/../demo/test.mtx"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {
  std::cout << "MCNLA "
            << MCNLA_MAJOR_VERSION << "."
            << MCNLA_MINOR_VERSION << "."
            << MCNLA_PATCH_VERSION << " test" << std::endl << std::endl;

  mcnla::matrix::DenseMatrixSet102<double> set(2, 5, 4);
  int i = 0;
  for ( auto &v : set.data() ) {
    v = ++i;
  }
  std::cout << set.unfold() << std::endl << std::endl;

  for ( auto i = 0; i < set.nmat(); ++i ) {
    std::cout << set(i) << std::endl << std::endl;
  }

  std::cout << set("", {1, 3}, "").unfold() << std::endl << std::endl;

  auto subset = set("", {1, 3}, "");

  std::cout << subset.unfold() << std::endl << std::endl;

  for ( auto i = 0; i < subset.nmat(); ++i ) {
    std::cout << subset(i) << std::endl << std::endl;
  }

  return 0;
}
