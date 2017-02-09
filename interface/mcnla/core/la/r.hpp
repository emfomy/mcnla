////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    interface/mcnla/core/la/r.hpp
/// @brief   The BLAS R routine interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_INTERFACE_CORE_LA_R_HPP_
#define MCNLA_INTERFACE_CORE_LA_R_HPP_

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
/// @brief  Performs a rank-1 update.
///
template <class _AType, class _XType, typename _Scalar>
inline void r(
          _AType &a,
    const _XType &x,
    const _Scalar alpha = 1,
    const _Scalar beta = 0
) noexcept;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_interface_module
/// @brief  Performs a rank-1 update (conjugated).
///
template <class _AType, class _XType, class _YType, typename _Scalar>
inline void r(
          _AType &a,
    const _XType &x,
    const _XType &y,
    const _Scalar alpha = 1,
    const _Scalar beta = 0
) noexcept;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_interface_module
/// @brief  Performs a rank-1 update (unconjugated).
///
template <class _AType, class _XType, class _YType, typename _Scalar>
inline void ru(
          _AType &a,
    const _XType &x,
    const _XType &y,
    const _Scalar alpha = 1,
    const _Scalar beta = 0
) noexcept;

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_INTERFACE_CORE_LA_R_HPP_
