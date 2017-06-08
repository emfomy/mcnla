////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/raw/blas/gemmt.hpp
/// @brief   The BLAS GEMMT.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_RAW_BLAS_GEMMT_HPP_
#define MCNLA_CORE_LA_RAW_BLAS_GEMMT_HPP_

#include <mcnla/core/la/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#ifdef MCNLA_USE_MKL

#include <mcnla/core/la/raw/plugin/blas_plugin_begin.h>

// Computes a matrix-matrix product with general matrices.
extern void sgemmt_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 transa, const FORTRAN_CHAR1 transb, const FORTRAN_INT n,
                    const FORTRAN_INT k, const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 a, const FORTRAN_INT lda,
                    const FORTRAN_REAL4 b, const FORTRAN_INT ldb, const FORTRAN_REAL4 beta, FORTRAN_REAL4 c,
                    const FORTRAN_INT ldc );
extern void dgemmt_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 transa, const FORTRAN_CHAR1 transb, const FORTRAN_INT n,
                    const FORTRAN_INT k, const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 a, const FORTRAN_INT lda,
                    const FORTRAN_REAL8 b, const FORTRAN_INT ldb, const FORTRAN_REAL8 beta, FORTRAN_REAL8 c,
                    const FORTRAN_INT ldc );
extern void cgemmt_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 transa, const FORTRAN_CHAR1 transb, const FORTRAN_INT n,
                    const FORTRAN_INT k, const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 a, const FORTRAN_INT lda,
                    const FORTRAN_COMP4 b, const FORTRAN_INT ldb, const FORTRAN_COMP4 beta, FORTRAN_COMP4 c,
                    const FORTRAN_INT ldc );
extern void zgemmt_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 transa, const FORTRAN_CHAR1 transb, const FORTRAN_INT n,
                    const FORTRAN_INT k, const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 a, const FORTRAN_INT lda,
                    const FORTRAN_COMP8 b, const FORTRAN_INT ldb, const FORTRAN_COMP8 beta, FORTRAN_COMP8 c,
                    const FORTRAN_INT ldc );

#include <mcnla/core/la/raw/plugin/blas_plugin_end.h>

#endif  // MCNLA_USE_MKL

#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The linear algebra namespace
//
namespace la {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace
//
namespace detail {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes a matrix-matrix product with general matrices but updates only the upper or lower triangular part of the
///         result matrix.
///
/// @note  The routine calls mcnla::la::gemm instead if there is no MKL support.
///
//@{
#ifdef MCNLA_USE_MKL

static inline void gemmt(
    const char uplo, const char transa, const char transb, const index_t n, const index_t k,
    const float alpha, const float *a, const index_t lda, const float *b, const index_t ldb,
    const float beta, float *c, const index_t ldc
) noexcept { sgemmt_(&uplo, &transa, &transb, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void gemmt(
    const char uplo, const char transa, const char transb, const index_t n, const index_t k,
    const double alpha, const double *a, const index_t lda, const double *b, const index_t ldb,
    const double beta, double *c, const index_t ldc
) noexcept { dgemmt_(&uplo, &transa, &transb, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void gemmt(
    const char uplo, const char transa, const char transb, const index_t n, const index_t k,
    const std::complex<float> alpha, const std::complex<float> *a, const index_t lda,
    const std::complex<float> *b, const index_t ldb,
    const std::complex<float> beta, std::complex<float> *c, const index_t ldc
) noexcept { cgemmt_(&uplo, &transa, &transb, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void gemmt(
    const char uplo, const char transa, const char transb, const index_t n, const index_t k,
    const std::complex<double> alpha, const std::complex<double> *a, const index_t lda,
    const std::complex<double> *b, const index_t ldb,
    const std::complex<double> beta, std::complex<double> *c, const index_t ldc
) noexcept { zgemmt_(&uplo, &transa, &transb, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }

#else  // MCNLA_USE_MKL

template <typename _Val>
static inline void gemmt(
    const char uplo, const char transa, const char transb, const index_t n, const index_t k,
    const _Val alpha, const _Val *a, const index_t lda, const _Val *b, const index_t ldb,
    const _Val beta, _Val *c, const index_t ldc
) noexcept { gemm(transa, transb, n, n, k, alpha, a, lda, b, ldb, beta, c, ldc); }

#endif  // MCNLA_USE_MKL
//@}

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_RAW_BLAS_GEMMT_HPP_
