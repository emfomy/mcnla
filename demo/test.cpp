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

  mcnla::matrix::DenseMatrixColMajor<double> gematA(m, m);
  mcnla::matrix::DenseMatrixRowMajor<double> gematB(m, n);
  mcnla::matrix::DenseMatrixRowMajor<double> gematC(m, n);
  auto symatA = gematA.viewSymmetric();

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

  mcnla::blas::mm(gematA, gematB, gematC);

  std::cout << gematA << std::endl;
  std::cout << gematB << std::endl;
  std::cout << gematC << std::endl;

  mcnla::blas::mm(gematB.t(), symatA.t(), gematC.t());

  std::cout << gematB.t() << std::endl;
  std::cout << symatA << std::endl;
  std::cout << gematC.t() << std::endl;

  return 0;
}
