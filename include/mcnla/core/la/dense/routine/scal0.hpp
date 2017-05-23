////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/scal0.hpp
/// @brief   The BLAS SCAL0 routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_SCAL0_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_SCAL0_HPP_

#include <mcnla/core/la/def.hpp>
#include <cstring>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/dense/routine/scal.hpp>
#include <mcnla/core/la/dense/routine/memset0.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The linear algebra namespace
//
namespace la {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas1_module
/// @brief  Computes the product of a vector by zero.
///
/// @attention  It is inefficient if the stride is not 1.
///             Uses memset0() instead if the out-of-range spaces are useless.
/// @attention  However, memset0() is slow if the stride is vary large.
///
template <typename _Val>
inline void scal0(
  DenseVector<_Val> &x
) noexcept {
  if ( x.isShrunk() ) {
    memset0(x);
  } else {
    scal(x, 0);
  }
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void scal0(
  DenseVector<_Val> &&x
) noexcept {
  scal0(x);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_SCAL0_HPP_
