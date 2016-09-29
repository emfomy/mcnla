////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/blas/routine/iamax.hpp
/// @brief   The BLAS IAMAX routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_BLAS_ROUTINE_IAMAX_HPP_
#define MCNLA_CORE_BLAS_ROUTINE_IAMAX_HPP_

#include <cmath>
#include <complex>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/blas/blas/iamax.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The BLAS namespace
//
namespace blas {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Finds the index of the element with maximum absolute value.
///
//@{
template <typename _Scalar>
inline index_t iamax(
    const DenseVector<_Scalar> &x
) noexcept {
  return detail::iamax(x.getLength(), x.getValue(), x.getStride());
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Finds the element with maximum absolute value.
///
//@{
template <typename _Scalar>
inline typename traits::ScalarTraits<_Scalar>::RealType amax(
    const DenseVector<_Scalar> &x
) noexcept {
  index_t idx = detail::iamax(x.getLength(), x.getValue(), x.getStride());
  return std::abs(x(idx));
}
//@}

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_ROUTINE_IAMAX_HPP_
