////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/asum.hpp
/// @brief   The BLAS ASUM routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_ASUM_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_ASUM_HPP_

#include <mcnla/core/la/def.hpp>
#include <cmath>
#include <complex>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/raw/blas/asum.hpp>

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
/// @brief  Computes the sum of magnitudes of the vector elements.
///
//@{
template <typename _Scalar>
inline _Scalar asum(
    const DenseVector<_Scalar> &x
) noexcept {
  return detail::asum(x.length(), x.valPtr(), x.stride());
}
//@}

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_ASUM_HPP_
