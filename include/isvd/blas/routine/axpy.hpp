////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/blas/routine/axpy.hpp
/// @brief   The BLAS AXPY routine.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_BLAS_ROUTINE_AXPY_HPP_
#define ISVD_BLAS_ROUTINE_AXPY_HPP_

#include <isvd/matrix.hpp>
#include <isvd/blas/blas/axpy.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace
//
namespace isvd {

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

}  // namespace isvd

#endif  // ISVD_BLAS_ROUTINE_AXPY_HPP_
