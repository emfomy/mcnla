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

  isvd::DenseMatrix<double> matA(5, 5, 15);
  for ( auto i = 0; i < matA.getNrow(); ++i ) {
    for ( auto j = 0; j < matA.getNcol(); ++j ) {
      matA(i, j) = i*j*j;
    }
  }
  std::cout << matA << std::endl;

  isvd::DenseMatrix<double> matB(5, 8);
  for ( auto i = 0; i < matB.getNrow(); ++i ) {
    for ( auto j = 0; j < matB.getNcol(); ++j ) {
      matB(i, j) = i*j*j;
    }
  }
  std::cout << matB << std::endl;

  isvd::DenseMatrix<double> matC(5, 8, 10);
  isvd::blas::symm(1.0, matA, matB, 0.0, matC);
  std::cout << matC << std::endl;
}
