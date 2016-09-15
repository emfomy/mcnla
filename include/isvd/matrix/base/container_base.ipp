////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/base/container_base.ipp
/// @brief   The implementation of container interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_BASE_CONTAINER_BASE_IPP_
#define ISVD_MATRIX_BASE_CONTAINER_BASE_IPP_

#include <isvd/matrix/base/container_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the iterator to beginning.
///
template <class _Derived>
typename ContainerBase<_Derived>::IteratorType ContainerBase<_Derived>::begin() noexcept {
  return IteratorType::getBegin(&(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  begin
///
template <class _Derived>
typename ContainerBase<_Derived>::ConstIteratorType ContainerBase<_Derived>::begin() const noexcept {
  return ConstIteratorType::getBegin(&(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  begin
///
template <class _Derived>
typename ContainerBase<_Derived>::ConstIteratorType ContainerBase<_Derived>::cbegin() const noexcept {
  return ConstIteratorType::getBegin(&(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the iterator to end.
///
template <class _Derived>
typename ContainerBase<_Derived>::IteratorType ContainerBase<_Derived>::end() noexcept {
  return IteratorType::getEnd(&(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  end
///
template <class _Derived>
typename ContainerBase<_Derived>::ConstIteratorType ContainerBase<_Derived>::end() const noexcept {
  return ConstIteratorType::getEnd(&(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  end
///
template <class _Derived>
typename ContainerBase<_Derived>::ConstIteratorType ContainerBase<_Derived>::cend() const noexcept {
  return ConstIteratorType::getEnd(&(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index iterator to beginning.
///
template <class _Derived>
typename ContainerBase<_Derived>::IdxIteratorType ContainerBase<_Derived>::ibegin() noexcept {
  return IdxIteratorType::getBegin(&(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  ibegin
///
template <class _Derived>
typename ContainerBase<_Derived>::ConstIdxIteratorType ContainerBase<_Derived>::ibegin() const noexcept {
  return ConstIdxIteratorType::getBegin(&(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  ibegin
///
template <class _Derived>
typename ContainerBase<_Derived>::ConstIdxIteratorType ContainerBase<_Derived>::cibegin() const noexcept {
  return ConstIdxIteratorType::getBegin(&(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index iterator to end.
///
template <class _Derived>
typename ContainerBase<_Derived>::IdxIteratorType ContainerBase<_Derived>::iend() noexcept {
  return IdxIteratorType::getEnd(&(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  iend
///
template <class _Derived>
typename ContainerBase<_Derived>::ConstIdxIteratorType ContainerBase<_Derived>::iend() const noexcept {
  return ConstIdxIteratorType::getEnd(&(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  iend
///
template <class _Derived>
typename ContainerBase<_Derived>::ConstIdxIteratorType ContainerBase<_Derived>::ciend() const noexcept {
  return ConstIdxIteratorType::getEnd(&(this->derived()));
}

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_BASE_CONTAINER_BASE_IPP_
