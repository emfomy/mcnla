////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    main/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#include <iostream>
#include <isvd.hpp>

template class isvd::DenseMatrix<double>;
template class isvd::impl::MatrixBase<isvd::DenseMatrix<double>>;
template class isvd::impl::DenseBase<isvd::DenseMatrix<double>, double>;
template class isvd::impl::DenseMatrixBase<isvd::DenseMatrix<double>, double>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main() {
  std::cout << "iSVD "
            << ISVD_VERSION_MAJOR << "."
            << ISVD_VERSION_MINOR << "."
            << ISVD_VERSION_PATCH << " test" << std::endl << std::endl;

  isvd::DenseMatrix<double> matrix(10, 20, 30);
  for ( auto i = 0; i < matrix.getNrow(); ++i ) {
    for ( auto j = 0; j < matrix.getNcol(); ++j ) {
      std::cout << i*j << '\t';
      matrix.getValue(i, j) = i*j;
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  auto submatrix = matrix.getBlock(1, 2, 3, 4);
  for ( auto i = 0; i < submatrix.getNrow(); ++i ) {
    for ( auto j = 0; j < submatrix.getNcol(); ++j ) {
      std::cout << submatrix.getValue(i, j) << '\t';
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  // std::cout << *(matrix->getData());
}
