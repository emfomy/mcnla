////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/blas/routine/scal.hpp
/// @brief   The BLAS SCAL routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_BLAS_ROUTINE_SCAL_HPP_
#define MCNLA_BLAS_ROUTINE_SCAL_HPP_

#include <mcnla/matrix.hpp>
#include <mcnla/blas/blas/scal.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The BLAS namespace
//
namespace blas {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes the product of a vector by a scalar.
///
//@{
template <typename _Scalar>
inline void scal(
    const typename DenseVector<_Scalar>::ScalarType alpha,
          DenseVector<_Scalar> &x
) noexcept {
  detail::scal(x.getLength(), alpha, x.getValue(), x.getStride());
}

template <typename _Scalar>
inline void scal(
    const typename DenseVector<std::complex<_Scalar>>::RealScalarType alpha,
          DenseVector<std::complex<_Scalar>> &x
) noexcept {
  detail::scal(x.getLength(), alpha, x.getValue(), x.getStride());
}

template <typename _Scalar>
inline void scal(
    const typename DenseVector<_Scalar>::ScalarType alpha,
          DenseVector<_Scalar> &&x
) noexcept {
  scal(alpha, x);
}

template <typename _Scalar>
inline void scal(
    const typename DenseVector<std::complex<_Scalar>>::RealScalarType alpha,
          DenseVector<std::complex<_Scalar>> &&x
) noexcept {
  scal(alpha, x);
}
//@}

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_BLAS_ROUTINE_SCAL_HPP_
