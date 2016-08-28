////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_cube.ipp
/// @brief   The implementation of dense cube.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_CUBE_IPP_
#define ISVD_MATRIX_DENSE_CUBE_IPP_

#include <cstdlib>
#include <isvd/matrix/dense_cube.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>::DenseCube() noexcept
  : nrow_(0),
    ncol_(0),
    npage_(0),
    pitch_(0),
    page_pitch_(0),
    offset_(0),
    data_() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>::DenseCube(
    const index_t nrow,
    const index_t ncol,
    const index_t npage
) noexcept
  : nrow_(nrow),
    ncol_(ncol),
    npage_(npage),
    pitch_(dim1_),
    page_pitch_(pitch_ * dim2_),
    offset_(0),
    data_(page_pitch_ * npage_) {
  assert(nrow_ > 0 && ncol_ > 0 && npage > 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>::DenseCube(
    const index_t nrow,
    const index_t ncol,
    const index_t npage,
    const index_t pitch
) noexcept
  : nrow_(nrow),
    ncol_(ncol),
    npage_(npage),
    pitch_(pitch),
    page_pitch_(pitch_ * dim2_),
    offset_(0),
    data_(page_pitch_ * npage_) {
  assert(nrow_ > 0 && ncol_ > 0 && npage > 0);
  assert(pitch_ >= dim1_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>::DenseCube(
    const index_t nrow,
    const index_t ncol,
    const index_t npage,
    const index_t pitch,
    const index_t page_pitch
) noexcept
  : nrow_(nrow),
    ncol_(ncol),
    npage_(npage),
    pitch_(pitch),
    page_pitch_(page_pitch),
    offset_(0),
    data_(page_pitch_ * npage_) {
  assert(nrow_ > 0 && ncol_ > 0 && npage > 0);
  assert(pitch_ >= dim1_);
  assert(page_pitch_ >= pitch_ * dim2_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
/// @attention  DO NOT FREE @a value!!
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>::DenseCube(
    const index_t nrow,
    const index_t ncol,
    const index_t npage,
    const index_t pitch,
    const index_t page_pitch,
    _Scalar *value
) noexcept
  : nrow_(nrow),
    ncol_(ncol),
    npage_(npage),
    pitch_(pitch),
    page_pitch_(page_pitch),
    offset_(0),
    data_(page_pitch_ * npage_, value) {
  assert(nrow_ > 0 && ncol_ > 0 && npage > 0);
  assert(pitch_ >= dim1_);
  assert(page_pitch_ >= pitch_ * dim2_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
/// @attention  DO NOT FREE @a value!!
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>::DenseCube(
    const index_t nrow,
    const index_t ncol,
    const index_t npage,
    const index_t pitch,
    const index_t page_pitch,
    _Scalar *value,
    const index_t capability,
    const index_t offset
) noexcept
  : nrow_(nrow),
    ncol_(ncol),
    npage_(npage),
    pitch_(pitch),
    page_pitch_(page_pitch),
    offset_(offset),
    data_(capability, value) {
  assert(nrow_ > 0 && ncol_ > 0 && npage > 0);
  assert(pitch >= dim1_);
  assert(page_pitch_ >= pitch_ * dim2_);
  assert(capability >= page_pitch_ * npage_);
  assert(offset_ >= 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct from data storage.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>::DenseCube(
    const index_t nrow,
    const index_t ncol,
    const index_t npage,
    const index_t pitch,
    const index_t page_pitch,
    const DenseData<_Scalar> &data,
    const index_t offset
) noexcept
  : nrow_(nrow),
    ncol_(ncol),
    npage_(npage),
    pitch_(pitch),
    page_pitch_(page_pitch),
    offset_(offset),
    data_(data) {
  assert(nrow_ > 0 && ncol_ > 0 && npage > 0);
  assert(pitch >= dim1_);
  assert(page_pitch_ >= pitch_ * dim2_);
  assert(data.getCapability() >= page_pitch_ * npage_);
  assert(offset_ >= 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default destructor.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>::~DenseCube() noexcept {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::DenseCubeBase::getLayout
///
template <typename _Scalar, Layout _layout>
Layout DenseCube<_Scalar, _layout>::getLayoutImpl() const noexcept { return _layout; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::CubeBase::getNrow
///
template <typename _Scalar, Layout _layout>
index_t DenseCube<_Scalar, _layout>::getNrowImpl() const noexcept { return nrow_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::CubeBase::getNcol
///
template <typename _Scalar, Layout _layout>
index_t DenseCube<_Scalar, _layout>::getNcolImpl() const noexcept { return ncol_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::CubeBase::getNpage
///
template <typename _Scalar, Layout _layout>
index_t DenseCube<_Scalar, _layout>::getNpageImpl() const noexcept { return npage_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::DenseCubeBase::getPitch
///
template <typename _Scalar, Layout _layout>
index_t DenseCube<_Scalar, _layout>::getPitchImpl() const noexcept { return pitch_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::DenseCubeBase::getPagePitch
///
template <typename _Scalar, Layout _layout>
index_t DenseCube<_Scalar, _layout>::getPagePitchImpl() const noexcept { return page_pitch_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the offset of starting position.
///
template <typename _Scalar, Layout _layout>
index_t DenseCube<_Scalar, _layout>::getOffsetImpl() const noexcept { return offset_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::DenseBase::getData
///
template <typename _Scalar, Layout _layout>
DenseData<_Scalar>& DenseCube<_Scalar, _layout>::getDataImpl() noexcept { return data_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::DenseBase::getData
///
template <typename _Scalar, Layout _layout>
const DenseData<_Scalar>& DenseCube<_Scalar, _layout>::getDataImpl() const noexcept { return data_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::CubeBase::getElement
///
template <typename _Scalar, Layout _layout>
_Scalar& DenseCube<_Scalar, _layout>::getElementImpl(
    const index_t rowidx,
    const index_t colidx,
    const index_t pageidx
) noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colidx >= 0 && colidx < ncol_);
  assert(pageidx >= 0 && pageidx < npage_);
  return this->getValue()[getIndexInternal(rowidx, colidx, pageidx)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::CubeBase::getElement
///
template <typename _Scalar, Layout _layout>
const _Scalar& DenseCube<_Scalar, _layout>::getElementImpl(
    const index_t rowidx,
    const index_t colidx,
    const index_t pageidx
) const noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colidx >= 0 && colidx < ncol_);
  assert(pageidx >= 0 && pageidx < npage_);
  return this->getValue()[getIndexInternal(rowidx, colidx, pageidx)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::CubeBase::resize
///
/// @attention  THE NEW SPACE IS NOT INITIALIZED.
///
template <typename _Scalar, Layout _layout>
void DenseCube<_Scalar, _layout>::resizeImpl(
    const index_t nrow,
    const index_t ncol,
    const index_t npage
) noexcept {
  assert(nrow >= 0 && ncol >= 0 && npage >= 0);
  assert((isColMajor(_layout) ? (ncol * pitch_) : (nrow * pitch_)) <= page_pitch_);
  assert(npage * page_pitch_ <= data_.getCapability());
  nrow_ = nrow;
  ncol_ = ncol;
  npage_ = npage;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::DenseCubeBase::getBlock
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout> DenseCube<_Scalar, _layout>::getBlockImpl(
    const IndexRange rowrange,
    const IndexRange colrange,
    const IndexRange pagerange
) noexcept {
  assert(rowrange.start >= 0 && rowrange.end <= nrow_ && rowrange.getLength() >= 0);
  assert(colrange.start >= 0 && colrange.end <= ncol_ && colrange.getLength() >= 0);
  assert(pagerange.start >= 0 && pagerange.end <= npage_ && pagerange.getLength() >= 0);
  return DenseCube<_Scalar, _layout>(rowrange.getLength(), colrange.getLength(), pagerange.getLength(), pitch_, page_pitch_,
                                     data_, getIndexInternal(rowrange.start, colrange.start, pagerange.start));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::DenseCubeBase::getPage
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout> DenseCube<_Scalar, _layout>::getPageImpl(
    const index_t pageidx,
    const IndexRange rowrange,
    const IndexRange colrange
) noexcept {
  assert(pageidx >= 0 && pageidx <= npage_);
  assert(rowrange.start >= 0 && rowrange.end <= nrow_ && rowrange.getLength() >= 0);
  assert(colrange.start >= 0 && colrange.end <= ncol_ && colrange.getLength() >= 0);
  return DenseMatrix<_Scalar, _layout>(rowrange.getLength(), colrange.getLength(), pitch_,
                                       data_, getIndexInternal(rowrange.start, colrange.start, pageidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::DenseCubeBase::getCol
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseCube<_Scalar, _layout>::getColImpl(
    const index_t colidx,
    const index_t pageidx,
    const IndexRange rowrange
) noexcept {
  assert(colidx >= 0 && colidx <= ncol_);
  assert(pageidx >= 0 && pageidx <= npage_);
  assert(rowrange.start >= 0 && rowrange.end <= nrow_ && rowrange.getLength() >= 0);
  return DenseVector<_Scalar>(rowrange.getLength(), getColIncInternal(),
                              data_, getIndexInternal(rowrange.start, colidx, pageidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::DenseCubeBase::getRow
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseCube<_Scalar, _layout>::getRowImpl(
    const index_t rowidx,
    const index_t pageidx,
    const IndexRange colrange
) noexcept {
  assert(rowidx >= 0 && rowidx <= nrow_);
  assert(pageidx >= 0 && pageidx <= npage_);
  assert(colrange.start >= 0 && colrange.end <= ncol_ && colrange.getLength() >= 0);
  return DenseVector<_Scalar>(colrange.getLength(), getRowIncInternal(),
                              data_, getIndexInternal(rowidx, colrange.start, pageidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::DenseCubeBase::getTube
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseCube<_Scalar, _layout>::getTubeImpl(
    const index_t rowidx,
    const index_t colidx,
    const IndexRange pagerange
) noexcept {
  assert(rowidx >= 0 && rowidx <= nrow_);
  assert(colidx >= 0 && colidx <= ncol_);
  assert(pagerange.start >= 0 && pagerange.end <= npage_ && pagerange.getLength() >= 0);
  return DenseVector<_Scalar>(pagerange.getLength(), getTubeIncInternal(),
                              data_, getIndexInternal(rowidx, colidx, pagerange.start));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::DenseCubeBase::getDiagonal
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseCube<_Scalar, _layout>::getDiagonalImpl(
    const index_t pageidx, const index_t idx
) noexcept {
  assert(idx > -nrow_ && idx < ncol_);
  index_t length;
  index_t idx0;
  if ( idx < 0 ) {
    idx0 = getIndexInternal(-idx, 0, pageidx);
    if ( nrow_ + idx > ncol_ && nrow_ > ncol_ ) {
      length = ncol_;
    } else {
      length = nrow_ + idx;
    }
  } else {
    idx0 = getIndexInternal(0, idx, pageidx);
    if ( ncol_ - idx > nrow_ && ncol_ > nrow_ ) {
      length = nrow_;
    } else {
      length = ncol_ - idx;
    }
  }
  return DenseVector<_Scalar>(length, pitch_+1, data_, idx0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::DenseCubeBase::vectorize
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseCube<_Scalar, _layout>::vectorizeImpl() noexcept {
  return DenseVector<_Scalar>(page_pitch_ * npage_, 1, data_, getIndexInternal(0, 0, 0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal index of given index.
///
template <typename _Scalar, Layout _layout>
index_t DenseCube<_Scalar, _layout>::getIndexInternal(
    const index_t rowidx,
    const index_t colidx,
    const index_t pageidx
) const noexcept {
  assert(rowidx >= 0 && rowidx <= nrow_);
  assert(colidx >= 0 && colidx <= ncol_);
  assert(pageidx >= 0 && pageidx <= npage_);
  return (isColMajor(_layout) ? (rowidx + colidx * pitch_) : (colidx + rowidx * pitch_)) + pageidx * page_pitch_ + offset_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the column increment.
///
template <typename _Scalar, Layout _layout>
index_t DenseCube<_Scalar, _layout>::getColIncInternal() const noexcept {
  return isColMajor(_layout) ? 1 : pitch_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the row increment.
///
template <typename _Scalar, Layout _layout>
index_t DenseCube<_Scalar, _layout>::getRowIncInternal() const noexcept {
  return isColMajor(_layout) ? pitch_ : 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the tube increment.
///
template <typename _Scalar, Layout _layout>
index_t DenseCube<_Scalar, _layout>::getTubeIncInternal() const noexcept {
  return page_pitch_;
}

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_CUBE_IPP_
