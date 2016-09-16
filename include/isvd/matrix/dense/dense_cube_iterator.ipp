////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense/dense_cube_iterator.ipp
/// @brief   The implementation of dense cube iterator.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DENSE_CUBE_ITERATOR_IPP_
#define ISVD_MATRIX_DENSE_DENSE_CUBE_ITERATOR_IPP_

#include <isvd/matrix/dense/dense_cube_iterator.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <typename _Scalar, Layout _layout, class _Cube>
DenseCubeIteratorBase<_Scalar, _layout, _Cube>::DenseCubeIteratorBase() noexcept
  : rowidx_(0),
    colidx_(0),
    pageidx_(0),
    container_(nullptr) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given cube.
///
template <typename _Scalar, Layout _layout, class _Cube>
DenseCubeIteratorBase<_Scalar, _layout, _Cube>::DenseCubeIteratorBase(
    _Cube *cube
) noexcept
  : rowidx_(0),
    colidx_(0),
    pageidx_(0),
    container_(cube) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given cube.
///
template <typename _Scalar, Layout _layout, class _Cube>
DenseCubeIteratorBase<_Scalar, _layout, _Cube>::DenseCubeIteratorBase(
    _Cube *cube,
    const index_t rowidx,
    const index_t colidx,
    const index_t pageidx
) noexcept
  : rowidx_(rowidx),
    colidx_(colidx),
    pageidx_(pageidx),
    container_(cube) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
template <typename _Scalar, Layout _layout, class _Cube>
DenseCubeIteratorBase<_Scalar, _layout, _Cube>::DenseCubeIteratorBase(
    const DenseCubeIteratorBase &other
) noexcept
  : rowidx_(other.rowidx_),
    colidx_(other.colidx_),
    pageidx_(other.pageidx_),
    container_(other.container_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
template <typename _Scalar, Layout _layout, class _Cube>
DenseCubeIteratorBase<_Scalar, _layout, _Cube>& DenseCubeIteratorBase<_Scalar, _layout, _Cube>::operator=(
    const DenseCubeIteratorBase &other
) noexcept {
  rowidx_ = other.rowidx_;
  colidx_ = other.colidx_;
  pageidx_ = other.pageidx_;
  container_ = other.container_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Equal-to operator.
///
template <typename _Scalar, Layout _layout, class _Cube>
bool DenseCubeIteratorBase<_Scalar, _layout, _Cube>::operator==(
    const DenseCubeIteratorBase &other
) const noexcept {
  return (container_ == other.container_) && (idx1_ == other.idx1_) && (idx2_ == other.idx2_) && (idx3_ == other.idx3_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Not-equal-to operator.
///
template <typename _Scalar, Layout _layout, class _Cube>
bool DenseCubeIteratorBase<_Scalar, _layout, _Cube>::operator!=(
    const DenseCubeIteratorBase &other
) const noexcept {
  return !(*this == other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Prefix increment operator.
///
template <typename _Scalar, Layout _layout, class _Cube>
DenseCubeIteratorBase<_Scalar, _layout, _Cube>& DenseCubeIteratorBase<_Scalar, _layout, _Cube>::operator++() noexcept {
  assert(container_ != nullptr);

  const auto size1 = container_->getSize1();
  const auto size2 = container_->getSize2();
  const auto size3 = container_->getSize3();
  if ( ++idx1_ >= size1 ) {
    idx1_ = 0;
    if ( ++idx2_ >= size2 ) {
      idx2_ = 0;
      if ( ++idx3_ >= size3 ) {
        idx3_ = size3;
      }
    }
  }
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Postfix increment operator.
///
template <typename _Scalar, Layout _layout, class _Cube>
DenseCubeIteratorBase<_Scalar, _layout, _Cube> DenseCubeIteratorBase<_Scalar, _layout, _Cube>::operator++( int ) noexcept {
  auto retval(*this);
  ++(*this);
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value.
///
/// @attention  Never call this when the iterator is at the end.
///
template <typename _Scalar, Layout _layout, class _Cube>
_Scalar& DenseCubeIteratorBase<_Scalar, _layout, _Cube>::getValue() noexcept {
  return container_->getValue()[getPos()];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar, Layout _layout, class _Cube>
const _Scalar& DenseCubeIteratorBase<_Scalar, _layout, _Cube>::getValue() const noexcept {
  return container_->getValue()[getPos()];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index tuple.
///
template <typename _Scalar, Layout _layout, class _Cube>
IdxTuple<3> DenseCubeIteratorBase<_Scalar, _layout, _Cube>::getIdxs() const noexcept {
  return makeIdxTuple(idx1_, idx2_, idx3_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the row index.
///
template <typename _Scalar, Layout _layout, class _Cube>
index_t DenseCubeIteratorBase<_Scalar, _layout, _Cube>::getRowIdx() const noexcept {
  return rowidx_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the column index.
///
template <typename _Scalar, Layout _layout, class _Cube>
index_t DenseCubeIteratorBase<_Scalar, _layout, _Cube>::getColIdx() const noexcept {
  return colidx_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the page index.
///
template <typename _Scalar, Layout _layout, class _Cube>
index_t DenseCubeIteratorBase<_Scalar, _layout, _Cube>::getPageIdx() const noexcept {
  return pageidx_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the leading index.
///
template <typename _Scalar, Layout _layout, class _Cube>
index_t DenseCubeIteratorBase<_Scalar, _layout, _Cube>::getIdx1() const noexcept {
  return idx1_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the second index.
///
template <typename _Scalar, Layout _layout, class _Cube>
index_t DenseCubeIteratorBase<_Scalar, _layout, _Cube>::getIdx2() const noexcept {
  return idx2_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the third index.
///
template <typename _Scalar, Layout _layout, class _Cube>
index_t DenseCubeIteratorBase<_Scalar, _layout, _Cube>::getIdx3() const noexcept {
  return idx3_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position.
///
template <typename _Scalar, Layout _layout, class _Cube>
index_t DenseCubeIteratorBase<_Scalar, _layout, _Cube>::getPos() const noexcept {
  return container_->getPos(colidx_, rowidx_, pageidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the iterator to beginning.
///
template <typename _Scalar, Layout _layout, class _Cube>
DenseCubeIteratorBase<_Scalar, _layout, _Cube>& DenseCubeIteratorBase<_Scalar, _layout, _Cube>::setBegin() noexcept {
  idx1_ = 0;
  idx2_ = 0;
  idx3_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the iterator to end.
///
template <typename _Scalar, Layout _layout, class _Cube>
DenseCubeIteratorBase<_Scalar, _layout, _Cube>& DenseCubeIteratorBase<_Scalar, _layout, _Cube>::setEnd() noexcept {
  idx1_ = 0;
  idx2_ = 0;
  idx3_ = (container_ != nullptr) ? container_->getNpage() : 0;
  return *this;
}

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_CUBE_ITERATOR_IPP_
