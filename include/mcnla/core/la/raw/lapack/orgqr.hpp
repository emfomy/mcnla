////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/raw/lapack/orgqr.hpp
/// @brief   The LAPACK ORGQR.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_RAW_LAPACK_ORGQR_HPP_
#define MCNLA_CORE_LA_RAW_LAPACK_ORGQR_HPP_

#include <mcnla/core/la/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <mcnla/core/la/raw/plugin/lapack_plugin_begin.h>

extern void sorgqr_( const FORTRAN_INT m, const FORTRAN_INT n, const FORTRAN_INT k, FORTRAN_REAL4 a, const FORTRAN_INT lda,
                     const FORTRAN_REAL4 tau, FORTRAN_REAL4 work, const FORTRAN_INT lwork, FORTRAN_INT info );
extern void dorgqr_( const FORTRAN_INT m, const FORTRAN_INT n, const FORTRAN_INT k, FORTRAN_REAL8 a, const FORTRAN_INT lda,
                     const FORTRAN_REAL8 tau, FORTRAN_REAL8 work, const FORTRAN_INT lwork, FORTRAN_INT info );
extern void corgqr_( const FORTRAN_INT m, const FORTRAN_INT n, const FORTRAN_INT k, FORTRAN_COMP4 a, const FORTRAN_INT lda,
                     const FORTRAN_COMP4 tau, FORTRAN_COMP4 work, const FORTRAN_INT lwork, FORTRAN_INT info );
extern void zorgqr_( const FORTRAN_INT m, const FORTRAN_INT n, const FORTRAN_INT k, FORTRAN_COMP8 a, const FORTRAN_INT lda,
                     const FORTRAN_COMP8 tau, FORTRAN_COMP8 work, const FORTRAN_INT lwork, FORTRAN_INT info );

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

//@{
static inline index_t orgqr(
    const index_t m, const index_t n, const index_t k, float *a, const index_t lda, float *tau,
    float *work, const index_t lwork
) noexcept { index_t info; sorgqr_(&m, &n, &k, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t orgqr(
    const index_t m, const index_t n, const index_t k, double *a, const index_t lda, double *tau,
    double *work, const index_t lwork
) noexcept { index_t info; dorgqr_(&m, &n, &k, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t orgqr(
    const index_t m, const index_t n, const index_t k, std::complex<float> *a, const index_t lda, std::complex<float> *tau,
    std::complex<float> *work, const index_t lwork
) noexcept { index_t info; corgqr_(&m, &n, &k, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t orgqr(
    const index_t m, const index_t n, const index_t k, std::complex<double> *a, const index_t lda, std::complex<double> *tau,
    std::complex<double> *work, const index_t lwork
) noexcept { index_t info; zorgqr_(&m, &n, &k, a, &lda, tau, work, &lwork, &info); return info; }
//@}

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_RAW_LAPACK_ORGQR_HPP_
