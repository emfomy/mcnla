////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/dimm.hpp
/// @brief   The BLAS DIMM routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_DIMM_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_DIMM_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>

#ifdef MCNLA_USE_MKL
  #include <mcnla/core/la/raw/spblas/diamm.hpp>
#endif  // MCNLA_USE_MKL
#include <mcnla/core/la/dense/routine/axpby.hpp>

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

#ifdef MCNLA_USE_MKL
template <typename _Val>
inline void dimmImpl2(
    const DenseDiagonalMatrix<_Val> &a,
    const DenseMatrix<_Val, Trans::NORMAL> &b,
          DenseMatrix<_Val, Trans::NORMAL> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  mcnla_assert_eq(a.size(), c.nrow());
  mcnla_assert_eq(b.sizes(), c.sizes());

  index_t idiag[1] = {0};
  diamm('N', c.nrow(), c.ncol(), a.size(), alpha, "D NC",
        a.valPtr(), a.size(), idiag, 1, b.valPtr(), b.pitch(), beta, c.valPtr(), c.pitch());
}
#endif  // MCNLA_USE_MKL

template <typename _Val, Trans _transb>
inline void dimmImpl2(
    const DenseDiagonalMatrix<_Val> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseMatrix<_Val, Trans::NORMAL> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  mcnla_assert_eq(a.size(), c.nrow());
  mcnla_assert_eq(b.sizes(), c.sizes());

  auto da = a.viewVector();
  for ( index_t i = 0; i < da.len(); ++i ) {
    la::axpby(b(i, ""_), c(i, ""_), da(i) * alpha, beta);
  }
}

template <typename _Val, Trans _transb>
inline void dimmImpl2(
    const DenseMatrix<_Val, _transb> &b,
    const DenseDiagonalMatrix<_Val> &a,
          DenseMatrix<_Val, Trans::NORMAL> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  mcnla_assert_eq(a.size(), c.ncol());
  mcnla_assert_eq(b.sizes(), c.sizes());

  auto da = a.viewVector();
  for ( index_t i = 0; i < da.len(); ++i ) {
    la::axpby(b(""_, i), c(""_, i), da(i) * alpha, beta);
  }
}

// ========================================================================================================================== //
// Impl1 Left
//

template <typename _Val, Trans _transb>
inline void dimmImpl1(
    const DenseDiagonalMatrix<_Val> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseMatrix<_Val, Trans::NORMAL> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  dimmImpl2(a, b, c, alpha, beta);
}

template <typename _Val, Trans _transb>
inline void dimmImpl1(
    const DenseDiagonalMatrix<_Val> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseMatrix<_Val, Trans::TRANS> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  dimmImpl2(b.t(), a.t(), c.t(), alpha, beta);
}

template <typename _Val, Trans _transb, Trans _transc, bool dummy = 0>
inline void dimmImpl1(
    const DenseDiagonalMatrix<_Val> &a,
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
  static_assert(dummy && false, "DIMM does not support conjugate matrices!");
}

// ========================================================================================================================== //
// Impl1 Right
//

template <typename _Val, Trans _transb>
inline void dimmImpl1(
    const DenseMatrix<_Val, _transb> &b,
    const DenseDiagonalMatrix<_Val> &a,
          DenseMatrix<_Val, Trans::NORMAL> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  dimmImpl2(b, a, c, alpha, beta);
}

template <typename _Val, Trans _transb>
inline void dimmImpl1(
    const DenseMatrix<_Val, _transb> &b,
    const DenseDiagonalMatrix<_Val> &a,
          DenseMatrix<_Val, Trans::TRANS> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  dimmImpl2(a.t(), b.t(), c.t(), alpha, beta);
}

template <typename _Val, Trans _transb, Trans _transc, bool dummy = 0>
inline void dimmImpl1(
    const DenseMatrix<_Val, _transb> &b,
    const DenseDiagonalMatrix<_Val> &a,
          DenseMatrix<_Val, _transc> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  static_cast<void>(a);
  static_cast<void>(b);
  static_cast<void>(c);
  static_cast<void>(alpha);
  static_cast<void>(beta);
  static_assert(dummy && false, "DIMM does not support conjugate matrices!");
}

// ========================================================================================================================== //
// Impl0
//

template <typename _Val, Trans _transc>
inline void dimmImpl0(
    const DenseDiagonalMatrix<_Val> &a,
          DenseMatrix<_Val, _transc> &c,
    const _Val alpha
) noexcept {
  mcnla_assert_eq(a.size(), c.nrow());

  auto da = a.viewVector();
  for ( index_t i = 0; i < da.len(); ++i ) {
    la::scal(c(i, ""_), da(i) * alpha);
  }
}

template <typename _Val, Trans _transc>
inline void dimmImpl0(
          DenseMatrix<_Val, _transc> &c,
    const DenseDiagonalMatrix<_Val> &a,
    const _Val alpha
) noexcept {
  mcnla_assert_eq(a.size(), c.ncol());

  auto da = a.viewVector();
  for ( index_t i = 0; i < da.len(); ++i ) {
    la::scal(c(""_, i), da(i) * alpha);
  }
}

