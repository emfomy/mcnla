////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/la/raw/blas/copy.hpp
/// @brief   The MAGMA BLAS COPY.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_LA_RAW_BLAS_COPY_HPP_
#define MCNLA_CORE_GPU_LA_RAW_BLAS_COPY_HPP_

#include <mcnla/core_gpu/la/def.hpp>
#include <magma.h>

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The GPU namespace
//
namespace gpu {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copies vector to another vector.
///
//@{
static inline void copy(
    const index_t n, const float* x, const index_t incx, float* y, const index_t incy
) noexcept { magma_scopy(n, x, incx, y, incy); }
static inline void copy(
    const index_t n, const double* x, const index_t incx, double* y, const index_t incy
) noexcept { magma_dcopy(n, x, incx, y, incy); }
// static inline void copy(
//     const index_t n, const std::complex<float>* x, const index_t incx, std::complex<float>* y, const index_t incy
// ) noexcept { magma_ccopy(n, x, incx, y, incy); }
// static inline void copy(
//     const index_t n, const std::complex<double>* x, const index_t incx, std::complex<double>* y, const index_t incy
// ) noexcept { magma_zcopy(n, x, incx, y, incy); }
//@}

}  // namespace gpu

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_LA_RAW_BLAS_COPY_HPP_
