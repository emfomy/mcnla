////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_matrix_data.ipp
/// @brief   The implementation of dense matrix data storage.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_MATRIX_DATA_IPP_
#define ISVD_MATRIX_DENSE_MATRIX_DATA_IPP_

#include <isvd/matrix/dense_matrix.hpp>
#include <isvd/matrix/dense_block.hpp>
#include <isvd/utility/memory.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The implementation namespace.
//
namespace impl {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Default constructor.
///
template <typename _Scalar, Layout _layout>
DenseMatrixData<_Scalar, _layout>::DenseMatrixData() noexcept
  : nrow_(0),
    ncol_(0),
    pitch_(0),
    value_(nullptr) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Construct with given size information.
///
template <typename _Scalar, Layout _layout>
DenseMatrixData<_Scalar, _layout>::DenseMatrixData(
    const index_t nrow,
    const index_t ncol
) noexcept
  : nrow_(nrow),
    ncol_(ncol),
    pitch_(dim1_),
    value_(Malloc<_Scalar>(pitch_ * dim2_)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Construct with given size information.
///
template <typename _Scalar, Layout _layout>
DenseMatrixData<_Scalar, _layout>::DenseMatrixData(
    const index_t nrow,
    const index_t ncol,
    const index_t pitch
) noexcept
  : nrow_(nrow),
    ncol_(ncol),
    pitch_(pitch),
    value_(Malloc<_Scalar>(pitch_ * dim2_)) {
  assert(pitch_ >= dim1_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Construct with given raw data.
///
/// @attention  DO NOT FREE @a value!!
///
template <typename _Scalar, Layout _layout>
DenseMatrixData<_Scalar, _layout>::DenseMatrixData(
    const index_t nrow,
    const index_t ncol,
    const index_t pitch,
    _Scalar *value
) noexcept
  : nrow_(nrow),
    ncol_(ncol),
    pitch_(pitch),
    value_(value) {
  assert(pitch_ >= dim1_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Default destructor.
///
template <typename _Scalar, Layout _layout>
DenseMatrixData<_Scalar, _layout>::~DenseMatrixData() noexcept {
  Free(value_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the storage layout.
///
template <typename _Scalar, Layout _layout>
Layout DenseMatrixData<_Scalar, _layout>::getLayout() const noexcept { return _layout; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the number of rows.
///
template <typename _Scalar, Layout _layout>
index_t DenseMatrixData<_Scalar, _layout>::getNrow() const noexcept { return nrow_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the number of columns.
///
template <typename _Scalar, Layout _layout>
index_t DenseMatrixData<_Scalar, _layout>::getNcol() const noexcept { return ncol_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the leading dimension.
///
template <typename _Scalar, Layout _layout>
index_t DenseMatrixData<_Scalar, _layout>::getPitch() const noexcept { return pitch_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the raw value array.
///
template <typename _Scalar, Layout _layout>
_Scalar* DenseMatrixData<_Scalar, _layout>::getValue() noexcept { return value_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the raw value array.
///
template <typename _Scalar, Layout _layout>
const _Scalar* DenseMatrixData<_Scalar, _layout>::getValue() const noexcept { return value_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the value of given index.
///
template <typename _Scalar, Layout _layout>
_Scalar& DenseMatrixData<_Scalar, _layout>::getValue(
    const index_t rowid,
    const index_t colid
) noexcept {
  assert(rowid >= 0 && rowid < nrow_);
  assert(colid >= 0 && colid < ncol_);
  return value_[(_layout == Layout::COLMAJOR) ? (rowid + colid * pitch_) : (colid + rowid * pitch_)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the value of given index.
///
template <typename _Scalar, Layout _layout>
const _Scalar& DenseMatrixData<_Scalar, _layout>::getValue(
    const index_t rowid,
    const index_t colid
) const noexcept {
  assert(rowid >= 0 && rowid < nrow_);
  assert(colid >= 0 && colid < ncol_);
  return value_[(_layout == Layout::COLMAJOR) ? (rowid + colid * pitch_) : (colid + rowid * pitch_)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets a block matrix.
///
template <typename _Scalar, Layout _layout>
DenseBlockData<_Scalar, _layout>* DenseMatrixData<_Scalar, _layout>::getBlock() noexcept {
  return new DenseBlockData<_Scalar, _layout>(nrow_, ncol_, pitch_, value_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets a block matrix.
///
template <typename _Scalar, Layout _layout>
DenseBlockData<_Scalar, _layout>* DenseMatrixData<_Scalar, _layout>::getBlock(
    const index_t rowid,
    const index_t colid,
    const index_t nrow,
    const index_t ncol
) noexcept {
  assert(rowid >= 0 && rowid + nrow <= nrow_);
  assert(colid >= 0 && colid + ncol <= ncol_);
  return new DenseBlockData<_Scalar, _layout>(nrow, ncol, pitch_, &getValue(rowid, colid));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets a block matrix.
///
template <typename _Scalar, Layout _layout>
DenseBlockData<_Scalar, _layout>* DenseMatrixData<_Scalar, _layout>::getRows(
    const index_t rowid,
    const index_t nrow
) noexcept {
  assert(rowid >= 0 && rowid + nrow <= nrow_);
  return new DenseBlockData<_Scalar, _layout>(nrow, ncol_, pitch_, &getValue(rowid, 0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets a block matrix.
///
template <typename _Scalar, Layout _layout>
DenseBlockData<_Scalar, _layout>* DenseMatrixData<_Scalar, _layout>::getCols(
    const index_t colid,
    const index_t ncol
) noexcept {
  assert(colid >= 0 && colid + ncol <= ncol_);
  return new DenseBlockData<_Scalar, _layout>(nrow_, ncol, pitch_, &getValue(0, colid));
}

}  // namespace impl

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_MATRIX_DATA_IPP_
