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
template <class _Derived, class _Iter, class _ConstIter>
_Iter IterableWrapper<_Derived, _Iter, _ConstIter>::begin() noexcept {
  return _Iter::beginImpl(&(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  begin
///
template <class _Derived, class _Iter, class _ConstIter>
_ConstIter IterableWrapper<_Derived, _Iter, _ConstIter>::begin() const noexcept {
  return _ConstIter::beginImpl(&(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  begin
///
template <class _Derived, class _Iter, class _ConstIter>
_ConstIter IterableWrapper<_Derived, _Iter, _ConstIter>::cbegin() const noexcept {
  return _ConstIter::beginImpl(&(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the iterator to end.
///
template <class _Derived, class _Iter, class _ConstIter>
_Iter IterableWrapper<_Derived, _Iter, _ConstIter>::end() noexcept {
  return _Iter::endImpl(&(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  end
///
template <class _Derived, class _Iter, class _ConstIter>
_ConstIter IterableWrapper<_Derived, _Iter, _ConstIter>::end() const noexcept {
  return _ConstIter::endImpl(&(this->derived()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  end
///
template <class _Derived, class _Iter, class _ConstIter>
_ConstIter IterableWrapper<_Derived, _Iter, _ConstIter>::cend() const noexcept {
  return _ConstIter::endImpl(&(this->derived()));
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_BASE_ITERABLE_WRAPPER_HPP_
