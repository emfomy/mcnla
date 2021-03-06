////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    interface/mcnla/core/la/sm.ipp
/// @brief   The BLAS SM routine interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_INTERFACE_CORE_LA_SM_IPP_
#define MCNLA_INTERFACE_CORE_LA_SM_IPP_

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
/// @brief  Solves a system of linear equations with multiple right-hand sides.
///
//@{
template <class _A, class _B, typename _Val>
inline void sm(
    const InverseView<MatrixWrapper<_A>> &a,
          MatrixWrapper<_B> &b,
    const _Val alpha = 1
) noexcept;

template <class _A, class _B, typename _Val>
inline void sm(
          MatrixWrapper<_B> &b,
    const InverseView<MatrixWrapper<_A>> &a,
    const _Val alpha = 1
) noexcept;
//@}

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_INTERFACE_CORE_LA_SM_IPP_
