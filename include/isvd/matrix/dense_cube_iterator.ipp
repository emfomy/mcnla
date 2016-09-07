////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/cube/dense_cube_iterator.ipp
/// @brief   The implementation of dense cube iterator.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_CUBE_ITERATOR_IPP_
#define ISVD_MATRIX_DENSE_CUBE_ITERATOR_IPP_

#include <isvd/matrix/dense_cube_iterator.hpp>

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
template <typename _Scalar, Layout _layout>
DenseCubeIterator<_Scalar, _layout>::DenseCubeIterator() noexcept
  : idx1_(0),
    idx2_(0),
    idx3_(0),
    cube_(nullptr) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given cube.
///
template <typename _Scalar, Layout _layout>
DenseCubeIterator<_Scalar, _layout>::DenseCubeIterator(
    DenseCube<_Scalar, _layout> *cube
) noexcept
  : idx1_(0),
    idx2_(0),
    idx3_(0),
    cube_(cube) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
template <typename _Scalar, Layout _layout>
DenseCubeIterator<_Scalar, _layout>::DenseCubeIterator(
    const DenseCubeIterator &other
) noexcept
  : idx1_(other.idx1_),
    idx2_(other.idx2_),
    idx3_(other.idx3_),
    cube_(other.cube_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
template <typename _Scalar, Layout _layout>
DenseCubeIterator<_Scalar, _layout>& DenseCubeIterator<_Scalar, _layout>::operator=(
    const DenseCubeIterator &other
) noexcept {
  idx1_ = other.idx1_;
  idx2_ = other.idx2_;
  idx3_ = other.idx3_;
  cube_ = other.cube_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Equal-to operator.
///
template <typename _Scalar, Layout _layout>
bool DenseCubeIterator<_Scalar, _layout>::operator==(
    const DenseCubeIterator &other
) const noexcept {
  if ( this == &other ) {
    return true;
  } else if ( *(cube_->getData()) != *(other.cube_->getData()) ) {
    return false;
  } else {
    return (idx1_ == other.idx1_) && (idx2_ == other.idx2_) && (idx3_ == other.idx3_);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Not-equal-to operator.
///
template <typename _Scalar, Layout _layout>
bool DenseCubeIterator<_Scalar, _layout>::operator!=(
    const DenseCubeIterator &other
) const noexcept {
  return !(*this == other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Prefix increment operator.
///
template <typename _Scalar, Layout _layout>
DenseCubeIterator<_Scalar, _layout>& DenseCubeIterator<_Scalar, _layout>::operator++() noexcept {
  assert(cube_ != nullptr);

  const auto size1 = cube_->getSize1();
  const auto size2 = cube_->getSize2();
  const auto size3 = cube_->getNpage();
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
template <typename _Scalar, Layout _layout>
DenseCubeIterator<_Scalar, _layout>& DenseCubeIterator<_Scalar, _layout>::operator++( int ) noexcept {
  auto retval(*this);
  (*this)++;
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar, Layout _layout>
_Scalar& DenseCubeIterator<_Scalar, _layout>::operator*() noexcept {
  return getValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar, Layout _layout>
const _Scalar& DenseCubeIterator<_Scalar, _layout>::operator*() const noexcept {
  return getValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar, Layout _layout>
_Scalar* DenseCubeIterator<_Scalar, _layout>::operator->() noexcept {
  return &getValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar, Layout _layout>
const _Scalar* DenseCubeIterator<_Scalar, _layout>::operator->() const noexcept {
  return &getValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value.
///
/// @attention  Never call this when the iterator is at the end.
///
template <typename _Scalar, Layout _layout>
_Scalar& DenseCubeIterator<_Scalar, _layout>::getValue() noexcept {
  return (*cube_)(rowidx_, colidx_, idx3_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar, Layout _layout>
const _Scalar& DenseCubeIterator<_Scalar, _layout>::getValue() const noexcept {
  return (*cube_)(rowidx_, colidx_, idx3_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the row index.
///
template <typename _Scalar, Layout _layout>
index_t DenseCubeIterator<_Scalar, _layout>::getRowIdx() noexcept {
  return rowidx_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the column index.
///
template <typename _Scalar, Layout _layout>
index_t DenseCubeIterator<_Scalar, _layout>::getColIdx() noexcept {
  return colidx_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the page index.
///
template <typename _Scalar, Layout _layout>
index_t DenseCubeIterator<_Scalar, _layout>::getPageIdx() noexcept {
  return idx3_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the leading index.
///
template <typename _Scalar, Layout _layout>
index_t DenseCubeIterator<_Scalar, _layout>::getIdx1() noexcept {
  return idx1_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the second index.
///
template <typename _Scalar, Layout _layout>
index_t DenseCubeIterator<_Scalar, _layout>::getIdx2() noexcept {
  return idx2_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the iterator to beginning.
///
template <typename _Scalar, Layout _layout>
DenseCubeIterator<_Scalar, _layout>& DenseCubeIterator<_Scalar, _layout>::setBegin() noexcept {
  idx1_ = 0;
  idx2_ = 0;
  idx3_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the iterator to end.
///
template <typename _Scalar, Layout _layout>
DenseCubeIterator<_Scalar, _layout>& DenseCubeIterator<_Scalar, _layout>::setEnd() noexcept {
  idx1_ = 0;
  idx2_ = 0;
  idx3_ = (cube_ != nullptr) ? cube_->getNpage() : 0;
  return *this;
}

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_CUBE_ITERATOR_IPP_
