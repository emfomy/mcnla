////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/blas/routine/axpby.hpp
/// @brief   The BLAS AXPBY routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_BLAS_ROUTINE_AXPBY_HPP_
#define MCNLA_CORE_BLAS_ROUTINE_AXPBY_HPP_

#include <mcnla/core/matrix.hpp>
#include <mcnla/core/blas/blas/axpby.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The BLAS namespace
//
namespace blas {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Scales two vectors, adds them to one another and stores result in the vector.
///
//@{
template <typename _Scalar>
inline void axpby(
    const typename DenseVector<_Scalar>::ScalarType alpha,
    const DenseVector<_Scalar> &x,
    const typename DenseVector<_Scalar>::ScalarType beta,
          DenseVector<_Scalar> &y
) noexcept {
  detail::axpby(x.getLength(), alpha, x.getValue(), x.getStride(), beta, y.getValue(), y.getStride());
}

template <typename _Scalar>
inline void axpby(
    const typename DenseVector<_Scalar>::ScalarType alpha,
    const DenseVector<_Scalar> &x,
    const typename DenseVector<_Scalar>::ScalarType beta,
          DenseVector<_Scalar> &&y
) noexcept {
  axpby(alpha, x, beta, y);
}
//@}

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_ROUTINE_AXPBY_HPP_