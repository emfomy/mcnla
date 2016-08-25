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
/// @brief  Default constructor.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout>::DenseMatrix() noexcept
  : nrow_(0),
    ncol_(0),
    pitch_(0),
    offset_(0),
    capability_(0),
    value_(nullptr) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout>::DenseMatrix(
    const index_t nrow,
    const index_t ncol
) noexcept
  : nrow_(nrow),
    ncol_(ncol),
    pitch_(dim1_),
    offset_(0),
    capability_(pitch_ * dim2_),
    value_(Malloc<_Scalar>(capability_)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout>::DenseMatrix(
    const index_t nrow,
    const index_t ncol,
    const index_t pitch
) noexcept
  : nrow_(nrow),
    ncol_(ncol),
    pitch_(pitch),
    offset_(0),
    capability_(pitch_ * dim2_),
    value_(Malloc<_Scalar>(capability_)) {
  assert(pitch_ >= dim1_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
/// @attention  DO NOT FREE @a value!!
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout>::DenseMatrix(
    const index_t nrow,
    const index_t ncol,
    const index_t pitch,
    _Scalar *value
) noexcept
  : nrow_(nrow),
    ncol_(ncol),
    pitch_(pitch),
    offset_(0),
    capability_(pitch_ * dim2_),
    value_(value) {
  assert(pitch_ >= dim1_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
/// @attention  DO NOT FREE @a value!!
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout>::DenseMatrix(
    const index_t nrow,
    const index_t ncol,
    const index_t pitch,
    _Scalar *value,
    const index_t capability,
    const index_t offset
) noexcept
  : nrow_(nrow),
    ncol_(ncol),
    pitch_(pitch),
    offset_(offset),
    capability_(capability),
    value_(value) {
  assert(capability_ >= pitch_ * dim2_);
  assert(pitch_ >= dim1_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct from another matrix.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout>::DenseMatrix(
    const DenseMatrix &other,
    const index_t nrow,
    const index_t ncol,
    const index_t offset
) noexcept
  : nrow_(nrow),
    ncol_(ncol),
    pitch_(other.pitch_),
    offset_(offset),
    capability_(other.capability_),
    value_(other.value_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default destructor.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout>::~DenseMatrix() noexcept {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the storage layout.
///
template <typename _Scalar, Layout _layout>
Layout DenseMatrix<_Scalar, _layout>::getLayoutImpl() const noexcept { return _layout; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of rows.
///
template <typename _Scalar, Layout _layout>
index_t DenseMatrix<_Scalar, _layout>::getNrowImpl() const noexcept { return nrow_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of columns.
///
template <typename _Scalar, Layout _layout>
index_t DenseMatrix<_Scalar, _layout>::getNcolImpl() const noexcept { return ncol_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the leading dimension.
///
template <typename _Scalar, Layout _layout>
index_t DenseMatrix<_Scalar, _layout>::getPitchImpl() const noexcept { return pitch_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size.
///
template <typename _Scalar, Layout _layout>
index_t DenseMatrix<_Scalar, _layout>::getSizeImpl() const noexcept { return nrow_ * ncol_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size.
///
template <typename _Scalar, Layout _layout>
index_t DenseMatrix<_Scalar, _layout>::getOffsetImpl() const noexcept { return offset_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size.
///
template <typename _Scalar, Layout _layout>
index_t DenseMatrix<_Scalar, _layout>::getCapabilityImpl() const noexcept { return capability_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw value array.
///
template <typename _Scalar, Layout _layout>
_Scalar* DenseMatrix<_Scalar, _layout>::getValueImpl() noexcept { return value_.get() + offset_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw value array.
///
template <typename _Scalar, Layout _layout>
const _Scalar* DenseMatrix<_Scalar, _layout>::getValueImpl() const noexcept { return value_.get() + offset_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value of given index.
///
template <typename _Scalar, Layout _layout>
_Scalar& DenseMatrix<_Scalar, _layout>::getValueImpl(
    const index_t rowid,
    const index_t colid
) noexcept {
  assert(rowid >= 0 && rowid < nrow_);
  assert(colid >= 0 && colid < ncol_);
  return getValueImpl()[(_layout == Layout::COLMAJOR) ? (rowid + colid * pitch_) : (colid + rowid * pitch_)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value of given index.
///
template <typename _Scalar, Layout _layout>
const _Scalar& DenseMatrix<_Scalar, _layout>::getValueImpl(
    const index_t rowid,
    const index_t colid
) const noexcept {
  assert(rowid >= 0 && rowid < nrow_);
  assert(colid >= 0 && colid < ncol_);
  return getValueImpl()[(_layout == Layout::COLMAJOR) ? (rowid + colid * pitch_) : (colid + rowid * pitch_)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a block matrix.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout> DenseMatrix<_Scalar, _layout>::getBlockImpl(
    const index_t rowid,
    const index_t colid,
    const index_t nrow,
    const index_t ncol
) noexcept {
  assert(rowid >= 0 && rowid + nrow <= nrow_);
  assert(colid >= 0 && colid + ncol <= ncol_);
  return DenseMatrix<_Scalar, _layout>(*this, nrow, ncol, &getValueImpl(rowid, colid) - getValueImpl());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a block matrix.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout> DenseMatrix<_Scalar, _layout>::getRowsImpl(
    const index_t rowid,
    const index_t nrow
) noexcept {
  return DenseMatrix<_Scalar, _layout>(*this, nrow, ncol_, &getValueImpl(rowid, 0) - getValueImpl());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a block matrix.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout> DenseMatrix<_Scalar, _layout>::getColsImpl(
    const index_t colid,
    const index_t ncol
) noexcept {
  return DenseMatrix<_Scalar, _layout>(*this, nrow_, ncol, &getValueImpl(0, colid) - getValueImpl());
}

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_MATRIX_IPP_
