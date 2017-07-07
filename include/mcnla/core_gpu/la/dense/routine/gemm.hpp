////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/la/dense/routine/gemm.hpp
/// @brief   The GPU BLAS GEMM routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_LA_DENSE_ROUTINE_GEMM_HPP_
#define MCNLA_CORE_GPU_LA_DENSE_ROUTINE_GEMM_HPP_

#include <mcnla/core_gpu/la/def.hpp>
#include <mcnla/core_gpu/matrix.hpp>
#include <mcnla/core_gpu/la/raw/blas/gemm.hpp>

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

// ========================================================================================================================== //
// Impl2
//
template <typename _Val, Trans _transa, Trans _transb>
inline void gemmImpl2(
    const DenseMatrixGpu<_Val, _transa> &a,
    const DenseMatrixGpu<_Val, _transb> &b,
          DenseMatrixGpu<_Val, Trans::NORMAL> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  mcnla_assert_eq(c.nrow(), a.nrow());
  mcnla_assert_eq(c.ncol(), b.ncol());
  mcnla_assert_eq(a.ncol(), b.nrow());

  gpu::gemm(toTransChar<_Val>(_transa), toTransChar<_Val>(_transb), c.nrow(), c.ncol(), a.ncol(),
       alpha, a.valPtr(), a.pitch(), b.valPtr(), b.pitch(), beta, c.valPtr(), c.pitch());
}

// ========================================================================================================================== //
// Impl1
//

template <typename _Val, Trans _transa, Trans _transb>
inline void gemmImpl1(
    const DenseMatrixGpu<_Val, _transa> &a,
    const DenseMatrixGpu<_Val, _transb> &b,
          DenseMatrixGpu<_Val, Trans::NORMAL> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  gemmImpl2(a, b, c, alpha, beta);
}

template <typename _Val, Trans _transa, Trans _transb>
inline void gemmImpl1(
    const DenseMatrixGpu<_Val, _transa> &a,
    const DenseMatrixGpu<_Val, _transb> &b,
          DenseMatrixGpu<_Val, Trans::TRANS> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  gemmImpl2(b.t(), a.t(), c.t(), alpha, beta);
}

template <typename _Val, Trans _transa, Trans _transb, Trans _transc, bool dummy = 0>
inline void gemmImpl1(
    const DenseMatrixGpu<_Val, _transa> &a,
    const DenseMatrixGpu<_Val, _transb> &b,
          DenseMatrixGpu<_Val, _transc> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  static_cast<void>(a);
  static_cast<void>(b);
  static_cast<void>(c);
  static_cast<void>(alpha);
  static_cast<void>(beta);
  static_assert(dummy && false, "GPU GEMM does not support conjugate matrices!");
}

//@}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas3_module
/// @brief  Computes a matrix-matrix product with general matrices.
///
template <typename _Val, Trans _transa, Trans _transb, Trans _transc>
inline void gemm(
    const DenseMatrixGpu<_Val, _transa> &a,
    const DenseMatrixGpu<_Val, _transb> &b,
          DenseMatrixGpu<_Val, _transc> &c,
    const ValT<DenseMatrixGpu<_Val, _transc>> alpha = 1,
    const ValT<DenseMatrixGpu<_Val, _transc>> beta  = 0
) noexcept {
  detail::gemmImpl1(a, b, c, alpha, beta);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _transa, Trans _transb, Trans _transc>
inline void gemm(
    const DenseMatrixGpu<_Val, _transa> &a,
    const DenseMatrixGpu<_Val, _transb> &b,
          DenseMatrixGpu<_Val, _transc> &&c,
    const ValT<DenseMatrixGpu<_Val, _transc>> alpha = 1,
    const ValT<DenseMatrixGpu<_Val, _transc>> beta  = 0
) noexcept {
  detail::gemmImpl1(a, b, c, alpha, beta);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::la::mm
///
template <typename _Val, Trans _transa, Trans _transb, Trans _transc>
inline void mm(
    const DenseMatrixGpu<_Val, _transa> &a,
    const DenseMatrixGpu<_Val, _transb> &b,
          DenseMatrixGpu<_Val, _transc> &c,
    const ValT<DenseMatrixGpu<_Val, _transc>> alpha = 1,
    const ValT<DenseMatrixGpu<_Val, _transc>> beta  = 0
) noexcept {
  gemm(a, b, c, alpha, beta);
}
#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _transa, Trans _transb, Trans _transc>
inline void mm(
    const DenseMatrixGpu<_Val, _transa> &a,
    const DenseMatrixGpu<_Val, _transb> &b,
          DenseMatrixGpu<_Val, _transc> &&c,
    const ValT<DenseMatrixGpu<_Val, _transc>> alpha = 1,
    const ValT<DenseMatrixGpu<_Val, _transc>> beta  = 0
) noexcept {
  gemm(a, b, c, alpha, beta);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_LA_DENSE_ROUTINE_GEMM_HPP_
