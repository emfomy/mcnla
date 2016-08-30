////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_matrix.ipp
/// @brief   The implementation of dense matrix.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_MATRIX_IPP_
#define ISVD_MATRIX_DENSE_MATRIX_IPP_

#include <cstdlib>
#include <isvd/matrix/dense_matrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout>::DenseMatrix() noexcept
  : MatrixBaseType(),
    DenseBaseType(),
    pitch_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout>::DenseMatrix(
    const index_t nrow,
    const index_t ncol
) noexcept
  : MatrixBaseType(nrow, ncol),
    DenseBaseType(dim1_ * dim2_),
    pitch_(dim1_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout>::DenseMatrix(
    const index_t nrow,
    const index_t ncol,
    const index_t pitch
) noexcept
  : MatrixBaseType(nrow, ncol),
    DenseBaseType(pitch * dim2_),
    pitch_(pitch) {
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
  : MatrixBaseType(nrow, ncol),
    DenseBaseType(pitch * dim2_, value),
    pitch_(pitch) {
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
    std::shared_ptr<_Scalar> value
) noexcept
  : MatrixBaseType(nrow, ncol),
    DenseBaseType(pitch * dim2_, value),
    pitch_(pitch) {
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
  : MatrixBaseType(nrow, ncol),
    DenseBaseType(capability, value, offset),
    pitch_(pitch) {
  assert(pitch_ >= dim1_);
  assert(capability >= pitch_ * dim2_);
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
    std::shared_ptr<_Scalar> value,
    const index_t capability,
    const index_t offset
) noexcept
  : MatrixBaseType(nrow, ncol),
    DenseBaseType(capability, value, offset),
    pitch_(pitch) {
  assert(pitch_ >= dim1_);
  assert(capability >= pitch_ * dim2_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct from data storage.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout>::DenseMatrix(
    const index_t nrow,
    const index_t ncol,
    const index_t pitch,
    const DenseData<_Scalar> &data,
    const index_t offset
) noexcept
  : MatrixBaseType(nrow, ncol),
    DenseBaseType(data, offset),
    pitch_(pitch) {
  assert(pitch_ >= dim1_);
  assert(data.getCapability() >= pitch_ * dim2_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default destructor.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout>::~DenseMatrix() noexcept {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Print to stream.
///
template <typename __Scalar, Layout __layout>
std::ostream& operator<< ( std::ostream &out, const DenseMatrix<__Scalar, __layout> &matrix ) {
  for ( auto i = 0; i < matrix.nrow_; ++i ) {
    for ( auto j = 0; j < matrix.ncol_; ++j ) {
      out << matrix(i, j) << '\t';
    }
    out << std::endl;
  }
  return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the leading dimension.
///
template <typename _Scalar, Layout _layout>
index_t DenseMatrix<_Scalar, _layout>::getPitch() const noexcept { return pitch_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element of given index.
///
template <typename _Scalar, Layout _layout>
_Scalar& DenseMatrix<_Scalar, _layout>::getElement(
    const index_t rowidx,
    const index_t colidx
) noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colidx >= 0 && colidx < ncol_);
  return this->getValue()[getIndexInternal(rowidx, colidx)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElement
///
template <typename _Scalar, Layout _layout>
const _Scalar& DenseMatrix<_Scalar, _layout>::getElement(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colidx >= 0 && colidx < ncol_);
  return this->getValue()[getIndexInternal(rowidx, colidx)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElement
///
template <typename _Scalar, Layout _layout>
_Scalar& DenseMatrix<_Scalar, _layout>::operator()(
    const index_t rowidx,
    const index_t colidx
) noexcept { return getElement(rowidx, colidx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElement
///
template <typename _Scalar, Layout _layout>
const _Scalar& DenseMatrix<_Scalar, _layout>::operator()(
    const index_t rowidx,
    const index_t colidx
) const noexcept { return getElement(rowidx, colidx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the transpose of the matrix.
///
/// @attention  THE STORAGE LAYOUT IS ALSO CHANGED.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, changeLayout(_layout)> DenseMatrix<_Scalar, _layout>::transpose() noexcept {
  return DenseMatrix<_Scalar, changeLayout(_layout)>(ncol_, nrow_, pitch_, data_, offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Resize the matrix.
///
/// @attention  THE NEW SPACE IS NOT INITIALIZED.
///
template <typename _Scalar, Layout _layout>
void DenseMatrix<_Scalar, _layout>::resize(
    const index_t nrow,
    const index_t ncol
) noexcept {
  assert(nrow > 0 && ncol > 0);
  assert(isColMajor(_layout) ? ncol : nrow <= pitch_);
  assert((isColMajor(_layout) ? (ncol * pitch_) : (nrow * pitch_)) <= data_.getCapability());
  nrow_ = nrow;
  ncol_ = ncol;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a matrix block.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout> DenseMatrix<_Scalar, _layout>::getBlock(
    const IndexRange rowrange,
    const IndexRange colrange
) noexcept {
  assert(rowrange.start >= 0 && rowrange.end <= nrow_ && rowrange.getLength() > 0);
  assert(colrange.start >= 0 && colrange.end <= ncol_ && colrange.getLength() > 0);
  return DenseMatrix<_Scalar, _layout>(rowrange.getLength(), colrange.getLength(), pitch_, data_,
                                       getIndexInternal(rowrange.start, colrange.start));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a matrix block.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout> DenseMatrix<_Scalar, _layout>::getCols(
    const IndexRange colrange
) noexcept {
  assert(colrange.start >= 0 && colrange.end <= ncol_ && colrange.getLength() > 0);
  return DenseMatrix<_Scalar, _layout>(nrow_, colrange.getLength(), pitch_, data_, getIndexInternal(0, colrange.start));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a matrix block.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout> DenseMatrix<_Scalar, _layout>::getRows(
    const IndexRange rowrange
) noexcept {
  assert(rowrange.start >= 0 && rowrange.end <= nrow_ && rowrange.getLength() > 0);
  return DenseMatrix<_Scalar, _layout>(rowrange.getLength(), ncol_, pitch_, data_, getIndexInternal(rowrange.start, 0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseMatrix<_Scalar, _layout>::getCol(
    const index_t colidx
) noexcept {
  assert(colidx >= 0 && colidx < ncol_);
  return DenseVector<_Scalar>(nrow_, getColIncInternal(), data_, getIndexInternal(0, colidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getCol
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseMatrix<_Scalar, _layout>::getCol(
    const index_t colidx,
    const IndexRange rowrange
) noexcept {
  assert(colidx >= 0 && colidx < ncol_);
  assert(rowrange.start >= 0 && rowrange.end <= nrow_ && rowrange.getLength() > 0);
  return DenseVector<_Scalar>(rowrange.getLength(), getColIncInternal(), data_, getIndexInternal(rowrange.start, colidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseMatrix<_Scalar, _layout>::getRow(
    const index_t rowidx
) noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  return DenseVector<_Scalar>(ncol_, getRowIncInternal(), data_, getIndexInternal(rowidx, 0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getRow
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseMatrix<_Scalar, _layout>::getRow(
    const index_t rowidx,
    const IndexRange colrange
) noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colrange.start >= 0 && colrange.end <= ncol_ && colrange.getLength() > 0);
  return DenseVector<_Scalar>(colrange.getLength(), getRowIncInternal(), data_, getIndexInternal(rowidx, colrange.start));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a diagonal vector.
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseMatrix<_Scalar, _layout>::getDiagonal(
    const index_t idx
) noexcept {
  assert(idx > -nrow_ && idx < ncol_);
  index_t length;
  index_t idx0;
  if ( idx < 0 ) {
    idx0 = getIndexInternal(-idx, 0);
    if ( nrow_ + idx > ncol_ && nrow_ > ncol_ ) {
      length = ncol_;
    } else {
      length = nrow_ + idx;
    }
  } else {
    idx0 = getIndexInternal(0, idx);
    if ( ncol_ - idx > nrow_ && ncol_ > nrow_ ) {
      length = nrow_;
    } else {
      length = ncol_ - idx;
    }
  }
  return DenseVector<_Scalar>(length, pitch_+1, data_, idx0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Vectorize the matrix.
///
/// @attention  !!!
///
/// @todo  Finish the description of the attention.
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseMatrix<_Scalar, _layout>::vectorize() noexcept {
  return DenseVector<_Scalar>(pitch_ * dim2_, 1, data_, getIndexInternal(0, 0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal index of given index.
///
template <typename _Scalar, Layout _layout>
index_t DenseMatrix<_Scalar, _layout>::getIndexInternal(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colidx >= 0 && colidx < ncol_);
  return isColMajor(_layout) ? (rowidx + colidx * pitch_) : (colidx + rowidx * pitch_) + offset_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the column increment.
///
template <typename _Scalar, Layout _layout>
index_t DenseMatrix<_Scalar, _layout>::getColIncInternal() const noexcept {
  return isColMajor(_layout) ? 1 : pitch_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the row increment.
///
template <typename _Scalar, Layout _layout>
index_t DenseMatrix<_Scalar, _layout>::getRowIncInternal() const noexcept {
  return isColMajor(_layout) ? pitch_ : 1;
}

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_MATRIX_IPP_
