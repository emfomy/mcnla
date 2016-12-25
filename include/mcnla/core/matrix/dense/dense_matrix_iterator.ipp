////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_matrix_iterator.ipp
/// @brief   The implementation of dense matrix iterator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_IPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_IPP_

#include <mcnla/core/matrix/dense/dense_matrix_iterator.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Print to stream.
///
template <typename __Scalar, Trans __trans, class __Matrix>
std::ostream& operator<< (
    std::ostream &out,
    const DenseMatrixIteratorBase<__Scalar, __trans, __Matrix> &iterator
) {
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
template <typename _Scalar, Trans _trans, class _Matrix>
_Scalar& DenseMatrixIteratorBase<_Scalar, _trans, _Matrix>::getValue() const noexcept {
  mcnla_assert_gelt(itidx_, 0, container_->getNelem());
  return container_->getValuePtr()[getPos()];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the row index.
///
template <typename _Scalar, Trans _trans, class _Matrix>
index_t DenseMatrixIteratorBase<_Scalar, _trans, _Matrix>::getRowIdx() const noexcept {
  return !isTrans(_trans) ? itidx_ % container_->getDim0() : itidx_ / container_->getDim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the column index.
///
template <typename _Scalar, Trans _trans, class _Matrix>
index_t DenseMatrixIteratorBase<_Scalar, _trans, _Matrix>::getColIdx() const noexcept {
  return !isTrans(_trans) ? itidx_ / container_->getDim0() : itidx_ % container_->getDim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position.
///
/// @attention  Never call this when the iterator is at the end.
///
template <typename _Scalar, Trans _trans, class _Matrix>
index_t DenseMatrixIteratorBase<_Scalar, _trans, _Matrix>::getPos() const noexcept {
  return container_->getPos(getRowIdx(), getColIdx());
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_IPP_
