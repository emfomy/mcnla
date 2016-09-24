////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/lapack/lapack/larnv.hpp
/// @brief   The LAPACK LARNV.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_LAPACK_LAPACK_LARNV_HPP_
#define ISVD_LAPACK_LAPACK_LARNV_HPP_

#include <isvd/isvd.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <isvd/plugin/lapack_plugin_begin.h>

// Returns a vector of random numbers from a uniform or normal distribution.
extern void slarnv_( const FORTRAN_INT idist, FORTRAN_INT iseed, const FORTRAN_INT n, FORTRAN_REAL4 x );
extern void dlarnv_( const FORTRAN_INT idist, FORTRAN_INT iseed, const FORTRAN_INT n, FORTRAN_REAL8 x );
extern void clarnv_( const FORTRAN_INT idist, FORTRAN_INT iseed, const FORTRAN_INT n, FORTRAN_COMP4 x );
extern void zlarnv_( const FORTRAN_INT idist, FORTRAN_INT iseed, const FORTRAN_INT n, FORTRAN_COMP8 x );

#include <isvd/plugin/lapack_plugin_end.h>

#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The LAPACK namespace
//
namespace lapack {

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

}  // namespace lapack

}  // namespace isvd

#endif  // ISVD_LAPACK_LAPACK_LARNV_HPP_
