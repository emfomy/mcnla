////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/matrix/base/container_base.ipp
/// @brief   The implementation of container interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_MATRIX_BASE_CONTAINER_BASE_IPP_
#define MCNLA_MATRIX_BASE_CONTAINER_BASE_IPP_

#include <mcnla/matrix/base/container_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Change to derived class.
///
template <class _Derived>
_Derived& ContainerBase<_Derived>::derived() noexcept {
  return static_cast<_Derived&>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  derived
///
template <class _Derived>
const _Derived& ContainerBase<_Derived>::derived() const noexcept {
  return static_cast<const _Derived&>(*this);
}

}  // namespace mcnla

#endif  // MCNLA_MATRIX_BASE_CONTAINER_BASE_IPP_
