////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/blas/routine/iamin.hpp
/// @brief   The BLAS IAMIN routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_BLAS_ROUTINE_IAMIN_HPP_
#define MCNLA_CORE_BLAS_ROUTINE_IAMIN_HPP_

#include <cmath>
#include <complex>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/blas/blas/iamin.hpp>

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
/// @brief  Finds the index of the element with minimum absolute value.
///
//@{
template <typename _Scalar>
inline index_t iamin(
    const DenseVector<_Scalar> &x
) noexcept {
  return detail::iamin(x.length(), x.valuePtr(), x.stride());
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  blas1_module
/// @brief  Finds the element with minimum absolute value.
///
//@{
template <typename _Scalar>
inline RealType<_Scalar> amin(
    const DenseVector<_Scalar> &x
) noexcept {
  index_t idx = detail::iamin(x.length(), x.valuePtr(), x.stride());
  return std::abs(x(idx));
}
//@}

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_ROUTINE_IAMIN_HPP_
