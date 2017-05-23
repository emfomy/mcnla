////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/raw/blas/asum.hpp
/// @brief   The BLAS ASUM.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_RAW_BLAS_ASUM_HPP_
#define MCNLA_CORE_LA_RAW_BLAS_ASUM_HPP_

#include <mcnla/core/la/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <mcnla/core/la/raw/plugin/blas_plugin_begin.h>

// Computes the sum of magnitudes of the vector elements.
extern CPP_REAL4 sasum_( const FORTRAN_INT n, const FORTRAN_REAL4 x, const FORTRAN_INT incx );
extern CPP_REAL8 dasum_( const FORTRAN_INT n, const FORTRAN_REAL8 x, const FORTRAN_INT incx );
extern CPP_COMP4 casum_( const FORTRAN_INT n, const FORTRAN_COMP4 x, const FORTRAN_INT incx );
extern CPP_COMP8 zasum_( const FORTRAN_INT n, const FORTRAN_COMP8 x, const FORTRAN_INT incx );

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
/// @brief  Computes the sum of magnitudes of the vector elements.
///
//@{
static inline float asum(
    const index_t n, const float* x, const index_t incx
) noexcept { return sasum_(&n, x, &incx); }
static inline double asum(
    const index_t n, const double* x, const index_t incx
) noexcept { return dasum_(&n, x, &incx); }
static inline std::complex<float> asum(
    const index_t n, const std::complex<float>* x, const index_t incx
) noexcept { return casum_(&n, x, &incx); }
static inline std::complex<double> asum(
    const index_t n, const std::complex<double>* x, const index_t incx
) noexcept { return zasum_(&n, x, &incx); }
//@}

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_RAW_BLAS_ASUM_HPP_
