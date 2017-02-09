////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    interface/mcnla/core/la/sm.hpp
/// @brief   The BLAS SM routine interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_INTERFACE_CORE_LA_SM_HPP_
#define MCNLA_INTERFACE_CORE_LA_SM_HPP_

#include <mcnla/core/la/def.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The linear algebra namespace
//
namespace la {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_interface_module
/// @brief  Solves a system of linear equations with multiple right-hand sides.
///
//@{
template <class _AInvType, class _BType, typename _Scalar>
inline void sm(
    const _AInvType &a,
          _BType &b,
    const _Scalar alpha = 1
) noexcept;

template <class _AInvType, class _BType, typename _Scalar>
inline void sm(
          _BType &b,
    const _AInvType &a,
    const _Scalar alpha = 1
) noexcept;
//@}

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_INTERFACE_CORE_LA_SM_HPP_
