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

  int m = 4, n = 5;

  mcnla::matrix::DenseMatrixColMajor<double> gematA(m, n);
  mcnla::matrix::DenseMatrixColMajor<double> gematU(m, m);
  mcnla::matrix::DenseMatrixColMajor<double> gematVt(m, n);
  mcnla::matrix::DenseVector<double>         vecS(m);

  int i = 0;
  for ( auto &v : gematA ) {
    v = ++i;
  }

  std::cout << gematA << std::endl;

  mcnla::lapack::gesvd<'S', 'S'>(gematA, vecS, gematU, gematVt);

  std::cout << gematU << std::endl;
  std::cout << gematVt << std::endl;
  std::cout << gematVt.t() << std::endl;
  std::cout << vecS << std::endl;
  std::cout << vecS.viewDiagonal() << std::endl;

  return 0;
}
