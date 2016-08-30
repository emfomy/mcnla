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

  isvd::DenseMatrix<double> matA(8, 15);
  for ( auto i = 0; i < matA.getNrow(); ++i ) {
    for ( auto j = 0; j < matA.getNcol(); ++j ) {
      matA(i, j) = i*j*j;
    }
  }
  std::cout << matA << std::endl;

  isvd::DenseVector<double> vecTau(8), vecWork(15);

  isvd::lapack::gerqf(matA.transpose(), vecTau, vecWork);

  std::cout << matA << std::endl;
}
