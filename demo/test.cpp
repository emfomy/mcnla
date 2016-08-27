////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    main/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#include <iostream>
#include <isvd.hpp>

template class isvd::DenseVector<double>;
template class isvd::internal::VectorBase<isvd::DenseVector<double>>;
template class isvd::internal::DenseBase<isvd::DenseVector<double>>;
template class isvd::internal::DenseVectorBase<isvd::DenseVector<double>>;

template class isvd::DenseMatrix<double>;
template class isvd::internal::MatrixBase<isvd::DenseMatrix<double>>;
template class isvd::internal::DenseBase<isvd::DenseMatrix<double>>;
template class isvd::internal::DenseMatrixBase<isvd::DenseMatrix<double>>;

template class isvd::DenseCube<double>;
template class isvd::internal::CubeBase<isvd::DenseCube<double>>;
template class isvd::internal::DenseBase<isvd::DenseCube<double>>;
template class isvd::internal::DenseCubeBase<isvd::DenseCube<double>>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main() {
  std::cout << "iSVD "
            << ISVD_VERSION_MAJOR << "."
            << ISVD_VERSION_MINOR << "."
            << ISVD_VERSION_PATCH << " test" << std::endl << std::endl;

  isvd::DenseVector<double> vector(10, 2);
  for ( auto i = 0; i < vector.getLength(); ++i ) {
    vector(i) = i;
  }
  std::cout << vector << std::endl;
  std::cout << vector.getSegment({1, 2}) << std::endl;

  isvd::DenseMatrix<double> matrix(10, 20, 30);
  for ( auto i = 0; i < matrix.getNrow(); ++i ) {
    for ( auto j = 0; j < matrix.getNcol(); ++j ) {
      matrix(i, j) = i*j;
    }
  }
  std::cout << matrix << std::endl;
  std::cout << matrix.getBlock(isvd::IndexRange::FULL, {3, 5}) << std::endl;
  std::cout << matrix.getRow(1, {3, 5}) << std::endl;
  std::cout << matrix.getCol(2, {4, 6}) << std::endl;
  std::cout << matrix.getDiagonal() << std::endl;
  std::cout << matrix.getDiagonal(-2) << std::endl;
  std::cout << matrix.getDiagonal(2) << std::endl;
  std::cout << matrix.getDiagonal(12) << std::endl;

  matrix.resize(20, 10);
  for ( auto i = 0; i < matrix.getNrow(); ++i ) {
    for ( auto j = 0; j < matrix.getNcol(); ++j ) {
      matrix(i, j) = i*j;
    }
  }
  std::cout << matrix << std::endl;
  std::cout << matrix.getBlock({1, 2}, {3, 4}) << std::endl;
  std::cout << matrix.getRow(1, {3, 5}) << std::endl;
  std::cout << matrix.getCol(2, {4, 6}) << std::endl;
  std::cout << matrix.getDiagonal() << std::endl;
  std::cout << matrix.getDiagonal(-12) << std::endl;
  std::cout << matrix.getDiagonal(-2) << std::endl;
  std::cout << matrix.getDiagonal(2) << std::endl;

  isvd::DenseCube<double> cube(5, 10, 15);
  for ( auto i = 0; i < cube.getNrow(); ++i ) {
    for ( auto j = 0; j < cube.getNcol(); ++j ) {
      for ( auto k = 0; k < cube.getNpage(); ++k ) {
        cube(i, j, k) = i*j*k;
      }
    }
  }
  std::cout << cube.getPage(1) << std::endl;
}
