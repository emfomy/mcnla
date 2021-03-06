////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/raw/lapack/syev.hpp
/// @brief   The LAPACK SYEV.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_RAW_LAPACK_SYEV_HPP_
#define MCNLA_CORE_LA_RAW_LAPACK_SYEV_HPP_

#include <mcnla/core/la/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <mcnla/core/la/raw/plugin/lapack_plugin_begin.h>

extern void ssyev_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT n, FORTRAN_REAL4 a,
                    const FORTRAN_INT lda, FORTRAN_REAL4 w, FORTRAN_REAL4 work, const FORTRAN_INT lwork,
                    FORTRAN_INT info );
extern void dsyev_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT n, FORTRAN_REAL8 a,
                    const FORTRAN_INT lda, FORTRAN_REAL8 w, FORTRAN_REAL8 work, const FORTRAN_INT lwork,
                    FORTRAN_INT info );
extern void cheev_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT n, FORTRAN_COMP4 a,
                    const FORTRAN_INT lda, FORTRAN_REAL4 w, FORTRAN_COMP4 work, const FORTRAN_INT lwork, FORTRAN_REAL4 rwork,
                    FORTRAN_INT info );
extern void zheev_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT n, FORTRAN_COMP8 a,
                    const FORTRAN_INT lda, FORTRAN_REAL8 w, FORTRAN_COMP8 work, const FORTRAN_INT lwork, FORTRAN_REAL8 rwork,
                    FORTRAN_INT info );

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
static inline index_t syev(
    const char jobz, const char uplo, const index_t n,
    float *a, const index_t lda, float *w, float *work, const index_t lwork, float *rwork
) noexcept { static_cast<void>(rwork); index_t info; ssyev_(&jobz, &uplo, &n, a, &lda, w, work, &lwork, &info); return info; }
static inline index_t syev(
    const char jobz, const char uplo, const index_t n,
    double *a, const index_t lda, double *w, double *work, const index_t lwork, double *rwork
) noexcept { static_cast<void>(rwork); index_t info; dsyev_(&jobz, &uplo, &n, a, &lda, w, work, &lwork, &info); return info; }
static inline index_t syev(
    const char jobz, const char uplo, const index_t n,
    std::complex<float> *a, const index_t lda, float *w, std::complex<float> *work, const index_t lwork, float *rwork
) noexcept { index_t info; cheev_(&jobz, &uplo, &n, a, &lda, w, work, &lwork, rwork, &info); return info; }
static inline index_t syev(
    const char jobz, const char uplo, const index_t n,
    std::complex<double> *a, const index_t lda, double *w, std::complex<double> *work, const index_t lwork, double *rwork
) noexcept { index_t info; zheev_(&jobz, &uplo, &n, a, &lda, w, work, &lwork, rwork, &info); return info; }
//@}

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_RAW_LAPACK_SYEV_HPP_
