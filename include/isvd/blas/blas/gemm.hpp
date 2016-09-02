////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/blas/blas/gemm.hpp
/// @brief   The BLAS GEMM.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_BLAS_BLAS_GEMM_HPP_
#define ISVD_BLAS_BLAS_GEMM_HPP_

#include <isvd/isvd.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

extern "C" {

#include <isvd/plugin/blas_plugin_start.h>

// Computes a matrix-matrix product with general matrices.
extern void sgemm_( const FORTRAN_CHAR1 transa, const FORTRAN_CHAR1 transb, const FORTRAN_INT8 m, const FORTRAN_INT8 n,
                    const FORTRAN_INT8 k, const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 a, const FORTRAN_INT8 lda,
                    const FORTRAN_REAL4 b, const FORTRAN_INT8 ldb, const FORTRAN_REAL4 beta, FORTRAN_REAL4 c,
                    const FORTRAN_INT8 ldc );
extern void dgemm_( const FORTRAN_CHAR1 transa, const FORTRAN_CHAR1 transb, const FORTRAN_INT8 m, const FORTRAN_INT8 n,
                    const FORTRAN_INT8 k, const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 a, const FORTRAN_INT8 lda,
                    const FORTRAN_REAL8 b, const FORTRAN_INT8 ldb, const FORTRAN_REAL8 beta, FORTRAN_REAL8 c,
                    const FORTRAN_INT8 ldc );
extern void cgemm_( const FORTRAN_CHAR1 transa, const FORTRAN_CHAR1 transb, const FORTRAN_INT8 m, const FORTRAN_INT8 n,
                    const FORTRAN_INT8 k, const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 a, const FORTRAN_INT8 lda,
                    const FORTRAN_COMP4 b, const FORTRAN_INT8 ldb, const FORTRAN_COMP4 beta, FORTRAN_COMP4 c,
                    const FORTRAN_INT8 ldc );
extern void zgemm_( const FORTRAN_CHAR1 transa, const FORTRAN_CHAR1 transb, const FORTRAN_INT8 m, const FORTRAN_INT8 n,
                    const FORTRAN_INT8 k, const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 a, const FORTRAN_INT8 lda,
                    const FORTRAN_COMP8 b, const FORTRAN_INT8 ldb, const FORTRAN_COMP8 beta, FORTRAN_COMP8 c,
                    const FORTRAN_INT8 ldc );

#include <isvd/plugin/blas_plugin_end.h>

}  // extern "C"

#endif  // DOXYGEN_SHOULD_SKIP_THIS

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
/// @brief  Computes a matrix-matrix product with general matrices.
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

}  // namespace blas

}  // namespace isvd

#endif  // ISVD_BLAS_BLAS_GEMM_HPP_
