////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/la/raw/magma/setmatrix.hpp
/// @brief   The MAGMA SETMATRIX.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_LA_RAW_MAGMA_SETMATRIX_HPP_
#define MCNLA_CORE_GPU_LA_RAW_MAGMA_SETMATRIX_HPP_

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
/// @brief  Copies CPU matrix to GPU matrix.
///
//@{
static inline void setmatrix(
    const index_t m, const index_t n, const float* a, const index_t lda, float* b, const index_t ldb
) noexcept { magma_ssetmatrix(m, n, a, lda, b, ldb); }
static inline void setmatrix(
    const index_t m, const index_t n, const double* a, const index_t lda, double* b, const index_t ldb
) noexcept { magma_dsetmatrix(m, n, a, lda, b, ldb); }
// static inline void setmatrix(
//     const index_t m, const index_t n,
//     const std::complex<float>* a, const index_t lda, std::complex<float>* b, const index_t ldb
// ) noexcept { magma_csetmatrix(m, n, a, lda, b, ldb); }
// static inline void setmatrix(
//     const index_t m, const index_t n,
//     const std::complex<double>* a, const index_t lda, std::complex<double>* b, const index_t ldb
// ) noexcept { magma_zsetmatrix(m, n, a, lda, b, ldb); }
// @}

}  // namespace gpu

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_LA_RAW_MAGMA_SETMATRIX_HPP_
