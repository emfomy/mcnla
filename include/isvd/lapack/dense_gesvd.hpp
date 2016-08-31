////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/lapack/dense_gesvd.hpp
/// @brief   The LAPACK GESVD routine for dense matrices
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_LAPACK_DENSE_GESVD_HPP_
#define ISVD_LAPACK_DENSE_GESVD_HPP_

#include <utility>
#include <isvd/utility/traits.hpp>
#include <isvd/matrix.hpp>
#include <isvd/lapack/lapack.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

extern "C" {

#include <isvd/plugin/lapack_plugin_start.h>

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
                     FORTRAN_COMP4 a, const FORTRAN_INT8 lda, FORTRAN_COMP4 s, FORTRAN_COMP4 u, const FORTRAN_INT8 ldu,
                     FORTRAN_COMP4 vt, const FORTRAN_INT8 ldvt, FORTRAN_COMP4 work, const FORTRAN_INT8 lwork,
                     FORTRAN_REAL4 rwork, FORTRAN_INT8 info );
extern void zgesvd_( const FORTRAN_CHAR1 jobu, const FORTRAN_CHAR1 jobvt, const FORTRAN_INT8 m, const FORTRAN_INT8 n,
                     FORTRAN_COMP8 a, const FORTRAN_INT8 lda, FORTRAN_COMP8 s, FORTRAN_COMP8 u, const FORTRAN_INT8 ldu,
                     FORTRAN_COMP8 vt, const FORTRAN_INT8 ldvt, FORTRAN_COMP8 work, const FORTRAN_INT8 lwork,
                     FORTRAN_REAL8 rwork, FORTRAN_INT8 info );

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
/// @copydoc isvd::lapack::gesvd
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
    std::complex<float> *a, const index_t lda, std::complex<float> *s,
    std::complex<float> *u, const index_t ldu, std::complex<float> *vt, const index_t ldvt,
    std::complex<float> *work, const index_t lwork, float *rwork
) noexcept {
  index_t info; cgesvd_(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, vt, &ldvt, work, &lwork, rwork, &info); return info;
}
static inline index_t gesvd(
    const char jobu, const char jobvt, const index_t m, const index_t n,
    std::complex<double> *a, const index_t lda, std::complex<double> *s,
    std::complex<double> *u, const index_t ldu, std::complex<double> *vt, const index_t ldvt,
    std::complex<double> *work, const index_t lwork, double *rwork
) noexcept {
  index_t info; zgesvd_(&jobu, &jobvt, &m, &n, a, &lda, s, u, &ldu, vt, &ldvt, work, &lwork, rwork, &info); return info;
}
//@}

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes the singular value decomposition of a general rectangular matrix.
///
//@{
template <JobOption _jobu, JobOption _jobvt, typename _Scalar, Layout _layout>
inline void gesvd(
    DenseMatrix<_Scalar, _layout> &a,
    DenseVector<typename isvd::internal::ScalarTraits<_Scalar>::RealType> &s,
    DenseMatrix<_Scalar, _layout> &u,
    DenseMatrix<_Scalar, _layout> &vt,
    DenseVector<_Scalar> &work,
    DenseVector<typename isvd::internal::ScalarTraits<_Scalar>::RealType> &rwork
) noexcept {
  static_assert(_jobu  == 'A' || _jobu  == 'S' || _jobu  == 'O' || _jobu  == 'N', "Job undefined!");
  static_assert(_jobvt == 'A' || _jobvt == 'S' || _jobvt == 'O' || _jobvt == 'N', "Job undefined!");
  static_assert(_jobu  != 'O' || _jobvt != 'O', "Job conflict!");

  if ( _jobu == 'A' ) {
    assert(u.getNrow() == a.getNrow() && u.getNcol() == a.getNrow());
  } else if ( _jobu == 'S' ) {
    assert(u.getNrow() == a.getNrow() && u.getNcol() == std::min(a.getNrow(), a.getNcol()));
  }

  if ( _jobvt == 'A' ) {
    assert(vt.getNcol() == a.getNcol() && vt.getNrow() == a.getNcol());
  } else if ( _jobvt == 'S' ) {
    assert(vt.getNcol() == a.getNcol() && vt.getNrow() == std::min(a.getNrow(), a.getNcol()));
  }

  if ( isvd::internal::ScalarTraits<_Scalar>::is_real ) {
    assert(work.getLength() >= 3 * std::min(a.getNrow(), a.getNcol()) + std::max(a.getNrow(), a.getNcol()));
    assert(work.getLength() >= 5 * std::min(a.getNrow(), a.getNcol()));
  } else {
    assert(work.getLength() >= 2 * std::min(a.getNrow(), a.getNcol()) + std::max(a.getNrow(), a.getNcol()));
    assert(rwork.getLength() >= 5 * std::min(a.getNrow(), a.getNcol()));
  }

  assert(internal::gesvd(_jobu, _jobvt, a.getNrow(), a.getNcol(), a.getValue(), a.getPitch(),
                         s.getValue(), u.getValue(), u.getPitch(), vt.getValue(), vt.getPitch(),
                         work.getValue(), work.getLength(), rwork.getValue()) == 0);
}

template <JobOption _jobu, JobOption _jobvt,
          class _TypeA, class _TypeS, class _TypeU, class _TypeVt, class _TypeWork, class _TypeRwork>
inline void gesvd( _TypeA &&a, _TypeS &&s, _TypeU &&u, _TypeVt &&vt, _TypeWork &&work, _TypeRwork &&rwork ) noexcept {
  gesvd<_jobu, _jobvt>(a, s, u, vt, work, rwork);
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Query the optimal workspace size for isvd::lapack::gesvd.
///
/// @return  The optimal length of parameter @p work.
///
//@{
template <JobOption _jobu, JobOption _jobvt, typename _Scalar, Layout _layout>
inline index_t gesvdQuery(
    DenseMatrix<_Scalar, _layout> &a
) noexcept {
  static_assert(_jobu  == 'A' || _jobu  == 'S' || _jobu  == 'O' || _jobu  == 'N', "Job undefined!");
  static_assert(_jobvt == 'A' || _jobvt == 'S' || _jobvt == 'O' || _jobvt == 'N', "Job undefined!");
  static_assert(_jobu  != 'O' || _jobvt != 'O', "Job conflict!");
  _Scalar lwork;
  assert(internal::gesvd(_jobu, _jobvt, a.getNrow(), a.getNcol(), nullptr, a.getPitch(), nullptr,
                         nullptr, a.getNrow(), nullptr, a.getNcol(), &lwork, -1, nullptr) == 0);
  return lwork;
}

template <JobOption _jobu, JobOption _jobvt, class _TypeA>
inline index_t gesvdQuery( _TypeA &&a ) noexcept {
  return gesvdQuery<_jobu, _jobvt>(a);
}
//@}

}  // namespace lapack

}  // namespace isvd

#endif  // ISVD_LAPACK_DENSE_GESVD_HPP_
