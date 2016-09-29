////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/blas/routine/iamin.hpp
/// @brief   The BLAS IAMIN routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_BLAS_ROUTINE_IAMIN_HPP_
#define MCNLA_BLAS_ROUTINE_IAMIN_HPP_

#include <cmath>
#include <complex>
#include <mcnla/matrix.hpp>
#include <mcnla/blas/blas/iamin.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The BLAS namespace
//
namespace blas {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Finds the index of the element with minimum absolute value.
///
//@{
template <typename _Scalar>
inline index_t iamin(
    const DenseVector<_Scalar> &x
) noexcept {
  return detail::iamin(x.getLength(), x.getValue(), x.getStride());
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Finds the element with minimum absolute value.
///
//@{
template <typename _Scalar>
inline typename mcnla::detail::ScalarTraits<_Scalar>::RealType amin(
    const DenseVector<_Scalar> &x
) noexcept {
  index_t idx = detail::iamin(x.getLength(), x.getValue(), x.getStride());
  return std::abs(x(idx));
}
//@}

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_BLAS_ROUTINE_IAMIN_HPP_
