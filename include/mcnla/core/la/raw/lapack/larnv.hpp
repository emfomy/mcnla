////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/raw/lapack/larnv.hpp
/// @brief   The LAPACK LARNV.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_RAW_LAPACK_LARNV_HPP_
#define MCNLA_CORE_LA_RAW_LAPACK_LARNV_HPP_

#include <mcnla/core/la/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <mcnla/core/la/raw/plugin/lapack_plugin_begin.h>

// Returns a vector of random numbers from a uniform or normal distribution.
extern void slarnv_( const FORTRAN_INT idist, FORTRAN_INT iseed, const FORTRAN_INT n, FORTRAN_REAL4 x );
extern void dlarnv_( const FORTRAN_INT idist, FORTRAN_INT iseed, const FORTRAN_INT n, FORTRAN_REAL8 x );
extern void clarnv_( const FORTRAN_INT idist, FORTRAN_INT iseed, const FORTRAN_INT n, FORTRAN_COMP4 x );
extern void zlarnv_( const FORTRAN_INT idist, FORTRAN_INT iseed, const FORTRAN_INT n, FORTRAN_COMP8 x );

#include <mcnla/core/la/raw/plugin/lapack_plugin_end.h>

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
/// @brief  Returns a vector of random numbers from a uniform or normal distribution.
///
//@{
static inline void larnv(
    const index_t idist, index_t iseed[4], const index_t n, float *x
) noexcept { slarnv_(&idist, iseed, &n, x); }
static inline void larnv(
    const index_t idist, index_t iseed[4], const index_t n, double *x
) noexcept { dlarnv_(&idist, iseed, &n, x); }
static inline void larnv(
    const index_t idist, index_t iseed[4], const index_t n, std::complex<float> *x
) noexcept { clarnv_(&idist, iseed, &n, x); }
static inline void larnv(
    const index_t idist, index_t iseed[4], const index_t n, std::complex<double> *x
) noexcept { zlarnv_(&idist, iseed, &n, x); }
//@}

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_RAW_LAPACK_LARNV_HPP_
