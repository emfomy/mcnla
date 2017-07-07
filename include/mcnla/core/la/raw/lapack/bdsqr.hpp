////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/raw/lapack/bdsqr.hpp
/// @brief   The LAPACK BDSQR.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_RAW_LAPACK_BDSQR_HPP_
#define MCNLA_CORE_LA_RAW_LAPACK_BDSQR_HPP_

#include <mcnla/core/la/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <mcnla/core/la/raw/plugin/lapack_plugin_begin.h>

extern void sbdsqr_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT n, const FORTRAN_INT ncvt, const FORTRAN_INT nru,
                     const FORTRAN_INT ncc, FORTRAN_REAL4 d, FORTRAN_REAL4 e, FORTRAN_REAL4 vt, const FORTRAN_INT ldvt,
                     FORTRAN_REAL4 u, const FORTRAN_INT ldu, FORTRAN_REAL4 c, const FORTRAN_INT ldc, FORTRAN_REAL4 work,
                     FORTRAN_INT info );
extern void dbdsqr_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT n, const FORTRAN_INT ncvt, const FORTRAN_INT nru,
                     const FORTRAN_INT ncc, FORTRAN_REAL8 d, FORTRAN_REAL8 e, FORTRAN_REAL8 vt, const FORTRAN_INT ldvt,
                     FORTRAN_REAL8 u, const FORTRAN_INT ldu, FORTRAN_REAL8 c, const FORTRAN_INT ldc, FORTRAN_REAL8 work,
                     FORTRAN_INT info );
extern void cbdsqr_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT n, const FORTRAN_INT ncvt, const FORTRAN_INT nru,
                     const FORTRAN_INT ncc, FORTRAN_REAL4 d, FORTRAN_REAL4 e, FORTRAN_COMP4 vt, const FORTRAN_INT ldvt,
                     FORTRAN_COMP4 u, const FORTRAN_INT ldu, FORTRAN_COMP4 c, const FORTRAN_INT ldc, FORTRAN_REAL4 rwork,
                     FORTRAN_INT info );
extern void zbdsqr_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT n, const FORTRAN_INT ncvt, const FORTRAN_INT nru,
                     const FORTRAN_INT ncc, FORTRAN_REAL8 d, FORTRAN_REAL8 e, FORTRAN_COMP8 vt, const FORTRAN_INT ldvt,
                     FORTRAN_COMP8 u, const FORTRAN_INT ldu, FORTRAN_COMP8 c, const FORTRAN_INT ldc, FORTRAN_REAL8 rwork,
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
static inline index_t bdsqr(
    const char uplo, const index_t n, const index_t ncvt, const index_t nru, const index_t ncc,
    float *d, float *e, float *vt, const index_t ldvt, float *u, const index_t ldu,
    float *c, const index_t ldc, float *work
) noexcept {
  index_t info; sbdsqr_(&uplo, &n, &ncvt, &nru, &ncc, d, e, vt, &ldvt, u, &ldu, c, &ldc, work, &info); return info;
}
static inline index_t bdsqr(
    const char uplo, const index_t n, const index_t ncvt, const index_t nru, const index_t ncc,
    double *d, double *e, double *vt, const index_t ldvt, double *u, const index_t ldu,
    double *c, const index_t ldc, double *work
) noexcept {
  index_t info; dbdsqr_(&uplo, &n, &ncvt, &nru, &ncc, d, e, vt, &ldvt, u, &ldu, c, &ldc, work, &info); return info;
}
static inline index_t bdsqr(
    const char uplo, const index_t n, const index_t ncvt, const index_t nru, const index_t ncc,
    float *d, float *e, std::complex<float> *vt, const index_t ldvt, std::complex<float> *u, const index_t ldu,
    std::complex<float> *c, const index_t ldc, float *rwork
) noexcept {
  index_t info; cbdsqr_(&uplo, &n, &ncvt, &nru, &ncc, d, e, vt, &ldvt, u, &ldu, c, &ldc, rwork, &info); return info;
}
static inline index_t gebrd(
    const char uplo, const index_t n, const index_t ncvt, const index_t nru, const index_t ncc,
    double *d, double *e, std::complex<double> *vt, const index_t ldvt, std::complex<double> *u, const index_t ldu,
    std::complex<double> *c, const index_t ldc, double *rwork
) noexcept {
  index_t info; zbdsqr_(&uplo, &n, &ncvt, &nru, &ncc, d, e, vt, &ldvt, u, &ldu, c, &ldc, rwork, &info); return info;
}
//@}

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_RAW_LAPACK_BDSQR_HPP_
