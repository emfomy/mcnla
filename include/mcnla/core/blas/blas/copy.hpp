////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/blas/blas/copy.hpp
/// @brief   The BLAS COPY.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_BLAS_BLAS_COPY_HPP_
#define MCNLA_CORE_BLAS_BLAS_COPY_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <mcnla/core/blas/plugin/blas_plugin_begin.h>

// Copies vector to another vector.
extern void scopy_( const FORTRAN_INT n, const FORTRAN_REAL4 x, const FORTRAN_INT incx, FORTRAN_REAL4 y,
                    const FORTRAN_INT incy );
extern void dcopy_( const FORTRAN_INT n, const FORTRAN_REAL8 x, const FORTRAN_INT incx, FORTRAN_REAL8 y,
                    const FORTRAN_INT incy );
extern void ccopy_( const FORTRAN_INT n, const FORTRAN_COMP4 x, const FORTRAN_INT incx, FORTRAN_COMP4 y,
                    const FORTRAN_INT incy );
extern void zcopy_( const FORTRAN_INT n, const FORTRAN_COMP8 x, const FORTRAN_INT incx, FORTRAN_COMP8 y,
                    const FORTRAN_INT incy );

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
/// @brief  Copies vector to another vector.
///
//@{
static inline void copy(
    const index_t n, const float* x, const index_t incx, float* y, const index_t incy
) noexcept { scopy_(&n, x, &incx, y, &incy); }
static inline void copy(
    const index_t n, const double* x, const index_t incx, double* y, const index_t incy
) noexcept { dcopy_(&n, x, &incx, y, &incy); }
static inline void copy(
    const index_t n, const std::complex<float>* x, const index_t incx, std::complex<float>* y, const index_t incy
) noexcept { ccopy_(&n, x, &incx, y, &incy); }
static inline void copy(
    const index_t n, const std::complex<double>* x, const index_t incx, std::complex<double>* y, const index_t incy
) noexcept { zcopy_(&n, x, &incx, y, &incy); }
//@}

}  // namespace detail

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_BLAS_COPY_HPP_