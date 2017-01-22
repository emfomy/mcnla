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
/// @ingroup  matrix_module
/// The container wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class IterableWrapper : public utility::CrtpBase<_Derived, IterableWrapper<_Derived>> {

 private:

  using IteratorType      = IteratorT<_Derived>;
  using ConstIteratorType = ConstIteratorT<_Derived>;

 protected:

  // Constructors
  inline IterableWrapper() noexcept = default;

 public:

  // Gets iterator
  inline IteratorType      begin() noexcept;
  inline ConstIteratorType begin() const noexcept;
  inline ConstIteratorType cbegin() const noexcept;
  inline IteratorType      end() noexcept;
  inline ConstIteratorType end() const noexcept;
  inline ConstIteratorType cend() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_BASE_ITERABLE_WRAPPER_HH_