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

  int n = 3, k = 4;

  mcnla::matrix::DenseMatrixRowMajor<double> gematA(n, k);
  mcnla::matrix::DenseMatrixColMajor<double> gematB(n, k);
  mcnla::matrix::DenseMatrixRowMajor<double> gematC(k, n);

  {
    int i = 0;
    for ( auto &v : gematA ) {
      v = ++i;
    }
  }

  // {
  //   int i = 0;
  //   for ( auto &v : gematB ) {
  //     v = i+=2;
  //   }
  // }

  mcnla::blas::copy(gematA, gematB);
  mcnla::blas::copy(gematA.t(), gematC);

  std::cout << gematA << std::endl;
  std::cout << gematB << std::endl;
  std::cout << gematC << std::endl;

  return 0;
}
