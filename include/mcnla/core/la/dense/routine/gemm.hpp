////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/gemm.hpp
/// @brief   The BLAS GEMM routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_GEMM_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_GEMM_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/raw/blas/gemm.hpp>

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
    const DenseMatrix<_Val, _transa> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseMatrix<_Val, Trans::NORMAL> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  mcnla_assert_eq(c.nrow(), a.nrow());
  mcnla_assert_eq(c.ncol(), b.ncol());
  mcnla_assert_eq(a.ncol(), b.nrow());

  gemm(toTransChar<_Val>(_transa), toTransChar<_Val>(_transb), c.nrow(), c.ncol(), a.ncol(),
       alpha, a.valPtr(), a.pitch(), b.valPtr(), b.pitch(), beta, c.valPtr(), c.pitch());
}

// ========================================================================================================================== //
// Impl1
//

template <typename _Val, Trans _transa, Trans _transb>
inline void gemmImpl1(
    const DenseMatrix<_Val, _transa> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseMatrix<_Val, Trans::NORMAL> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  gemmImpl2(a, b, c, alpha, beta);
}

template <typename _Val, Trans _transa, Trans _transb>
inline void gemmImpl1(
    const DenseMatrix<_Val, _transa> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseMatrix<_Val, Trans::TRANS> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  gemmImpl2(b.t(), a.t(), c.t(), alpha, beta);
}

template <typename _Val, Trans _transa, Trans _transb, Trans _transc, bool dummy = 0>
inline void gemmImpl1(
    const DenseMatrix<_Val, _transa> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseMatrix<_Val, _transc> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  static_cast<void>(a);
  static_cast<void>(b);
  static_cast<void>(c);
  static_cast<void>(alpha);
  static_cast<void>(beta);
  static_assert(dummy && false, "GEMM does not support conjugate matrices!");
}

//@}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas3_module
/// @brief  Computes a matrix-matrix product with general matrices.
///
template <typename _Val, Trans _transa, Trans _transb, Trans _transc>
inline void gemm(
    const DenseMatrix<_Val, _transa> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseMatrix<_Val, _transc> &c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1,
    const ValT<DenseMatrix<_Val, _transc>> beta  = 0
) noexcept {
  detail::gemmImpl1(a, b, c, alpha, beta);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _transa, Trans _transb, Trans _transc>
inline void gemm(
    const DenseMatrix<_Val, _transa> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseMatrix<_Val, _transc> &&c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1,
    const ValT<DenseMatrix<_Val, _transc>> beta  = 0
) noexcept {
  detail::gemmImpl1(a, b, c, alpha, beta);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::la::mm
///
template <typename _Val, Trans _transa, Trans _transb, Trans _transc>
inline void mm(
    const DenseMatrix<_Val, _transa> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseMatrix<_Val, _transc> &c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1,
    const ValT<DenseMatrix<_Val, _transc>> beta  = 0
) noexcept {
  gemm(a, b, c, alpha, beta);
}
#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _transa, Trans _transb, Trans _transc>
inline void mm(
    const DenseMatrix<_Val, _transa> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseMatrix<_Val, _transc> &&c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1,
    const ValT<DenseMatrix<_Val, _transc>> beta  = 0
) noexcept {
  gemm(a, b, c, alpha, beta);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_GEMM_HPP_
