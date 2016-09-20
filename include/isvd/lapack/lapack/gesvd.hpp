////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/lapack/lapack/gesvd.hpp
/// @brief   The LAPACK GESVD.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_LAPACK_LAPACK_GESVD_HPP_
#define ISVD_LAPACK_LAPACK_GESVD_HPP_

#include <isvd/isvd.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <isvd/plugin/lapack_plugin_begin.h>

// Computes the singular value decomposition of a general rectangular matrix.
extern void sgesvd_( const FORTRAN_CHAR1 jobu, const FORTRAN_CHAR1 jobvt, const FORTRAN_INT8 m, const FORTRAN_INT8 n,
                     FORTRAN_REAL4 a, const FORTRAN_INT8 lda, FORTRAN_REAL4 s, FORTRAN_REAL4 u, const FORTRAN_INT8 ldu,
                     FORTRAN_REAL4 vt, const FORTRAN_INT8 ldvt, FORTRAN_REAL4 work, const FORTRAN_INT8 lwork,
                                          FORTRAN_INT8 info );
extern void dgesvd_( const FORTRAN_CHAR1 jobu, const FORTRAN_CHAR1 jobvt, const FORTRAN_INT8 m, const FORTRAN_INT8 n,
                     FORTRAN_REAL8 a, const FORTRAN_INT8 lda, FORTRAN_REAL8 s, FORTRAN_REAL8 u, const FORTRAN_INT8 ldu,
                     FORTRAN_REAL8 vt, const FORTRAN_INT8 ldvt, FORTRAN_REAL8 work, const FORTRAN_INT8 lwork,
                                          FORTRAN_INT8 info );
extern void cgesvd_( const FORTRAN_CHAR1 jobu, const FORTRAN_CHAR1 jobvt, const FORTRAN_INT8 m, const FORTRAN_INT8 n,
                     FORTRAN_COMP4 a, const FORTRAN_INT8 lda, FORTRAN_REAL4 s, FORTRAN_COMP4 u, const FORTRAN_INT8 ldu,
                     FORTRAN_COMP4 vt, const FORTRAN_INT8 ldvt, FORTRAN_COMP4 work, const FORTRAN_INT8 lwork,
                     FORTRAN_REAL4 rwork, FORTRAN_INT8 info );
extern void zgesvd_( const FORTRAN_CHAR1 jobu, const FORTRAN_CHAR1 jobvt, const FORTRAN_INT8 m, const FORTRAN_INT8 n,
                     FORTRAN_COMP8 a, const FORTRAN_INT8 lda, FORTRAN_REAL8 s, FORTRAN_COMP8 u, const FORTRAN_INT8 ldu,
                     FORTRAN_COMP8 vt, const FORTRAN_INT8 ldvt, FORTRAN_COMP8 work, const FORTRAN_INT8 lwork,
                     FORTRAN_REAL8 rwork, FORTRAN_INT8 info );

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
/// @brief  Computes the singular value decomposition of a general rectangular matrix.
///
//@{
static inline index_t gesvd(
    const char jobu, const char jobvt, const index_t m, const index_t n,
    float *a, const index_t lda, float *s,
    float *u, const index_t ldu, float *vt, const index_t ldvt,
    float *work, const index_t lwork, float *rwork
) noexcept { static_cast<void>(rwork);
  index_t info; sgesvd_(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, vt, &ldvt, work, &lwork, &info); return info;
}
static inline index_t gesvd(
    const char jobu, const char jobvt, const index_t m, const index_t n,
    double *a, const index_t lda, double *s,
    double *u, const index_t ldu, double *vt, const index_t ldvt,
    double *work, const index_t lwork, double *rwork
) noexcept { static_cast<void>(rwork);
  index_t info; dgesvd_(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, vt, &ldvt, work, &lwork, &info); return info;
}
static inline index_t gesvd(
    const char jobu, const char jobvt, const index_t m, const index_t n,
    std::complex<float> *a, const index_t lda, float *s,
    std::complex<float> *u, const index_t ldu, std::complex<float> *vt, const index_t ldvt,
    std::complex<float> *work, const index_t lwork, float *rwork
) noexcept {
  index_t info; cgesvd_(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, vt, &ldvt, work, &lwork, rwork, &info); return info;
}
static inline index_t gesvd(
    const char jobu, const char jobvt, const index_t m, const index_t n,
    std::complex<double> *a, const index_t lda, double *s,
    std::complex<double> *u, const index_t ldu, std::complex<double> *vt, const index_t ldvt,
    std::complex<double> *work, const index_t lwork, double *rwork
) noexcept {
  index_t info; zgesvd_(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, vt, &ldvt, work, &lwork, rwork, &info); return info;
}
//@}

}  // namespace detail

}  // namespace lapack

}  // namespace isvd

#endif  // ISVD_LAPACK_LAPACK_GESVD_HPP_
