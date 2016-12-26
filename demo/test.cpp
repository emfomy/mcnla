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

  int m = 3, n = 4;

  mcnla::matrix::DenseMatrixRowMajor<double> gematA(m, n);
  mcnla::matrix::DenseMatrixColMajor<double> gematB(m, m);
  mcnla::matrix::DenseMatrixRowMajor<double> gematC(n, n);
  auto symatB = gematB.viewSymmetric();
  auto symatC = gematC.viewSymmetric();

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

  mcnla::blas::rk(gematA, symatB);
  mcnla::blas::rk(gematA.t(), symatC);

  std::cout << gematA << std::endl;
  std::cout << symatB << std::endl;
  std::cout << symatC << std::endl;

  return 0;
}
