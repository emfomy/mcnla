////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/raw/spblas/coomm.hpp
/// @brief   The Sparse BLAS COOMM.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_RAW_SPBLAS_COOMM_HPP_
#define MCNLA_CORE_LA_RAW_SPBLAS_COOMM_HPP_

#include <mcnla/core/la/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <mcnla/core/la/raw/plugin/spblas_plugin_begin.h>

// Computes matrix-matrix product of a sparse matrix stored in the coordinate format.
extern void mkl_scoomm_( const FORTRAN_CHAR1 transa, const FORTRAN_INT m, const FORTRAN_INT n, const FORTRAN_INT k,
                         const FORTRAN_REAL4 alpha, const FORTRAN_CHAR1 matdescra, const FORTRAN_REAL4 val,
                         const FORTRAN_INT rowind, const FORTRAN_INT colind, const FORTRAN_INT nnz, const FORTRAN_REAL4 b,
                         const FORTRAN_INT ldb, const FORTRAN_REAL4 beta, FORTRAN_REAL4 c, const FORTRAN_INT ldc );
extern void mkl_dcoomm_( const FORTRAN_CHAR1 transa, const FORTRAN_INT m, const FORTRAN_INT n, const FORTRAN_INT k,
                         const FORTRAN_REAL8 alpha, const FORTRAN_CHAR1 matdescra, const FORTRAN_REAL8 val,
                         const FORTRAN_INT rowind, const FORTRAN_INT colind, const FORTRAN_INT nnz, const FORTRAN_REAL8 b,
                         const FORTRAN_INT ldb, const FORTRAN_REAL8 beta, FORTRAN_REAL8 c, const FORTRAN_INT ldc );
extern void mkl_ccoomm_( const FORTRAN_CHAR1 transa, const FORTRAN_INT m, const FORTRAN_INT n, const FORTRAN_INT k,
                         const FORTRAN_COMP4 alpha, const FORTRAN_CHAR1 matdescra, const FORTRAN_COMP4 val,
                         const FORTRAN_INT rowind, const FORTRAN_INT colind, const FORTRAN_INT nnz, const FORTRAN_COMP4 b,
                         const FORTRAN_INT ldb, const FORTRAN_COMP4 beta, FORTRAN_COMP4 c, const FORTRAN_INT ldc );
extern void mkl_zcoomm_( const FORTRAN_CHAR1 transa, const FORTRAN_INT m, const FORTRAN_INT n, const FORTRAN_INT k,
                         const FORTRAN_COMP8 alpha, const FORTRAN_CHAR1 matdescra, const FORTRAN_COMP8 val,
                         const FORTRAN_INT rowind, const FORTRAN_INT colind, const FORTRAN_INT nnz, const FORTRAN_COMP8 b,
                         const FORTRAN_INT ldb, const FORTRAN_COMP8 beta, FORTRAN_COMP8 c, const FORTRAN_INT ldc );

#include <mcnla/core/la/raw/plugin/spblas_plugin_end.h>

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

//@{
static inline void coomm(
    const char transa, const index_t m, const index_t n, const index_t k, const float alpha, const char *matdescra,
    const float *val, const index_t *rowind, const index_t *colind, const index_t nnz,
    const float *b, const index_t ldb, const float beta, float *c, const index_t ldc
) noexcept { mkl_scoomm_(&transa, &m, &n, &k, &alpha, matdescra, val, rowind, colind, &nnz, b, &ldb, &beta, c, &ldc); }
static inline void coomm(
    const char transa, const index_t m, const index_t n, const index_t k, const double alpha, const char *matdescra,
    const double *val, const index_t *rowind, const index_t *colind, const index_t nnz,
    const double *b, const index_t ldb, const double beta, double *c, const index_t ldc
) noexcept { mkl_dcoomm_(&transa, &m, &n, &k, &alpha, matdescra, val, rowind, colind, &nnz, b, &ldb, &beta, c, &ldc); }
static inline void coomm(
    const char transa, const index_t m, const index_t n, const index_t k,
    const std::complex<float> alpha, const char *matdescra,
    const std::complex<float> *val, const index_t *rowind, const index_t *colind, const index_t nnz,
    const std::complex<float> *b, const index_t ldb,
    const std::complex<float> beta, std::complex<float> *c, const index_t ldc
) noexcept { mkl_ccoomm_(&transa, &m, &n, &k, &alpha, matdescra, val, rowind, colind, &nnz, b, &ldb, &beta, c, &ldc); }
static inline void coomm(
    const char transa, const index_t m, const index_t n, const index_t k,
    const std::complex<double> alpha, const char *matdescra,
    const std::complex<double> *val, const index_t *rowind, const index_t *colind, const index_t nnz,
    const std::complex<double> *b, const index_t ldb,
    const std::complex<double> beta, std::complex<double> *c, const index_t ldc
) noexcept { mkl_zcoomm_(&transa, &m, &n, &k, &alpha, matdescra, val, rowind, colind, &nnz, b, &ldb, &beta, c, &ldc); }
//@}

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_RAW_SPBLAS_COOMM_HPP_
