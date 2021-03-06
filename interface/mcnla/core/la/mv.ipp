////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    interface/mcnla/core/la/mv.ipp
/// @brief   The BLAS MV routine interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_INTERFACE_CORE_LA_MV_IPP_
#define MCNLA_INTERFACE_CORE_LA_MV_IPP_

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
/// @brief  Computes a matrix-vector product.
///
template <class _A, class _X, class _Y, typename _Val>
inline void mv(
    const MatrixWrapper<_A> &a,
    const VectorWrapper<_X> &x,
          VectorWrapper<_Y> &y,
    const _Val alpha = 1,
    const _Val beta = 0
) noexcept;

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_INTERFACE_CORE_LA_MV_IPP_
