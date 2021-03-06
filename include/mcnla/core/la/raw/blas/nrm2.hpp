////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/raw/blas/nrm2.hpp
/// @brief   The BLAS NRM2.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_RAW_BLAS_NRM2_HPP_
#define MCNLA_CORE_LA_RAW_BLAS_NRM2_HPP_

#include <mcnla/core/la/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <mcnla/core/la/raw/plugin/blas_plugin_begin.h>

extern CPP_REAL4 snrm2_(  const FORTRAN_INT n, const FORTRAN_REAL4 x, const FORTRAN_INT incx );
extern CPP_REAL8 dnrm2_(  const FORTRAN_INT n, const FORTRAN_REAL8 x, const FORTRAN_INT incx );
extern CPP_REAL4 scnrm2_( const FORTRAN_INT n, const FORTRAN_COMP4 x, const FORTRAN_INT incx );
extern CPP_REAL8 dznrm2_( const FORTRAN_INT n, const FORTRAN_COMP8 x, const FORTRAN_INT incx );

#include <mcnla/core/la/raw/plugin/blas_plugin_end.h>

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
static inline float nrm2(
    const index_t n, const float* x, const index_t incx
) noexcept { return snrm2_(&n, x, &incx); }
static inline double nrm2(
    const index_t n, const double* x, const index_t incx
) noexcept { return dnrm2_(&n, x, &incx); }
static inline float nrm2(
    const index_t n, const std::complex<float>* x, const index_t incx
) noexcept { return scnrm2_(&n, x, &incx); }
static inline double nrm2(
    const index_t n, const std::complex<double>* x, const index_t incx
) noexcept { return dznrm2_(&n, x, &incx); }
//@}

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_RAW_BLAS_NRM2_HPP_
