////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/lapack/dense_orgqr.hpp
/// @brief   The LAPACK ORGQR & ORGLQ routines for dense matrices
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_LAPACK_DENSE_ORGQR_HPP_
#define ISVD_LAPACK_DENSE_ORGQR_HPP_

#include <utility>
#include <isvd/matrix.hpp>
#include <isvd/lapack/lapack.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

extern "C" {

#include <isvd/plugin/lapack_plugin_start.h>

// Generates the real orthogonal matrix Q of the QR factorization formed by GEQRF.
extern void sorgqr_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 k, FORTRAN_REAL4 a, const FORTRAN_INT8 lda,
                     const FORTRAN_REAL4 tau, FORTRAN_REAL4 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void dorgqr_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 k, FORTRAN_REAL8 a, const FORTRAN_INT8 lda,
                     const FORTRAN_REAL8 tau, FORTRAN_REAL8 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );

// Generates the real complex unitary Q of the QR factorization formed by GEQRF.
extern void cungqr_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 k, FORTRAN_COMP4 a, const FORTRAN_INT8 lda,
                     const FORTRAN_COMP4 tau, FORTRAN_COMP4 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void zungqr_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 k, FORTRAN_COMP8 a, const FORTRAN_INT8 lda,
                     const FORTRAN_COMP8 tau, FORTRAN_COMP8 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );

// Generates the real orthogonal matrix Q of the LQ factorization formed by GELQF.
extern void sorglq_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 k, FORTRAN_REAL4 a, const FORTRAN_INT8 lda,
                     const FORTRAN_REAL4 tau, FORTRAN_REAL4 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void dorglq_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 k, FORTRAN_REAL8 a, const FORTRAN_INT8 lda,
                     const FORTRAN_REAL8 tau, FORTRAN_REAL8 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );

// Generates the complex unitary matrix Q of the LQ factorization formed by GELQF.
extern void cunglq_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 k, FORTRAN_COMP4 a, const FORTRAN_INT8 lda,
                     const FORTRAN_COMP4 tau, FORTRAN_COMP4 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void zunglq_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 k, FORTRAN_COMP8 a, const FORTRAN_INT8 lda,
                     const FORTRAN_COMP8 tau, FORTRAN_COMP8 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );

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
/// @copydoc isvd::lapack::orgqr
///
//@{
static inline index_t orgqr(
    const index_t m, const index_t n, const index_t k,
    float *a, const index_t lda, const float *tau, float *work, index_t lwork
) noexcept { index_t info; sorgqr_(&m, &n, &k, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t orgqr(
    const index_t m, const index_t n, const index_t k,
    double *a, const index_t lda, const double *tau, double *work, index_t lwork
) noexcept { index_t info; dorgqr_(&m, &n, &k, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t orgqr(
    const index_t m, const index_t n, const index_t k,
    std::complex<float> *a, const index_t lda, const std::complex<float> *tau, std::complex<float> *work, index_t lwork
) noexcept { index_t info; cungqr_(&m, &n, &k, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t orgqr(
    const index_t m, const index_t n, const index_t k,
    std::complex<double> *a, const index_t lda, const std::complex<double> *tau, std::complex<double> *work, index_t lwork
) noexcept { index_t info; zungqr_(&m, &n, &k, a, &lda, tau, work, &lwork, &info); return info; }
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc isvd::lapack::orglq
///
//@{
static inline index_t orglq(
    const index_t m, const index_t n, const index_t k,
    float *a, const index_t lda, const float *tau, float *work, index_t lwork
) noexcept { index_t info; sorglq_(&m, &n, &k, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t orglq(
    const index_t m, const index_t n, const index_t k,
    double *a, const index_t lda, const double *tau, double *work, index_t lwork
) noexcept { index_t info; dorglq_(&m, &n, &k, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t orglq(
    const index_t m, const index_t n, const index_t k,
    std::complex<float> *a, const index_t lda, const std::complex<float> *tau, std::complex<float> *work, index_t lwork
) noexcept { index_t info; cunglq_(&m, &n, &k, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t orglq(
    const index_t m, const index_t n, const index_t k,
    std::complex<double> *a, const index_t lda, const std::complex<double> *tau, std::complex<double> *work, index_t lwork
) noexcept { index_t info; zunglq_(&m, &n, &k, a, &lda, tau, work, &lwork, &info); return info; }
//@}

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Generates the real orthogonal or complex unitary matrix Q of the QR factorization formed by GEQRF.
///
//@{
template <typename _Scalar, Layout _layout>
inline void orgqr(
          DenseMatrix<_Scalar, _layout> &a,
    const DenseVector<_Scalar> &tau,
          DenseVector<_Scalar> &work,
    const index_t ncol,
    const index_t rank
) noexcept {
  assert(ncol >= rank && rank >= 0);
  assert(a.getNrow() >= ncol && a.getNcol() >= ncol);
  assert(tau.getLength() >= rank);
  assert(work.getLength() >= ncol);

  if ( isColMajor(_layout) ) {
    assert(internal::orgqr(a.getNrow(), ncol, rank, a.getValue(), a.getPitch(),
                           tau.getValue(), work.getValue(), work.getLength()) == 0);
  } else {
    assert(internal::orglq(ncol, a.getNcol(), rank, a.getValue(), a.getPitch(),
                           tau.getValue(), work.getValue(), work.getLength()) == 0);
  }
  a.resize(a.getNrow(), ncol);
}

template <class _TypeA, class _TypeTau, class _TypeWork>
inline void orgqr( _TypeA &&a, const _TypeTau &tau, _TypeWork &&work, const index_t ncol, const index_t rank ) noexcept {
  orgqr(a, tau, work, ncol, rank);
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Generates the real orthogonal or complex unitary matrix Q of the LQ factorization formed by GELQF.
///
//@{
template <typename _Scalar, Layout _layout>
inline void orglq(
          DenseMatrix<_Scalar, _layout> &a,
    const DenseVector<_Scalar> &tau,
          DenseVector<_Scalar> &work,
    const index_t nrow,
    const index_t rank
) noexcept {
  orgqr(a.transpose(), tau, work, nrow, rank);
}

template <class _TypeA, class _TypeTau, class _TypeWork>
inline void orglq( _TypeA &&a, const _TypeTau &tau, _TypeWork &&work, const index_t nrow, const index_t rank ) noexcept {
  orglq(a, tau, work, nrow, rank);
}
//@}

}  // namespace lapack

}  // namespace isvd

#endif  // ISVD_LAPACK_DENSE_ORGQR_HPP_
