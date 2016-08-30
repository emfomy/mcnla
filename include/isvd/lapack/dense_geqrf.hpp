////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/lapack/dense_geqrf.hpp
/// @brief   The LAPACK GEQRF & GELQF routines for dense matrices
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_LAPACK_DENSE_GEQRF_HPP_
#define ISVD_LAPACK_DENSE_GEQRF_HPP_

#include <utility>
#include <isvd/matrix.hpp>
#include <isvd/lapack/lapack.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

extern "C" {

#include <isvd/plugin/lapack_plugin_start.h>

// Computes the QR factorization of a general m-by-n matrix.
extern void sgeqrf_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, FORTRAN_REAL4 a, const FORTRAN_INT8 lda, FORTRAN_REAL4 tau,
                     FORTRAN_REAL4 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void dgeqrf_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, FORTRAN_REAL8 a, const FORTRAN_INT8 lda, FORTRAN_REAL8 tau,
                     FORTRAN_REAL8 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void cgeqrf_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, FORTRAN_COMP4 a, const FORTRAN_INT8 lda, FORTRAN_COMP4 tau,
                     FORTRAN_COMP4 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void zgeqrf_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, FORTRAN_COMP8 a, const FORTRAN_INT8 lda, FORTRAN_COMP8 tau,
                     FORTRAN_COMP8 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );

// Computes the LQ factorization of a general m-by-n matrix.
extern void sgelqf_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, FORTRAN_REAL4 a, const FORTRAN_INT8 lda, FORTRAN_REAL4 tau,
                     FORTRAN_REAL4 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void dgelqf_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, FORTRAN_REAL8 a, const FORTRAN_INT8 lda, FORTRAN_REAL8 tau,
                     FORTRAN_REAL8 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void cgelqf_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, FORTRAN_COMP4 a, const FORTRAN_INT8 lda, FORTRAN_COMP4 tau,
                     FORTRAN_COMP4 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void zgelqf_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, FORTRAN_COMP8 a, const FORTRAN_INT8 lda, FORTRAN_COMP8 tau,
                     FORTRAN_COMP8 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );

#include <isvd/plugin/lapack_plugin_end.h>

}  // extern "C"

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
//  The internal namespace
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc isvd::lapack::geqrf
///
//@{
static inline index_t geqrf(
    const index_t m, const index_t n,
    float *a, const index_t lda, float *tau, float *work, index_t lwork
) noexcept { index_t info; sgeqrf_(&m, &n, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t geqrf(
    const index_t m, const index_t n,
    double *a, const index_t lda, double *tau, double *work, index_t lwork
) noexcept { index_t info; dgeqrf_(&m, &n, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t geqrf(
    const index_t m, const index_t n,
    std::complex<float> *a, const index_t lda, std::complex<float> *tau, std::complex<float> *work, index_t lwork
) noexcept { index_t info; cgeqrf_(&m, &n, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t geqrf(
    const index_t m, const index_t n,
    std::complex<double> *a, const index_t lda, std::complex<double> *tau, std::complex<double> *work, index_t lwork
) noexcept { index_t info; zgeqrf_(&m, &n, a, &lda, tau, work, &lwork, &info); return info; }
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc isvd::lapack::gelqf
///
//@{
static inline index_t gelqf(
    const index_t m, const index_t n,
    float *a, const index_t lda, float *tau, float *work, index_t lwork
) noexcept { index_t info; sgelqf_(&m, &n, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t gelqf(
    const index_t m, const index_t n,
    double *a, const index_t lda, double *tau, double *work, index_t lwork
) noexcept { index_t info; dgelqf_(&m, &n, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t gelqf(
    const index_t m, const index_t n,
    std::complex<float> *a, const index_t lda, std::complex<float> *tau, std::complex<float> *work, index_t lwork
) noexcept { index_t info; cgelqf_(&m, &n, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t gelqf(
    const index_t m, const index_t n,
    std::complex<double> *a, const index_t lda, std::complex<double> *tau, std::complex<double> *work, index_t lwork
) noexcept { index_t info; zgelqf_(&m, &n, a, &lda, tau, work, &lwork, &info); return info; }
//@}

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes the QR factorization of a general m-by-n matrix.
///
//@{
template <typename _Scalar, Layout _layout>
inline void geqrf(
    DenseMatrix<_Scalar, _layout> &a,
    DenseVector<_Scalar> &tau,
    DenseVector<_Scalar> &work
) noexcept {
  assert(tau.getLength() >= std::min(a.getNrow(), a.getNcol()));
  assert(work.getLength() >= a.getNcol());

  if ( isColMajor(_layout) ) {
    assert(internal::geqrf(a.getNrow(), a.getNcol(), a.getValue(), a.getPitch(),
                           tau.getValue(), work.getValue(), work.getLength()) == 0);
  } else {
    assert(internal::gelqf(a.getNcol(), a.getNrow(), a.getValue(), a.getPitch(),
                           tau.getValue(), work.getValue(), work.getLength()) == 0);
  }
}

template <class _TypeA, class _TypeTau, class _TypeWork>
inline void geqrf( _TypeA &&a, _TypeTau &&tau, _TypeWork &&work ) noexcept {
  geqrf(a, tau, work);
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes the LQ factorization of a general m-by-n matrix.
///
//@{
template <typename _Scalar, Layout _layout>
inline void gelqf(
    DenseMatrix<_Scalar, _layout> &a,
    DenseVector<_Scalar> &tau,
    DenseVector<_Scalar> &work
) noexcept {
  geqrf(a.transpose(), tau, work);
}

template <class _TypeA, class _TypeTau, class _TypeWork>
inline void gelqf( _TypeA &&a, _TypeTau &&tau, _TypeWork &&work ) noexcept {
  gelqf(a, tau, work);
}
//@}

}  // namespace lapack

}  // namespace isvd

#endif  // ISVD_LAPACK_DENSE_GEQRF_HPP_
