////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/raw/blas/axpy.hpp
/// @brief   The BLAS AXPY.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_RAW_BLAS_AXPY_HPP_
#define MCNLA_CORE_LA_RAW_BLAS_AXPY_HPP_

#include <mcnla/core/la/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <mcnla/core/la/raw/plugin/blas_plugin_begin.h>

extern void saxpy_( const FORTRAN_INT n, const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 x, const FORTRAN_INT incx,
                    FORTRAN_REAL4 y, const FORTRAN_INT incy );
extern void daxpy_( const FORTRAN_INT n, const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 x, const FORTRAN_INT incx,
                    FORTRAN_REAL8 y, const FORTRAN_INT incy );
extern void caxpy_( const FORTRAN_INT n, const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 x, const FORTRAN_INT incx,
                    FORTRAN_COMP4 y, const FORTRAN_INT incy );
extern void zaxpy_( const FORTRAN_INT n, const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 x, const FORTRAN_INT incx,
                    FORTRAN_COMP8 y, const FORTRAN_INT incy );

#include <mcnla/core/la/raw/plugin/blas_plugin_end.h>

#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The linear algebra namespace
//
namespace la {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace
//
namespace detail {

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

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_RAW_BLAS_AXPY_HPP_
