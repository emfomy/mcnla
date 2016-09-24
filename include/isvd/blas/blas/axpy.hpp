////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/blas/blas/axpy.hpp
/// @brief   The BLAS AXPY.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_BLAS_BLAS_AXPY_HPP_
#define ISVD_BLAS_BLAS_AXPY_HPP_

#include <isvd/isvd.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <isvd/plugin/blas_plugin_begin.h>

// Computes a vector-scalar product and adds the result to a vector.
extern void saxpy_( const FORTRAN_INT n, const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 x, const FORTRAN_INT incx,
                    FORTRAN_REAL4 y, const FORTRAN_INT incy );
extern void daxpy_( const FORTRAN_INT n, const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 x, const FORTRAN_INT incx,
                    FORTRAN_REAL8 y, const FORTRAN_INT incy );
extern void caxpy_( const FORTRAN_INT n, const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 x, const FORTRAN_INT incx,
                    FORTRAN_COMP4 y, const FORTRAN_INT incy );
extern void zaxpy_( const FORTRAN_INT n, const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 x, const FORTRAN_INT incx,
                    FORTRAN_COMP8 y, const FORTRAN_INT incy );

#include <isvd/plugin/blas_plugin_end.h>

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
//  The detail namespace
//
namespace detail {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes a vector-scalar product and adds the result to a vector.
///
//@{
static inline void axpy(
    const index_t n, const float alpha,
    const float* x, const index_t incx, float* y, const index_t incy
) noexcept { saxpy_(&n, &alpha, x, &incx, y, &incy); }
static inline void axpy(
    const index_t n, const double alpha,
    const double* x, const index_t incx, double* y, const index_t incy
) noexcept { daxpy_(&n, &alpha, x, &incx, y, &incy); }
static inline void axpy(
    const index_t n, const std::complex<float> alpha,
    const std::complex<float>* x, const index_t incx, std::complex<float>* y, const index_t incy
) noexcept { caxpy_(&n, &alpha, x, &incx, y, &incy); }
static inline void axpy(
    const index_t n, const std::complex<double> alpha,
    const std::complex<double>* x, const index_t incx, std::complex<double>* y, const index_t incy
) noexcept { zaxpy_(&n, &alpha, x, &incx, y, &incy); }
//@}

}  // namespace detail

}  // namespace blas

}  // namespace isvd

#endif  // ISVD_BLAS_BLAS_AXPY_HPP_
