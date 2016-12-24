////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/utility/crtp.hpp
/// @brief   The curiously recurring template pattern utilities.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_UTILITY_CRTP_HPP_
#define MCNLA_CORE_UTILITY_CRTP_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The utility namespace.
//
namespace utility {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_module
/// The curiously recurring template pattern (CRTP) interface.
///
/// @tparam  _Derived  The derived types.
/// @tparam  _Base     The interface class type.
///
template <class _Derived, class _Base = void>
class CrtpBase {

 protected:

  inline CrtpBase() noexcept = default;

 public:

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief  Cast to derived class.
  ///
  inline _Derived& derived() noexcept {
    return static_cast<_Derived&>(*this);
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @copydoc  derived
  ///
  inline const _Derived& derived() const noexcept {
    return static_cast<const _Derived&>(*this);
  }

};

}  // namespace utility

}  // namespace mcnla

#endif  // MCNLA_CORE_UTILITY_CRTP_HPP_
