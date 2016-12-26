////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/base/container_wrapper.ipp
/// @brief   The implementation of container wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_BASE_CONTAINER_WRAPPER_IPP_
#define MCNLA_CORE_MATRIX_BASE_CONTAINER_WRAPPER_IPP_

#include <mcnla/core/matrix/base/container_wrapper.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the iterator to beginning.
///
template <class _Derived>
typename ContainerWrapper<_Derived>::IteratorType ContainerWrapper<_Derived>::begin() noexcept {
  return IteratorType::beginImpl(&(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  begin
///
template <class _Derived>
typename ContainerWrapper<_Derived>::ConstIteratorType ContainerWrapper<_Derived>::begin() const noexcept {
  return ConstIteratorType::beginImpl(&(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  begin
///
template <class _Derived>
typename ContainerWrapper<_Derived>::ConstIteratorType ContainerWrapper<_Derived>::cbegin() const noexcept {
  return ConstIteratorType::beginImpl(&(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the iterator to end.
///
template <class _Derived>
typename ContainerWrapper<_Derived>::IteratorType ContainerWrapper<_Derived>::end() noexcept {
  return IteratorType::endImpl(&(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  end
///
template <class _Derived>
typename ContainerWrapper<_Derived>::ConstIteratorType ContainerWrapper<_Derived>::end() const noexcept {
  return ConstIteratorType::endImpl(&(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  end
///
template <class _Derived>
typename ContainerWrapper<_Derived>::ConstIteratorType ContainerWrapper<_Derived>::cend() const noexcept {
  return ConstIteratorType::endImpl(&(this->derived()));
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_BASE_CONTAINER_WRAPPER_IPP_
