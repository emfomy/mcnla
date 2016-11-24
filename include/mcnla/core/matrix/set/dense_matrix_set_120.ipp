////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/set/dense_matrix_set_120.ipp
/// @brief   The implementation of the dense matrix set with dimension order [1 2 0].
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_SET_DENSE_MATRIX_SET_120_IPP_
#define MCNLA_CORE_MATRIX_SET_DENSE_MATRIX_SET_120_IPP_

#include <mcnla/core/matrix/set/dense_matrix_set_120.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <class _Scalar>
DenseMatrixSet120<_Scalar>::DenseMatrixSet120() noexcept
  : BaseType(),
    DataType(),
    ncol_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Scalar>
DenseMatrixSet120<_Scalar>::DenseMatrixSet120(
    const index_t nrow,
    const index_t ncol,
    const index_t nmat
) noexcept
  : BaseType(),
    DataType(nrow, ncol*nmat),
    ncol_(ncol) {
  mcnla_assert_ge(nrow, 0);
  mcnla_assert_ge(ncol, 0);
  mcnla_assert_ge(nmat, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixSetBase::getNrow
///
template <class _Scalar>
index_t DenseMatrixSet120<_Scalar>::getNrowImpl() const noexcept { return DataType::nrow_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixSetBase::getNcol
///
template <class _Scalar>
index_t DenseMatrixSet120<_Scalar>::getNcolImpl() const noexcept { return ncol_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixSetBase::getNmat
///
template <class _Scalar>
index_t DenseMatrixSet120<_Scalar>::getNmatImpl() const noexcept { return DataType::ncol_ / ncol_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixSetBase::getMatrix
///
template <class _Scalar>
DenseMatrix<_Scalar, Layout::ROWMAJOR> DenseMatrixSet120<_Scalar>::getMatrixImpl( const index_t idx ) noexcept {
  mcnla_assert_gelt(idx, 0, this->getNmat());
  return DataType::getCols({idx*ncol_, (idx+1)*ncol_});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixSetBase::getMatrix
///
template <class _Scalar>
const DenseMatrix<_Scalar, Layout::ROWMAJOR> DenseMatrixSet120<_Scalar>::getMatrixImpl( const index_t idx ) const noexcept {
  mcnla_assert_gelt(idx, 0, this->getNmat());
  return DataType::getCols({idx*ncol_, (idx+1)*ncol_});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Unfold the set.
///
template <class _Scalar>
DenseMatrix<_Scalar, Layout::ROWMAJOR> DenseMatrixSet120<_Scalar>::unfold() noexcept { return *this; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  unfold
///
template <class _Scalar>
const DenseMatrix<_Scalar, Layout::ROWMAJOR> DenseMatrixSet120<_Scalar>::unfold() const noexcept { return *this; }

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_SET_DENSE_MATRIX_SET_120_IPP_
