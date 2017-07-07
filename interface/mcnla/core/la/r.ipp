////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    interface/mcnla/core/la/r.ipp
/// @brief   The BLAS R routine interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_INTERFACE_CORE_LA_R_IPP_
#define MCNLA_INTERFACE_CORE_LA_R_IPP_

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
/// @brief  Performs a rank-1 update.
///
template <class _A, class _X, typename _Val>
inline void r(
          MatrixWrapper<_A> &a,
    const VectorWrapper<_X> &x,
    const _Val alpha = 1,
    const _Val beta = 0
) noexcept;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_interface_module
/// @brief  Performs a rank-1 update (conjugated).
///
template <class _A, class _X, class _Y, typename _Val>
inline void r(
          MatrixWrapper<_A> &a,
    const VectorWrapper<_X> &x,
    const VectorWrapper<_Y> &y,
    const _Val alpha = 1,
    const _Val beta = 0
) noexcept;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_interface_module
/// @brief  Performs a rank-1 update (unconjugated).
///
template <class _A, class _X, class _Y, typename _Val>
inline void ru(
          MatrixWrapper<_A> &a,
    const VectorWrapper<_X> &x,
    const VectorWrapper<_Y> &y,
    const _Val alpha = 1,
    const _Val beta = 0
) noexcept;

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_INTERFACE_CORE_LA_R_IPP_
