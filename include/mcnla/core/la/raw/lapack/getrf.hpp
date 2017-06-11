////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/raw/lapack/getrf.hpp
/// @brief   The LAPACK GETRF.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_RAW_LAPACK_GETRF_HPP_
#define MCNLA_CORE_LA_RAW_LAPACK_GETRF_HPP_

#include <mcnla/core/la/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <mcnla/core/la/raw/plugin/lapack_plugin_begin.h>

extern void sgetrf_( const FORTRAN_INT m, const FORTRAN_INT n, FORTRAN_REAL4 a, const FORTRAN_INT lda, FORTRAN_INT ipiv,
                     FORTRAN_INT info );
extern void dgetrf_( const FORTRAN_INT m, const FORTRAN_INT n, FORTRAN_REAL8 a, const FORTRAN_INT lda, FORTRAN_INT ipiv,
                     FORTRAN_INT info );
extern void cgetrf_( const FORTRAN_INT m, const FORTRAN_INT n, FORTRAN_COMP4 a, const FORTRAN_INT lda, FORTRAN_INT ipiv,
                     FORTRAN_INT info );
extern void zgetrf_( const FORTRAN_INT m, const FORTRAN_INT n, FORTRAN_COMP8 a, const FORTRAN_INT lda, FORTRAN_INT ipiv,
                     FORTRAN_INT info );

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
static inline index_t getrf(
    const index_t m, const index_t n, float *a, const index_t lda, index_t *ipiv
) noexcept {index_t info; sgetrf_(&m, &n, a, &lda, ipiv, &info); return info;
}
static inline index_t getrf(
    const index_t m, const index_t n, double *a, const index_t lda, index_t *ipiv
) noexcept {index_t info; dgetrf_(&m, &n, a, &lda, ipiv, &info); return info;
}
static inline index_t getrf(
    const index_t m, const index_t n, std::complex<float> *a, const index_t lda, index_t *ipiv
) noexcept {index_t info; cgetrf_(&m, &n, a, &lda, ipiv, &info); return info;
}
static inline index_t getrf(
    const index_t m, const index_t n, std::complex<double> *a, const index_t lda, index_t *ipiv
) noexcept {index_t info; zgetrf_(&m, &n, a, &lda, ipiv, &info); return info;
}
//@}

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_RAW_LAPACK_GETRF_HPP_
