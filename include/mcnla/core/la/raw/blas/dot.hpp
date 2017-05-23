////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/raw/blas/dot.hpp
/// @brief   The BLAS DOT.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_RAW_BLAS_DOT_HPP_
#define MCNLA_CORE_LA_RAW_BLAS_DOT_HPP_

#include <mcnla/core/la/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <mcnla/core/la/raw/plugin/blas_plugin_begin.h>

// Computes a vector-vector dot product.
extern CPP_REAL4 sdot_(  const FORTRAN_INT n, const FORTRAN_REAL4 x, const FORTRAN_INT incx, const FORTRAN_REAL4 y,
                         const FORTRAN_INT incy );
extern CPP_REAL8 ddot_(  const FORTRAN_INT n, const FORTRAN_REAL8 x, const FORTRAN_INT incx, const FORTRAN_REAL8 y,
                         const FORTRAN_INT incy );
extern CPP_COMP4 cdotu_( const FORTRAN_INT n, const FORTRAN_COMP4 x, const FORTRAN_INT incx, const FORTRAN_COMP4 y,
                         const FORTRAN_INT incy );
extern CPP_COMP8 zdotu_( const FORTRAN_INT n, const FORTRAN_COMP8 x, const FORTRAN_INT incx, const FORTRAN_COMP8 y,
                         const FORTRAN_INT incy );
extern CPP_COMP4 cdotc_( const FORTRAN_INT n, const FORTRAN_COMP4 x, const FORTRAN_INT incx, const FORTRAN_COMP4 y,
                         const FORTRAN_INT incy );
extern CPP_COMP8 zdotc_( const FORTRAN_INT n, const FORTRAN_COMP8 x, const FORTRAN_INT incx, const FORTRAN_COMP8 y,
                         const FORTRAN_INT incy );

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
/// @brief  Computes a vector-vector dot product.
///
//@{
static inline float dot(
    const index_t n, const float* x, const index_t incx, const float* y, const index_t incy
) noexcept { return sdot_(&n, x, &incx, y, &incy); }
static inline double dot(
    const index_t n, const double* x, const index_t incx, const double* y, const index_t incy
) noexcept { return ddot_(&n, x, &incx, y, &incy); }
// static inline std::complex<float> dot(
//     const index_t n, std::complex<float>* x, const index_t incx, std::complex<float>* y, const index_t incy
// ) noexcept { return cdotu_(&n, x, &incx, y, &incy); }
// static inline std::complex<double> dot(
//     const index_t n, std::complex<double>* x, const index_t incx, std::complex<double>* y, const index_t incy
// ) noexcept { return zdotu_(&n, x, &incx, y, &incy); }
static inline std::complex<float> dot(
    const index_t n, const std::complex<float>* x, const index_t incx, const std::complex<float>* y, const index_t incy
) noexcept { return cdotc_(&n, x, &incx, y, &incy); }
static inline std::complex<double> dot(
    const index_t n, const std::complex<double>* x, const index_t incx, const std::complex<double>* y, const index_t incy
) noexcept { return zdotc_(&n, x, &incx, y, &incy); }
//@}

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_RAW_BLAS_DOT_HPP_
