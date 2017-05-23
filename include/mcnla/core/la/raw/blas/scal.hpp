////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/raw/blas/scal.hpp
/// @brief   The BLAS SCAL.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_RAW_BLAS_SCAL_HPP_
#define MCNLA_CORE_LA_RAW_BLAS_SCAL_HPP_

#include <mcnla/core/la/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <mcnla/core/la/raw/plugin/blas_plugin_begin.h>

// Computes the product of a vector by a scalar.
extern void sscal_(  const FORTRAN_INT n, const FORTRAN_REAL4 alpha, FORTRAN_REAL4 x, const FORTRAN_INT incx );
extern void dscal_(  const FORTRAN_INT n, const FORTRAN_REAL8 alpha, FORTRAN_REAL8 x, const FORTRAN_INT incx );
extern void cscal_(  const FORTRAN_INT n, const FORTRAN_COMP4 alpha, FORTRAN_COMP4 x, const FORTRAN_INT incx );
extern void zscal_(  const FORTRAN_INT n, const FORTRAN_COMP8 alpha, FORTRAN_COMP8 x, const FORTRAN_INT incx );
extern void csscal_( const FORTRAN_INT n, const FORTRAN_REAL4 alpha, FORTRAN_COMP4 x, const FORTRAN_INT incx );
extern void zdscal_( const FORTRAN_INT n, const FORTRAN_REAL8 alpha, FORTRAN_COMP8 x, const FORTRAN_INT incx );

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes the product of a vector by a scalar.
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
static inline void scal(
    const index_t n, const float alpha, std::complex<float>* x, const index_t incx
) noexcept { csscal_(&n, &alpha, x, &incx); }
static inline void scal(
    const index_t n, const double alpha, std::complex<double>* x, const index_t incx
) noexcept { zdscal_(&n, &alpha, x, &incx); }
//@}

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_RAW_BLAS_SCAL_HPP_
