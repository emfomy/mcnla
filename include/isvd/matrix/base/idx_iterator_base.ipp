////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/base/idx_iterator_base.ipp
/// @brief   The implementation of index iterator interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_BASE_IDX_ITERATOR_BASE_IPP_
#define ISVD_MATRIX_BASE_IDX_ITERATOR_BASE_IPP_

#include <isvd/matrix/base/idx_iterator_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index tuple.
///
template <class _Derived>
typename IdxIteratorBase<_Derived>::IdxTupleType IdxIteratorBase<_Derived>::operator*() const noexcept {
  return this->derived().getIdxs();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value iterator.
///
template <class _Derived>
typename IdxIteratorBase<_Derived>::ValueIteratorType&
    IdxIteratorBase<_Derived>::toValueIterator() noexcept {
  return static_cast<ValueIteratorType&>(static_cast<BaseIteratorType&>(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the to beginning iterator.
///
template <class _Derived>
typename IdxIteratorBase<_Derived>::IdxIteratorType
    IdxIteratorBase<_Derived>::getBegin( ContainerType *container ) noexcept {
  IdxIteratorType retval(container); retval.setBegin(); return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the to end iterator.
///
template <class _Derived>
typename IdxIteratorBase<_Derived>::IdxIteratorType
    IdxIteratorBase<_Derived>::getEnd( ContainerType *container ) noexcept {
  IdxIteratorType retval(container); retval.setEnd(); return retval;
}

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_BASE_IDX_ITERATOR_BASE_IPP_
