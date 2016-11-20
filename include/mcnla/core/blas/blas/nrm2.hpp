////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/blas/blas/nrm2.hpp
/// @brief   The BLAS NRM2.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_BLAS_BLAS_NRM2_HPP_
#define MCNLA_CORE_BLAS_BLAS_NRM2_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <mcnla/core/blas/plugin/blas_plugin_begin.h>

// Computes the Euclidean norm of a vector.
extern CPP_REAL4 snrm2_(  const FORTRAN_INT n, const FORTRAN_REAL4 x, const FORTRAN_INT incx );
extern CPP_REAL8 dnrm2_(  const FORTRAN_INT n, const FORTRAN_REAL8 x, const FORTRAN_INT incx );
extern CPP_REAL4 scnrm2_( const FORTRAN_INT n, const FORTRAN_COMP4 x, const FORTRAN_INT incx );
extern CPP_REAL8 dznrm2_( const FORTRAN_INT n, const FORTRAN_COMP8 x, const FORTRAN_INT incx );

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
/// @brief  Computes the Euclidean norm of a vector.
///
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

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_BLAS_NRM2_HPP_
