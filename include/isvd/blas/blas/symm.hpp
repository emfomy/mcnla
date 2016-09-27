////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/blas/blas/symm.hpp
/// @brief   The BLAS SYMM.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef ISVD_BLAS_BLAS_SYMM_HPP_
#define ISVD_BLAS_BLAS_SYMM_HPP_

#include <isvd/isvd.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <isvd/plugin/blas_plugin_begin.h>

// Computes a matrix-matrix product where one input matrix is symmetric.
extern void ssymm_( const FORTRAN_CHAR1 side, const FORTRAN_CHAR1 uplo, const FORTRAN_INT m, const FORTRAN_INT n,
                    const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 a, const FORTRAN_INT lda, const FORTRAN_REAL4 b,
                    const FORTRAN_INT ldb, const FORTRAN_REAL4 beta, FORTRAN_REAL4 c, const FORTRAN_INT ldc );
extern void dsymm_( const FORTRAN_CHAR1 side, const FORTRAN_CHAR1 uplo, const FORTRAN_INT m, const FORTRAN_INT n,
                    const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 a, const FORTRAN_INT lda, const FORTRAN_REAL8 b,
                    const FORTRAN_INT ldb, const FORTRAN_REAL8 beta, FORTRAN_REAL8 c, const FORTRAN_INT ldc );

// Computes a matrix-matrix product where one input matrix is Hermitian.
extern void chemm_( const FORTRAN_CHAR1 side, const FORTRAN_CHAR1 uplo, const FORTRAN_INT m, const FORTRAN_INT n,
                    const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 a, const FORTRAN_INT lda, const FORTRAN_COMP4 b,
                    const FORTRAN_INT ldb, const FORTRAN_COMP4 beta, FORTRAN_COMP4 c, const FORTRAN_INT ldc );
extern void zhemm_( const FORTRAN_CHAR1 side, const FORTRAN_CHAR1 uplo, const FORTRAN_INT m, const FORTRAN_INT n,
                    const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 a, const FORTRAN_INT lda, const FORTRAN_COMP8 b,
                    const FORTRAN_INT ldb, const FORTRAN_COMP8 beta, FORTRAN_COMP8 c, const FORTRAN_INT ldc );

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
//  The detail namespace
//
namespace detail {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes a matrix-matrix product where one input matrix is symmetric/Hermitian.
///
//@{
static inline void symm(
    const char side, const char uplo, const index_t m, const index_t n,
    const float alpha, const float *a, const index_t lda, const float *b, const index_t ldb,
    const float beta, float *c, const index_t ldc
) noexcept {
  ssymm_(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc);
}
static inline void symm(
    const char side, const char uplo, const index_t m, const index_t n,
    const double alpha, const double *a, const index_t lda, const double *b, const index_t ldb,
    const double beta, double *c, const index_t ldc
) noexcept {
  dsymm_(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc);
}
static inline void symm(
    const char side, const char uplo, const index_t m, const index_t n,
    const std::complex<float> alpha, const std::complex<float> *a, const index_t lda,
    const std::complex<float> *b, const index_t ldb,
    const std::complex<float> beta, std::complex<float> *c, const index_t ldc
) noexcept {
  chemm_(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc);
}
static inline void symm(
    const char side, const char uplo, const index_t m, const index_t n,
    const std::complex<double> alpha, const std::complex<double> *a, const index_t lda,
    const std::complex<double> *b, const index_t ldb,
    const std::complex<double> beta, std::complex<double> *c, const index_t ldc
) noexcept {
  zhemm_(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc);
}
//@}

}  // namespace detail

}  // namespace blas

}  // namespace isvd

#endif  // ISVD_BLAS_BLAS_SYMM_HPP_
