////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_matrix.ipp
/// @brief   The implementation of dense matrix.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_MATRIX_IPP_
#define ISVD_MATRIX_DENSE_MATRIX_IPP_

#include <isvd/matrix/dense_matrix.hpp>
#include <isvd/utility/memory.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Construct with given size information.
///
template <typename _Type, Layout _layout>
DenseMatrix<_Type, _layout>::DenseMatrix() noexcept
  : Matrix<DataType>(new DataType()) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Construct with given size information.
///
template <typename _Type, Layout _layout>
DenseMatrix<_Type, _layout>::DenseMatrix(
    const index_t nrow,
    const index_t ncol
) noexcept
  : Matrix<DataType>(new DataType(nrow, ncol)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Construct with given size information.
///
template <typename _Type, Layout _layout>
DenseMatrix<_Type, _layout>::DenseMatrix(
    const index_t nrow,
    const index_t ncol,
    const index_t pitch
) noexcept
  : Matrix<DataType>(new DataType(nrow, ncol, pitch)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Construct with given raw data.
///
/// @attention  DO NOT FREE #value!!
///
template <typename _Type, Layout _layout>
DenseMatrix<_Type, _layout>::DenseMatrix(
    const index_t nrow,
    const index_t ncol,
    const index_t pitch,
    _Type *&value
) noexcept
  : Matrix<DataType>(new DataType(nrow, ncol, pitch, value)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the storage layout.
///
template <typename _Type, Layout _layout>
Layout DenseMatrix<_Type, _layout>::getLayout() const noexcept { return this.data_->_layout; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the number of rows.
///
template <typename _Type, Layout _layout>
index_t DenseMatrix<_Type, _layout>::getNrow() const noexcept { return this.data_->getNrow(&this); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the number of columns.
///
template <typename _Type, Layout _layout>
index_t DenseMatrix<_Type, _layout>::getNcol() const noexcept { return this.data_->getNcol(&this); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the leading dimension.
///
template <typename _Type, Layout _layout>
index_t DenseMatrix<_Type, _layout>::getPitch() const noexcept { return this.data_->pitch_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the number of columns.
///
template <typename _Type, Layout _layout>
_Type* DenseMatrix<_Type, _layout>::getValue() const noexcept { return this.data_->value_; }

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_MATRIX_IPP_
