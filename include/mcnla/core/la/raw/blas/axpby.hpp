////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/raw/blas/axpby.hpp
/// @brief   The BLAS AXPBY.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_RAW_BLAS_AXPBY_HPP_
#define MCNLA_CORE_LA_RAW_BLAS_AXPBY_HPP_

#include <mcnla/core/la/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#ifdef MCNLA_USE_MKL

#include <mcnla/core/la/raw/plugin/blas_plugin_begin.h>

// Scales two vectors, adds them to one another and stores result in the vector.
extern void saxpby_( const FORTRAN_INT n, const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 x, const FORTRAN_INT incx,
                     const FORTRAN_REAL4 beta, FORTRAN_REAL4 y, const FORTRAN_INT incy );
extern void daxpby_( const FORTRAN_INT n, const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 x, const FORTRAN_INT incx,
                     const FORTRAN_REAL8 beta, FORTRAN_REAL8 y, const FORTRAN_INT incy );
extern void caxpby_( const FORTRAN_INT n, const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 x, const FORTRAN_INT incx,
                     const FORTRAN_COMP4 beta, FORTRAN_COMP4 y, const FORTRAN_INT incy );
extern void zaxpby_( const FORTRAN_INT n, const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 x, const FORTRAN_INT incx,
                     const FORTRAN_COMP8 beta, FORTRAN_COMP8 y, const FORTRAN_INT incy );

#include <mcnla/core/la/raw/plugin/blas_plugin_end.h>

#else  // MCNLA_USE_MKL

#include <mcnla/core/la/raw/blas/axpy.hpp>
#include <mcnla/core/la/raw/blas/scal.hpp>

#endif  // MCNLA_USE_MKL

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Scales two vectors, adds them to one another and stores result in the vector.
///
//@{
#ifdef MCNLA_USE_MKL

static inline void axpby(
    const index_t n, const float alpha, const float* x, const index_t incx,
    const float beta, float* y, const index_t incy
) noexcept { saxpby_(&n, &alpha, x, &incx, &beta, y, &incy); }
static inline void axpby(
    const index_t n, const double alpha, const double* x, const index_t incx,
    const double beta, double* y, const index_t incy
) noexcept { daxpby_(&n, &alpha, x, &incx, &beta, y, &incy); }
static inline void axpby(
    const index_t n, const std::complex<float> alpha, const std::complex<float>* x, const index_t incx,
    const std::complex<float> beta, std::complex<float>* y, const index_t incy
) noexcept { caxpby_(&n, &alpha, x, &incx, &beta, y, &incy); }
static inline void axpby(
    const index_t n, const std::complex<double> alpha, const std::complex<double>* x, const index_t incx,
    const std::complex<double> beta, std::complex<double>* y, const index_t incy
) noexcept { zaxpby_(&n, &alpha, x, &incx, &beta, y, &incy); }

#else  // MCNLA_USE_MKL

template <typename _Scalar>
inline void axpby(
    const index_t n, const _Scalar alpha, const _Scalar* x, const index_t incx,
    const _Scalar beta, _Scalar* y, const index_t incy
) noexcept {
  scal(n, beta, y, incy);
  axpy(n, alpha, x, incx, 1, y, incy);
}

#endif  // MCNLA_USE_MKL
//@}

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_RAW_BLAS_AXPBY_HPP_
