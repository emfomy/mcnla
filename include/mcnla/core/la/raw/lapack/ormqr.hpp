////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/raw/lapack/ormqr.hpp
/// @brief   The LAPACK ORMQR.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_RAW_LAPACK_ORMQR_HPP_
#define MCNLA_CORE_LA_RAW_LAPACK_ORMQR_HPP_

#include <mcnla/core/la/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <mcnla/core/la/raw/plugin/lapack_plugin_begin.h>

extern void sormqr_( const FORTRAN_CHAR1 side, const FORTRAN_CHAR1 trsns, const FORTRAN_INT m, const FORTRAN_INT n,
                     const FORTRAN_INT k, const FORTRAN_REAL4 a, const FORTRAN_INT lda, const FORTRAN_REAL4 tau,
                     FORTRAN_REAL4 c, const FORTRAN_INT ldc, FORTRAN_REAL4 work, const FORTRAN_INT lwork, FORTRAN_INT info );
extern void dormqr_( const FORTRAN_CHAR1 side, const FORTRAN_CHAR1 trsns, const FORTRAN_INT m, const FORTRAN_INT n,
                     const FORTRAN_INT k, const FORTRAN_REAL8 a, const FORTRAN_INT lda, const FORTRAN_REAL8 tau,
                     FORTRAN_REAL8 c, const FORTRAN_INT ldc, FORTRAN_REAL8 work, const FORTRAN_INT lwork, FORTRAN_INT info );
extern void cunmqr_( const FORTRAN_CHAR1 side, const FORTRAN_CHAR1 trsns, const FORTRAN_INT m, const FORTRAN_INT n,
                     const FORTRAN_INT k, const FORTRAN_COMP4 a, const FORTRAN_INT lda, const FORTRAN_COMP4 tau,
                     FORTRAN_COMP4 c, const FORTRAN_INT ldc, FORTRAN_COMP4 work, const FORTRAN_INT lwork, FORTRAN_INT info );
extern void zunmqr_( const FORTRAN_CHAR1 side, const FORTRAN_CHAR1 trsns, const FORTRAN_INT m, const FORTRAN_INT n,
                     const FORTRAN_INT k, const FORTRAN_COMP8 a, const FORTRAN_INT lda, const FORTRAN_COMP8 tau,
                     FORTRAN_COMP8 c, const FORTRAN_INT ldc, FORTRAN_COMP8 work, const FORTRAN_INT lwork, FORTRAN_INT info );

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
static inline index_t ormqr(
    const char side, const char trans, const index_t m, const index_t n, const index_t k,
    const float *a, const index_t lda, const float *tau,
    float *c, const index_t ldc, float *work, const index_t lwork
) noexcept { index_t info; sormqr_(&side, &trans, &m, &n, &k, a, &lda, tau, c, &ldc, work, &lwork, &info); return info; }
static inline index_t ormqr(
    const char side, const char trans, const index_t m, const index_t n, const index_t k,
    const double *a, const index_t lda, const double *tau,
    double *c, const index_t ldc, double *work, const index_t lwork
) noexcept { index_t info; dormqr_(&side, &trans, &m, &n, &k, a, &lda, tau, c, &ldc, work, &lwork, &info); return info; }
static inline index_t ormqr(
    const char side, const char trans, const index_t m, const index_t n, const index_t k,
    const std::complex<float> *a, const index_t lda, const std::complex<float> *tau,
    std::complex<float> *c, const index_t ldc, std::complex<float> *work, const index_t lwork
) noexcept { index_t info; cunmqr_(&side, &trans, &m, &n, &k, a, &lda, tau, c, &ldc, work, &lwork, &info); return info; }
static inline index_t ormqr(
    const char side, const char trans, const index_t m, const index_t n, const index_t k,
    const std::complex<double> *a, const index_t lda, const std::complex<double> *tau,
    std::complex<double> *c, const index_t ldc, std::complex<double> *work, const index_t lwork
) noexcept { index_t info; zunmqr_(&side, &trans, &m, &n, &k, a, &lda, tau, c, &ldc, work, &lwork, &info); return info; }
//@}

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_RAW_LAPACK_ORMQR_HPP_
