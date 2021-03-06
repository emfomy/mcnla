////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/raw/lapack/gelqf.hpp
/// @brief   The LAPACK GELQF.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_RAW_LAPACK_GELQF_HPP_
#define MCNLA_CORE_LA_RAW_LAPACK_GELQF_HPP_

#include <mcnla/core/la/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <mcnla/core/la/raw/plugin/lapack_plugin_begin.h>

extern void sgelqf_( const FORTRAN_INT m, const FORTRAN_INT n, FORTRAN_REAL4 a, const FORTRAN_INT lda, FORTRAN_REAL4 tau,
                     FORTRAN_REAL4 work, const FORTRAN_INT lwork, FORTRAN_INT info );
extern void dgelqf_( const FORTRAN_INT m, const FORTRAN_INT n, FORTRAN_REAL8 a, const FORTRAN_INT lda, FORTRAN_REAL8 tau,
                     FORTRAN_REAL8 work, const FORTRAN_INT lwork, FORTRAN_INT info );
extern void cgelqf_( const FORTRAN_INT m, const FORTRAN_INT n, FORTRAN_COMP4 a, const FORTRAN_INT lda, FORTRAN_COMP4 tau,
                     FORTRAN_COMP4 work, const FORTRAN_INT lwork, FORTRAN_INT info );
extern void zgelqf_( const FORTRAN_INT m, const FORTRAN_INT n, FORTRAN_COMP8 a, const FORTRAN_INT lda, FORTRAN_COMP8 tau,
                     FORTRAN_COMP8 work, const FORTRAN_INT lwork, FORTRAN_INT info );

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
static inline index_t gelqf(
    const index_t m, const index_t n, float *a, const index_t lda, float *tau,
    float *work, const index_t lwork
) noexcept { index_t info; sgelqf_(&m, &n, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t gelqf(
    const index_t m, const index_t n, double *a, const index_t lda, double *tau,
    double *work, const index_t lwork
) noexcept { index_t info; dgelqf_(&m, &n, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t gelqf(
    const index_t m, const index_t n, std::complex<float> *a, const index_t lda, std::complex<float> *tau,
    std::complex<float> *work, const index_t lwork
) noexcept { index_t info; cgelqf_(&m, &n, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t gelqf(
    const index_t m, const index_t n, std::complex<double> *a, const index_t lda, std::complex<double> *tau,
    std::complex<double> *work, const index_t lwork
) noexcept { index_t info; zgelqf_(&m, &n, a, &lda, tau, work, &lwork, &info); return info; }
//@}

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_RAW_LAPACK_GELQF_HPP_
