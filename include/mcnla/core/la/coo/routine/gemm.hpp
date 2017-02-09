////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/coo/routine/gemm.hpp
/// @brief   The BLAS GEMM routine for COO format.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_COO_ROUTINE_GEMM_HPP_
#define MCNLA_CORE_LA_COO_ROUTINE_GEMM_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>

#ifdef MCNLA_USE_MKL
  #include <mcnla/core/la/raw/spblas/coomm.hpp>
#endif  // MCNLA_USE_MKL
#include <mcnla/core/la/dense/routine/axpy.hpp>
#include <mcnla/core/la/dense/routine/scal.hpp>

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
// Impl3
//

#ifdef MCNLA_USE_MKL
template <typename _Scalar, Trans _transa>
inline void gemmImpl3(
    const DenseMatrix<_Scalar, Trans::NORMAL> &b,
    const CooMatrix<_Scalar, _transa> &a,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  mcnla_assert_eq(c.nrow(), b.nrow());
  mcnla_assert_eq(c.ncol(), a.ncol());
  mcnla_assert_eq(a.nrow(), b.ncol());

  coomm(toTransChar<_Scalar>(_transa), c.ncol(), c.nrow(), a.ncol(), alpha, "G  C",
        a.valPtr(), a.rowidxPtr(), a.colidxPtr(), a.nnz(), b.valPtr(), b.pitch(), beta, c.valPtr(), c.pitch());
}
#else  // MCNLA_USE_MKL
template <typename _Scalar, Trans _transa>
inline void gemmImpl3(
    const DenseMatrix<_Scalar, Trans::NORMAL> &b,
    const CooMatrix<_Scalar, _transa> &a,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  mcnla_assert_eq(c.nrow(), b.nrow());
  mcnla_assert_eq(c.ncol(), a.ncol());
  mcnla_assert_eq(a.nrow(), b.ncol());

  if ( c.isShrunk() ) {
    la::scal(c.vectorize(), beta);
  } else {
    for ( index_t i = 0; i < c.nrow(); ++i ) {
      la::scal(c("", i), beta);
    }
  }

  for ( index_t i = 0; i < a.nnz(); ++i ) {
    la::axpy(b("", a.rowidxPtr()[i]), c("", a.colidxPtr()[i]), a.valPtr()[i] * alpha);
  }
}
#endif  // MCNLA_USE_MKL

template <typename _Scalar, Trans _transa, Trans _transb, bool dummy = 0>
inline void gemmImpl3(
    const CooMatrix<_Scalar, _transa> &a,
    const DenseMatrix<_Scalar, Trans::NORMAL> &b,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  static_cast<void>(a);
  static_cast<void>(b);
  static_cast<void>(c);
  static_cast<void>(alpha);
  static_cast<void>(beta);
  static_assert(dummy && false, "COO GEMM does not support this layout!");
}

// ========================================================================================================================== //
// Impl2 Left
//

template <typename _Scalar, Trans _transa>
inline void gemmImpl2(
    const CooMatrix<_Scalar, _transa> &a,
    const DenseMatrix<_Scalar, Trans::NORMAL> &b,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  gemmImpl3(a, b, c, alpha, beta);
}

template <typename _Scalar, Trans _transa, Trans _transb>
inline void gemmImpl2(
    const CooMatrix<_Scalar, _transa> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  static_cast<void>(a);
  static_cast<void>(b);
  static_cast<void>(c);
  static_cast<void>(alpha);
  static_cast<void>(beta);
  static_assert(_transb == Trans::NORMAL, "The layout of B and C in COO GEMM must be the same!");
}

// ========================================================================================================================== //
// Impl2 Right
//

template <typename _Scalar, Trans _transa>
inline void gemmImpl2(
    const DenseMatrix<_Scalar, Trans::NORMAL> &b,
    const CooMatrix<_Scalar, _transa> &a,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  gemmImpl3(b, a, c, alpha, beta);
}

template <typename _Scalar, Trans _transa, Trans _transb>
inline void gemmImpl2(
    const DenseMatrix<_Scalar, _transb> &b,
    const CooMatrix<_Scalar, _transa> &a,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  static_cast<void>(a);
  static_cast<void>(b);
  static_cast<void>(c);
  static_cast<void>(alpha);
  static_cast<void>(beta);
  static_assert(_transb == Trans::NORMAL, "The layout of B and C in COO GEMM must be the same!");
}

// ========================================================================================================================== //
// Impl1 Left
//

