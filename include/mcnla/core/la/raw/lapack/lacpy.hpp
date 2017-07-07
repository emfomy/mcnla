////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/raw/lapack/lacpy.hpp
/// @brief   The LAPACK LACPY.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_RAW_LAPACK_LACPY_HPP_
#define MCNLA_CORE_LA_RAW_LAPACK_LACPY_HPP_

#include <mcnla/core/la/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <mcnla/core/la/raw/plugin/lapack_plugin_begin.h>

extern void slacpy_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT m, const FORTRAN_INT n, const FORTRAN_REAL4 a,
                     const FORTRAN_INT lda, FORTRAN_REAL4 b, const FORTRAN_INT ldb );
extern void dlacpy_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT m, const FORTRAN_INT n, const FORTRAN_REAL8 a,
                     const FORTRAN_INT lda, FORTRAN_REAL8 b, const FORTRAN_INT ldb );
extern void clacpy_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT m, const FORTRAN_INT n, const FORTRAN_COMP4 a,
                     const FORTRAN_INT lda, FORTRAN_COMP4 b, const FORTRAN_INT ldb );
extern void zlacpy_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT m, const FORTRAN_INT n, const FORTRAN_COMP8 a,
                     const FORTRAN_INT lda, FORTRAN_COMP8 b, const FORTRAN_INT ldb );

#include <mcnla/core/la/raw/plugin/lapack_plugin_end.h>

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
static inline void lacpy(
    const char uplo, const index_t m, const index_t n, const float *a, const index_t lda, float *b, const index_t ldb
) noexcept { slacpy_(&uplo, &m, &n, a, &lda, b, &ldb); }
static inline void lacpy(
    const char uplo, const index_t m, const index_t n, const double *a, const index_t lda, double *b, const index_t ldb
) noexcept { dlacpy_(&uplo, &m, &n, a, &lda, b, &ldb); }
static inline void lacpy(
    const char uplo, const index_t m, const index_t n,
    const std::complex<float> *a, const index_t lda, std::complex<float> *b, const index_t ldb
) noexcept { clacpy_(&uplo, &m, &n, a, &lda, b, &ldb); }
static inline void lacpy(
    const char uplo, const index_t m, const index_t n,
    const std::complex<double> *a, const index_t lda, std::complex<double> *b, const index_t ldb
) noexcept { zlacpy_(&uplo, &m, &n, a, &lda, b, &ldb); }
//@}

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_RAW_LAPACK_LACPY_HPP_
