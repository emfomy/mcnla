////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/blas/dense_scal.hpp
/// @brief   The BLAS SCAL routine for dense matrices
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_BLAS_DENSE_SCAL_HPP_
#define ISVD_BLAS_DENSE_SCAL_HPP_

#include <utility>
#include <isvd/matrix.hpp>
#include <isvd/blas/blas.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The BLAS namespace
//
namespace blas {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @scaldoc isvd::blas::scal
///
//@{
static inline void scal(
    const index_t n, const float alpha, float* x, const index_t incx
) noexcept { sscal_(&n, &alpha, x, &incx); }
static inline void scal(
    const index_t n, const double alpha, double* x, const index_t incx
) noexcept { dscal_(&n, &alpha, x, &incx); }
static inline void scal(
    const index_t n, const std::complex<float> alpha, std::complex<float>* x, const index_t incx
) noexcept { cscal_(&n, &alpha, x, &incx); }
static inline void scal(
    const index_t n, const std::complex<double> alpha, std::complex<double>* x, const index_t incx
) noexcept { zscal_(&n, &alpha, x, &incx); }
//@}

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes the product of a vector by a scalar.
///
template <class _Derived>
inline void scal(
    const typename isvd::internal::Traits<_Derived>::ScalarType alpha,
    isvd::internal::DenseVectorBase<_Derived> &x ) noexcept {
  internal::scal(x.getLength(), alpha, x.getValue(), x.getIncrement());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copies vector to another vector.
///
template <class _Derived>
inline void scal(
    const typename isvd::internal::Traits<_Derived>::ScalarType alpha,
    isvd::internal::DenseVectorBase<_Derived> &&x ) noexcept {
  scal(alpha, x);
}

}  // namespace blas

}  // namespace isvd

#endif  // ISVD_BLAS_DENSE_SCAL_HPP_
