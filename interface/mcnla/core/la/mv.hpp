////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    interface/mcnla/core/la/mv.hpp
/// @brief   The BLAS MV routine interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_INTERFACE_CORE_LA_MV_HPP_
#define MCNLA_INTERFACE_CORE_LA_MV_HPP_

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
/// @brief  Computes a matrix-vector product.
///
template <class _AType, class _XType, class _YType, typename _Scalar>
inline void mv(
    const _AType &a,
    const _XType &x,
          _YType &y,
    const _Scalar alpha = 1,
    const _Scalar beta = 0
) noexcept;

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_INTERFACE_CORE_LA_MV_HPP_
