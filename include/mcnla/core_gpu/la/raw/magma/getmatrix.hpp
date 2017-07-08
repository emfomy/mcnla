////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/la/raw/magma/getmatrix.hpp
/// @brief   The MAGMA GETMATRIX.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_LA_RAW_MAGMA_GETMATRIX_HPP_
#define MCNLA_CORE_GPU_LA_RAW_MAGMA_GETMATRIX_HPP_

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
/// @brief  Copies GPU matrix to CPU matrix.
///
//@{
static inline void getmatrix(
    const index_t m, const index_t n, const float* a, const index_t lda, float* b, const index_t ldb
) noexcept { magma_sgetmatrix(m, n, a, lda, b, ldb); }
static inline void getmatrix(
    const index_t m, const index_t n, const double* a, const index_t lda, double* b, const index_t ldb
) noexcept { magma_dgetmatrix(m, n, a, lda, b, ldb); }
// static inline void getmatrix(
//     const index_t m, const index_t n,
//     const std::complex<float>* a, const index_t lda, std::complex<float>* b, const index_t ldb
// ) noexcept { magma_cgetmatrix(m, n, a, lda, b, ldb); }
// static inline void getmatrix(
//     const index_t m, const index_t n,
//     const std::complex<double>* a, const index_t lda, std::complex<double>* b, const index_t ldb
// ) noexcept { magma_zgetmatrix(m, n, a, lda, b, ldb); }
// @}

}  // namespace gpu

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_LA_RAW_MAGMA_GETMATRIX_HPP_
