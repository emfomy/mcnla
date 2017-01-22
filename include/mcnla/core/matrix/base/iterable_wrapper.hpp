////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/base/iterable_wrapper.hpp
/// @brief   The iterable container wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_BASE_ITERABLE_WRAPPER_HPP_
#define MCNLA_CORE_MATRIX_BASE_ITERABLE_WRAPPER_HPP_

#include <mcnla/core/matrix/base/iterable_wrapper.hh>

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
IteratorT<_Derived> IterableWrapper<_Derived>::begin() noexcept {
  return IteratorType::beginImpl(&(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  begin
///
template <class _Derived>
ConstIteratorT<_Derived> IterableWrapper<_Derived>::begin() const noexcept {
  return ConstIteratorType::beginImpl(&(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  begin
///
template <class _Derived>
ConstIteratorT<_Derived> IterableWrapper<_Derived>::cbegin() const noexcept {
  return ConstIteratorType::beginImpl(&(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the iterator to end.
///
template <class _Derived>
IteratorT<_Derived> IterableWrapper<_Derived>::end() noexcept {
  return IteratorType::endImpl(&(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  end
///
template <class _Derived>
ConstIteratorT<_Derived> IterableWrapper<_Derived>::end() const noexcept {
  return ConstIteratorType::endImpl(&(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  end
///
template <class _Derived>
ConstIteratorT<_Derived> IterableWrapper<_Derived>::cend() const noexcept {
  return ConstIteratorType::endImpl(&(this->derived()));
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_BASE_ITERABLE_WRAPPER_HPP_