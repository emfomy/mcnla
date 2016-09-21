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
/// @brief  Print to stream.
///
template <typename __Scalar, Layout __layout, class __Cube>
std::ostream& operator<< ( std::ostream &out, const DenseCubeIteratorBase<__Scalar, __layout, __Cube> &iterator ) {
  const index_t width_r = log10(iterator.container_->getNrow())+1;
  const index_t width_c = log10(iterator.container_->getNcol())+1;
  const index_t width_p = log10(iterator.container_->getNpage())+1;
  return out << "(" << std::setw(width_r) << iterator.getRowIdx() << ", "
                    << std::setw(width_c) << iterator.getColIdx() << ", "
                    << std::setw(width_p) << iterator.getPageIdx() << ")  " << std::setw(ios_width) << iterator.getValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value.
///
/// @attention  Never call this when the iterator is at the end.
///
template <typename _Scalar, Layout _layout, class _Cube>
_Scalar& DenseCubeIteratorBase<_Scalar, _layout, _Cube>::getValue() const noexcept {
  assert(itidx_ >= 0 && itidx_ < container_->getNelem());
  return container_->getValue()[getPos()];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the row index.
///
template <typename _Scalar, Layout _layout, class _Cube>
index_t DenseCubeIteratorBase<_Scalar, _layout, _Cube>::getRowIdx() const noexcept {
  return isColMajor(_layout) ? getIdx1() : getIdx2();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the column index.
///
template <typename _Scalar, Layout _layout, class _Cube>
index_t DenseCubeIteratorBase<_Scalar, _layout, _Cube>::getColIdx() const noexcept {
  return isColMajor(_layout) ? getIdx2() : getIdx3();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the page index.
///
template <typename _Scalar, Layout _layout, class _Cube>
index_t DenseCubeIteratorBase<_Scalar, _layout, _Cube>::getPageIdx() const noexcept {
  return getIdx3();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the leading index.
///
template <typename _Scalar, Layout _layout, class _Cube>
index_t DenseCubeIteratorBase<_Scalar, _layout, _Cube>::getIdx1() const noexcept {
  return itidx_ % container_->getSize1();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the second index.
///
template <typename _Scalar, Layout _layout, class _Cube>
index_t DenseCubeIteratorBase<_Scalar, _layout, _Cube>::getIdx2() const noexcept {
  return (itidx_ / container_->getSize1()) % container_->getSize2();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the third index.
///
template <typename _Scalar, Layout _layout, class _Cube>
index_t DenseCubeIteratorBase<_Scalar, _layout, _Cube>::getIdx3() const noexcept {
  return (itidx_ / container_->getSize1()) / container_->getSize2();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position.
///
template <typename _Scalar, Layout _layout, class _Cube>
index_t DenseCubeIteratorBase<_Scalar, _layout, _Cube>::getPos() const noexcept {
  return container_->getPos(getRowIdx(), getColIdx(), getPageIdx());
}

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_CUBE_ITERATOR_IPP_
