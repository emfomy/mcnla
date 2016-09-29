////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/matrix/dense/dense_matrix_iterator.ipp
/// @brief   The implementation of dense matrix iterator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_IPP_
#define MCNLA_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_IPP_

#include <mcnla/matrix/dense/dense_matrix_iterator.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Print to stream.
///
template <typename __Scalar, Layout __layout, class __Matrix>
std::ostream& operator<< ( std::ostream &out, const DenseMatrixIteratorBase<__Scalar, __layout, __Matrix> &iterator ) {
  const index_t width_r = log10(iterator.container_->getNrow())+1;
  const index_t width_c = log10(iterator.container_->getNcol())+1;
  const index_t width   = std::max(width_r, width_c);
  return out << "(" << std::setw(width) << iterator.getRowIdx() << ", "
                    << std::setw(width) << iterator.getColIdx() << ")  "
                    << std::setw(ios_width) << iterator.getValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value.
///
/// @attention  Never call this when the iterator is at the end.
///
template <typename _Scalar, Layout _layout, class _Matrix>
_Scalar& DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::getValue() const noexcept {
  assert(itidx_ >= 0 && itidx_ < container_->getNelem());
  return container_->getValue()[getPos()];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the row index.
///
template <typename _Scalar, Layout _layout, class _Matrix>
index_t DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::getRowIdx() const noexcept {
  return isColMajor(_layout) ? itidx_ % container_->template getSize<0>()
                             : itidx_ / container_->template getSize<0>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the column index.
///
template <typename _Scalar, Layout _layout, class _Matrix>
index_t DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::getColIdx() const noexcept {
  return isColMajor(_layout) ? itidx_ / container_->template getSize<0>()
                             : itidx_ % container_->template getSize<0>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position.
///
/// @attention  Never call this when the iterator is at the end.
///
template <typename _Scalar, Layout _layout, class _Matrix>
index_t DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::getPos() const noexcept {
  return container_->getPos(getRowIdx(), getColIdx());
}

}  // namespace mcnla

#endif  // MCNLA_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_IPP_
