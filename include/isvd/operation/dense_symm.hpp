////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/operation/dense_symm.hpp
/// @brief   The BLAS SYMM routine for dense matrices
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_OPERATION_DENSE_SYMM_HPP_
#define ISVD_OPERATION_DENSE_SYMM_HPP_

#include <utility>
#include <isvd/matrix.hpp>
#include <isvd/utility/blas.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The BLAS namespace
//
namespace blas {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc isvd::blas::symm
///
//@{
static inline void symm(
    const char side, const char uplo, const int64_t m, const int64_t n,
    const float alpha, const float *a, const int64_t lda, const float *b, const int64_t ldb,
    const float beta, float *c, const int64_t ldc
) noexcept {
  ssymm_(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc);
}
static inline void symm(
    const char side, const char uplo, const int64_t m, const int64_t n,
    const double alpha, const double *a, const int64_t lda, const double *b, const int64_t ldb,
    const double beta, double *c, const int64_t ldc
) noexcept {
  dsymm_(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc);
}
static inline void symm(
    const char side, const char uplo, const int64_t m, const int64_t n,
    const std::complex<float> alpha, const std::complex<float> *a, const int64_t lda,
    const std::complex<float> *b, const int64_t ldb,
    const std::complex<float> beta, std::complex<float> *c, const int64_t ldc
) noexcept {
  chemm_(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc);
}
static inline void symm(
    const char side, const char uplo, const int64_t m, const int64_t n,
    const std::complex<double> alpha, const std::complex<double> *a, const int64_t lda,
    const std::complex<double> *b, const int64_t ldb,
    const std::complex<double> beta, std::complex<double> *c, const int64_t ldc
) noexcept {
  zhemm_(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc);
}
//@}

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes a matrix-matrix product where one input matrix is symmetric/Hermitian.
///
template<SideOption _side = SideOption::LEFT,
         UploOption _uplo = UploOption::LOWER, class _Derived>
inline void symm(
    const typename isvd::internal::Traits<_Derived>::ScalarType alpha,
    const isvd::internal::DenseMatrixBase<_Derived> &a,
    const isvd::internal::DenseMatrixBase<_Derived> &b,
    const typename isvd::internal::Traits<_Derived>::ScalarType beta,
          isvd::internal::DenseMatrixBase<_Derived> &c ) noexcept {
  assert(c.getData() != a.getData());
  assert(c.getData() != b.getData());

  if ( isColMajor(isvd::internal::Traits<_Derived>::layout) ) {
    if ( isLeftSide(_side) ) {
      assert(a.getNrow() == a.getNcol());
      assert(a.getNrow() == c.getNrow());
      assert(b.getNrow() == c.getNrow());
      assert(b.getNcol() == c.getNcol());
    } else {
      assert(b.getNrow() == b.getNcol());
      assert(b.getNcol() == c.getNcol());
      assert(a.getNrow() == c.getNrow());
      assert(a.getNcol() == c.getNcol());
    }
    internal::symm(SideChar<_side>::value, UploChar<_uplo>::value, c.getNrow(), c.getNcol(),
                   alpha, a.getValue(), a.getPitch(), b.getValue(), b.getPitch(),
                   beta, c.getValue(), c.getPitch());
  } else {
    if ( isRightSide(_side) ) {
      assert(b.getNcol() == b.getNrow());
      assert(b.getNcol() == c.getNcol());
      assert(a.getNcol() == c.getNcol());
      assert(a.getNrow() == c.getNrow());
    } else {
      assert(a.getNcol() == a.getNrow());
      assert(a.getNrow() == c.getNrow());
      assert(b.getNcol() == c.getNcol());
      assert(b.getNrow() == c.getNrow());
    }
    internal::symm(SideChar<_side>::value, UploChar<_uplo>::value, c.getNcol(), c.getNrow(),
                   alpha, b.getValue(), b.getPitch(), a.getValue(), a.getPitch(),
                   beta, c.getValue(), c.getPitch());
  }
}

}  // namespace blas

}  // namespace isvd

#endif  // ISVD_OPERATION_DENSE_SYMM_HPP_