////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/operation/dense_gemm.hpp
/// @brief   The BLAS GEMM routine for dense matrices
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_OPERATION_DENSE_GEMM_HPP_
#define ISVD_OPERATION_DENSE_GEMM_HPP_

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
/// @copydoc isvd::blas::gemm
///
//@{
static inline void gemm(
    const char transa, const char transb, const int64_t m, const int64_t n, const int64_t k,
    const float alpha, const float *a, const int64_t lda, const float *b, const int64_t ldb,
    const float beta, float *c, const int64_t ldc
) noexcept {
  sgemm_(&transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc);
}
static inline void gemm(
    const char transa, const char transb, const int64_t m, const int64_t n, const int64_t k,
    const double alpha, const double *a, const int64_t lda, const double *b, const int64_t ldb,
    const double beta, double *c, const int64_t ldc
) noexcept {
  dgemm_(&transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc);
}
static inline void gemm(
    const char transa, const char transb, const int64_t m, const int64_t n, const int64_t k,
    const std::complex<float> alpha, const std::complex<float> *a, const int64_t lda,
    const std::complex<float> *b, const int64_t ldb,
    const std::complex<float> beta, std::complex<float> *c, const int64_t ldc
) noexcept {
  cgemm_(&transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc);
}
static inline void gemm(
    const char transa, const char transb, const int64_t m, const int64_t n, const int64_t k,
    const std::complex<double> alpha, const std::complex<double> *a, const int64_t lda,
    const std::complex<double> *b, const int64_t ldb,
    const std::complex<double> beta, std::complex<double> *c, const int64_t ldc
) noexcept {
  zgemm_(&transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc);
}
//@}

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes a matrix-matrix product with general matrices.
///
template<TransOption _transa = isvd::TransOption::NORMAL,
         TransOption _transb = isvd::TransOption::NORMAL, class _Derived>
inline void gemm(
    const typename isvd::internal::Traits<_Derived>::ScalarType alpha,
    const isvd::internal::DenseMatrixBase<_Derived> &a,
    const isvd::internal::DenseMatrixBase<_Derived> &b,
    const typename isvd::internal::Traits<_Derived>::ScalarType beta,
          isvd::internal::DenseMatrixBase<_Derived> &c ) noexcept {
  assert(c.getData() != a.getData());
  assert(c.getData() != b.getData());

  if ( isColMajor(isvd::internal::Traits<_Derived>::layout) ) {
    assert(c.template getNrow()          == a.template getNrow<_transa>());
    assert(c.template getNcol()          == b.template getNcol<_transb>());
    assert(a.template getNcol<_transa>() == b.template getNrow<_transb>());
    internal::gemm(TransChar<_transa>::value, TransChar<_transb>::value,
                   c.template getNrow(), c.template getNcol(), a.template getNcol<_transa>(),
                   alpha, a.getValue(), a.getPitch(), b.getValue(), b.getPitch(),
                   beta, c.getValue(), c.getPitch());
  } else {
    assert(c.template getNcol()          == b.template getNcol<_transb>());
    assert(c.template getNrow()          == a.template getNrow<_transa>());
    assert(b.template getNrow<_transb>() == a.template getNcol<_transa>());
    internal::gemm(TransChar<_transb>::value, TransChar<_transa>::value,
                   c.template getNcol(), c.template getNrow(), a.template getNcol<_transa>(),
                   alpha, b.getValue(), b.getPitch(), a.getValue(), a.getPitch(),
                   beta, c.getValue(), c.getPitch());
  }
}

}  // namespace blas

}  // namespace isvd

#endif  // ISVD_OPERATION_DENSE_GEMM_HPP_