////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/raw/spblas/diasm.hpp
/// @brief   The Sparse BLAS DIASM.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_RAW_SPBLAS_DIASM_HPP_
#define MCNLA_CORE_LA_RAW_SPBLAS_DIASM_HPP_

#include <mcnla/core/la/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <mcnla/core/la/raw/plugin/spblas_plugin_begin.h>

extern void mkl_sdiasm_( const FORTRAN_CHAR1 transa, const FORTRAN_INT m, const FORTRAN_INT n, const FORTRAN_REAL4 alpha,
                         const FORTRAN_CHAR1 matdescra, const FORTRAN_REAL4 val, const FORTRAN_INT lval,
                         const FORTRAN_INT idiag, const FORTRAN_INT ndiag, const FORTRAN_REAL4 b, const FORTRAN_INT ldb,
                         FORTRAN_REAL4 c, const FORTRAN_INT ldc );
extern void mkl_ddiasm_( const FORTRAN_CHAR1 transa, const FORTRAN_INT m, const FORTRAN_INT n, const FORTRAN_REAL8 alpha,
                         const FORTRAN_CHAR1 matdescra, const FORTRAN_REAL8 val, const FORTRAN_INT lval,
                         const FORTRAN_INT idiag, const FORTRAN_INT ndiag, const FORTRAN_REAL8 b, const FORTRAN_INT ldb,
                         FORTRAN_REAL8 c, const FORTRAN_INT ldc );
extern void mkl_cdiasm_( const FORTRAN_CHAR1 transa, const FORTRAN_INT m, const FORTRAN_INT n, const FORTRAN_COMP4 alpha,
                         const FORTRAN_CHAR1 matdescra, const FORTRAN_COMP4 val, const FORTRAN_INT lval,
                         const FORTRAN_INT idiag, const FORTRAN_INT ndiag, const FORTRAN_COMP4 b, const FORTRAN_INT ldb,
                         FORTRAN_COMP4 c, const FORTRAN_INT ldc );
extern void mkl_zdiasm_( const FORTRAN_CHAR1 transa, const FORTRAN_INT m, const FORTRAN_INT n, const FORTRAN_COMP8 alpha,
                         const FORTRAN_CHAR1 matdescra, const FORTRAN_COMP8 val, const FORTRAN_INT lval,
                         const FORTRAN_INT idiag, const FORTRAN_INT ndiag, const FORTRAN_COMP8 b, const FORTRAN_INT ldb,
                         FORTRAN_COMP8 c, const FORTRAN_INT ldc );

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
static inline void diasm(
    const char transa, const index_t m, const index_t n, const float alpha, const char *matdescra,
    const float *val, const index_t lval, const index_t *idiag, const index_t ndiag,
    const float *b, const index_t ldb, float *c, const index_t ldc
) noexcept { mkl_sdiasm_(&transa, &m, &n, &alpha, matdescra, val, &lval, idiag, &ndiag, b, &ldb, c, &ldc); }
static inline void diasm(
    const char transa, const index_t m, const index_t n, const double alpha, const char *matdescra,
    const double *val, const index_t lval, const index_t *idiag, const index_t ndiag,
    const double *b, const index_t ldb, double *c, const index_t ldc
) noexcept { mkl_ddiasm_(&transa, &m, &n, &alpha, matdescra, val, &lval, idiag, &ndiag, b, &ldb, c, &ldc); }
static inline void diasm(
    const char transa, const index_t m, const index_t n, const std::complex<float> alpha, const char *matdescra,
    const std::complex<float> *val, const index_t lval, const index_t *idiag, const index_t ndiag,
    const std::complex<float> *b, const index_t ldb, std::complex<float> *c, const index_t ldc
) noexcept { mkl_cdiasm_(&transa, &m, &n, &alpha, matdescra, val, &lval, idiag, &ndiag, b, &ldb, c, &ldc); }
static inline void diasm(
    const char transa, const index_t m, const index_t n, const std::complex<double> alpha, const char *matdescra,
    const std::complex<double> *val, const index_t lval, const index_t *idiag, const index_t ndiag,
    const std::complex<double> *b, const index_t ldb, std::complex<double> *c, const index_t ldc
) noexcept { mkl_zdiasm_(&transa, &m, &n, &alpha, matdescra, val, &lval, idiag, &ndiag, b, &ldb, c, &ldc); }
//@}

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_RAW_SPBLAS_DIASM_HPP_
