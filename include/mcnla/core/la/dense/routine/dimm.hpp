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

template <typename _Scalar>
inline void dimmImpl2(
    const DenseDiagonalMatrix<_Scalar> &a,
    const DenseMatrix<_Scalar, Trans::NORMAL> &b,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  mcnla_assert_eq(a.size(), c.nrow());
  mcnla_assert_eq(b.sizes(), c.sizes());

  index_t idiag[1] = {0};
  diamm('N', c.nrow(), c.ncol(), a.size(), alpha, "D NC",
        a.valPtr(), a.size(), idiag, 1, b.valPtr(), b.pitch(), beta, c.valPtr(), c.pitch());
}

#endif  // MCNLA_USE_MKL

template <typename _Scalar, Trans _transb>
inline void dimmImpl2(
    const DenseDiagonalMatrix<_Scalar> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  mcnla_assert_eq(a.size(), c.nrow());
  mcnla_assert_eq(b.sizes(), c.sizes());

  auto da = a.vectorize();
  for ( index_t i = 0; i < da.length(); ++i ) {
    la::axpby(b(i, ""), c(i, ""), da(i) * alpha, beta);
  }
}

template <typename _Scalar, Trans _transb>
inline void dimmImpl2(
    const DenseMatrix<_Scalar, _transb> &b,
    const DenseDiagonalMatrix<_Scalar> &a,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  mcnla_assert_eq(a.size(), c.ncol());
  mcnla_assert_eq(b.sizes(), c.sizes());

  auto da = a.vectorize();
  for ( index_t i = 0; i < da.length(); ++i ) {
    la::axpby(b("", i), c("", i), da(i) * alpha, beta);
  }
}

// ========================================================================================================================== //
// Impl1 Left
//

template <typename _Scalar, Trans _transb>
inline void dimmImpl1(
    const DenseDiagonalMatrix<_Scalar> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  dimmImpl2(a, b, c, alpha, beta);
}

template <typename _Scalar, Trans _transb>
inline void dimmImpl1(
    const DenseDiagonalMatrix<_Scalar> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, Trans::TRANS> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  dimmImpl2(b.t(), a.t(), c.t(), alpha, beta);
}

template <typename _Scalar, Trans _transb, Trans _transc>
inline void dimmImpl1(
    const DenseDiagonalMatrix<_Scalar> &a,
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
  static_assert(!isConj(_transc), "DIMM does not support conjugate matrices!");
}

// ========================================================================================================================== //
// Impl1 Right
//

template <typename _Scalar, Trans _transb>
inline void dimmImpl1(
    const DenseMatrix<_Scalar, _transb> &b,
    const DenseDiagonalMatrix<_Scalar> &a,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  dimmImpl2(b, a, c, alpha, beta);
}

template <typename _Scalar, Trans _transb>
inline void dimmImpl1(
    const DenseMatrix<_Scalar, _transb> &b,
    const DenseDiagonalMatrix<_Scalar> &a,
          DenseMatrix<_Scalar, Trans::TRANS> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  dimmImpl2(a.t(), b.t(), c.t(), alpha, beta);
}

template <typename _Scalar, Trans _transb, Trans _transc>
inline void dimmImpl1(
    const DenseMatrix<_Scalar, _transb> &b,
    const DenseDiagonalMatrix<_Scalar> &a,
          DenseMatrix<_Scalar, _transc> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  static_cast<void>(a);
  static_cast<void>(b);
  static_cast<void>(c);
  static_cast<void>(alpha);
  static_cast<void>(beta);
  static_assert(!isConj(_transc), "DIMM does not support conjugate matrices!");
}

//@}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas3_module
/// @brief  Computes a matrix-matrix product where one input matrix is diagonal.
///
//@{
template <typename _Scalar, Trans _transb, Trans _transc>
inline void dimm(
    const DenseDiagonalMatrix<_Scalar> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, _transc> &c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  detail::dimmImpl1(a, b, c, alpha, beta);
}

