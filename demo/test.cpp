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

  mcnla::matrix::DenseMatrixColMajor<double> matA(m, m);
  mcnla::matrix::DenseMatrixRowMajor<double> matB(m, n);
  mcnla::matrix::DenseMatrixRowMajor<double> matC(m, n);

  {
    int i = 0;
    for ( auto &v : matA ) {
      v = ++i;
    }
  }

  {
    int i = 0;
    for ( auto &v : matB ) {
      v = i+=2;
    }
  }

  mcnla::blas::symm(matA.viewSymmetric(), matB, matC);

  std::cout << matA << std::endl;
  std::cout << matB << std::endl;
  std::cout << matC << std::endl;

  return 0;
}
