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
  : nrow_(0),
    ncol_(0),
    pitch_(0),
    offset_(0),
    data_() {}

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
    data_(pitch_ * dim2_) {
  assert(nrow_ > 0 && ncol_ > 0);
}

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
    data_(pitch_ * dim2_) {
  assert(nrow_ > 0 && ncol_ > 0);
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
    data_(pitch_ * dim2_, value) {
  assert(nrow_ > 0 && ncol_ > 0);
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
    data_(capability, value) {
  assert(nrow_ > 0 && ncol_ > 0);
  assert(pitch >= dim1_);
  assert(capability >= pitch_ * dim2_);
  assert(offset_ >= 0);
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
  : nrow_(nrow),
    ncol_(ncol),
    pitch_(pitch),
    offset_(offset),
    data_(data) {
  assert(nrow_ > 0 && ncol_ > 0);
  assert(pitch >= dim1_);
  assert(data.getCapability() >= pitch_ * dim2_);
  assert(offset_ >= 0);
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
/// @copydoc  isvd::internal::DenseMatrixBase::getLayout
///
template <typename _Scalar, Layout _layout>
Layout DenseMatrix<_Scalar, _layout>::getLayoutImpl() const noexcept { return _layout; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::MatrixBase::getNrow
///
template <typename _Scalar, Layout _layout>
index_t DenseMatrix<_Scalar, _layout>::getNrowImpl() const noexcept { return nrow_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::MatrixBase::getNcol
///
template <typename _Scalar, Layout _layout>
index_t DenseMatrix<_Scalar, _layout>::getNcolImpl() const noexcept { return ncol_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::DenseMatrixBase::getPitch
///
template <typename _Scalar, Layout _layout>
index_t DenseMatrix<_Scalar, _layout>::getPitchImpl() const noexcept { return pitch_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::DenseBase::getOffset
///
template <typename _Scalar, Layout _layout>
index_t DenseMatrix<_Scalar, _layout>::getOffsetImpl() const noexcept { return offset_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::DenseBase::getData
///
template <typename _Scalar, Layout _layout>
DenseData<_Scalar>& DenseMatrix<_Scalar, _layout>::getDataImpl() noexcept { return data_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::DenseBase::getData
///
template <typename _Scalar, Layout _layout>
const DenseData<_Scalar>& DenseMatrix<_Scalar, _layout>::getDataImpl() const noexcept { return data_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::MatrixBase::getElement
///
template <typename _Scalar, Layout _layout>
_Scalar& DenseMatrix<_Scalar, _layout>::getElementImpl(
    const index_t rowidx,
    const index_t colidx
) noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colidx >= 0 && colidx < ncol_);
  return this->getValue()[getIndexInternal(rowidx, colidx)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::MatrixBase::getElement
///
template <typename _Scalar, Layout _layout>
const _Scalar& DenseMatrix<_Scalar, _layout>::getElementImpl(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colidx >= 0 && colidx < ncol_);
  return this->getValue()[getIndexInternal(rowidx, colidx)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::MatrixBase::resize
///
/// @attention  THE NEW SPACE IS NOT INITIALIZED.
///
template <typename _Scalar, Layout _layout>
void DenseMatrix<_Scalar, _layout>::resizeImpl(
    const index_t nrow,
    const index_t ncol
) noexcept {
  assert(nrow >= 0 && ncol >= 0);
  assert((isColMajor(_layout) ? (ncol * pitch_) : (nrow * pitch_)) <= data_.getCapability());
  nrow_ = nrow;
  ncol_ = ncol;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::DenseMatrixBase::getBlock
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout> DenseMatrix<_Scalar, _layout>::getBlockImpl(
    const IndexRange rowrange,
    const IndexRange colrange
) noexcept {
  assert(rowrange.start >= 0 && rowrange.end <= nrow_ && rowrange.getLength() >= 0);
  assert(colrange.start >= 0 && colrange.end <= ncol_ && colrange.getLength() >= 0);
  return DenseMatrix<_Scalar, _layout>(rowrange.getLength(), colrange.getLength(), pitch_, data_,
                                       getIndexInternal(rowrange.start, colrange.start));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::DenseMatrixBase::getCol
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseMatrix<_Scalar, _layout>::getColImpl(
    const index_t colidx,
    const IndexRange rowrange
) noexcept {
  assert(colidx >= 0 && colidx <= ncol_);
  assert(rowrange.start >= 0 && rowrange.end <= nrow_ && rowrange.getLength() >= 0);
  return DenseVector<_Scalar>(rowrange.getLength(), getColIncInternal(),
                              data_, getIndexInternal(rowrange.start, colidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::DenseMatrixBase::getRow
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseMatrix<_Scalar, _layout>::getRowImpl(
    const index_t rowidx,
    const IndexRange colrange
) noexcept {
  assert(rowidx >= 0 && rowidx <= nrow_);
  assert(colrange.start >= 0 && colrange.end <= ncol_ && colrange.getLength() >= 0);
  return DenseVector<_Scalar>(colrange.getLength(), getRowIncInternal(),
                              data_, getIndexInternal(rowidx, colrange.start));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::DenseMatrixBase::getDiagonal
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseMatrix<_Scalar, _layout>::getDiagonalImpl(
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
/// @copydoc  isvd::internal::DenseMatrixBase::vectorize
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseMatrix<_Scalar, _layout>::vectorizeImpl() noexcept {
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
  assert(rowidx >= 0 && rowidx <= nrow_);
  assert(colidx >= 0 && colidx <= ncol_);
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
