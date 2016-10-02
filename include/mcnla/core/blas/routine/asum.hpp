////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/blas/routine/asum.hpp
/// @brief   The BLAS ASUM routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_BLAS_ROUTINE_ASUM_HPP_
#define MCNLA_CORE_BLAS_ROUTINE_ASUM_HPP_

#include <cmath>
#include <complex>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/blas/blas/asum.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The BLAS namespace
//
namespace blas {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  blas1_module
/// @brief  Computes the sum of magnitudes of the vector elements.
///
//@{
template <typename _Scalar>
inline _Scalar asum(
    const DenseVector<_Scalar> &x
) noexcept {
  return detail::asum(x.getLength(), x.getValue(), x.getStride());
}
//@}

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_ROUTINE_ASUM_HPP_
