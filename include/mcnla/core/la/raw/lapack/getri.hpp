////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/raw/lapack/getri.hpp
/// @brief   The LAPACK GETRI.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_RAW_LAPACK_GETRI_HPP_
#define MCNLA_CORE_LA_RAW_LAPACK_GETRI_HPP_

#include <mcnla/core/la/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <mcnla/core/la/raw/plugin/lapack_plugin_begin.h>

extern void sgetri_( const FORTRAN_INT n, FORTRAN_REAL4 a, const FORTRAN_INT lda, const FORTRAN_INT ipiv, FORTRAN_REAL4 work,
                     const FORTRAN_INT lwork, FORTRAN_INT info );
extern void dgetri_( const FORTRAN_INT n, FORTRAN_REAL8 a, const FORTRAN_INT lda, const FORTRAN_INT ipiv, FORTRAN_REAL8 work,
                     const FORTRAN_INT lwork, FORTRAN_INT info );
extern void cgetri_( const FORTRAN_INT n, FORTRAN_COMP4 a, const FORTRAN_INT lda, const FORTRAN_INT ipiv, FORTRAN_COMP4 work,
                     const FORTRAN_INT lwork, FORTRAN_INT info );
extern void zgetri_( const FORTRAN_INT n, FORTRAN_COMP8 a, const FORTRAN_INT lda, const FORTRAN_INT ipiv, FORTRAN_COMP8 work,
                     const FORTRAN_INT lwork, FORTRAN_INT info );

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
static inline index_t getri(
    const index_t n, float *a, const index_t lda, const index_t *ipiv,
    float *work, const index_t lwork
) noexcept {index_t info; sgetri_(&n, a, &lda, ipiv, work, &lwork, &info); return info;
}
static inline index_t getri(
    const index_t n, double *a, const index_t lda, const index_t *ipiv,
    double *work, const index_t lwork
) noexcept {index_t info; dgetri_(&n, a, &lda, ipiv, work, &lwork, &info); return info;
}
static inline index_t getri(
    const index_t n, std::complex<float> *a, const index_t lda, const index_t *ipiv,
    std::complex<float> *work, const index_t lwork
) noexcept {index_t info; cgetri_(&n, a, &lda, ipiv, work, &lwork, &info); return info;
}
static inline index_t getri(
    const index_t n, std::complex<double> *a, const index_t lda, const index_t *ipiv,
    std::complex<double> *work, const index_t lwork
) noexcept {index_t info; zgetri_(&n, a, &lda, ipiv, work, &lwork, &info); return info;
}
//@}

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_RAW_LAPACK_GETRI_HPP_