template <typename _Scalar, Trans _transa, Trans _transb>
inline void gemmImpl1(
    const CooMatrix<_Scalar, _transa> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  gemmImpl2(a, b, c, alpha, beta);
}

template <typename _Scalar, Trans _transa, Trans _transb>
inline void gemmImpl1(
    const CooMatrix<_Scalar, _transa> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, Trans::TRANS> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  gemmImpl2(b.t(), a.t(), c.t(), alpha, beta);
}

template <typename _Scalar, Trans _transa, Trans _transb, Trans _transc>
inline void gemmImpl1(
    const CooMatrix<_Scalar, _transa> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, _transc> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  static_cast<void>(a);
  static_cast<void>(b);
  static_cast<void>(c);
  static_cast<void>(alpha);
  static_cast<void>(beta);
  static_assert(!isConj(_transc), "COO GEMM does not support conjugate matrices!");
}

// ========================================================================================================================== //
// Impl1 Right
//

template <typename _Scalar, Trans _transa, Trans _transb>
inline void gemmImpl1(
    const DenseMatrix<_Scalar, _transb> &b,
    const CooMatrix<_Scalar, _transa> &a,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  gemmImpl2(b, a, c, alpha, beta);
}

template <typename _Scalar, Trans _transa, Trans _transb>
inline void gemmImpl1(
    const DenseMatrix<_Scalar, _transb> &b,
    const CooMatrix<_Scalar, _transa> &a,
          DenseMatrix<_Scalar, Trans::TRANS> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  gemmImpl2(a.t(), b.t(), c.t(), alpha, beta);
}

template <typename _Scalar, Trans _transa, Trans _transb, Trans _transc>
inline void gemmImpl1(
    const DenseMatrix<_Scalar, _transb> &b,
    const CooMatrix<_Scalar, _transa> &a,
          DenseMatrix<_Scalar, _transc> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  static_cast<void>(a);
  static_cast<void>(b);
  static_cast<void>(c);
  static_cast<void>(alpha);
  static_cast<void>(beta);
  static_assert(!isConj(_transc), "COO GEMM does not support conjugate matrices!");
}

//@}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_coo_blas3_module
/// @brief  Computes a matrix-matrix product with general matrices.
///
//@{
template <typename _Scalar, Trans _transa, Trans _transb, Trans _transc>
inline void gemm(
    const CooMatrix<_Scalar, _transa> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, _transc> &c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  detail::gemmImpl1(a, b, c, alpha, beta);
}

template <typename _Scalar, Trans _transa, Trans _transb, Trans _transc>
inline void gemm(
    const DenseMatrix<_Scalar, _transb> &b,
    const CooMatrix<_Scalar, _transa> &a,
          DenseMatrix<_Scalar, _transc> &c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  detail::gemmImpl1(b, a, c, alpha, beta);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Trans _transa, Trans _transb, Trans _transc>
inline void gemm(
    const CooMatrix<_Scalar, _transa> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, _transc> &&c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  detail::gemmImpl1(a, b, c, alpha, beta);
}

template <typename _Scalar, Trans _transa, Trans _transb, Trans _transc>
inline void gemm(
    const DenseMatrix<_Scalar, _transb> &b,
    const CooMatrix<_Scalar, _transa> &a,
          DenseMatrix<_Scalar, _transc> &&c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  detail::gemmImpl1(b, a, c, alpha, beta);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Trans _transa, Trans _transb, Trans _transc>
inline void mm(
    const CooMatrix<_Scalar, _transa> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, _transc> &c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  gemm(a, b, c, alpha, beta);
}

template <typename _Scalar, Trans _transa, Trans _transb, Trans _transc>
inline void mm(
    const DenseMatrix<_Scalar, _transb> &b,
    const CooMatrix<_Scalar, _transa> &a,
          DenseMatrix<_Scalar, _transc> &c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  gemm(b, a, c, alpha, beta);
}

template <typename _Scalar, Trans _transa, Trans _transb, Trans _transc>
inline void mm(
    const CooMatrix<_Scalar, _transa> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, _transc> &&c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  gemm(a, b, c, alpha, beta);
}

template <typename _Scalar, Trans _transa, Trans _transb, Trans _transc>
inline void mm(
    const DenseMatrix<_Scalar, _transb> &b,
    const CooMatrix<_Scalar, _transa> &a,
          DenseMatrix<_Scalar, _transc> &&c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  gemm(b, a, c, alpha, beta);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_COO_ROUTINE_GEMM_HPP_
