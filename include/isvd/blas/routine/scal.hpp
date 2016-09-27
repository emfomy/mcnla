////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/blas/routine/scal.hpp
/// @brief   The BLAS SCAL routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef ISVD_BLAS_ROUTINE_SCAL_HPP_
#define ISVD_BLAS_ROUTINE_SCAL_HPP_

#include <isvd/matrix.hpp>
#include <isvd/blas/blas/scal.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace
//
namespace isvd {

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

}  // namespace isvd

#endif  // ISVD_BLAS_ROUTINE_SCAL_HPP_
