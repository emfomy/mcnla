////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#define MCNLA_TEST

#include <cstdio>
#include <iostream>
#include <mcnla.hpp>

// #define MTX_PATH MCNLA_DATA_PATH "/../demo/test.mtx"
#define MTX_PATH MCNLA_DATA_PATH "/../demo/b1_ss.mtx"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {
  std::cout << "MCNLA "
            << MCNLA_MAJOR_VERSION << "."
            << MCNLA_MINOR_VERSION << "."
            << MCNLA_PATCH_VERSION << " test" << std::endl << std::endl;

  mcnla::matrix::CooMatrixColMajor<double> a;

  mcnla::io::loadMatrixMarket(a, MTX_PATH);

  std::cout << a << std::endl;

  return 0;
}
