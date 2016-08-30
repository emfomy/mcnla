////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/blas/dense_gemm.hpp
/// @brief   The BLAS GEMM routine for dense matrices
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_BLAS_DENSE_GEMM_HPP_
#define ISVD_BLAS_DENSE_GEMM_HPP_

#include <utility>
#include <isvd/matrix.hpp>
#include <isvd/blas/blas.hpp>

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
    const char transa, const char transb, const index_t m, const index_t n, const index_t k,
    const float alpha, const float *a, const index_t lda, const float *b, const index_t ldb,
    const float beta, float *c, const index_t ldc
) noexcept { sgemm_(&transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void gemm(
    const char transa, const char transb, const index_t m, const index_t n, const index_t k,
    const double alpha, const double *a, const index_t lda, const double *b, const index_t ldb,
    const double beta, double *c, const index_t ldc
) noexcept { dgemm_(&transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void gemm(
    const char transa, const char transb, const index_t m, const index_t n, const index_t k,
    const std::complex<float> alpha, const std::complex<float> *a, const index_t lda,
    const std::complex<float> *b, const index_t ldb,
    const std::complex<float> beta, std::complex<float> *c, const index_t ldc
) noexcept { cgemm_(&transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void gemm(
    const char transa, const char transb, const index_t m, const index_t n, const index_t k,
    const std::complex<double> alpha, const std::complex<double> *a, const index_t lda,
    const std::complex<double> *b, const index_t ldb,
    const std::complex<double> beta, std::complex<double> *c, const index_t ldc
) noexcept { zgemm_(&transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
//@}

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes a matrix-matrix product with general matrices.
///
//@{
template <TransOption _transa = isvd::TransOption::NORMAL,
          TransOption _transb = isvd::TransOption::NORMAL,
          typename _Scalar, Layout _layout>
inline void gemm(
    const typename DenseMatrix<_Scalar, _layout>::ScalarType alpha,
    const DenseMatrix<_Scalar, _layout> &a,
    const DenseMatrix<_Scalar, _layout> &b,
    const typename DenseMatrix<_Scalar, _layout>::ScalarType beta,
          DenseMatrix<_Scalar, _layout> &c ) noexcept {
  if ( isColMajor(_layout) ) {
    assert(c.getNrow() == a.template getNrow<_transa>());
    assert(c.getNcol() == b.template getNcol<_transb>());
    assert(a.template getNcol<_transa>() == b.template getNrow<_transb>());
    internal::gemm(TransChar<_transa>::value, TransChar<_transb>::value,
                   c.getNrow(), c.getNcol(), a.template getNcol<_transa>(),
                   alpha, a.getValue(), a.getPitch(), b.getValue(), b.getPitch(),
                   beta, c.getValue(), c.getPitch());
  } else {
    assert(c.getNcol() == b.template getNcol<_transb>());
    assert(c.getNrow() == a.template getNrow<_transa>());
    assert(b.template getNrow<_transb>() == a.template getNcol<_transa>());
    internal::gemm(TransChar<_transb>::value, TransChar<_transa>::value,
                   c.getNcol(), c.getNrow(), a.template getNcol<_transa>(),
                   alpha, b.getValue(), b.getPitch(), a.getValue(), a.getPitch(),
                   beta, c.getValue(), c.getPitch());
  }
}

template <TransOption _transa = isvd::TransOption::NORMAL,
          TransOption _transb = isvd::TransOption::NORMAL,
          typename _Scalar, Layout _layout>
inline void gemm(
    const typename DenseMatrix<_Scalar, _layout>::ScalarType alpha,
    const DenseMatrix<_Scalar, _layout> &a,
    const DenseMatrix<_Scalar, _layout> &b,
    const typename DenseMatrix<_Scalar, _layout>::ScalarType beta,
          DenseMatrix<_Scalar, _layout> &&c ) noexcept {
  gemm<_transa, _transb>(alpha, a, b, beta, c);
}
//@}

}  // namespace blas

}  // namespace isvd

#endif  // ISVD_BLAS_DENSE_GEMM_HPP_
