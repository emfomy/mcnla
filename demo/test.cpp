////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    main/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#include <iostream>
#include <isvd.hpp>

template class isvd::DenseVector<double>;
template class isvd::DenseMatrix<double>;
template class isvd::DenseCube<double>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main() {
  std::cout << "iSVD "
            << ISVD_VERSION_MAJOR << "."
            << ISVD_VERSION_MINOR << "."
            << ISVD_VERSION_PATCH << " test" << std::endl << std::endl;

  isvd::DenseMatrix<double> matA(8, 10, 15);
  for ( auto i = 0; i < matA.getNrow(); ++i ) {
    for ( auto j = 0; j < matA.getNcol(); ++j ) {
      matA(i, j) = i*j*j;
    }
  }
  std::cout << matA << std::endl;
  std::cout << matA.vectorize() << std::endl;

  // isvd::DenseMatrix<double> matB(10, 5);
  // for ( auto i = 0; i < matB.getNrow(); ++i ) {
  //   for ( auto j = 0; j < matB.getNcol(); ++j ) {
  //     matB(i, j) = i*j*j;
  //   }
  // }
  // std::cout << matB << std::endl;

  // isvd::DenseMatrix<double> matC(8, 5);
  // isvd::blas::gemm(1, matA, matB, 0, matC);
  // std::cout << matC << std::endl;
}
