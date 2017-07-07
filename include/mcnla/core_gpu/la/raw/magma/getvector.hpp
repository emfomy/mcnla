////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/la/raw/magma/getvector.hpp
/// @brief   The MAGMA GETVECTOR.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_LA_RAW_MAGMA_GETVECTOR_HPP_
#define MCNLA_CORE_GPU_LA_RAW_MAGMA_GETVECTOR_HPP_

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
/// @brief  Copies GPU vector to CPU vector.
///
//@{
static inline void getvector(
    const index_t n, const float* x, const index_t incx, float* y, const index_t incy
) noexcept { magma_sgetvector(n, x, incx, y, incy); }
static inline void getvector(
    const index_t n, const double* x, const index_t incx, double* y, const index_t incy
) noexcept { magma_dgetvector(n, x, incx, y, incy); }
// static inline void getvector(
//     const index_t n, const std::complex<float>* x, const index_t incx, std::complex<float>* y, const index_t incy
// ) noexcept { magma_cgetvector(n, x, incx, y, incy); }
// static inline void getvector(
//     const index_t n, const std::complex<double>* x, const index_t incx, std::complex<double>* y, const index_t incy
// ) noexcept { magma_zgetvector(n, x, incx, y, incy); }
//@}

}  // namespace gpu

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_LA_RAW_MAGMA_GETVECTOR_HPP_
