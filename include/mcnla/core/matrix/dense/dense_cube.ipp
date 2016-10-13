////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_cube.ipp
/// @brief   The implementation of dense cube.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_CUBE_IPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_CUBE_IPP_

#include <mcnla/core/matrix/dense/dense_cube.hpp>

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
DenseCube<_Scalar, _layout>::DenseCube() noexcept
  : CubeBaseType(),
    DenseBaseType(),
    pitch0_(1),
    pitch1_(1) {}

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
    DenseBaseType(size0_ * size1_ * size2_),
    pitch0_(size0_),
    pitch1_(size1_) {
  mcnla_assert_gt(pitch0_, 0);
  mcnla_assert_gt(pitch1_, 0);
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
    const index_t pitch0
) noexcept
  : CubeBaseType(nrow, ncol, npage),
    DenseBaseType(pitch0 * size1_ * size2_),
    pitch0_(pitch0),
    pitch1_(size1_) {
  mcnla_assert_ge(pitch0_, size0_);
  mcnla_assert_gt(pitch0_, 0);
  mcnla_assert_gt(pitch1_, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>::DenseCube(
    const index_t nrow,
    const index_t ncol,
    const index_t npage,
    const index_t pitch0,
    const index_t pitch1
) noexcept
  : CubeBaseType(nrow, ncol, npage),
    DenseBaseType(pitch0 * pitch1 * size2_),
    pitch0_(pitch0),
    pitch1_(pitch1) {
  mcnla_assert_ge(pitch0, size0_);
  mcnla_assert_ge(pitch1, size1_);
  mcnla_assert_gt(pitch0_, 0);
  mcnla_assert_gt(pitch1_, 0);
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
    const index_t pitch0,
    const index_t pitch1,
    const index_t capacity
) noexcept
  : CubeBaseType(nrow, ncol, npage),
    DenseBaseType(capacity),
    pitch0_(pitch0),
    pitch1_(pitch1) {
  mcnla_assert_ge(pitch0_, size0_);
  mcnla_assert_ge(pitch1_, size1_);
  mcnla_assert_gt(pitch0_, 0);
  mcnla_assert_gt(pitch1_, 0);
  mcnla_assert_ge(capacity, pitch0_ * pitch1_ * npage_ - pitch0_ * (pitch1_-size1_) - (pitch0_-size0_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>::DenseCube(
    const std::tuple<index_t, index_t, index_t> sizes,
    const std::pair<index_t, index_t> pitches,
    const index_t capacity
) noexcept
  : DenseCube(std::get<0>(sizes), std::get<1>(sizes), std::get<2>(sizes), pitches.first, pitches.second, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>::DenseCube(
    const index_t nrow,
    const index_t ncol,
    const index_t npage,
    const index_t pitch0,
    const index_t pitch1,
    const ValueArrayType &value
) noexcept
  : CubeBaseType(nrow, ncol, npage),
    DenseBaseType(value),
    pitch0_(pitch0),
    pitch1_(pitch1) {
  mcnla_assert_ge(pitch0_, size0_);
  mcnla_assert_ge(pitch1_, size1_);
  mcnla_assert_gt(pitch0_, 0);
  mcnla_assert_gt(pitch1_, 0);
  mcnla_assert_ge(this->getCapacity(), pitch0_ * pitch1_ * npage_ - pitch0_ * (pitch1_-size1_) - (pitch0_-size0_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct from data storage.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>::DenseCube(
    const index_t nrow,
    const index_t ncol,
    const index_t npage,
    const index_t pitch0,
    const index_t pitch1,
    const DataType &data,
    const index_t offset
) noexcept
  : CubeBaseType(nrow, ncol, npage),
    DenseBaseType(data >> offset),
    pitch0_(pitch0),
    pitch1_(pitch1) {
  mcnla_assert_ge(pitch0_, size0_);
  mcnla_assert_ge(pitch1_, size1_);
  mcnla_assert_gt(pitch0_, 0);
  mcnla_assert_gt(pitch1_, 0);
  mcnla_assert_ge(this->getCapacity(), pitch0_ * pitch1_ * npage_ - pitch0_ * (pitch1_-size1_) - (pitch0_-size0_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>::DenseCube( const DenseCube &other ) noexcept
  : CubeBaseType(other),
    DenseBaseType(other),
    pitch0_(other.pitch0_),
    pitch1_(other.pitch1_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>::DenseCube( DenseCube &&other ) noexcept
  : CubeBaseType(std::move(other)),
    DenseBaseType(std::move(other)),
    pitch0_(other.pitch0_),
    pitch1_(other.pitch1_) {
  other.pitch0_ = 1; other.pitch1_ = 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>& DenseCube<_Scalar, _layout>::operator=( const DenseCube &other ) noexcept {
  CubeBaseType::operator=(other); DenseBaseType::operator=(other);
  pitch0_ = other.pitch0_; pitch1_ = other.pitch1_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout>& DenseCube<_Scalar, _layout>::operator=( DenseCube &&other ) noexcept {
  CubeBaseType::operator=(std::move(other)); DenseBaseType::operator=(std::move(other));
  pitch0_ = other.pitch0_; pitch1_ = other.pitch1_;
  other.pitch0_ = 1;       other.pitch1_ = 1;
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
index_t DenseCube<_Scalar, _layout>::getPitch0() const noexcept { return pitch0_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the second dimension.
///
template <typename _Scalar, Layout _layout>
index_t DenseCube<_Scalar, _layout>::getPitch1() const noexcept { return pitch1_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the dimensions.
///
template <typename _Scalar, Layout _layout>
std::pair<index_t, index_t> DenseCube<_Scalar, _layout>::getPitches() const noexcept {
  return std::make_pair(pitch0_, pitch1_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the dimensions is equal to the sizes.
///
template <typename _Scalar, Layout _layout>
bool DenseCube<_Scalar, _layout>::isShrunk() const noexcept {
  return (size0_ == pitch0_ && size1_ == pitch1_);
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
  mcnla_assert_gelt(rowidx,  0, nrow_);
  mcnla_assert_gelt(colidx,  0, ncol_);
  mcnla_assert_gelt(pageidx, 0, npage_);
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
  mcnla_assert_gelt(rowidx,  0, nrow_);
  mcnla_assert_gelt(colidx,  0, ncol_);
  mcnla_assert_gelt(pageidx, 0, npage_);
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
/// @brief  Gets the value valarray mask.
///
template <typename _Scalar, Layout _layout>
const std::gslice DenseCube<_Scalar, _layout>::getValueMask() const noexcept {
  return std::gslice(this->getOffset(), {size_t(size2_), size_t(size1_), size_t(size0_)},
                                        {size_t(pitch1_), size_t(pitch0_), 1});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position of given index.
///
template <typename _Scalar, Layout _layout>
index_t DenseCube<_Scalar, _layout>::getPos(
    const index_t rowidx,
    const index_t colidx,
    const index_t pageidx
) const noexcept {
  return (isColMajor(_layout) ? (rowidx + colidx * pitch0_) : (colidx + rowidx * pitch0_)) + pageidx * pitch0_ * pitch1_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the transpose of the cube.
///
/// @attention  The storage layout is also changed.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, changeLayout(_layout)> DenseCube<_Scalar, _layout>::transpose() noexcept {
  return DenseCube<_Scalar, changeLayout(_layout)>(ncol_, nrow_, npage_, pitch0_, pitch1_, data_);
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
  mcnla_assert_gelt(rowidx,  0, nrow_);
  mcnla_assert_gelt(colidx,  0, ncol_);
  mcnla_assert_gelt(pageidx, 0, npage_);
  auto itidx = (isColMajor(_layout) ? (rowidx + colidx * size0_) : (colidx + rowidx * size0_)) + pageidx * size0_ * size1_;
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
  mcnla_assert_gelt(rowidx,  0, nrow_);
  mcnla_assert_gelt(colidx,  0, ncol_);
  mcnla_assert_gelt(pageidx, 0, npage_);
  auto itidx = (isColMajor(_layout) ? (rowidx + colidx * size0_) : (colidx + rowidx * size0_)) + pageidx * size0_ * size1_;
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
  mcnla_assert_ge(nrow,  0);
  mcnla_assert_ge(ncol,  0);
  mcnla_assert_ge(npage, 0);
  mcnla_assert_le(pitch0_, isColMajor(_layout) ? nrow : ncol);
  mcnla_assert_le(pitch1_, isColMajor(_layout) ? ncol : nrow);
  mcnla_assert_ge(data_.getCapacity(), pitch0_ * pitch1_ * npage);
  nrow_ = nrow;
  ncol_ = ncol;
  npage_ = npage;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a cube block.
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout> DenseCube<_Scalar, _layout>::getSubCube(
    const IdxRange rowrange,
    const IdxRange colrange,
    const IdxRange pagerange
) noexcept {
  mcnla_assert_gelt(rowrange.begin,  0, nrow_);  mcnla_assert_ge(rowrange.getLength(), 0);
  mcnla_assert_gelt(colrange.begin,  0, ncol_);  mcnla_assert_ge(colrange.getLength(), 0);
  mcnla_assert_gelt(pagerange.begin, 0, npage_); mcnla_assert_ge(pagerange.getLength(), 0);
  return CubeType(rowrange.getLength(), colrange.getLength(), pagerange.getLength(), pitch0_, pitch1_, data_,
                  getPos(rowrange.begin, colrange.begin, pagerange.begin));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getSubCube
///
template <typename _Scalar, Layout _layout>
const DenseCube<_Scalar, _layout> DenseCube<_Scalar, _layout>::getSubCube(
    const IdxRange rowrange,
    const IdxRange colrange,
    const IdxRange pagerange
) const noexcept {
  mcnla_assert_gelt(rowrange.begin,  0, nrow_);  mcnla_assert_ge(rowrange.getLength(), 0);
  mcnla_assert_gelt(colrange.begin,  0, ncol_);  mcnla_assert_ge(colrange.getLength(), 0);
  mcnla_assert_gelt(pagerange.begin, 0, npage_); mcnla_assert_ge(pagerange.getLength(), 0);
  return CubeType(rowrange.getLength(), colrange.getLength(), pagerange.getLength(), pitch0_, pitch1_, data_,
                  getPos(rowrange.begin, colrange.begin, pagerange.begin));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getSubCube
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout> DenseCube<_Scalar, _layout>::getTubes(
    const IdxRange rowrange,
    const IdxRange colrange
) noexcept {
  mcnla_assert_gelt(rowrange.begin, 0, nrow_); mcnla_assert_ge(rowrange.getLength(), 0);
  mcnla_assert_gelt(colrange.begin, 0, ncol_); mcnla_assert_ge(colrange.getLength(), 0);
  return CubeType(rowrange.getLength(), colrange.getLength(), npage_, pitch0_, pitch1_, data_,
                  getPos(rowrange.begin, colrange.begin, 0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getTubes
///
template <typename _Scalar, Layout _layout>
const DenseCube<_Scalar, _layout> DenseCube<_Scalar, _layout>::getTubes(
    const IdxRange rowrange,
    const IdxRange colrange
) const noexcept {
  mcnla_assert_gelt(rowrange.begin, 0, nrow_); mcnla_assert_ge(rowrange.getLength(), 0);
  mcnla_assert_gelt(colrange.begin, 0, ncol_); mcnla_assert_ge(colrange.getLength(), 0);
  return CubeType(rowrange.getLength(), colrange.getLength(), npage_, pitch0_, pitch1_, data_,
                  getPos(rowrange.begin, colrange.begin, 0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getSubCube
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout> DenseCube<_Scalar, _layout>::getPages(
    const IdxRange pagerange
) noexcept {
  mcnla_assert_gelt(pagerange.begin, 0, npage_); mcnla_assert_ge(pagerange.getLength(), 0);
  return CubeType(nrow_, ncol_, pagerange.getLength(), pitch0_, pitch1_, data_, getPos(0, 0, pagerange.begin));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getPages
///
template <typename _Scalar, Layout _layout>
const DenseCube<_Scalar, _layout> DenseCube<_Scalar, _layout>::getPages(
    const IdxRange pagerange
) const noexcept {
  mcnla_assert_gelt(pagerange.begin, 0, npage_); mcnla_assert_ge(pagerange.getLength(), 0);
  return CubeType(nrow_, ncol_, pagerange.getLength(), pitch0_, pitch1_, data_, getPos(0, 0, pagerange.begin));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getSubCube
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout> DenseCube<_Scalar, _layout>::getColPages(
    const IdxRange colrange
) noexcept {
  mcnla_assert_gelt(colrange.begin, 0, ncol_); mcnla_assert_ge(colrange.getLength(), 0);
  return CubeType(nrow_, colrange.getLength(), npage_, pitch0_, pitch1_, data_, getPos(0, colrange.begin, 0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getColPages
///
template <typename _Scalar, Layout _layout>
const DenseCube<_Scalar, _layout> DenseCube<_Scalar, _layout>::getColPages(
    const IdxRange colrange
) const noexcept {
  mcnla_assert_gelt(colrange.begin, 0, ncol_); mcnla_assert_ge(colrange.getLength(), 0);
  return CubeType(nrow_, colrange.getLength(), npage_, pitch0_, pitch1_, data_, getPos(0, colrange.begin, 0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getSubCube
///
template <typename _Scalar, Layout _layout>
DenseCube<_Scalar, _layout> DenseCube<_Scalar, _layout>::getRowPages(
    const IdxRange rowrange
) noexcept {
  mcnla_assert_gelt(rowrange.begin, 0, nrow_); mcnla_assert_ge(rowrange.getLength(), 0);
  return CubeType(rowrange.getLength(), ncol_, npage_, pitch0_, pitch1_, data_, getPos(rowrange.begin, 0, 0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getRowPages
///
template <typename _Scalar, Layout _layout>
const DenseCube<_Scalar, _layout> DenseCube<_Scalar, _layout>::getRowPages(
    const IdxRange rowrange
) const noexcept {
  mcnla_assert_gelt(rowrange.begin, 0, nrow_); mcnla_assert_ge(rowrange.getLength(), 0);
  return CubeType(rowrange.getLength(), ncol_, npage_, pitch0_, pitch1_, data_, getPos(rowrange.begin, 0, 0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a matrix block.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout> DenseCube<_Scalar, _layout>::getPage(
    const index_t pageidx
) noexcept {
  mcnla_assert_gelt(pageidx, 0, npage_);
  return MatrixType(nrow_, ncol_, pitch0_, data_, getPos(0, 0, pageidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getPage
///
template <typename _Scalar, Layout _layout>
const DenseMatrix<_Scalar, _layout> DenseCube<_Scalar, _layout>::getPage(
    const index_t pageidx
) const noexcept {
  mcnla_assert_gelt(pageidx, 0, npage_);
  return MatrixType(nrow_, ncol_, pitch0_, data_, getPos(0, 0, pageidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getPage
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout> DenseCube<_Scalar, _layout>::getCols(
    const index_t pageidx,
    const IdxRange colrange
) noexcept {
  mcnla_assert_gelt(pageidx, 0, npage_);
  mcnla_assert_gelt(colrange.begin, 0, ncol_); mcnla_assert_ge(colrange.getLength(), 0);
  return MatrixType(nrow_, colrange.getLength(), pitch0_, data_, getPos(0, colrange.begin, pageidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getCols
///
template <typename _Scalar, Layout _layout>
const DenseMatrix<_Scalar, _layout> DenseCube<_Scalar, _layout>::getCols(
    const index_t pageidx,
    const IdxRange colrange
) const noexcept {
  mcnla_assert_gelt(pageidx, 0, npage_);
  mcnla_assert_gelt(colrange.begin, 0, ncol_); mcnla_assert_ge(colrange.getLength(), 0);
  return MatrixType(nrow_, colrange.getLength(), pitch0_, data_, getPos(0, colrange.begin, pageidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getPage
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout> DenseCube<_Scalar, _layout>::getRows(
    const index_t pageidx,
    const IdxRange rowrange
) noexcept {
  mcnla_assert_gelt(pageidx, 0, npage_);
  mcnla_assert_gelt(rowrange.begin, 0, nrow_); mcnla_assert_ge(rowrange.getLength(), 0);
  return MatrixType(rowrange.getLength(), ncol_, pitch0_, data_, getPos(rowrange.begin, 0, pageidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getRows
///
template <typename _Scalar, Layout _layout>
const DenseMatrix<_Scalar, _layout> DenseCube<_Scalar, _layout>::getRows(
    const index_t pageidx,
    const IdxRange rowrange
) const noexcept {
  mcnla_assert_gelt(pageidx, 0, npage_);
  mcnla_assert_gelt(rowrange.begin, 0, nrow_); mcnla_assert_ge(rowrange.getLength(), 0);
  return MatrixType(rowrange.getLength(), ncol_, pitch0_, data_, getPos(rowrange.begin, 0, pageidx));
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
  mcnla_assert_gelt(pageidx, 0, npage_);
  mcnla_assert_gelt(rowrange.begin, 0, nrow_); mcnla_assert_ge(rowrange.getLength(), 0);
  mcnla_assert_gelt(colrange.begin, 0, ncol_); mcnla_assert_ge(colrange.getLength(), 0);
  return MatrixType(rowrange.getLength(), colrange.getLength(), pitch0_, data_,
                    getPos(rowrange.begin, colrange.begin, pageidx));
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
  mcnla_assert_gelt(pageidx, 0, npage_);
  mcnla_assert_gelt(rowrange.begin, 0, nrow_); mcnla_assert_ge(rowrange.getLength(), 0);
  mcnla_assert_gelt(colrange.begin, 0, ncol_); mcnla_assert_ge(colrange.getLength(), 0);
  return MatrixType(rowrange.getLength(), colrange.getLength(), pitch0_, data_,
                    getPos(rowrange.begin, colrange.begin, pageidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Unfold the cube.
///
/// @attention  The output matrix contains the out-of-range spaces in the second dimension.
///
template <typename _Scalar, Layout _layout>
DenseMatrix<_Scalar, _layout> DenseCube<_Scalar, _layout>::unfold() noexcept {
  if ( isColMajor(_layout) ) {
    return MatrixType(nrow_, pitch1_ * npage_ - (pitch0_-size0_), pitch0_, data_, getPos(0, 0, 0));
  } else {
    return MatrixType(pitch1_ * npage_ - (pitch0_-size0_), ncol_, pitch0_, data_, getPos(0, 0, 0));
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  unfold
///
template <typename _Scalar, Layout _layout>
const DenseMatrix<_Scalar, _layout> DenseCube<_Scalar, _layout>::unfold() const noexcept {
  if ( isColMajor(_layout) ) {
    return MatrixType(nrow_, pitch1_ * npage_ - (pitch0_-size0_), pitch0_, data_, getPos(0, 0, 0));
  } else {
    return MatrixType(pitch1_ * npage_ - (pitch0_-size0_), ncol_, pitch0_, data_, getPos(0, 0, 0));
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
  mcnla_assert_gelt(colidx,  0, ncol_);
  mcnla_assert_gelt(pageidx, 0, npage_);
  return VectorType(nrow_, getColInc(), data_, getPos(0, colidx, pageidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getCol
///
template <typename _Scalar, Layout _layout>
const DenseVector<_Scalar> DenseCube<_Scalar, _layout>::getCol(
    const index_t colidx,
    const index_t pageidx
) const noexcept {
  mcnla_assert_gelt(colidx,  0, ncol_);
  mcnla_assert_gelt(pageidx, 0, npage_);
  return VectorType(nrow_, getColInc(), data_, getPos(0, colidx, pageidx));
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
  mcnla_assert_gelt(colidx,  0, ncol_);
  mcnla_assert_gelt(pageidx, 0, npage_);
  mcnla_assert_gelt(rowrange.begin, 0, nrow_); mcnla_assert_ge(rowrange.getLength(), 0);
  return VectorType(rowrange.getLength(), getColInc(), data_, getPos(rowrange.begin, colidx, pageidx));
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
  mcnla_assert_gelt(colidx,  0, ncol_);
  mcnla_assert_gelt(pageidx, 0, npage_);
  mcnla_assert_gelt(rowrange.begin, 0, nrow_); mcnla_assert_ge(rowrange.getLength(), 0);
  return VectorType(rowrange.getLength(), getColInc(), data_, getPos(rowrange.begin, colidx, pageidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseCube<_Scalar, _layout>::getRow(
    const index_t rowidx,
    const index_t pageidx
) noexcept {
  mcnla_assert_gelt(rowidx,  0, nrow_);
  mcnla_assert_gelt(pageidx, 0, npage_);
  return VectorType(ncol_, getRowInc(), data_, getPos(rowidx, 0, pageidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getRow
///
template <typename _Scalar, Layout _layout>
const DenseVector<_Scalar> DenseCube<_Scalar, _layout>::getRow(
    const index_t rowidx,
    const index_t pageidx
) const noexcept {
  mcnla_assert_gelt(rowidx,  0, nrow_);
  mcnla_assert_gelt(pageidx, 0, npage_);
  return VectorType(ncol_, getRowInc(), data_, getPos(rowidx, 0, pageidx));
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
  mcnla_assert_gelt(rowidx,  0, nrow_);
  mcnla_assert_gelt(pageidx, 0, npage_);
  mcnla_assert_gelt(colrange.begin, 0, ncol_); mcnla_assert_ge(colrange.getLength(), 0);
  return VectorType(colrange.getLength(), getRowInc(), data_, getPos(rowidx, colrange.begin, pageidx));
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
  mcnla_assert_gelt(rowidx,  0, nrow_);
  mcnla_assert_gelt(pageidx, 0, npage_);
  mcnla_assert_gelt(colrange.begin, 0, ncol_); mcnla_assert_ge(colrange.getLength(), 0);
  return VectorType(colrange.getLength(), getRowInc(), data_, getPos(rowidx, colrange.begin, pageidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseCube<_Scalar, _layout>::getTube(
    const index_t rowidx,
    const index_t colidx
) noexcept {
  mcnla_assert_gelt(rowidx,  0, nrow_);
  mcnla_assert_gelt(colidx,  0, ncol_);
  return VectorType(npage_, getTubeInc(), data_, getPos(rowidx, colidx, 0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getTube
///
template <typename _Scalar, Layout _layout>
const DenseVector<_Scalar> DenseCube<_Scalar, _layout>::getTube(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  mcnla_assert_gelt(rowidx,  0, nrow_);
  mcnla_assert_gelt(colidx,  0, ncol_);
  return VectorType(npage_, getTubeInc(), data_, getPos(rowidx, colidx, 0));
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
  mcnla_assert_gelt(rowidx,  0, nrow_);
  mcnla_assert_gelt(colidx,  0, ncol_);
  mcnla_assert_gelt(pagerange.begin, 0, npage_); mcnla_assert_ge(pagerange.getLength(), 0);
  return VectorType(pagerange.getLength(), getTubeInc(), data_, getPos(rowidx, colidx, pagerange.begin));
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
  mcnla_assert_gelt(rowidx,  0, nrow_);
  mcnla_assert_gelt(colidx,  0, ncol_);
  mcnla_assert_gelt(pagerange.begin, 0, npage_); mcnla_assert_ge(pagerange.getLength(), 0);
  return VectorType(pagerange.getLength(), getTubeInc(), data_, getPos(rowidx, colidx, pagerange.begin));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a diagonal vector.
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseCube<_Scalar, _layout>::getDiagonal(
    const index_t pageidx, const index_t idx
) noexcept {
  mcnla_assert_gtlt(idx, -nrow_, ncol_);
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
  return VectorType(length, pitch0_+1, data_, idx0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getDiagonal
///
template <typename _Scalar, Layout _layout>
const DenseVector<_Scalar> DenseCube<_Scalar, _layout>::getDiagonal(
    const index_t pageidx, const index_t idx
) const noexcept {
  mcnla_assert_gtlt(idx, -nrow_, ncol_);
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
  return VectorType(length, pitch0_+1, data_, idx0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Vectorize the cube.
///
/// @attention  The output vector contains the out-of-range spaces.
///
template <typename _Scalar, Layout _layout>
DenseVector<_Scalar> DenseCube<_Scalar, _layout>::vectorize() noexcept {
  return VectorType(pitch0_ * pitch1_ * npage_ - pitch0_ * (pitch1_-size1_) - (pitch0_-size0_), 1, data_, getPos(0, 0, 0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  vectorize
///
template <typename _Scalar, Layout _layout>
const DenseVector<_Scalar> DenseCube<_Scalar, _layout>::vectorize() const noexcept {
  return VectorType(pitch0_ * pitch1_ * npage_ - pitch0_ * (pitch1_-size1_) - (pitch0_-size0_), 1, data_, getPos(0, 0, 0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the column stride.
///
template <typename _Scalar, Layout _layout>
index_t DenseCube<_Scalar, _layout>::getColInc() const noexcept {
  return isColMajor(_layout) ? 1 : pitch0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the row stride.
///
template <typename _Scalar, Layout _layout>
index_t DenseCube<_Scalar, _layout>::getRowInc() const noexcept {
  return isColMajor(_layout) ? pitch0_ : 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the tube stride.
///
template <typename _Scalar, Layout _layout>
index_t DenseCube<_Scalar, _layout>::getTubeInc() const noexcept {
  return pitch0_ * pitch1_;
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_CUBE_IPP_
