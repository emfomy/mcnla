////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/base/iterator_base.ipp
/// @brief   The implementation of iterator interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_BASE_ITERATOR_BASE_IPP_
#define ISVD_MATRIX_BASE_ITERATOR_BASE_IPP_

#include <isvd/matrix/base/iterator_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value.
///
template <class _Derived>
typename ValueIteratorBase<_Derived>::ScalarType& ValueIteratorBase<_Derived>::operator*() noexcept {
  return this->derived().getValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value.
///
template <class _Derived>
const typename ValueIteratorBase<_Derived>::ScalarType& ValueIteratorBase<_Derived>::operator*() const noexcept {
  return this->derived().getValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value.
///
template <class _Derived>
typename ValueIteratorBase<_Derived>::ScalarType* ValueIteratorBase<_Derived>::operator->() noexcept {
  return &(this->derived().getValue());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value.
///
template <class _Derived>
const typename ValueIteratorBase<_Derived>::ScalarType* ValueIteratorBase<_Derived>::operator->() const noexcept {
  return &(this->derived().getValue());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index iterator.
///
template <class _Derived>
typename ValueIteratorBase<_Derived>::IdxIteratorType&
    ValueIteratorBase<_Derived>::toIdxIterator() noexcept {
  return static_cast<IdxIteratorType&>(static_cast<BaseIteratorType&>(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the to beginning iterator.
///
template <class _Derived>
typename ValueIteratorBase<_Derived>::ValueIteratorType
    ValueIteratorBase<_Derived>::getBegin( ContainerType *container ) noexcept {
  ValueIteratorType retval(container); retval.setBegin(); return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the to end iterator.
///
template <class _Derived>
typename ValueIteratorBase<_Derived>::ValueIteratorType
    ValueIteratorBase<_Derived>::getEnd( ContainerType *container ) noexcept {
  ValueIteratorType retval(container); retval.setEnd(); return retval;
}

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

#endif  // ISVD_MATRIX_BASE_ITERATOR_BASE_IPP_
