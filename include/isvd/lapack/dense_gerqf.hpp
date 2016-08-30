////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/lapack/dense_gerqf.hpp
/// @brief   The LAPACK GERQF & GEQL routines for dense matrices
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_LAPACK_DENSE_GERQF_HPP_
#define ISVD_LAPACK_DENSE_GERQF_HPP_

#include <utility>
#include <isvd/matrix.hpp>
#include <isvd/lapack/lapack.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

extern "C" {

#include <isvd/plugin/lapack_plugin_start.h>

// Computes the RQ factorization of a general m-by-n matrix.
extern void sgerqf_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, FORTRAN_REAL4 a, const FORTRAN_INT8 lda, FORTRAN_REAL4 tau,
                     FORTRAN_REAL4 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void dgerqf_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, FORTRAN_REAL8 a, const FORTRAN_INT8 lda, FORTRAN_REAL8 tau,
                     FORTRAN_REAL8 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void cgerqf_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, FORTRAN_COMP4 a, const FORTRAN_INT8 lda, FORTRAN_COMP4 tau,
                     FORTRAN_COMP4 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void zgerqf_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, FORTRAN_COMP8 a, const FORTRAN_INT8 lda, FORTRAN_COMP8 tau,
                     FORTRAN_COMP8 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );

// Computes the QL factorization of a general m-by-n matrix.
extern void sgeqlf_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, FORTRAN_REAL4 a, const FORTRAN_INT8 lda, FORTRAN_REAL4 tau,
                     FORTRAN_REAL4 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void dgeqlf_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, FORTRAN_REAL8 a, const FORTRAN_INT8 lda, FORTRAN_REAL8 tau,
                     FORTRAN_REAL8 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void cgeqlf_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, FORTRAN_COMP4 a, const FORTRAN_INT8 lda, FORTRAN_COMP4 tau,
                     FORTRAN_COMP4 work, FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void zgeqlf_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, FORTRAN_COMP8 a, const FORTRAN_INT8 lda, FORTRAN_COMP8 tau,
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
/// @copydoc isvd::lapack::gerqf
///
//@{
static inline index_t gerqf(
    const index_t m, const index_t n,
    float *a, const index_t lda, float *tau, float *work, index_t lwork
) noexcept { index_t info; sgerqf_(&m, &n, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t gerqf(
    const index_t m, const index_t n,
    double *a, const index_t lda, double *tau, double *work, index_t lwork
) noexcept { index_t info; dgerqf_(&m, &n, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t gerqf(
    const index_t m, const index_t n,
    std::complex<float> *a, const index_t lda, std::complex<float> *tau, std::complex<float> *work, index_t lwork
) noexcept { index_t info; cgerqf_(&m, &n, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t gerqf(
    const index_t m, const index_t n,
    std::complex<double> *a, const index_t lda, std::complex<double> *tau, std::complex<double> *work, index_t lwork
) noexcept { index_t info; zgerqf_(&m, &n, a, &lda, tau, work, &lwork, &info); return info; }
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc isvd::lapack::geqlf
///
//@{
static inline index_t geqlf(
    const index_t m, const index_t n,
    float *a, const index_t lda, float *tau, float *work, index_t lwork
) noexcept { index_t info; sgeqlf_(&m, &n, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t geqlf(
    const index_t m, const index_t n,
    double *a, const index_t lda, double *tau, double *work, index_t lwork
) noexcept { index_t info; dgeqlf_(&m, &n, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t geqlf(
    const index_t m, const index_t n,
    std::complex<float> *a, const index_t lda, std::complex<float> *tau, std::complex<float> *work, index_t lwork
) noexcept { index_t info; cgeqlf_(&m, &n, a, &lda, tau, work, &lwork, &info); return info; }
static inline index_t geqlf(
    const index_t m, const index_t n,
    std::complex<double> *a, const index_t lda, std::complex<double> *tau, std::complex<double> *work, index_t lwork
) noexcept { index_t info; zgeqlf_(&m, &n, a, &lda, tau, work, &lwork, &info); return info; }
//@}

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes the RQ factorization of a general m-by-n matrix.
///
//@{
template <typename _Scalar, Layout _layout>
inline void gerqf(
    DenseMatrix<_Scalar, _layout> &a,
    DenseVector<_Scalar> &tau,
    DenseVector<_Scalar> &work ) noexcept {
  assert(tau.getLength() == std::min(a.getNrow(), a.getNcol()));
  assert(work.getLength() >= a.getNcol());

  if ( isColMajor(_layout) ) {
    assert(internal::gerqf(a.getNrow(), a.getNcol(), a.getValue(), a.getPitch(),
                           tau.getValue(), work.getValue(), work.getLength()) == 0);
  } else {
    assert(internal::geqlf(a.getNcol(), a.getNrow(), a.getValue(), a.getPitch(),
                           tau.getValue(), work.getValue(), work.getLength()) == 0);
  }
}

template <class _TypeA, class _TypeTau, class _TypeWork>
inline void gerqf( _TypeA &&a, _TypeTau &&tau, _TypeWork &&work ) noexcept {
  gerqf(a, tau, work);
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes the QL factorization of a general m-by-n matrix.
///
//@{
template <typename _Scalar, Layout _layout>
inline void geqlf(
    DenseMatrix<_Scalar, _layout> &a,
    DenseVector<_Scalar> &tau,
    DenseVector<_Scalar> &work ) noexcept {
  assert(tau.getLength() == std::min(a.getNrow(), a.getNcol()));
  assert(work.getLength() >= a.getNrow());

  if ( isColMajor(_layout) ) {
    assert(internal::gerqf(a.getNrow(), a.getNcol(), a.getValue(), a.getPitch(),
                           tau.getValue(), work.getValue(), work.getLength()) == 0);
  } else {
    assert(internal::geqlf(a.getNcol(), a.getNrow(), a.getValue(), a.getPitch(),
                           tau.getValue(), work.getValue(), work.getLength()) == 0);
  }
}

template <class _TypeA, class _TypeTau, class _TypeWork>
inline void geqlf( _TypeA &&a, _TypeTau &&tau, _TypeWork &&work ) noexcept {
  geqlf(a, tau, work);
}
//@}

}  // namespace lapack

}  // namespace isvd

#endif  // ISVD_LAPACK_DENSE_GERQF_HPP_