//@}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas3_module
/// @brief  Computes a matrix-matrix product where one input matrix is diagonal.
///
//@{
template <typename _Val, Trans _transb, Trans _transc>
inline void dimm(
    const DenseDiagonalMatrix<_Val> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseMatrix<_Val, _transc> &c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1,
    const ValT<DenseMatrix<_Val, _transc>> beta  = 0
) noexcept {
  detail::dimmImpl1(a, b, c, alpha, beta);
}

template <typename _Val, Trans _transb, Trans _transc>
inline void dimm(
    const DenseMatrix<_Val, _transb> &b,
    const DenseDiagonalMatrix<_Val> &a,
          DenseMatrix<_Val, _transc> &c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1,
    const ValT<DenseMatrix<_Val, _transc>> beta  = 0
) noexcept {
  detail::dimmImpl1(b, a, c, alpha, beta);
}

template <typename _Val, Trans _transc>
inline void dimm(
    const DenseDiagonalMatrix<_Val> &a,
    const FullRange,
          DenseMatrix<_Val, _transc> &c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1
) noexcept {
  detail::dimmImpl0(a, c, alpha);
}

template <typename _Val, Trans _transc>
inline void dimm(
    const FullRange,
    const DenseDiagonalMatrix<_Val> &a,
          DenseMatrix<_Val, _transc> &c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1
) noexcept {
  detail::dimmImpl0(c, a, alpha);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _transb, Trans _transc>
inline void dimm(
    const DenseDiagonalMatrix<_Val> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseMatrix<_Val, _transc> &&c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1,
    const ValT<DenseMatrix<_Val, _transc>> beta  = 0
) noexcept {
  detail::dimmImpl1(a, b, c, alpha, beta);
}

template <typename _Val, Trans _transb, Trans _transc>
inline void dimm(
    const DenseMatrix<_Val, _transb> &b,
    const DenseDiagonalMatrix<_Val> &a,
          DenseMatrix<_Val, _transc> &&c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1,
    const ValT<DenseMatrix<_Val, _transc>> beta  = 0
) noexcept {
  detail::dimmImpl1(b, a, c, alpha, beta);
}

template <typename _Val, Trans _transc>
inline void dimm(
    const DenseDiagonalMatrix<_Val> &a,
    const FullRange,
          DenseMatrix<_Val, _transc> &&c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1
) noexcept {
  detail::dimmImpl0(a, c, alpha);
}

template <typename _Val, Trans _transc>
inline void dimm(
    const FullRange,
    const DenseDiagonalMatrix<_Val> &a,
          DenseMatrix<_Val, _transc> &&c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1
) noexcept {
  detail::dimmImpl0(c, a, alpha);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::la::mm
///
//@{
template <typename _Val, Trans _transb, Trans _transc>
inline void mm(
    const DenseDiagonalMatrix<_Val> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseMatrix<_Val, _transc> &c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1,
    const ValT<DenseMatrix<_Val, _transc>> beta  = 0
) noexcept {
  dimm(a, b, c, alpha, beta);
}

template <typename _Val, Trans _transb, Trans _transc>
inline void mm(
    const DenseMatrix<_Val, _transb> &b,
    const DenseDiagonalMatrix<_Val> &a,
          DenseMatrix<_Val, _transc> &c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1,
    const ValT<DenseMatrix<_Val, _transc>> beta  = 0
) noexcept {
  dimm(b, a, c, alpha, beta);
}

template <typename _Val, Trans _transc>
inline void mm(
    const DenseDiagonalMatrix<_Val> &a,
    const FullRange,
          DenseMatrix<_Val, _transc> &c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1
) noexcept {
  dimm(a, ""_, c, alpha);
}

template <typename _Val, Trans _transc>
inline void mm(
    const FullRange,
    const DenseDiagonalMatrix<_Val> &a,
          DenseMatrix<_Val, _transc> &c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1
) noexcept {
  dimm(""_, a, c, alpha);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _transb, Trans _transc>
inline void mm(
    const DenseDiagonalMatrix<_Val> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseMatrix<_Val, _transc> &&c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1,
    const ValT<DenseMatrix<_Val, _transc>> beta  = 0
) noexcept {
  dimm(a, b, c, alpha, beta);
}

template <typename _Val, Trans _transb, Trans _transc>
inline void mm(
    const DenseMatrix<_Val, _transb> &b,
    const DenseDiagonalMatrix<_Val> &a,
          DenseMatrix<_Val, _transc> &&c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1,
    const ValT<DenseMatrix<_Val, _transc>> beta  = 0
) noexcept {
  dimm(b, a, c, alpha, beta);
}

template <typename _Val, Trans _transc>
inline void mm(
    const DenseDiagonalMatrix<_Val> &a,
    const FullRange,
          DenseMatrix<_Val, _transc> &&c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1
) noexcept {
  dimm(a, ""_, c, alpha);
}

template <typename _Val, Trans _transc>
inline void mm(
    const FullRange,
    const DenseDiagonalMatrix<_Val> &a,
          DenseMatrix<_Val, _transc> &&c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1
) noexcept {
  dimm(""_, a, c, alpha);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_DIMM_HPP_
