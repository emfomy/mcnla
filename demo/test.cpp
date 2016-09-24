////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#include <iostream>
#include <isvd.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {

  isvd::index_t iseed[] = {0, 0, 0, 1};

  isvd::CooMatrix<double> matA(3, 3, 24, 50);
  isvd::DenseMatrix<double> matB(3, 4), matC(3, 4);

  matA.setNnz(std::min(matA.getNrow(), matA.getNcol()));
  int i = 0;
  for ( auto tuple : matA ) {
    tuple(i, i, i);
    ++i;
  }
  std::cout << matA << std::endl;

  isvd::lapack::larnv<3>(matB.vectorize(), iseed);
  std::cout << matB << std::endl;

  isvd::blas::gemm<isvd::TransOption::TRANS>(1.0, matA, matB, 0.0, matC);
  std::cout << matC << std::endl;

}
