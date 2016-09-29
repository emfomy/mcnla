////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_cube_iterator.ipp
/// @brief   The implementation of dense cube iterator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_CUBE_ITERATOR_IPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_CUBE_ITERATOR_IPP_

#include <mcnla/core/matrix/dense/dense_cube_iterator.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Print to stream.
///
template <typename __Scalar, Layout __layout, class __Cube>
std::ostream& operator<< ( std::ostream &out, const DenseCubeIteratorBase<__Scalar, __layout, __Cube> &iterator ) {
  const index_t width_r = log10(iterator.container_->getNrow())+1;
  const index_t width_c = log10(iterator.container_->getNcol())+1;
  const index_t width_p = log10(iterator.container_->getNpage())+1;
  const index_t width   = std::max(std::max(width_r, width_c), width_p);
  return out << "(" << std::setw(width) << iterator.getRowIdx() << ", "
                    << std::setw(width) << iterator.getColIdx() << ", "
                    << std::setw(width) << iterator.getPageIdx() << ")  "
                    << std::setw(ios_width) << iterator.getValue();
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
  return isColMajor(_layout) ? itidx_ % container_->template getSize<0>()
                             : (itidx_ / container_->template getSize<0>()) % container_->template getSize<1>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the column index.
///
template <typename _Scalar, Layout _layout, class _Cube>
index_t DenseCubeIteratorBase<_Scalar, _layout, _Cube>::getColIdx() const noexcept {
  return isColMajor(_layout) ? (itidx_ / container_->template getSize<0>()) % container_->template getSize<1>()
                             : itidx_ % container_->template getSize<0>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the page index.
///
template <typename _Scalar, Layout _layout, class _Cube>
index_t DenseCubeIteratorBase<_Scalar, _layout, _Cube>::getPageIdx() const noexcept {
  return (itidx_ / container_->template getSize<0>()) / container_->template getSize<1>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position.
///
template <typename _Scalar, Layout _layout, class _Cube>
index_t DenseCubeIteratorBase<_Scalar, _layout, _Cube>::getPos() const noexcept {
  return container_->getPos(getRowIdx(), getColIdx(), getPageIdx());
}

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_CUBE_ITERATOR_IPP_
