////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_vector_iterator.hpp
/// @brief   The COO vector iterator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_VECTOR_ITERATOR_HPP_
#define MCNLA_CORE_MATRIX_COO_COO_VECTOR_ITERATOR_HPP_

#include <mcnla/core/matrix/coo/coo_vector_iterator.hh>

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
template <typename __Val, typename __Idx, class __Vector>
std::ostream& operator<<(
    std::ostream &os,
    const CooVectorIteratorBase<__Val, __Idx, __Vector> &it
) {
  return os << *it;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value.
///
/// @attention  Never call this method when the iterator is at the end.
///
template <typename _Val, typename _Idx, class _Vector>
_Val& CooVectorIteratorBase<_Val, _Idx, _Vector>::val() const noexcept {
  mcnla_assert_gelt(itidx_, 0, container_->nnz());
  return container_->valPtr()[itidx_];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index.
///
template <typename _Val, typename _Idx, class _Vector>
_Idx& CooVectorIteratorBase<_Val, _Idx, _Vector>::idx() const noexcept {
  mcnla_assert_gelt(itidx_, 0, container_->nnz());
  return container_->idxPtr()[itidx_];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the tuple.
///
template <typename _Val, typename _Idx, class _Vector>
CooTuple1<_Val, _Idx> CooVectorIteratorBase<_Val, _Idx, _Vector>::tuple() const noexcept {
  return TupleType(val(), idx());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position.
///
/// @attention  Never call this method when the iterator is at the end.
///
template <typename _Val, typename _Idx, class _Vector>
index_t CooVectorIteratorBase<_Val, _Idx, _Vector>::pos() const noexcept {
  return itidx_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element reference.
///
template <typename _Val, typename _Idx, class _Vector>
CooTuple1<_Val, _Idx> CooVectorIteratorBase<_Val, _Idx, _Vector>::elemRef() const noexcept {
  return tuple();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element pointer.
///
template <typename _Val, typename _Idx, class _Vector>
CooTuple1Ptr<_Val, _Idx> CooVectorIteratorBase<_Val, _Idx, _Vector>::elemPtr() const noexcept {
  return ElemPtrType(tuple());
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_VECTOR_ITERATOR_HPP_
