////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/blas/routine/scal.hpp
/// @brief   The BLAS SCAL routine.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_BLAS_ROUTINE_SCAL_HPP_
#define ISVD_BLAS_ROUTINE_SCAL_HPP_

#include <isvd/matrix.hpp>
#include <isvd/blas/blas.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

extern "C" {

#include <isvd/plugin/blas_plugin_start.h>

// Computes the product of a vector by a scalar.
extern void sscal_( const FORTRAN_INT8 n, const FORTRAN_REAL4 alpha, FORTRAN_REAL4 x, const FORTRAN_INT8 incx );
extern void dscal_( const FORTRAN_INT8 n, const FORTRAN_REAL8 alpha, FORTRAN_REAL8 x, const FORTRAN_INT8 incx );
extern void cscal_( const FORTRAN_INT8 n, const FORTRAN_COMP4 alpha, FORTRAN_COMP4 x, const FORTRAN_INT8 incx );
extern void zscal_( const FORTRAN_INT8 n, const FORTRAN_COMP8 alpha, FORTRAN_COMP8 x, const FORTRAN_INT8 incx );

#include <isvd/plugin/blas_plugin_end.h>

}  // extern "C"

#endif  // DOXYGEN_SHOULD_SKIP_THIS

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
/// @copydoc isvd::blas::scal
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
//@{
template <typename _Scalar>
inline void scal(
    const typename DenseVector<_Scalar>::ScalarType alpha,
          DenseVector<_Scalar> &x
) noexcept {
  internal::scal(x.getLength(), alpha, x.getValue(), x.getIncrement());
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
