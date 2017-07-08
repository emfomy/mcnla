////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/la/raw/blas/gemm.hpp
/// @brief   The MAGMA BLAS GEMM.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_LA_RAW_BLAS_GEMM_HPP_
#define MCNLA_CORE_GPU_LA_RAW_BLAS_GEMM_HPP_

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
/// @brief  Computes a matrix-matrix product with general matrices.
///
//@{
static inline void gemm(
    const char transa, const char transb, const index_t m, const index_t n, const index_t k,
    const float alpha, const float *a, const index_t lda, const float *b, const index_t ldb,
    const float beta, float *c, const index_t ldc
) noexcept { magmablas_sgemm(magma_trans_const(transa), magma_trans_const(transb),
                         m, n, k, alpha, a, lda, b, ldb, beta, c, ldc); }
static inline void gemm(
    const char transa, const char transb, const index_t m, const index_t n, const index_t k,
    const double alpha, const double *a, const index_t lda, const double *b, const index_t ldb,
    const double beta, double *c, const index_t ldc
) noexcept { magmablas_dgemm(magma_trans_const(transa), magma_trans_const(transb),
                         m, n, k, alpha, a, lda, b, ldb, beta, c, ldc); }
// static inline void gemm(
//     const char transa, const char transb, const index_t m, const index_t n, const index_t k,
//     const std::complex<float> alpha, const std::complex<float> *a, const index_t lda,
//     const std::complex<float> *b, const index_t ldb,
//     const std::complex<float> beta, std::complex<float> *c, const index_t ldc
// ) noexcept { magmablas_cgemm(magma_trans_const(transa), magma_trans_const(transb),
//                          m, n, k, alpha, a, lda, b, ldb, beta, c, ldc); }
// static inline void gemm(
//     const char transa, const char transb, const index_t m, const index_t n, const index_t k,
//     const std::complex<double> alpha, const std::complex<double> *a, const index_t lda,
//     const std::complex<double> *b, const index_t ldb,
//     const std::complex<double> beta, std::complex<double> *c, const index_t ldc
// ) noexcept { magmablas_zgemm(magma_trans_const(transa), magma_trans_const(transb),
//                          m, n, k, alpha, a, lda, b, ldb, beta, c, ldc); }
//@}

}  // namespace gpu

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_LA_RAW_BLAS_GEMM_HPP_
