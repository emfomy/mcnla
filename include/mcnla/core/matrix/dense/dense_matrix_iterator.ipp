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
  const index_t width_r = log10(iterator.container_->nrow())+1;
  const index_t width_c = log10(iterator.container_->ncol())+1;
  const index_t width   = std::max(width_r, width_c);
  return out << "(" << std::setw(width) << iterator.rowidx() << ", "
                    << std::setw(width) << iterator.colidx() << ")  "
                    << std::setw(ios_width) << iterator.value();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value.
///
/// @attention  Never call this when the iterator is at the end.
///
template <typename _Scalar, Trans _trans, class _Matrix>
_Scalar& DenseMatrixIteratorBase<_Scalar, _trans, _Matrix>::value() const noexcept {
  mcnla_assert_gelt(itidx_, 0, container_->nelem());
  return container_->valuePtr()[pos()];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the row index.
///
template <typename _Scalar, Trans _trans, class _Matrix>
index_t DenseMatrixIteratorBase<_Scalar, _trans, _Matrix>::rowidx() const noexcept {
  return !isTrans(_trans) ? itidx_ % container_->dim0() : itidx_ / container_->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the column index.
///
template <typename _Scalar, Trans _trans, class _Matrix>
index_t DenseMatrixIteratorBase<_Scalar, _trans, _Matrix>::colidx() const noexcept {
  return !isTrans(_trans) ? itidx_ / container_->dim0() : itidx_ % container_->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position.
///
/// @attention  Never call this when the iterator is at the end.
///
template <typename _Scalar, Trans _trans, class _Matrix>
index_t DenseMatrixIteratorBase<_Scalar, _trans, _Matrix>::pos() const noexcept {
  return container_->pos(rowidx(), colidx());
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_IPP_
