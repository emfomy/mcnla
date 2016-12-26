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
  mcnla::matrix::DenseMatrixRowMajor<double> gematB(n, k);
  mcnla::matrix::DenseMatrixRowMajor<double> gematC(n, n);
  mcnla::matrix::DenseMatrixRowMajor<double> gematD(k, k);
  auto symatC = gematC.viewSymmetric();
  auto symatD = gematD.viewSymmetric();

  {
    int i = 0;
    for ( auto &v : gematA ) {
      v = ++i;
    }
  }

  {
    int i = 0;
    for ( auto &v : gematB ) {
      v = i+=2;
    }
  }

  mcnla::blas::r2k(gematA, gematB, symatC);
  mcnla::blas::r2k(gematA.t(), gematB.t(), symatD);

  std::cout << gematA << std::endl;
  std::cout << gematB << std::endl;
  std::cout << symatC << std::endl;
  std::cout << symatD << std::endl;

  return 0;
}
