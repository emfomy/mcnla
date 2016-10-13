////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_matrix.ipp
/// @brief   The implementation of dense matrix.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_IPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_IPP_

#include <mcnla/core/matrix/dense/dense_matrix.hpp>
#include <iomanip>

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
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout>::DenseMatrix() noexcept
  : MatrixBaseType(),
    DenseBaseType(),
    pitch_(1) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout>::DenseMatrix(
    const index_t nrow,
    const index_t ncol
) noexcept
  : MatrixBaseType(nrow, ncol),
    DenseBaseType(size0_ * size1_),
    pitch_(size0_) {
  assert(pitch_ > 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout>::DenseMatrix(
    const std::pair<index_t, index_t> sizes
) noexcept
  : DenseMatrix(sizes.first, sizes.second) {}

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
    DenseBaseType(pitch * size1_),
    pitch_(pitch) {
  assert(pitch_ >= size0_);
  assert(pitch_ > 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout>::DenseMatrix(
    const std::pair<index_t, index_t> sizes,
    const index_t pitch
) noexcept
  : DenseMatrix(sizes.first, sizes.second, pitch) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout>::DenseMatrix(
    const index_t nrow,
    const index_t ncol,
    const index_t pitch,
    const index_t capacity
) noexcept
  : MatrixBaseType(nrow, ncol),
    DenseBaseType(capacity),
    pitch_(pitch) {
  assert(pitch_ >= size0_);
  assert(pitch_ > 0);
  assert(capacity >= pitch_ * size1_ - (pitch_-size0_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout>::DenseMatrix(
    const std::pair<index_t, index_t> sizes,
    const index_t pitch,
    const index_t capacity
) noexcept
  : DenseMatrix(sizes.first, sizes.second, pitch, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout>::DenseMatrix(
    const index_t nrow,
    const index_t ncol,
    const index_t pitch,
    const ValueArrayType &value
) noexcept
  : MatrixBaseType(nrow, ncol),
    DenseBaseType(value),
    pitch_(pitch) {
  assert(pitch_ >= size0_);
  assert(pitch_ > 0);
  assert(this->getCapacity() >= pitch_ * size1_ - (pitch_-size0_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct from data storage.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout>::DenseMatrix(
    const index_t nrow,
    const index_t ncol,
    const index_t pitch,
    const DataType &data,
    const index_t offset
) noexcept
  : MatrixBaseType(nrow, ncol),
    DenseBaseType(data >> offset),
    pitch_(pitch) {
  assert(pitch_ >= size0_);
  assert(pitch_ > 0);
  assert(this->getCapacity() >= pitch_ * size1_ - (pitch_-size0_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout>::DenseMatrix( const DenseMatrix &other ) noexcept
  : MatrixBaseType(other),
    DenseBaseType(other),
    pitch_(other.pitch_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout>::DenseMatrix( DenseMatrix &&other ) noexcept
  : MatrixBaseType(std::move(other)),
    DenseBaseType(std::move(other)),
    pitch_(other.pitch_) {
  other.pitch_ = 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout>& DenseMatrix<_Scalar, _layout>::operator=( const DenseMatrix &other ) noexcept {
  MatrixBaseType::operator=(other); DenseBaseType::operator=(other); pitch_ = other.pitch_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout>& DenseMatrix<_Scalar, _layout>::operator=( DenseMatrix &&other ) noexcept {
  MatrixBaseType::operator=(std::move(other)); DenseBaseType::operator=(std::move(other));
  pitch_ = other.pitch_; other.pitch_ = 1;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Print to stream.
///
template <typename __Scalar, Layout __layout>
std::ostream& operator<< ( std::ostream &out, const DenseMatrix<__Scalar, __layout> &matrix ) {
  for ( index_t i = 0; i < matrix.nrow_; ++i ) {
    out << matrix.getRow(i);
  }
  return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the leading dimension.
///
template <typename _Scalar, Layout _layout>
index_t DenseMatrix<_Scalar, _layout>::getPitch() const noexcept { return pitch_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the dimensions is equal to the sizes.
///
template <typename _Scalar, Layout _layout>
bool DenseMatrix<_Scalar, _layout>::isShrunk() const noexcept {
  return (size0_ == pitch_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the matrix is square.
///
template <typename _Scalar, Layout _layout>
bool DenseMatrix<_Scalar, _layout>::isSquare() const noexcept {
  return (size0_ == size1_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element of given index.
///
template <typename _Scalar, Layout _layout>
_Scalar& DenseMatrix<_Scalar, _layout>::getElem(
    const index_t rowidx,
    const index_t colidx
) noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colidx >= 0 && colidx < ncol_);
  return this->getValue()[getPos(rowidx, colidx)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElem
///
template <typename _Scalar, Layout _layout>
const _Scalar& DenseMatrix<_Scalar, _layout>::getElem(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colidx >= 0 && colidx < ncol_);
  return this->getValue()[getPos(rowidx, colidx)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElem
///
template <typename _Scalar, Layout _layout>
_Scalar& DenseMatrix<_Scalar, _layout>::operator()(
    const index_t rowidx,
    const index_t colidx
) noexcept { return getElem(rowidx, colidx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElem
///
template <typename _Scalar, Layout _layout>
const _Scalar& DenseMatrix<_Scalar, _layout>::operator()(
    const index_t rowidx,
    const index_t colidx
) const noexcept { return getElem(rowidx, colidx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value valarray mask.
///
template <typename _Scalar, Layout _layout>
const std::gslice DenseMatrix<_Scalar, _layout>::getValueMask() const noexcept {
  return std::gslice(this->getOffset(), {size_t(size1_), size_t(size0_)}, {size_t(pitch_), 1});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position of given index.
///
template <typename _Scalar, Layout _layout>
index_t DenseMatrix<_Scalar, _layout>::getPos(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  return isColMajor(_layout) ? (rowidx + colidx * pitch_) : (colidx + rowidx * pitch_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the transpose of the matrix.
///
/// @attention  The storage layout is also changed.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, changeLayout(_layout)> DenseMatrix<_Scalar, _layout>::transpose() noexcept {
  return DenseMatrix<_Scalar, changeLayout(_layout)>(ncol_, nrow_, pitch_, data_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Finds the iterator to element
///
template <typename _Scalar, Layout _layout>
typename DenseMatrix<_Scalar, _layout>::IteratorType DenseMatrix<_Scalar, _layout>::find(
    const index_t rowidx,
    const index_t colidx
) noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colidx >= 0 && colidx < ncol_);
  auto itidx = isColMajor(_layout) ? (rowidx + colidx * size0_) : (colidx + rowidx * size0_);
  return IteratorType(this, itidx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  find
///
template <typename _Scalar, Layout _layout>
typename DenseMatrix<_Scalar, _layout>::ConstIteratorType DenseMatrix<_Scalar, _layout>::find(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colidx >= 0 && colidx < ncol_);
  auto itidx = isColMajor(_layout) ? (rowidx + colidx * size0_) : (colidx + rowidx * size0_);
  return ConstIteratorType(this, itidx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  find
///
template <typename _Scalar, Layout _layout>
typename DenseMatrix<_Scalar, _layout>::ConstIteratorType DenseMatrix<_Scalar, _layout>::cfind(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  return find(rowidx, colidx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Resizes the matrix.
///
/// @attention  The new space is not initialized.
///
template <typename _Scalar, Layout _layout>
void DenseMatrix<_Scalar, _layout>::resize(
    const index_t nrow,
    const index_t ncol
) noexcept {
  assert(nrow >= 0 && ncol >= 0);
  assert((isColMajor(_layout) ? nrow : ncol) <= pitch_);
  assert((isColMajor(_layout) ? (pitch_ * ncol) : (pitch_ * nrow)) <= data_.getCapacity());
  nrow_ = nrow;
  ncol_ = ncol;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a matrix block.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout> DenseMatrix<_Scalar, _layout>::getBlock(
    const IdxRange rowrange,
    const IdxRange colrange
) noexcept {
  assert(rowrange.begin >= 0 && rowrange.end <= nrow_ && rowrange.getLength() >= 0);
  assert(colrange.begin >= 0 && colrange.end <= ncol_ && colrange.getLength() >= 0);
  return MatrixType(rowrange.getLength(), colrange.getLength(), pitch_, data_, getPos(rowrange.begin, colrange.begin));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getBlock
///
template <typename _Scalar, Layout _layout>
const DenseMatrix<_Scalar, _layout> DenseMatrix<_Scalar, _layout>::getBlock(
    const IdxRange rowrange,
    const IdxRange colrange
) const noexcept {
  assert(rowrange.begin >= 0 && rowrange.end <= nrow_ && rowrange.getLength() >= 0);
  assert(colrange.begin >= 0 && colrange.end <= ncol_ && colrange.getLength() >= 0);
  return MatrixType(rowrange.getLength(), colrange.getLength(), pitch_, data_, getPos(rowrange.begin, colrange.begin));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getBlock
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout> DenseMatrix<_Scalar, _layout>::getCols(
    const IdxRange colrange
) noexcept {
  assert(colrange.begin >= 0 && colrange.end <= ncol_ && colrange.getLength() >= 0);
  return MatrixType(nrow_, colrange.getLength(), pitch_, data_, getPos(0, colrange.begin));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getCols
///
template <typename _Scalar, Layout _layout>
const DenseMatrix<_Scalar, _layout> DenseMatrix<_Scalar, _layout>::getCols(
    const IdxRange colrange
) const noexcept {
  assert(colrange.begin >= 0 && colrange.end <= ncol_ && colrange.getLength() >= 0);
  return MatrixType(nrow_, colrange.getLength(), pitch_, data_, getPos(0, colrange.begin));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getBlock
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout> DenseMatrix<_Scalar, _layout>::getRows(
    const IdxRange rowrange
) noexcept {
  assert(rowrange.begin >= 0 && rowrange.end <= nrow_ && rowrange.getLength() >= 0);
  return MatrixType(rowrange.getLength(), ncol_, pitch_, data_, getPos(rowrange.begin, 0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getRows
///
template <typename _Scalar, Layout _layout>
const DenseMatrix<_Scalar, _layout> DenseMatrix<_Scalar, _layout>::getRows(
    const IdxRange rowrange
) const noexcept {
  assert(rowrange.begin >= 0 && rowrange.end <= nrow_ && rowrange.getLength() >= 0);
  return MatrixType(rowrange.getLength(), ncol_, pitch_, data_, getPos(rowrange.begin, 0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseMatrix<_Scalar, _layout>::getCol(
    const index_t colidx
) noexcept {
  assert(colidx >= 0 && colidx < ncol_);
  return VectorType(nrow_, getColInc(), data_, getPos(0, colidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getCol
///
template <typename _Scalar, Layout _layout>
const DenseVector<_Scalar> DenseMatrix<_Scalar, _layout>::getCol(
    const index_t colidx
) const noexcept {
  assert(colidx >= 0 && colidx < ncol_);
  return VectorType(nrow_, getColInc(), data_, getPos(0, colidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getCol
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseMatrix<_Scalar, _layout>::getColSegment(
    const index_t colidx,
    const IdxRange rowrange
) noexcept {
  assert(colidx >= 0 && colidx < ncol_);
  assert(rowrange.begin >= 0 && rowrange.end <= nrow_ && rowrange.getLength() >= 0);
  return VectorType(rowrange.getLength(), getColInc(), data_, getPos(rowrange.begin, colidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getColSegment
///
template <typename _Scalar, Layout _layout>
const DenseVector<_Scalar> DenseMatrix<_Scalar, _layout>::getColSegment(
    const index_t colidx,
    const IdxRange rowrange
) const noexcept {
  assert(colidx >= 0 && colidx < ncol_);
  assert(rowrange.begin >= 0 && rowrange.end <= nrow_ && rowrange.getLength() >= 0);
  return VectorType(rowrange.getLength(), getColInc(), data_, getPos(rowrange.begin, colidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseMatrix<_Scalar, _layout>::getRow(
    const index_t rowidx
) noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  return VectorType(ncol_, getRowInc(), data_, getPos(rowidx, 0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getRow
///
template <typename _Scalar, Layout _layout>
const DenseVector<_Scalar> DenseMatrix<_Scalar, _layout>::getRow(
    const index_t rowidx
) const noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  return VectorType(ncol_, getRowInc(), data_, getPos(rowidx, 0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getRow
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseMatrix<_Scalar, _layout>::getRowSegment(
    const index_t rowidx,
    const IdxRange colrange
) noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colrange.begin >= 0 && colrange.end <= ncol_ && colrange.getLength() >= 0);
  return VectorType(colrange.getLength(), getRowInc(), data_, getPos(rowidx, colrange.begin));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getRowSegment
///
template <typename _Scalar, Layout _layout>
const DenseVector<_Scalar> DenseMatrix<_Scalar, _layout>::getRowSegment(
    const index_t rowidx,
    const IdxRange colrange
) const noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colrange.begin >= 0 && colrange.end <= ncol_ && colrange.getLength() >= 0);
  return VectorType(colrange.getLength(), getRowInc(), data_, getPos(rowidx, colrange.begin));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a diagonal vector.
///
/// @note @a idx > 0 for above diagonals, @a idx < 0 for below diagonals.
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseMatrix<_Scalar, _layout>::getDiagonal(
    const index_t idx
) noexcept {
  assert(idx > -nrow_ && idx < ncol_);
  index_t length;
  index_t internal_idx;
  if ( idx < 0 ) {
    internal_idx = getPos(-idx, 0);
    if ( nrow_ + idx > ncol_ && nrow_ > ncol_ ) {
      length = ncol_;
    } else {
      length = nrow_ + idx;
    }
  } else {
    internal_idx = getPos(0, idx);
    if ( ncol_ - idx > nrow_ && ncol_ > nrow_ ) {
      length = nrow_;
    } else {
      length = ncol_ - idx;
    }
  }
  return VectorType(length, pitch_+1, data_, internal_idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getDiagonal
///
template <typename _Scalar, Layout _layout>
const DenseVector<_Scalar> DenseMatrix<_Scalar, _layout>::getDiagonal(
    const index_t idx
) const noexcept {
  assert(idx > -nrow_ && idx < ncol_);
  index_t length;
  index_t internal_idx;
  if ( idx < 0 ) {
    internal_idx = getPos(-idx, 0);
    if ( nrow_ + idx > ncol_ && nrow_ > ncol_ ) {
      length = ncol_;
    } else {
      length = nrow_ + idx;
    }
  } else {
    internal_idx = getPos(0, idx);
    if ( ncol_ - idx > nrow_ && ncol_ > nrow_ ) {
      length = nrow_;
    } else {
      length = ncol_ - idx;
    }
  }
  return VectorType(length, pitch_+1, data_, internal_idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Vectorize the matrix.
///
/// @attention  The output vector contains the out-of-range spaces.
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseMatrix<_Scalar, _layout>::vectorize() noexcept {
  return VectorType(pitch_ * size1_ - (pitch_-size0_), 1, data_, getPos(0, 0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  vectorize
///
template <typename _Scalar, Layout _layout>
const DenseVector<_Scalar> DenseMatrix<_Scalar, _layout>::vectorize() const noexcept {
  return VectorType(pitch_ * size1_ - (pitch_-size0_), 1, data_, getPos(0, 0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the column stride.
///
template <typename _Scalar, Layout _layout>
index_t DenseMatrix<_Scalar, _layout>::getColInc() const noexcept {
  return isColMajor(_layout) ? 1 : pitch_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the row stride.
///
template <typename _Scalar, Layout _layout>
index_t DenseMatrix<_Scalar, _layout>::getRowInc() const noexcept {
  return isColMajor(_layout) ? pitch_ : 1;
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_IPP_
