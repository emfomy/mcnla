////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/lapack/lapack/syev.hpp
/// @brief   The LAPACK SYEV.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_LAPACK_LAPACK_SYEV_HPP_
#define ISVD_LAPACK_LAPACK_SYEV_HPP_

#include <isvd/isvd.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <isvd/plugin/lapack_plugin_begin.h>

// Computes all eigenvalues and, optionally, eigenvectors of a symmetric matrix.
extern void ssyev_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT n, FORTRAN_REAL4 a,
                    const FORTRAN_INT lda, FORTRAN_REAL4 w, FORTRAN_REAL4 work, const FORTRAN_INT lwork,
                    FORTRAN_INT info );
extern void dsyev_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT n, FORTRAN_REAL8 a,
                    const FORTRAN_INT lda, FORTRAN_REAL8 w, FORTRAN_REAL8 work, const FORTRAN_INT lwork,
                    FORTRAN_INT info );

// Computes all eigenvalues and, optionally, eigenvectors of a Hermitian matrix.
extern void cheev_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT n, FORTRAN_COMP4 a,
                    const FORTRAN_INT lda, FORTRAN_REAL4 w, FORTRAN_COMP4 work, const FORTRAN_INT lwork, FORTRAN_REAL4 rwork,
                    FORTRAN_INT info );
extern void zheev_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT n, FORTRAN_COMP8 a,
                    const FORTRAN_INT lda, FORTRAN_REAL8 w, FORTRAN_COMP8 work, const FORTRAN_INT lwork, FORTRAN_REAL8 rwork,
                    FORTRAN_INT info );

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
/// @brief  Computes all eigenvalues and, optionally, eigenvectors of a symmetric or Hermitian matrix.
///
//@{
static inline index_t syev(
    const char jobz, const char uplo, const index_t n,
    float *a, const index_t lda, float *w, float *work, const index_t lwork, float *rwork
) noexcept { index_t info; ssyev_(&jobz, &uplo, &n, a, &lda, w, work, &lwork, &info); return info; static_cast<void>(rwork); }
static inline index_t syev(
    const char jobz, const char uplo, const index_t n,
    double *a, const index_t lda, double *w, double *work, const index_t lwork, double *rwork
) noexcept { index_t info; dsyev_(&jobz, &uplo, &n, a, &lda, w, work, &lwork, &info); return info; static_cast<void>(rwork); }
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

}  // namespace lapack

}  // namespace isvd

#endif  // ISVD_LAPACK_LAPACK_SYEV_HPP_
