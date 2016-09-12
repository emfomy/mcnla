////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/blas/routine/scal.hpp
/// @brief   The BLAS SCAL routine.
///
/// @author  Mu Yang <emfomy@gmail.com>
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
/// @copydoc  isvd::blas::internal::scal
///
//@{
template <typename _Scalar>
inline void scal(
    const typename DenseVector<_Scalar>::ScalarType alpha,
          DenseVector<_Scalar> &x
) noexcept {
  internal::scal(x.getLength(), alpha, x.getValue(), x.getStride());
}

template <typename _Scalar>
inline void scal(
    const typename DenseVector<_Scalar>::ScalarType alpha,
          DenseVector<_Scalar> &&x
) noexcept {
  scal(alpha, x);
}
//@}

}  // namespace blas

}  // namespace isvd

#endif  // ISVD_BLAS_ROUTINE_SCAL_HPP_
