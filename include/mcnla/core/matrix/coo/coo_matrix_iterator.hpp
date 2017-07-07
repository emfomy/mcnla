////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_matrix_iterator.hpp
/// @brief   The COO matrix iterator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_MATRIX_ITERATOR_HPP_
#define MCNLA_CORE_MATRIX_COO_COO_MATRIX_ITERATOR_HPP_

#include <mcnla/core/matrix/coo/coo_matrix_iterator.hh>

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
    const CooMatrixIteratorBase<_Args...> &it
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
template <typename _Val, typename _Idx, Trans _trans, class _Matrix>
_Val& CooMatrixIteratorBase<_Val, _Idx, _trans, _Matrix>::val() const noexcept {
  mcnla_assert_gelt(itidx_, 0, container_->nnz());
  return container_->valPtr()[itidx_];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the row index.
///
template <typename _Val, typename _Idx, Trans _trans, class _Matrix>
_Idx& CooMatrixIteratorBase<_Val, _Idx, _trans, _Matrix>::rowidx() const noexcept {
  mcnla_assert_gelt(itidx_, 0, container_->nnz());
  return container_->rowidxPtr()[itidx_];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the column index.
///
template <typename _Val, typename _Idx, Trans _trans, class _Matrix>
_Idx& CooMatrixIteratorBase<_Val, _Idx, _trans, _Matrix>::colidx() const noexcept {
  mcnla_assert_gelt(itidx_, 0, container_->nnz());
  return container_->colidxPtr()[itidx_];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the first dimension index.
///
template <typename _Val, typename _Idx, Trans _trans, class _Matrix>
_Idx& CooMatrixIteratorBase<_Val, _Idx, _trans, _Matrix>::idx0() const noexcept {
  mcnla_assert_gelt(itidx_, 0, container_->nnz());
  return container_->idx0Ptr()[itidx_];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the first dimension index.
///
template <typename _Val, typename _Idx, Trans _trans, class _Matrix>
_Idx& CooMatrixIteratorBase<_Val, _Idx, _trans, _Matrix>::idx1() const noexcept {
  mcnla_assert_gelt(itidx_, 0, container_->nnz());
  return container_->idx1Ptr()[itidx_];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the tuple.
///
template <typename _Val, typename _Idx, Trans _trans, class _Matrix>
CooTuple2<_Val, _Idx, _trans> CooMatrixIteratorBase<_Val, _Idx, _trans, _Matrix>::tuple() const noexcept {
  return TupleType(val(), rowidx(), colidx());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position.
///
/// @attention  Never call this method when the iterator is at the end.
///
template <typename _Val, typename _Idx, Trans _trans, class _Matrix>
index_t CooMatrixIteratorBase<_Val, _Idx, _trans, _Matrix>::pos() const noexcept {
  return itidx_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element reference.
///
template <typename _Val, typename _Idx, Trans _trans, class _Matrix>
CooTuple2<_Val, _Idx, _trans> CooMatrixIteratorBase<_Val, _Idx, _trans, _Matrix>::elemRef() const noexcept {
  return tuple();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element pointer.
///
template <typename _Val, typename _Idx, Trans _trans, class _Matrix>
CooTuple2Ptr<_Val, _Idx, _trans> CooMatrixIteratorBase<_Val, _Idx, _trans, _Matrix>::elemPtr() const noexcept {
  return ElemPtrType(tuple());
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_MATRIX_ITERATOR_HPP_
