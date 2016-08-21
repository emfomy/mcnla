////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    main/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#include <iostream>
#include <isvd.hpp>

template class isvd::impl::DenseMatrixData<double, isvd::Layout::COLMAJOR>;
template class isvd::impl::DenseBlockData<double, isvd::Layout::COLMAJOR>;
template class isvd::DenseMatrix<double>;
template class isvd::DenseBlock<double>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main() {
  std::cout << "iSVD "
            << ISVD_VERSION_MAJOR << "."
            << ISVD_VERSION_MINOR << "."
            << ISVD_VERSION_PATCH << " test" << std::endl << std::endl;

  isvd::DenseMatrix<double> matrix(10, 20, 30);
  for ( auto i = 0; i < matrix->getNrow(); ++i ) {
    for ( auto j = 0; j < matrix->getNcol(); ++j ) {
      matrix->getValue(i, j) = i*j;
    }
  }
  isvd::impl::DenseMatrixData<double, isvd::Layout::COLMAJOR>* data = *matrix;
  // std::cout << *(matrix->getData());
}
