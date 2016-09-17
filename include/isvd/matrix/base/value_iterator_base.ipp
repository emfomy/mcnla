////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/base/value_iterator_base.ipp
/// @brief   The implementation of value iterator interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_BASE_VALUE_ITERATOR_BASE_IPP_
#define ISVD_MATRIX_BASE_VALUE_ITERATOR_BASE_IPP_

#include <isvd/matrix/base/value_iterator_base.hpp>

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
  return static_cast<_Derived&>(*this).getValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value.
///
template <class _Derived>
const typename ValueIteratorBase<_Derived>::ScalarType& ValueIteratorBase<_Derived>::operator*() const noexcept {
  return static_cast<const _Derived&>(*this).getValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value.
///
template <class _Derived>
typename ValueIteratorBase<_Derived>::ScalarType* ValueIteratorBase<_Derived>::operator->() noexcept {
  return &(static_cast<_Derived&>(*this).getValue());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value.
///
template <class _Derived>
const typename ValueIteratorBase<_Derived>::ScalarType* ValueIteratorBase<_Derived>::operator->() const noexcept {
  return &(static_cast<const _Derived&>(*this).getValue());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value iterator.
///
template <class _Derived>
typename ValueIteratorBase<_Derived>::IdxIteratorType
    ValueIteratorBase<_Derived>::toIdxIterator() noexcept {
  return IdxIteratorType(derived().getContainer(), derived().getItIdx());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value iterator.
///
template <class _Derived>
const typename ValueIteratorBase<_Derived>::IdxIteratorType
    ValueIteratorBase<_Derived>::toIdxIterator() const noexcept {
  return IdxIteratorType(derived().getContainer(), derived().getItIdx());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Change to derived class.
///
template <class _Derived>
_Derived& ValueIteratorBase<_Derived>::derived() noexcept {
  return static_cast<_Derived&>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  derived
///
template <class _Derived>
const _Derived& ValueIteratorBase<_Derived>::derived() const noexcept {
  return static_cast<const _Derived&>(*this);
}

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_BASE_VALUE_ITERATOR_BASE_IPP_
