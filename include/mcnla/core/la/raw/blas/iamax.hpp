////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/raw/blas/iamax.hpp
/// @brief   The BLAS IAMAX.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_RAW_BLAS_IAMAX_HPP_
#define MCNLA_CORE_LA_RAW_BLAS_IAMAX_HPP_

#include <mcnla/core/la/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <mcnla/core/la/raw/plugin/blas_plugin_begin.h>

extern CPP_INT isamax_( const FORTRAN_INT n, const FORTRAN_REAL4 x, const FORTRAN_INT incx );
extern CPP_INT idamax_( const FORTRAN_INT n, const FORTRAN_REAL8 x, const FORTRAN_INT incx );
extern CPP_INT icamax_( const FORTRAN_INT n, const FORTRAN_COMP4 x, const FORTRAN_INT incx );
extern CPP_INT izamax_( const FORTRAN_INT n, const FORTRAN_COMP8 x, const FORTRAN_INT incx );

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
static inline index_t iamax(
    const index_t n, const float* x, const index_t incx
) noexcept { return isamax_(&n, x, &incx) - 1; }
static inline index_t iamax(
    const index_t n, const double* x, const index_t incx
) noexcept { return idamax_(&n, x, &incx) - 1; }
static inline index_t iamax(
    const index_t n, const std::complex<float>* x, const index_t incx
) noexcept { return icamax_(&n, x, &incx) - 1; }
static inline index_t iamax(
    const index_t n, const std::complex<double>* x, const index_t incx
) noexcept { return izamax_(&n, x, &incx) - 1; }
//@}

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_RAW_BLAS_IAMAX_HPP_
