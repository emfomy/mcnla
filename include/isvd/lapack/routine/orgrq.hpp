////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/lapack/routine/orgrq.hpp
/// @brief   The LAPACK ORGRQ & ORGQL routines.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_LAPACK_ROUTINE_ORGRQ_HPP_
#define ISVD_LAPACK_ROUTINE_ORGRQ_HPP_

#include <isvd/matrix.hpp>
#include <isvd/lapack/lapack.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

extern "C" {

#include <isvd/plugin/lapack_plugin_start.h>

// Generates the real orthogonal matrix Q of the RQ factorization formed by GERQF.
extern void sorgrq_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 k, FORTRAN_REAL4 a, const FORTRAN_INT8 lda,
                     const FORTRAN_REAL4 tau, FORTRAN_REAL4 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void dorgrq_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 k, FORTRAN_REAL8 a, const FORTRAN_INT8 lda,
                     const FORTRAN_REAL8 tau, FORTRAN_REAL8 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );

// Generates the complex unitary matrix Q of the RQ factorization formed by GERQF.
extern void cungqr_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 k, FORTRAN_COMP4 a, const FORTRAN_INT8 lda,
                     const FORTRAN_COMP4 tau, FORTRAN_COMP4 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void zungqr_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 k, FORTRAN_COMP8 a, const FORTRAN_INT8 lda,
                     const FORTRAN_COMP8 tau, FORTRAN_COMP8 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );

// Generates the real orthogonal matrix Q of the QL factorization formed by GEQLF.
extern void sorgql_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 k, FORTRAN_REAL4 a, const FORTRAN_INT8 lda,
                     const FORTRAN_REAL4 tau, FORTRAN_REAL4 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void dorgql_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 k, FORTRAN_REAL8 a, const FORTRAN_INT8 lda,
                     const FORTRAN_REAL8 tau, FORTRAN_REAL8 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );

// Generates the complex unitary matrix Q of the QL factorization formed by GEQLF.
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
/// @copydoc isvd::lapack::orgrq
///
//@{
static inline index_t orgrq(
    const index_t m, const index_t n, const index_t k,
    float *a, const index_t lda, const float *tau, float *work, index_t lwork
) noexcept { index_t info; sorgrq_(&m, &n, &k, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t orgrq(
    const index_t m, const index_t n, const index_t k,
    double *a, const index_t lda, const double *tau, double *work, index_t lwork
) noexcept { index_t info; dorgrq_(&m, &n, &k, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t orgrq(
    const index_t m, const index_t n, const index_t k,
    std::complex<float> *a, const index_t lda, const std::complex<float> *tau, std::complex<float> *work, index_t lwork
) noexcept { index_t info; cungqr_(&m, &n, &k, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t orgrq(
    const index_t m, const index_t n, const index_t k,
    std::complex<double> *a, const index_t lda, const std::complex<double> *tau, std::complex<double> *work, index_t lwork
) noexcept { index_t info; zungqr_(&m, &n, &k, a, &lda, tau, work, &lwork, &info); return info; }
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc isvd::lapack::orgql
///
//@{
static inline index_t orgql(
    const index_t m, const index_t n, const index_t k,
    float *a, const index_t lda, const float *tau, float *work, index_t lwork
) noexcept { index_t info; sorgql_(&m, &n, &k, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t orgql(
    const index_t m, const index_t n, const index_t k,
    double *a, const index_t lda, const double *tau, double *work, index_t lwork
) noexcept { index_t info; dorgql_(&m, &n, &k, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t orgql(
    const index_t m, const index_t n, const index_t k,
    std::complex<float> *a, const index_t lda, const std::complex<float> *tau, std::complex<float> *work, index_t lwork
) noexcept { index_t info; cunglq_(&m, &n, &k, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t orgql(
    const index_t m, const index_t n, const index_t k,
    std::complex<double> *a, const index_t lda, const std::complex<double> *tau, std::complex<double> *work, index_t lwork
) noexcept { index_t info; zunglq_(&m, &n, &k, a, &lda, tau, work, &lwork, &info); return info; }
//@}

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Generates the real orthogonal or complex unitary matrix Q of the RQ factorization formed by GERQF.
///
//@{
template <typename _Scalar, Layout _layout>
inline void orgrq(
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
    assert(internal::orgrq(a.getNrow(), ncol, rank, a.getValue(), a.getPitch(),
                           tau.getValue(), work.getValue(), work.getLength()) == 0);
  } else {
    assert(internal::orgql(ncol, a.getNcol(), rank, a.getValue(), a.getPitch(),
                           tau.getValue(), work.getValue(), work.getLength()) == 0);
  }
  a.resize(a.getNrow(), ncol);
}

template <class _TypeA, class _TypeTau, class _TypeWork>
inline void orgrq( _TypeA &&a, const _TypeTau &tau, _TypeWork &&work, const index_t ncol, const index_t rank ) noexcept {
  orgrq(a, tau, work, ncol, rank);
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Generates the real orthogonal or complex unitary matrix Q of the QL factorization formed by GEQLF.
///
//@{
template <typename _Scalar, Layout _layout>
inline void orgql(
          DenseMatrix<_Scalar, _layout> &a,
    const DenseVector<_Scalar> &tau,
          DenseVector<_Scalar> &work,
    const index_t nrow,
    const index_t rank
) noexcept {
  orgrq(a.transpose(), tau, work, nrow, rank);
}

template <class _TypeA, class _TypeTau, class _TypeWork>
inline void orgql( _TypeA &&a, const _TypeTau &tau, _TypeWork &&work, const index_t nrow, const index_t rank ) noexcept {
  orgql(a, tau, work, nrow, rank);
}
//@}

}  // namespace lapack

}  // namespace isvd

#endif  // ISVD_LAPACK_ROUTINE_ORGRQ_HPP_
