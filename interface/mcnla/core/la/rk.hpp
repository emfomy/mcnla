////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    interface/mcnla/core/la/rk.hpp
/// @brief   The BLAS RK routine interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_INTERFACE_CORE_LA_RK_HPP_
#define MCNLA_INTERFACE_CORE_LA_RK_HPP_

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
/// @brief  Performs a rank-k update.
///
template <class _AType, class _CType, typename _Scalar>
inline void rk(
    const _AType &a,
		const _CType &c,
    const _Scalar alpha = 1,
    const _Scalar beta = 0
) noexcept;

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_INTERFACE_CORE_LA_RK_HPP_
