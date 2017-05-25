////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_matrix_iterator.hpp
/// @brief   The dense matrix iterator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_HPP_

#include <mcnla/core/matrix/dense/dense_matrix_iterator.hh>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Output to stream.
///
template <typename ..._Args>
std::ostream& operator<<(
    std::ostream &os,
    const DenseMatrixIteratorBase<_Args...> &it
) noexcept {
  return os << "(" << std::setw(kOsIdxWidth) << it.rowidx() << ", "
                   << std::setw(kOsIdxWidth) << it.colidx() << ")  "
                   << std::setw(kOsValWidth) << it.val();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value.
///
/// @attention  Never call this method when the iterator is at the end.
///
template <typename _Val, Trans _trans, class _Matrix>
_Val& DenseMatrixIteratorBase<_Val, _trans, _Matrix>::val() const noexcept {
  mcnla_assert_gelt(itidx_, 0, container_->nelem());
  return container_->valPtr()[pos()];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the row index.
///
template <typename _Val, Trans _trans, class _Matrix>
index_t DenseMatrixIteratorBase<_Val, _trans, _Matrix>::rowidx() const noexcept {
  return !isTrans(_trans) ? idx0() : idx1();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the column index.
///
template <typename _Val, Trans _trans, class _Matrix>
index_t DenseMatrixIteratorBase<_Val, _trans, _Matrix>::colidx() const noexcept {
  return !isTrans(_trans) ? idx1() : idx0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the first dimension index.
///
template <typename _Val, Trans _trans, class _Matrix>
index_t DenseMatrixIteratorBase<_Val, _trans, _Matrix>::idx0() const noexcept {
  return itidx_ % container_->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the second dimension index.
///
template <typename _Val, Trans _trans, class _Matrix>
index_t DenseMatrixIteratorBase<_Val, _trans, _Matrix>::idx1() const noexcept {
  return itidx_ / container_->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position.
///
/// @attention  Never call this method when the iterator is at the end.
///
template <typename _Val, Trans _trans, class _Matrix>
index_t DenseMatrixIteratorBase<_Val, _trans, _Matrix>::pos() const noexcept {
  return container_->pos(rowidx(), colidx());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element reference.
///
/// @attention  Never call this method when the iterator is at the end.
///
template <typename _Val, Trans _trans, class _Matrix>
_Val& DenseMatrixIteratorBase<_Val, _trans, _Matrix>::elemRef() const noexcept {
  return val();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element pointer.
///
/// @attention  Never call this method when the iterator is at the end.
///
template <typename _Val, Trans _trans, class _Matrix>
_Val* DenseMatrixIteratorBase<_Val, _trans, _Matrix>::elemPtr() const noexcept {
  return &(val());
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_HPP_
