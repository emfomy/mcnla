////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/blas/dense_copy.hpp
/// @brief   The BLAS COPY routine for dense matrices
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_BLAS_DENSE_COPY_HPP_
#define ISVD_BLAS_DENSE_COPY_HPP_

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
/// @copydoc isvd::blas::copy
///
//@{
static inline void copy(
    const int64_t n, const float* x, const int64_t incx, float* y, const int64_t incy
) noexcept { scopy_(&n, x, &incx, y, &incy); }
static inline void copy(
    const int64_t n, const double* x, const int64_t incx, double* y, const int64_t incy
) noexcept { dcopy_(&n, x, &incx, y, &incy); }
static inline void copy(
    const int64_t n, const std::complex<float>* x, const int64_t incx, std::complex<float>* y, const int64_t incy
) noexcept { ccopy_(&n, x, &incx, y, &incy); }
static inline void copy(
    const int64_t n, const std::complex<double>* x, const int64_t incx, std::complex<double>* y, const int64_t incy
) noexcept { zcopy_(&n, x, &incx, y, &incy); }
//@}

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copies vector to another vector.
///
template <class _Derived>
inline void copy(
    const isvd::internal::DenseVectorBase<_Derived> &x,
          isvd::internal::DenseVectorBase<_Derived> &y ) noexcept {
  assert(y.getValue() != x.getValue());
  assert(y.getLength() == x.getLength());
  internal::copy(x.getLength(), x.getValue(), x.getIncrement(), y.getValue(), y.getIncrement());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copies vector to another vector.
///
template <class _Derived>
inline void copy(
    const isvd::internal::DenseVectorBase<_Derived> &x,
          isvd::internal::DenseVectorBase<_Derived> &&y ) noexcept {
  copy(x, y);
}

}  // namespace blas

}  // namespace isvd

#endif  // ISVD_BLAS_DENSE_COPY_HPP_
