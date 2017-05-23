////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/utility/crtp.hpp
/// @brief   The curiously recurring template pattern utilities.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_UTILITY_CRTP_HPP_
#define MCNLA_CORE_UTILITY_CRTP_HPP_

#include <mcnla/core/utility/def.hpp>

#define CRTP_BASE( _Base ) \
    inline _Base& base() noexcept { return static_cast<_Base&>(*this); } \
    inline const _Base& base() const noexcept { return static_cast<const _Base&>(*this); }

#define CRTP_DERIVED( _Derived ) \
    inline _Derived& derived() noexcept { return static_cast<_Derived&>(*this); } \
    inline const _Derived& derived() const noexcept { return static_cast<const _Derived&>(*this); }

#endif  // MCNLA_CORE_UTILITY_CRTP_HPP_
