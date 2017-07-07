////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/base/iterable_wrapper.hh
/// @brief   The definition of iterable container wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_BASE_ITERABLE_WRAPPER_HH_
#define MCNLA_CORE_MATRIX_BASE_ITERABLE_WRAPPER_HH_

#include <mcnla/core/matrix/def.hpp>
#include <mcnla/core/utility/crtp.hpp>
#include <mcnla/core/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The iterable container wrapper.
///
/// @tparam  _Derived    The derived type.
/// @tparam  _Iter       The iterator type.
/// @tparam  _ConstIter  The constant iterator type.
///
template <class _Derived, class _Iter, class _ConstIter>
class IterableWrapper {

 protected:

  // Constructors
  inline IterableWrapper() noexcept = default;

 public:

  // Gets iterator
  inline _Iter      begin() noexcept;
  inline _ConstIter begin() const noexcept;
  inline _ConstIter cbegin() const noexcept;
  inline _Iter      end() noexcept;
  inline _ConstIter end() const noexcept;
  inline _ConstIter cend() const noexcept;

 protected:

  MCNLA_CRTP_DERIVED(_Derived)

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_BASE_ITERABLE_WRAPPER_HH_
