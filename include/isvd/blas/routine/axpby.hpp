////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/blas/routine/axpby.hpp
/// @brief   The BLAS AXPBY routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef ISVD_BLAS_ROUTINE_AXPBY_HPP_
#define ISVD_BLAS_ROUTINE_AXPBY_HPP_

#include <isvd/matrix.hpp>
#include <isvd/blas/blas/axpby.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace
//
namespace isvd {

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

}  // namespace isvd

#endif  // ISVD_BLAS_ROUTINE_AXPBY_HPP_
