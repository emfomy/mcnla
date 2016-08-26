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
template class isvd::impl::DenseBase<isvd::DenseMatrix<double>>;
template class isvd::impl::DenseMatrixBase<isvd::DenseMatrix<double>>;

template class isvd::DenseVector<double>;
template class isvd::impl::VectorBase<isvd::DenseVector<double>>;
template class isvd::impl::DenseBase<isvd::DenseVector<double>>;
template class isvd::impl::DenseVectorBase<isvd::DenseVector<double>>;

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
      matrix.getValue(i, j) = i*j;
    }
  }
  std::cout << matrix << std::endl;
  std::cout << matrix.getBlock(1, 2, 3, 4) << std::endl;
  std::cout << matrix.getRow(1, 2, 3) << std::endl;

  isvd::DenseVector<double> vector(10, 2);
  for ( auto i = 0; i < vector.getLength(); ++i ) {
    vector.getValue(i) = i;
  }
  std::cout << vector << std::endl;
  std::cout << vector.getSegment(1, 2) << std::endl;
}
