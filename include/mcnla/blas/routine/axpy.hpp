////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/blas/routine/axpy.hpp
/// @brief   The BLAS AXPY routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_BLAS_ROUTINE_AXPY_HPP_
#define MCNLA_BLAS_ROUTINE_AXPY_HPP_

#include <mcnla/matrix.hpp>
#include <mcnla/blas/blas/axpy.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The BLAS namespace
//
namespace blas {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes a vector-scalar product and adds the result to a vector.
///
//@{
template <typename _Scalar>
inline void axpy(
    const typename DenseVector<_Scalar>::ScalarType alpha,
    const DenseVector<_Scalar> &x,
          DenseVector<_Scalar> &y
) noexcept {
  detail::axpy(x.getLength(), alpha, x.getValue(), x.getStride(), y.getValue(), y.getStride());
}

template <typename _Scalar>
inline void axpy(
    const typename DenseVector<_Scalar>::ScalarType alpha,
    const DenseVector<_Scalar> &x,
          DenseVector<_Scalar> &&y
) noexcept {
  axpy(alpha, x, y);
}
//@}

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_BLAS_ROUTINE_AXPY_HPP_
