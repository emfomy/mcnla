////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/raw/lapack/lange.hpp
/// @brief   The LAPACK LANGE.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_RAW_LAPACK_LANGE_HPP_
#define MCNLA_CORE_LA_RAW_LAPACK_LANGE_HPP_

#include <mcnla/core/la/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <mcnla/core/la/raw/plugin/lapack_plugin_begin.h>

extern CPP_REAL4 slange_( const FORTRAN_CHAR1 norm, const FORTRAN_INT m, const FORTRAN_INT n, const FORTRAN_REAL4 a,
                          const FORTRAN_INT lda, FORTRAN_REAL4 work );
extern CPP_REAL8 dlange_( const FORTRAN_CHAR1 norm, const FORTRAN_INT m, const FORTRAN_INT n, const FORTRAN_REAL8 a,
                          const FORTRAN_INT lda, FORTRAN_REAL8 work );
extern CPP_REAL4 clange_( const FORTRAN_CHAR1 norm, const FORTRAN_INT m, const FORTRAN_INT n, const FORTRAN_COMP4 a,
                          const FORTRAN_INT lda, FORTRAN_REAL4 work );
extern CPP_REAL8 zlange_( const FORTRAN_CHAR1 norm, const FORTRAN_INT m, const FORTRAN_INT n, const FORTRAN_COMP8 a,
                          const FORTRAN_INT lda, FORTRAN_REAL8 work );

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
static inline float lange(
    const char norm, const index_t m, const index_t n, const float *a, const index_t lda, float *work
) noexcept { return slange_(&norm, &m, &n, a, &lda, work); }
static inline double lange(
    const char norm, const index_t m, const index_t n, const double *a, const index_t lda, double *work
) noexcept { return dlange_(&norm, &m, &n, a, &lda, work); }
static inline float lange(
    const char norm, const index_t m, const index_t n, const std::complex<float> *a, const index_t lda, float *work
) noexcept { return clange_(&norm, &m, &n, a, &lda, work); }
static inline double lange(
    const char norm, const index_t m, const index_t n, const std::complex<double> *a, const index_t lda, double *work
) noexcept { return zlange_(&norm, &m, &n, a, &lda, work); }
//@}

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_RAW_LAPACK_LANGE_HPP_