template <typename _Scalar, Trans _transb, Trans _transc>
inline void dimm(
    const DenseMatrix<_Scalar, _transb> &b,
    const DenseDiagonalMatrix<_Scalar> &a,
          DenseMatrix<_Scalar, _transc> &c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  detail::dimmImpl1(b, a, c, alpha, beta);
}

template <typename _Scalar, Trans _transc>
inline void dimm(
    const DenseDiagonalMatrix<_Scalar> &a,
    const char*,
          DenseMatrix<_Scalar, _transc> &c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  detail::dimmImpl1(a, c, c, alpha, beta);
}

template <typename _Scalar, Trans _transc>
inline void dimm(
    const char*,
    const DenseDiagonalMatrix<_Scalar> &a,
          DenseMatrix<_Scalar, _transc> &c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  detail::dimmImpl1(c, a, c, alpha, beta);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Trans _transb, Trans _transc>
inline void dimm(
    const DenseDiagonalMatrix<_Scalar> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, _transc> &&c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  detail::dimmImpl1(a, b, c, alpha, beta);
}

template <typename _Scalar, Trans _transb, Trans _transc>
inline void dimm(
    const DenseMatrix<_Scalar, _transb> &b,
    const DenseDiagonalMatrix<_Scalar> &a,
          DenseMatrix<_Scalar, _transc> &&c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  detail::dimmImpl1(b, a, c, alpha, beta);
}

template <typename _Scalar, Trans _transc>
inline void dimm(
    const DenseDiagonalMatrix<_Scalar> &a,
    const char*,
          DenseMatrix<_Scalar, _transc> &&c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  detail::dimmImpl1(a, c, c, alpha, beta);
}

template <typename _Scalar, Trans _transc>
inline void dimm(
    const char*,
    const DenseDiagonalMatrix<_Scalar> &a,
          DenseMatrix<_Scalar, _transc> &&c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  detail::dimmImpl1(c, a, c, alpha, beta);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_wrapper_module
/// @brief  Computes a matrix-matrix product.
///
//@{
template <typename _Scalar, Trans _transb, Trans _transc>
inline void mm(
    const DenseDiagonalMatrix<_Scalar> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, _transc> &c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  dimm(a, b, c, alpha, beta);
}

template <typename _Scalar, Trans _transb, Trans _transc>
inline void mm(
    const DenseMatrix<_Scalar, _transb> &b,
    const DenseDiagonalMatrix<_Scalar> &a,
          DenseMatrix<_Scalar, _transc> &c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  dimm(b, a, c, alpha, beta);
}

template <typename _Scalar, Trans _transc>
inline void mm(
    const DenseDiagonalMatrix<_Scalar> &a,
    const char*,
          DenseMatrix<_Scalar, _transc> &c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  dimm(a, c, c, alpha, beta);
}

template <typename _Scalar, Trans _transc>
inline void mm(
    const char*,
    const DenseDiagonalMatrix<_Scalar> &a,
          DenseMatrix<_Scalar, _transc> &c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  dimm(c, a, c, alpha, beta);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Trans _transb, Trans _transc>
inline void mm(
    const DenseDiagonalMatrix<_Scalar> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, _transc> &&c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  dimm(a, b, c, alpha, beta);
}

template <typename _Scalar, Trans _transb, Trans _transc>
inline void mm(
    const DenseMatrix<_Scalar, _transb> &b,
    const DenseDiagonalMatrix<_Scalar> &a,
          DenseMatrix<_Scalar, _transc> &&c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  dimm(b, a, c, alpha, beta);
}

template <typename _Scalar, Trans _transc>
inline void mm(
    const DenseDiagonalMatrix<_Scalar> &a,
    const char*,
          DenseMatrix<_Scalar, _transc> &&c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  dimm(a, c, c, alpha, beta);
}

template <typename _Scalar, Trans _transc>
inline void mm(
    const char*,
    const DenseDiagonalMatrix<_Scalar> &a,
          DenseMatrix<_Scalar, _transc> &&c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  dimm(c, a, c, alpha, beta);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_DIMM_HPP_
