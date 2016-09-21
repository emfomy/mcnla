////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense/dense_cube.ipp
/// @brief   The implementation of dense cube.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DENSE_CUBE_IPP_
#define ISVD_MATRIX_DENSE_DENSE_CUBE_IPP_

#include <isvd/matrix/dense/dense_cube.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>::DenseCube() noexcept
  : CubeBaseType(),
    DenseBaseType(),
    pitch1_(1),
    pitch2_(1) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>::DenseCube(
    const index_t nrow,
    const index_t ncol,
    const index_t npage
) noexcept
  : CubeBaseType(nrow, ncol, npage),
    DenseBaseType(size1_ * size2_ * size3_),
    pitch1_(size1_),
    pitch2_(size2_) {
  assert(pitch1_ > 0 && pitch2_ > 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>::DenseCube(
    const std::tuple<index_t, index_t, index_t> sizes
) noexcept
  : DenseCube(std::get<0>(sizes), std::get<1>(sizes), std::get<2>(sizes)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>::DenseCube(
    const index_t nrow,
    const index_t ncol,
    const index_t npage,
    const index_t pitch1
) noexcept
  : CubeBaseType(nrow, ncol, npage),
    DenseBaseType(pitch1 * size2_ * size3_),
    pitch1_(pitch1),
    pitch2_(size2_) {
  assert(pitch1_ >= size1_);
  assert(pitch1_ > 0 && pitch2_ > 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>::DenseCube(
    const index_t nrow,
    const index_t ncol,
    const index_t npage,
    const index_t pitch1,
    const index_t pitch2
) noexcept
  : CubeBaseType(nrow, ncol, npage),
    DenseBaseType(pitch1 * pitch2 * size3_),
    pitch1_(pitch1),
    pitch2_(pitch2) {
  assert(pitch1_ >= size1_ && pitch2_ >= size2_);
  assert(pitch1_ > 0 && pitch2_ > 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>::DenseCube(
    const std::tuple<index_t, index_t, index_t> sizes,
    const std::pair<index_t, index_t> pitches
) noexcept
  : DenseCube(std::get<0>(sizes), std::get<1>(sizes), std::get<2>(sizes), pitches.first, pitches.second) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>::DenseCube(
    const index_t nrow,
    const index_t ncol,
    const index_t npage,
    const index_t pitch1,
    const index_t pitch2,
    const index_t capability,
    const index_t offset
) noexcept
  : CubeBaseType(nrow, ncol, npage),
    DenseBaseType(capability, offset),
    pitch1_(pitch1),
    pitch2_(pitch2) {
  assert(pitch1_ >= size1_ && pitch2_ >= size2_);
  assert(pitch1_ > 0 && pitch2_ > 0);
  assert(capability >= pitch1_ * pitch2_ * npage_ - (pitch1_-size1_) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>::DenseCube(
    const std::tuple<index_t, index_t, index_t> sizes,
    const std::pair<index_t, index_t> pitches,
    const index_t capability,
    const index_t offset
) noexcept
  : DenseCube(std::get<0>(sizes), std::get<1>(sizes), std::get<2>(sizes), pitches.first, pitches.second, capability, offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>::DenseCube(
    const index_t nrow,
    const index_t ncol,
    const index_t npage,
    const index_t pitch1,
    const index_t pitch2,
    const ValuePtrType &value,
    const index_t offset
) noexcept
  : CubeBaseType(nrow, ncol, npage),
    DenseBaseType(value, offset),
    pitch1_(pitch1),
    pitch2_(pitch2) {
  assert(pitch1_ >= size1_ && pitch2_ >= size2_);
  assert(pitch1_ > 0 && pitch2_ > 0);
  assert(this->getCapability() >= pitch1_ * pitch2_ * npage_ - (pitch1_-size1_) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct from data storage.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>::DenseCube(
    const index_t nrow,
    const index_t ncol,
    const index_t npage,
    const index_t pitch1,
    const index_t pitch2,
    const DataType &data,
    const index_t offset
) noexcept
  : CubeBaseType(nrow, ncol, npage),
    DenseBaseType(data, offset),
    pitch1_(pitch1),
    pitch2_(pitch2) {
  assert(pitch1_ >= size1_ && pitch2_ >= size2_);
  assert(pitch1_ > 0 && pitch2_ > 0);
  assert(this->getCapability() >= pitch1_ * pitch2_ * npage_ - (pitch1_-size1_) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses isvd::blas::copy.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>::DenseCube( const DenseCube &other ) noexcept
  : CubeBaseType(other),
    DenseBaseType(other),
    pitch1_(other.pitch1_),
    pitch2_(other.pitch2_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>::DenseCube( DenseCube &&other ) noexcept
  : CubeBaseType(std::move(other)),
    DenseBaseType(std::move(other)),
    pitch1_(other.pitch1_),
    pitch2_(other.pitch2_) {
  other.pitch1_ = 1; other.pitch2_ = 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses isvd::blas::copy.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>& DenseCube<_Scalar, _layout>::operator=( const DenseCube &other ) noexcept {
  CubeBaseType::operator=(other); DenseBaseType::operator=(other);
  pitch1_ = other.pitch1_; pitch2_ = other.pitch2_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>& DenseCube<_Scalar, _layout>::operator=( DenseCube &&other ) noexcept {
  CubeBaseType::operator=(std::move(other)); DenseBaseType::operator=(std::move(other));
  pitch1_ = other.pitch1_; pitch2_ = other.pitch2_;
  other.pitch1_ = 1;       other.pitch2_ = 1;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Print to stream.
///
template <typename __Scalar, Layout __layout>
std::ostream& operator<< ( std::ostream &out, const DenseCube<__Scalar, __layout> &cube ) {
  for ( index_t i = 0; i < cube.npage_; ++i ) {
    out << cube.getPage(i) << std::endl;
  }
  return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the leading dimension.
///
template <typename _Scalar, Layout _layout>
index_t DenseCube<_Scalar, _layout>::getPitch1() const noexcept { return pitch1_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the second dimension.
///
template <typename _Scalar, Layout _layout>
index_t DenseCube<_Scalar, _layout>::getPitch2() const noexcept { return pitch2_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the dimensions.
///
template <typename _Scalar, Layout _layout>
std::pair<index_t, index_t> DenseCube<_Scalar, _layout>::getPitches() const noexcept {
  return std::make_pair(pitch1_, pitch2_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the dimensions is equal to the sizes.
///
template <typename _Scalar, Layout _layout>
bool DenseCube<_Scalar, _layout>::isShrunk() const noexcept {
  return (size1_ == pitch1_ && size2_ == pitch2_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element of given index.
///
template <typename _Scalar, Layout _layout>
_Scalar& DenseCube<_Scalar, _layout>::getElem(
    const index_t rowidx,
    const index_t colidx,
    const index_t pageidx
) noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colidx >= 0 && colidx < ncol_);
  assert(pageidx >= 0 && pageidx < npage_);
  return this->getValue()[getPos(rowidx, colidx, pageidx)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElem
///
template <typename _Scalar, Layout _layout>
const _Scalar& DenseCube<_Scalar, _layout>::getElem(
    const index_t rowidx,
    const index_t colidx,
    const index_t pageidx
) const noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colidx >= 0 && colidx < ncol_);
  assert(pageidx >= 0 && pageidx < npage_);
  return this->getValue()[getPos(rowidx, colidx, pageidx)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElem
///
template <typename _Scalar, Layout _layout>
_Scalar& DenseCube<_Scalar, _layout>::operator()(
    const index_t rowidx,
    const index_t colidx,
    const index_t pageidx
) noexcept { return getElem(rowidx, colidx, pageidx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElem
///
template <typename _Scalar, Layout _layout>
const _Scalar& DenseCube<_Scalar, _layout>::operator()(
    const index_t rowidx,
    const index_t colidx,
    const index_t pageidx
) const noexcept { return getElem(rowidx, colidx, pageidx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position of given index.
///
template <typename _Scalar, Layout _layout>
index_t DenseCube<_Scalar, _layout>::getPos(
    const index_t rowidx,
    const index_t colidx,
    const index_t pageidx
) const noexcept {
  return (isColMajor(_layout) ? (rowidx + colidx * pitch1_) : (colidx + rowidx * pitch1_))
         + pageidx * pitch1_ * pitch2_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the transpose of the cube.
///
/// @attention  The storage layout is also changed.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, changeLayout(_layout)> DenseCube<_Scalar, _layout>::transpose() noexcept {
  return DenseCube<_Scalar, changeLayout(_layout)>(ncol_, nrow_, npage_, pitch1_, pitch2_, data_, offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Finds the iterator to element
///
template <typename _Scalar, Layout _layout>
typename DenseCube<_Scalar, _layout>::IteratorType DenseCube<_Scalar, _layout>::find(
    const index_t rowidx,
    const index_t colidx,
    const index_t pageidx
) noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colidx >= 0 && colidx < ncol_);
  assert(pageidx >= 0 && pageidx < npage_);
  auto itidx = (isColMajor(_layout) ? (rowidx + colidx * size1_) : (colidx + rowidx * size1_)) + pageidx * size1_ * size2_;
  return IteratorType(this, itidx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  find
///
template <typename _Scalar, Layout _layout>
typename DenseCube<_Scalar, _layout>::ConstIteratorType DenseCube<_Scalar, _layout>::find(
    const index_t rowidx,
    const index_t colidx,
    const index_t pageidx
) const noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colidx >= 0 && colidx < ncol_);
  assert(pageidx >= 0 && pageidx < npage_);
  auto itidx = (isColMajor(_layout) ? (rowidx + colidx * size1_) : (colidx + rowidx * size1_)) + pageidx * size1_ * size2_;
  return ConstIteratorType(this, itidx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  find
///
template <typename _Scalar, Layout _layout>
typename DenseCube<_Scalar, _layout>::ConstIteratorType DenseCube<_Scalar, _layout>::cfind(
    const index_t rowidx,
    const index_t colidx,
    const index_t pageidx
) const noexcept {
  return find(rowidx, colidx, pageidx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Resizes the cube.
///
/// @attention  The new space is not initialized.
///
template <typename _Scalar, Layout _layout>
void DenseCube<_Scalar, _layout>::resize(
    const index_t nrow,
    const index_t ncol,
    const index_t npage
) noexcept {
  assert(nrow >= 0 && ncol >= 0 && npage >= 0);
  assert((isColMajor(_layout) ? nrow : ncol) <= pitch1_);
  assert((isColMajor(_layout) ? ncol : nrow) <= pitch2_);
  assert(pitch1_ * pitch2_ * npage <= data_.getCapability());
  nrow_ = nrow;
  ncol_ = ncol;
  npage_ = npage;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a cube block.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout> DenseCube<_Scalar, _layout>::getCube(
    const IdxRange rowrange,
    const IdxRange colrange,
    const IdxRange pagerange
) noexcept {
  assert(rowrange.begin >= 0 && rowrange.end <= nrow_ && rowrange.getLength() >= 0);
  assert(colrange.begin >= 0 && colrange.end <= ncol_ && colrange.getLength() >= 0);
  assert(pagerange.begin >= 0 && pagerange.end <= npage_ && pagerange.getLength() >= 0);
  return DenseCube<_Scalar, _layout>(rowrange.getLength(), colrange.getLength(), pagerange.getLength(), pitch1_, pitch2_,
                                     data_, getPos(rowrange.begin, colrange.begin, pagerange.begin) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getCube
///
template <typename _Scalar, Layout _layout>
const DenseCube<_Scalar, _layout> DenseCube<_Scalar, _layout>::getCube(
    const IdxRange rowrange,
    const IdxRange colrange,
    const IdxRange pagerange
) const noexcept {
  assert(rowrange.begin >= 0 && rowrange.end <= nrow_ && rowrange.getLength() >= 0);
  assert(colrange.begin >= 0 && colrange.end <= ncol_ && colrange.getLength() >= 0);
  assert(pagerange.begin >= 0 && pagerange.end <= npage_ && pagerange.getLength() >= 0);
  return DenseCube<_Scalar, _layout>(rowrange.getLength(), colrange.getLength(), pagerange.getLength(), pitch1_, pitch2_,
                                     data_, getPos(rowrange.begin, colrange.begin, pagerange.begin) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getCube
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout> DenseCube<_Scalar, _layout>::getTubes(
    const IdxRange rowrange,
    const IdxRange colrange
) noexcept {
  assert(rowrange.begin >= 0 && rowrange.end <= nrow_ && rowrange.getLength() >= 0);
  assert(colrange.begin >= 0 && colrange.end <= ncol_ && colrange.getLength() >= 0);
  return DenseCube<_Scalar, _layout>(rowrange.getLength(), colrange.getLength(), npage_, pitch1_, pitch2_,
                                     data_, getPos(rowrange.begin, colrange.begin, 0) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getTubes
///
template <typename _Scalar, Layout _layout>
const DenseCube<_Scalar, _layout> DenseCube<_Scalar, _layout>::getTubes(
    const IdxRange rowrange,
    const IdxRange colrange
) const noexcept {
  assert(rowrange.begin >= 0 && rowrange.end <= nrow_ && rowrange.getLength() >= 0);
  assert(colrange.begin >= 0 && colrange.end <= ncol_ && colrange.getLength() >= 0);
  return DenseCube<_Scalar, _layout>(rowrange.getLength(), colrange.getLength(), npage_, pitch1_, pitch2_,
                                     data_, getPos(rowrange.begin, colrange.begin, 0) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getCube
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout> DenseCube<_Scalar, _layout>::getPages(
    const IdxRange pagerange
) noexcept {
  assert(pagerange.begin >= 0 && pagerange.end <= npage_ && pagerange.getLength() >= 0);
  return DenseCube<_Scalar, _layout>(nrow_, ncol_, pagerange.getLength(), pitch1_, pitch2_,
                                     data_, getPos(0, 0, pagerange.begin) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getPages
///
template <typename _Scalar, Layout _layout>
const DenseCube<_Scalar, _layout> DenseCube<_Scalar, _layout>::getPages(
    const IdxRange pagerange
) const noexcept {
  assert(pagerange.begin >= 0 && pagerange.end <= npage_ && pagerange.getLength() >= 0);
  return DenseCube<_Scalar, _layout>(nrow_, ncol_, pagerange.getLength(), pitch1_, pitch2_,
                                     data_, getPos(0, 0, pagerange.begin) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getCube
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout> DenseCube<_Scalar, _layout>::getColPages(
    const IdxRange colrange
) noexcept {
  assert(colrange.begin >= 0 && colrange.end <= ncol_ && colrange.getLength() >= 0);
  return DenseCube<_Scalar, _layout>(nrow_, colrange.getLength(), npage_, pitch1_, pitch2_,
                                     data_, getPos(0, colrange.begin, 0) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getColPages
///
template <typename _Scalar, Layout _layout>
const DenseCube<_Scalar, _layout> DenseCube<_Scalar, _layout>::getColPages(
    const IdxRange colrange
) const noexcept {
  assert(colrange.begin >= 0 && colrange.end <= ncol_ && colrange.getLength() >= 0);
  return DenseCube<_Scalar, _layout>(nrow_, colrange.getLength(), npage_, pitch1_, pitch2_,
                                     data_, getPos(0, colrange.begin, 0) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getCube
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout> DenseCube<_Scalar, _layout>::getRowPages(
    const IdxRange rowrange
) noexcept {
  assert(rowrange.begin >= 0 && rowrange.end <= nrow_ && rowrange.getLength() >= 0);
  return DenseCube<_Scalar, _layout>(rowrange.getLength(), ncol_, npage_, pitch1_, pitch2_,
                                     data_, getPos(rowrange.begin, 0, 0) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getRowPages
///
template <typename _Scalar, Layout _layout>
const DenseCube<_Scalar, _layout> DenseCube<_Scalar, _layout>::getRowPages(
    const IdxRange rowrange
) const noexcept {
  assert(rowrange.begin >= 0 && rowrange.end <= nrow_ && rowrange.getLength() >= 0);
  return DenseCube<_Scalar, _layout>(rowrange.getLength(), ncol_, npage_, pitch1_, pitch2_,
                                     data_, getPos(rowrange.begin, 0, 0) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a matrix block.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout> DenseCube<_Scalar, _layout>::getPage(
    const index_t pageidx
) noexcept {
  assert(pageidx >= 0 && pageidx < npage_);
  return DenseMatrix<_Scalar, _layout>(nrow_, ncol_, pitch1_, data_, getPos(0, 0, pageidx) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getPage
///
template <typename _Scalar, Layout _layout>
const DenseMatrix<_Scalar, _layout> DenseCube<_Scalar, _layout>::getPage(
    const index_t pageidx
) const noexcept {
  assert(pageidx >= 0 && pageidx < npage_);
  return DenseMatrix<_Scalar, _layout>(nrow_, ncol_, pitch1_, data_, getPos(0, 0, pageidx) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getPage
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout> DenseCube<_Scalar, _layout>::getCols(
    const index_t pageidx,
    const IdxRange colrange
) noexcept {
  assert(pageidx >= 0 && pageidx < npage_);
  assert(colrange.begin >= 0 && colrange.end <= ncol_ && colrange.getLength() >= 0);
  return DenseMatrix<_Scalar, _layout>(nrow_, colrange.getLength(), pitch1_, data_,
                                       getPos(0, colrange.begin, pageidx) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getCols
///
template <typename _Scalar, Layout _layout>
const DenseMatrix<_Scalar, _layout> DenseCube<_Scalar, _layout>::getCols(
    const index_t pageidx,
    const IdxRange colrange
) const noexcept {
  assert(pageidx >= 0 && pageidx < npage_);
  assert(colrange.begin >= 0 && colrange.end <= ncol_ && colrange.getLength() >= 0);
  return DenseMatrix<_Scalar, _layout>(nrow_, colrange.getLength(), pitch1_, data_,
                                       getPos(0, colrange.begin, pageidx) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getPage
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout> DenseCube<_Scalar, _layout>::getRows(
    const index_t pageidx,
    const IdxRange rowrange
) noexcept {
  assert(pageidx >= 0 && pageidx < npage_);
  assert(rowrange.begin >= 0 && rowrange.end <= nrow_ && rowrange.getLength() >= 0);
  return DenseMatrix<_Scalar, _layout>(rowrange.getLength(), ncol_, pitch1_, data_,
                                       getPos(rowrange.begin, 0, pageidx) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getRows
///
template <typename _Scalar, Layout _layout>
const DenseMatrix<_Scalar, _layout> DenseCube<_Scalar, _layout>::getRows(
    const index_t pageidx,
    const IdxRange rowrange
) const noexcept {
  assert(pageidx >= 0 && pageidx < npage_);
  assert(rowrange.begin >= 0 && rowrange.end <= nrow_ && rowrange.getLength() >= 0);
  return DenseMatrix<_Scalar, _layout>(rowrange.getLength(), ncol_, pitch1_, data_,
                                       getPos(rowrange.begin, 0, pageidx) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getPage
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout> DenseCube<_Scalar, _layout>::getBlock(
    const index_t pageidx,
    const IdxRange rowrange,
    const IdxRange colrange
) noexcept {
  assert(pageidx >= 0 && pageidx < npage_);
  assert(rowrange.begin >= 0 && rowrange.end <= nrow_ && rowrange.getLength() >= 0);
  assert(colrange.begin >= 0 && colrange.end <= ncol_ && colrange.getLength() >= 0);
  return DenseMatrix<_Scalar, _layout>(rowrange.getLength(), colrange.getLength(), pitch1_, data_,
                                       getPos(rowrange.begin, colrange.begin, pageidx) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getBlock
///
template <typename _Scalar, Layout _layout>
const DenseMatrix<_Scalar, _layout> DenseCube<_Scalar, _layout>::getBlock(
    const index_t pageidx,
    const IdxRange rowrange,
    const IdxRange colrange
) const noexcept {
  assert(pageidx >= 0 && pageidx < npage_);
  assert(rowrange.begin >= 0 && rowrange.end <= nrow_ && rowrange.getLength() >= 0);
  assert(colrange.begin >= 0 && colrange.end <= ncol_ && colrange.getLength() >= 0);
  return DenseMatrix<_Scalar, _layout>(rowrange.getLength(), colrange.getLength(), pitch1_, data_,
                                       getPos(rowrange.begin, colrange.begin, pageidx) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Unfold the cube.
///
/// @attention  The output matrix contains the out-of-range spaces in the second dimension.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout> DenseCube<_Scalar, _layout>::unfold() noexcept {
  if ( isColMajor(_layout) ) {
    return DenseMatrix<_Scalar, _layout>(nrow_, pitch2_ * npage_, pitch1_, data_, getPos(0, 0, 0) + offset_);
  } else {
    return DenseMatrix<_Scalar, _layout>(pitch2_ * npage_, ncol_, pitch1_, data_, getPos(0, 0, 0) + offset_);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  unfold
///
template <typename _Scalar, Layout _layout>
const DenseMatrix<_Scalar, _layout> DenseCube<_Scalar, _layout>::unfold() const noexcept {
  if ( isColMajor(_layout) ) {
    return DenseMatrix<_Scalar, _layout>(nrow_, pitch2_ * npage_, pitch1_, data_, getPos(0, 0, 0) + offset_);
  } else {
    return DenseMatrix<_Scalar, _layout>(pitch2_ * npage_, ncol_, pitch1_, data_, getPos(0, 0, 0) + offset_);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseCube<_Scalar, _layout>::getCol(
    const index_t colidx,
    const index_t pageidx
) noexcept {
  assert(colidx >= 0 && colidx < ncol_);
  assert(pageidx >= 0 && pageidx < npage_);
  return DenseVector<_Scalar>(nrow_, getColInc(), data_, getPos(0, colidx, pageidx) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getCol
///
template <typename _Scalar, Layout _layout>
const DenseVector<_Scalar> DenseCube<_Scalar, _layout>::getCol(
    const index_t colidx,
    const index_t pageidx
) const noexcept {
  assert(colidx >= 0 && colidx < ncol_);
  assert(pageidx >= 0 && pageidx < npage_);
  return DenseVector<_Scalar>(nrow_, getColInc(), data_, getPos(0, colidx, pageidx) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getCol
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseCube<_Scalar, _layout>::getColSegment(
    const index_t colidx,
    const index_t pageidx,
    const IdxRange rowrange
) noexcept {
  assert(colidx >= 0 && colidx < ncol_);
  assert(pageidx >= 0 && pageidx < npage_);
  assert(rowrange.begin >= 0 && rowrange.end <= nrow_ && rowrange.getLength() >= 0);
  return DenseVector<_Scalar>(rowrange.getLength(), getColInc(),
                              data_, getPos(rowrange.begin, colidx, pageidx) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getColSegment
///
template <typename _Scalar, Layout _layout>
const DenseVector<_Scalar> DenseCube<_Scalar, _layout>::getColSegment(
    const index_t colidx,
    const index_t pageidx,
    const IdxRange rowrange
) const noexcept {
  assert(colidx >= 0 && colidx < ncol_);
  assert(pageidx >= 0 && pageidx < npage_);
  assert(rowrange.begin >= 0 && rowrange.end <= nrow_ && rowrange.getLength() >= 0);
  return DenseVector<_Scalar>(rowrange.getLength(), getColInc(),
                              data_, getPos(rowrange.begin, colidx, pageidx) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseCube<_Scalar, _layout>::getRow(
    const index_t rowidx,
    const index_t pageidx
) noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(pageidx >= 0 && pageidx < npage_);
  return DenseVector<_Scalar>(ncol_, getRowInc(), data_, getPos(rowidx, 0, pageidx) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getRow
///
template <typename _Scalar, Layout _layout>
const DenseVector<_Scalar> DenseCube<_Scalar, _layout>::getRow(
    const index_t rowidx,
    const index_t pageidx
) const noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(pageidx >= 0 && pageidx < npage_);
  return DenseVector<_Scalar>(ncol_, getRowInc(), data_, getPos(rowidx, 0, pageidx) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getRow
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseCube<_Scalar, _layout>::getRowSegment(
    const index_t rowidx,
    const index_t pageidx,
    const IdxRange colrange
) noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(pageidx >= 0 && pageidx < npage_);
  assert(colrange.begin >= 0 && colrange.end <= ncol_ && colrange.getLength() >= 0);
  return DenseVector<_Scalar>(colrange.getLength(), getRowInc(),
                              data_, getPos(rowidx, colrange.begin, pageidx) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getRowSegment
///
template <typename _Scalar, Layout _layout>
const DenseVector<_Scalar> DenseCube<_Scalar, _layout>::getRowSegment(
    const index_t rowidx,
    const index_t pageidx,
    const IdxRange colrange
) const noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(pageidx >= 0 && pageidx < npage_);
  assert(colrange.begin >= 0 && colrange.end <= ncol_ && colrange.getLength() >= 0);
  return DenseVector<_Scalar>(colrange.getLength(), getRowInc(),
                              data_, getPos(rowidx, colrange.begin, pageidx) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseCube<_Scalar, _layout>::getTube(
    const index_t rowidx,
    const index_t colidx
) noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colidx >= 0 && colidx < ncol_);
  return DenseVector<_Scalar>(npage_, getTubeInc(), data_, getPos(rowidx, colidx, 0) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getTube
///
template <typename _Scalar, Layout _layout>
const DenseVector<_Scalar> DenseCube<_Scalar, _layout>::getTube(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colidx >= 0 && colidx < ncol_);
  return DenseVector<_Scalar>(npage_, getTubeInc(), data_, getPos(rowidx, colidx, 0) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getTube
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseCube<_Scalar, _layout>::getTubeSegment(
    const index_t rowidx,
    const index_t colidx,
    const IdxRange pagerange
) noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colidx >= 0 && colidx < ncol_);
  assert(pagerange.begin >= 0 && pagerange.end <= npage_ && pagerange.getLength() >= 0);
  return DenseVector<_Scalar>(pagerange.getLength(), getTubeInc(), data_, getPos(rowidx, colidx, pagerange.begin) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getTubeSegment
///
template <typename _Scalar, Layout _layout>
const DenseVector<_Scalar> DenseCube<_Scalar, _layout>::getTubeSegment(
    const index_t rowidx,
    const index_t colidx,
    const IdxRange pagerange
) const noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colidx >= 0 && colidx < ncol_);
  assert(pagerange.begin >= 0 && pagerange.end <= npage_ && pagerange.getLength() >= 0);
  return DenseVector<_Scalar>(pagerange.getLength(), getTubeInc(), data_, getPos(rowidx, colidx, pagerange.begin) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a diagonal vector.
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseCube<_Scalar, _layout>::getDiagonal(
    const index_t pageidx, const index_t idx
) noexcept {
  assert(idx > -nrow_ && idx < ncol_);
  index_t length;
  index_t idx0;
  if ( idx < 0 ) {
    idx0 = getPos(-idx, 0, pageidx);
    if ( nrow_ + idx > ncol_ && nrow_ > ncol_ ) {
      length = ncol_;
    } else {
      length = nrow_ + idx;
    }
  } else {
    idx0 = getPos(0, idx, pageidx);
    if ( ncol_ - idx > nrow_ && ncol_ > nrow_ ) {
      length = nrow_;
    } else {
      length = ncol_ - idx;
    }
  }
  return DenseVector<_Scalar>(length, pitch1_+1, data_, idx0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getDiagonal
///
template <typename _Scalar, Layout _layout>
const DenseVector<_Scalar> DenseCube<_Scalar, _layout>::getDiagonal(
    const index_t pageidx, const index_t idx
) const noexcept {
  assert(idx > -nrow_ && idx < ncol_);
  index_t length;
  index_t idx0;
  if ( idx < 0 ) {
    idx0 = getPos(-idx, 0, pageidx);
    if ( nrow_ + idx > ncol_ && nrow_ > ncol_ ) {
      length = ncol_;
    } else {
      length = nrow_ + idx;
    }
  } else {
    idx0 = getPos(0, idx, pageidx);
    if ( ncol_ - idx > nrow_ && ncol_ > nrow_ ) {
      length = nrow_;
    } else {
      length = ncol_ - idx;
    }
  }
  return DenseVector<_Scalar>(length, pitch1_+1, data_, idx0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Vectorize the cube.
///
/// @attention  The output vector contains the out-of-range spaces.
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseCube<_Scalar, _layout>::vectorize() noexcept {
  return DenseVector<_Scalar>(pitch1_ * pitch2_ * npage_, 1, data_, getPos(0, 0, 0) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  vectorize
///
template <typename _Scalar, Layout _layout>
const DenseVector<_Scalar> DenseCube<_Scalar, _layout>::vectorize() const noexcept {
  return DenseVector<_Scalar>(pitch1_ * pitch2_ * npage_, 1, data_, getPos(0, 0, 0) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the column stride.
///
template <typename _Scalar, Layout _layout>
index_t DenseCube<_Scalar, _layout>::getColInc() const noexcept {
  return isColMajor(_layout) ? 1 : pitch1_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the row stride.
///
template <typename _Scalar, Layout _layout>
index_t DenseCube<_Scalar, _layout>::getRowInc() const noexcept {
  return isColMajor(_layout) ? pitch1_ : 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the tube stride.
///
template <typename _Scalar, Layout _layout>
index_t DenseCube<_Scalar, _layout>::getTubeInc() const noexcept {
  return pitch1_ * pitch2_;
}

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_CUBE_IPP_
