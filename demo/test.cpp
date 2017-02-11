////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#define MCNLA_TEST

#include <iostream>
#include <mcnla.hpp>

#define MTX_PATH MCNLA_DATA_PATH "/../demo/test.mtx"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {
  std::cout << "MCNLA "
            << MCNLA_MAJOR_VERSION << "."
            << MCNLA_MINOR_VERSION << "."
            << MCNLA_PATCH_VERSION << " test" << std::endl << std::endl;

  double ad = 1.1; int ai0 = 1, ai1 = 1;
  double bd = 2.2; int bi0 = 0, bi1 = 2;
  auto a = mcnla::matrix::makeCooTuple(ad, ai0, ai1);
  auto b = mcnla::matrix::makeCooTuple(bd, bi0, bi1);
  std::cout << a << std::endl;
  std::cout << b << std::endl;
  std::cout << (a < b) << std::endl;

  return 0;
}
