////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/blas/blas/syr2k.hpp
/// @brief   The BLAS SYR2K.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_BLAS_BLAS_SYR2K_HPP_
#define MCNLA_CORE_BLAS_BLAS_SYR2K_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <mcnla/core/blas/plugin/blas_plugin_begin.h>

// Performs a symmetric rank-k update.
extern void ssyr2k_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_INT n, const FORTRAN_INT k,
                     const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 a, const FORTRAN_INT lda, const FORTRAN_REAL4 b,
                     const FORTRAN_INT ldb, const FORTRAN_REAL4 beta, FORTRAN_REAL4 c, const FORTRAN_INT ldc );
extern void dsyr2k_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_INT n, const FORTRAN_INT k,
                     const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 a, const FORTRAN_INT lda, const FORTRAN_REAL8 b,
                     const FORTRAN_INT ldb, const FORTRAN_REAL8 beta, FORTRAN_REAL8 c, const FORTRAN_INT ldc );

// Performs a Hermitian rank-k update.
extern void cher2k_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_INT n, const FORTRAN_INT k,
                     const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 a, const FORTRAN_INT lda, const FORTRAN_COMP4 b,
                     const FORTRAN_INT ldb, const FORTRAN_COMP4 beta, FORTRAN_COMP4 c, const FORTRAN_INT ldc );
extern void zher2k_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_INT n, const FORTRAN_INT k,
                     const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 a, const FORTRAN_INT lda, const FORTRAN_COMP8 b,
                     const FORTRAN_INT ldb, const FORTRAN_COMP8 beta, FORTRAN_COMP8 c, const FORTRAN_INT ldc );

#include <mcnla/core/blas/plugin/blas_plugin_end.h>

#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The BLAS namespace
//
namespace blas {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace
//
namespace detail {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Performs a symmetric/Hermitian rank-2k update.
///
//@{
static inline void syr2k(
    const char uplo, const char trans, const index_t n, const index_t k,
    const float alpha, const float* a, const index_t lda, const float* b, const index_t ldb,
    const float beta, float* c, const index_t ldc
) noexcept { ssyr2k_(&uplo, &trans, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void syr2k(
    const char uplo, const char trans, const index_t n, const index_t k,
    const double alpha, const double* a, const index_t lda, const double* b, const index_t ldb,
    const double beta, double* c, const index_t ldc
) noexcept { dsyr2k_(&uplo, &trans, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void syr2k(
    const char uplo, const char trans, const index_t n, const index_t k,
    const std::complex<float> alpha, const std::complex<float>* a, const index_t lda,
    const std::complex<float>* b, const index_t ldb,
    const std::complex<float> beta, std::complex<float>* c, const index_t ldc
) noexcept { cher2k_(&uplo, &trans, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void syr2k(
    const char uplo, const char trans, const index_t n, const index_t k,
    const std::complex<double> alpha, const std::complex<double>* a, const index_t lda,
    const std::complex<double>* b, const index_t ldb,
    const std::complex<double> beta, std::complex<double>* c, const index_t ldc
) noexcept { zher2k_(&uplo, &trans, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
//@}

}  // namespace detail

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_BLAS_SYR2K_HPP_
