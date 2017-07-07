////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/raw/lapack/gebrd.hpp
/// @brief   The LAPACK GEBRD.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_RAW_LAPACK_GEBRD_HPP_
#define MCNLA_CORE_LA_RAW_LAPACK_GEBRD_HPP_

#include <mcnla/core/la/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <mcnla/core/la/raw/plugin/lapack_plugin_begin.h>

extern void sgebrd_( const FORTRAN_INT m, const FORTRAN_INT n, FORTRAN_REAL4 a, const FORTRAN_INT lda, FORTRAN_REAL4 d,
                     FORTRAN_REAL4 e, FORTRAN_REAL4 tauq, FORTRAN_REAL4 taup, FORTRAN_REAL4 work, const FORTRAN_INT lwork,
                     FORTRAN_INT info );
extern void dgebrd_( const FORTRAN_INT m, const FORTRAN_INT n, FORTRAN_REAL8 a, const FORTRAN_INT lda, FORTRAN_REAL8 d,
                     FORTRAN_REAL8 e, FORTRAN_REAL8 tauq, FORTRAN_REAL8 taup, FORTRAN_REAL8 work, const FORTRAN_INT lwork,
                     FORTRAN_INT info );
extern void cgebrd_( const FORTRAN_INT m, const FORTRAN_INT n, FORTRAN_COMP4 a, const FORTRAN_INT lda, FORTRAN_REAL4 d,
                     FORTRAN_REAL4 e, FORTRAN_COMP4 tauq, FORTRAN_COMP4 taup, FORTRAN_COMP4 work, const FORTRAN_INT lwork,
                     FORTRAN_INT info );
extern void zgebrd_( const FORTRAN_INT m, const FORTRAN_INT n, FORTRAN_COMP8 a, const FORTRAN_INT lda, FORTRAN_REAL8 d,
                     FORTRAN_REAL8 e, FORTRAN_COMP8 tauq, FORTRAN_COMP8 taup, FORTRAN_COMP8 work, const FORTRAN_INT lwork,
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
static inline index_t gebrd(
    const index_t m, const index_t n, float *a, const index_t lda,
    float *d, float *e, float *tauq, float *taup,
    float *work, const index_t lwork
) noexcept { index_t info; sgebrd_(&m, &n, a, &lda, d, e, tauq, taup, work, &lwork, &info); return info; }
static inline index_t gebrd(
    const index_t m, const index_t n, double *a, const index_t lda,
    double *d, double *e, double *tauq, double *taup,
    double *work, const index_t lwork
) noexcept { index_t info; dgebrd_(&m, &n, a, &lda, d, e, tauq, taup, work, &lwork, &info); return info; }
static inline index_t gebrd(
    const index_t m, const index_t n, std::complex<float> *a, const index_t lda,
    float *d, float *e, std::complex<float> *tauq, std::complex<float> *taup,
    std::complex<float> *work, const index_t lwork
) noexcept { index_t info; cgebrd_(&m, &n, a, &lda, d, e, tauq, taup, work, &lwork, &info); return info; }
static inline index_t gebrd(
    const index_t m, const index_t n, std::complex<double> *a, const index_t lda,
    double *d, double *e, std::complex<double> *tauq, std::complex<double> *taup,
    std::complex<double> *work, const index_t lwork
) noexcept { index_t info; zgebrd_(&m, &n, a, &lda, d, e, tauq, taup, work, &lwork, &info); return info; }
//@}

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_RAW_LAPACK_GEBRD_HPP_
