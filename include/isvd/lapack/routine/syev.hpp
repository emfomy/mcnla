////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/lapack/routine/syev.hpp
/// @brief   The LAPACK SYEV routine.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_LAPACK_ROUTINE_SYEV_HPP_
#define ISVD_LAPACK_ROUTINE_SYEV_HPP_

#include <isvd/utility/traits.hpp>
#include <isvd/matrix.hpp>
#include <isvd/lapack/lapack.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

extern "C" {

#include <isvd/plugin/lapack_plugin_start.h>

// Computes all eigenvalues and, optionally, eigenvectors of a symmetric matrix.
extern void ssyev_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, FORTRAN_REAL4 a,
                    const FORTRAN_INT8 lda, FORTRAN_REAL4 w, FORTRAN_REAL4 work, const FORTRAN_INT8 lwork,
                    FORTRAN_INT8 info );
extern void dsyev_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, FORTRAN_REAL8 a,
                    const FORTRAN_INT8 lda, FORTRAN_REAL8 w, FORTRAN_REAL8 work, const FORTRAN_INT8 lwork,
                    FORTRAN_INT8 info );

// Computes all eigenvalues and, optionally, eigenvectors of a Hermitian matrix.
extern void cheev_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, FORTRAN_COMP4 a,
                    const FORTRAN_INT8 lda, FORTRAN_COMP4 w, FORTRAN_COMP4 work, const FORTRAN_INT8 lwork, FORTRAN_REAL4 rwork,
                    FORTRAN_INT8 info );
extern void zheev_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, FORTRAN_COMP8 a,
                    const FORTRAN_INT8 lda, FORTRAN_COMP8 w, FORTRAN_COMP8 work, const FORTRAN_INT8 lwork, FORTRAN_REAL8 rwork,
                    FORTRAN_INT8 info );

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
/// @copydoc isvd::lapack::syev
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
    std::complex<float> *a, const index_t lda, std::complex<float> *w,
    std::complex<float> *work, const index_t lwork, float *rwork
) noexcept { index_t info; cheev_(&jobz, &uplo, &n, a, &lda, w, work, &lwork, rwork, &info); return info; }
static inline index_t syev(
    const char jobz, const char uplo, const index_t n,
    std::complex<double> *a, const index_t lda, std::complex<double> *w,
    std::complex<double> *work, const index_t lwork, double *rwork
) noexcept { index_t info; zheev_(&jobz, &uplo, &n, a, &lda, w, work, &lwork, rwork, &info); return info; }
//@}

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes all eigenvalues and, optionally, eigenvectors of a symmetric or Hermitian matrix.
///
//@{
template <JobOption _jobz, UploOption _uplo = UploOption::LOWER, typename _Scalar, Layout _layout>
inline void syev(
    DenseMatrix<_Scalar, _layout> &a,
    DenseVector<typename isvd::internal::ScalarTraits<_Scalar>::RealType> &w,
    DenseVector<_Scalar> &work,
    DenseVector<typename isvd::internal::ScalarTraits<_Scalar>::RealType> &rwork
) noexcept {
  static_assert(_jobz == 'N' || _jobz == 'V', "Job undefined!");
  assert(a.getNrow() == a.getNcol());
  assert(w.getLength() == a.getNrow());
  if ( isvd::internal::ScalarTraits<_Scalar>::is_real ) {
    assert(work.getLength() >= 3 * a.getNrow()-1);
  } else {
    assert(work.getLength() >= 2 * a.getNrow()-1);
    assert(rwork.getLength() >= 3 * a.getNrow()-2);
  }

  assert(internal::syev(_jobz, UploChar<_uplo, _layout>::value, a.getNrow(), a.getValue(), a.getPitch(),
                        w.getValue(), work.getValue(), work.getLength(), rwork.getValue()) == 0);
}

template <JobOption _jobz, UploOption _uplo = UploOption::LOWER,
          class _TypeA, class _TypeW, class _TypeWork, class _TypeRwork>
inline void syev( _TypeA &&a, _TypeW &&w, _TypeWork &&work, _TypeRwork &&rwork ) noexcept {
  syev<_jobz, _uplo>(a, w, work, rwork);
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Query the optimal workspace size for isvd::lapack::syev.
///
/// @return  The optimal length of parameter @p work.
///
template <JobOption _jobz, UploOption _uplo = UploOption::LOWER, typename _Scalar, Layout _layout>
inline index_t syevQuery(
    const DenseMatrix<_Scalar, _layout> &a
) noexcept {
  static_assert(_jobz == 'N' || _jobz == 'V', "Job undefined!");
  assert(a.getNrow() == a.getNcol());
  _Scalar lwork;
  assert(internal::syev(_jobz, UploChar<_uplo, _layout>::value, a.getNrow(),
                        nullptr, a.getPitch(), nullptr, &lwork, -1, nullptr) == 0);
  return lwork;
}

}  // namespace lapack

}  // namespace isvd

#endif  // ISVD_LAPACK_ROUTINE_SYEV_HPP_
