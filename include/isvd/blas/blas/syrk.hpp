////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/blas/blas/syrk.hpp
/// @brief   The BLAS SYRK.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_BLAS_BLAS_SYRK_HPP_
#define ISVD_BLAS_BLAS_SYRK_HPP_

#include <isvd/isvd.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <isvd/plugin/blas_plugin_begin.h>

// Performs a symmetric rank-k update.
extern void ssyrk_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_INT8 n, const FORTRAN_INT8 k,
                    const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 a, const FORTRAN_INT8 lda, const FORTRAN_REAL4 beta,
                    FORTRAN_REAL4 c, const FORTRAN_INT8 ldc );
extern void dsyrk_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_INT8 n, const FORTRAN_INT8 k,
                    const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 a, const FORTRAN_INT8 lda, const FORTRAN_REAL8 beta,
                    FORTRAN_REAL8 c, const FORTRAN_INT8 ldc );

// Performs a Hermitian rank-k update.
extern void cherk_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_INT8 n, const FORTRAN_INT8 k,
                    const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 a, const FORTRAN_INT8 lda, const FORTRAN_COMP4 beta,
                    FORTRAN_COMP4 c, const FORTRAN_INT8 ldc );
extern void zherk_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_INT8 n, const FORTRAN_INT8 k,
                    const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 a, const FORTRAN_INT8 lda, const FORTRAN_COMP8 beta,
                    FORTRAN_COMP8 c, const FORTRAN_INT8 ldc );

#include <isvd/plugin/blas_plugin_end.h>

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
/// @brief  Performs a symmetric/Hermitian rank-k update.
///
//@{
static inline void syrk(
    const char uplo, const char trans, const index_t n, const index_t k,
    const float alpha, const float* a, const index_t lda,
    const float beta, float* c, const index_t ldc
) noexcept { ssyrk_(&uplo, &trans, &n, &k, &alpha, a, &lda, &beta, c, &ldc); }
static inline void syrk(
    const char uplo, const char trans, const index_t n, const index_t k,
    const double alpha, const double* a, const index_t lda,
    const double beta, double* c, const index_t ldc
) noexcept { dsyrk_(&uplo, &trans, &n, &k, &alpha, a, &lda, &beta, c, &ldc); }
static inline void syrk(
    const char uplo, const char trans, const index_t n, const index_t k,
    const std::complex<float> alpha, const std::complex<float>* a, const index_t lda,
    const std::complex<float> beta, std::complex<float>* c, const index_t ldc
) noexcept { cherk_(&uplo, &trans, &n, &k, &alpha, a, &lda, &beta, c, &ldc); }
static inline void syrk(
    const char uplo, const char trans, const index_t n, const index_t k,
    const std::complex<double> alpha, const std::complex<double>* a, const index_t lda,
    const std::complex<double> beta, std::complex<double>* c, const index_t ldc
) noexcept { zherk_(&uplo, &trans, &n, &k, &alpha, a, &lda, &beta, c, &ldc); }
//@}

}  // namespace internal

}  // namespace blas

}  // namespace isvd

#endif  // ISVD_BLAS_BLAS_SYRK_HPP_
