////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    interface/mcnla/core/la/rk.ipp
/// @brief   The BLAS RK routine interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_INTERFACE_CORE_LA_RK_IPP_
#define MCNLA_INTERFACE_CORE_LA_RK_IPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>

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
template <class _A, class _C, typename _Val>
inline void rk(
    const MatrixWrapper<_A> &a,
		      MatrixWrapper<_C> &c,
    const _Val alpha = 1,
    const _Val beta = 0
) noexcept;

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_INTERFACE_CORE_LA_RK_IPP_
