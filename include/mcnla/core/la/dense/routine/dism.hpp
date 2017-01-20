////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/dism.hpp
/// @brief   The BLAS DISM routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_DISM_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_DISM_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>

#ifdef MCNLA_USE_MKL
  #include <mcnla/core/la/raw/spblas/diasm.hpp>
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
// Impl3
//

#ifdef MCNLA_USE_MKL

template <typename _Scalar>
inline void dismImpl2(
    const DenseDiagonalMatrix<_Scalar> &a,
    const DenseMatrix<_Scalar, Trans::NORMAL> &b,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha
) noexcept {
  mcnla_assert_eq(a.size(), c.nrow());
  mcnla_assert_eq(b.sizes(), c.sizes());

  index_t idiag[1] = {0};
  diasm('N', c.nrow(), c.ncol(), alpha, "TLNC",
        a.valuePtr(), a.size(), idiag, 1, b.valuePtr(), b.pitch(), c.valuePtr(), c.pitch());
}

#endif  // MCNLA_USE_MKL

template <typename _Scalar, Trans _transb>
inline void dismImpl2(
    const DenseDiagonalMatrix<_Scalar> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha
) noexcept {
  mcnla_assert_eq(a.size(), c.nrow());
  mcnla_assert_eq(b.sizes(), c.sizes());

  auto da = a.vectorize();
  for ( index_t i = 0; i < da.length(); ++i ) {
    la::axpby(b(i, ""), c(i, ""), alpha / da(i), 0.0);
  }
}

template <typename _Scalar, Trans _transb>
inline void dismImpl2(
    const DenseMatrix<_Scalar, _transb> &b,
    const DenseDiagonalMatrix<_Scalar> &a,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha
) noexcept {
  mcnla_assert_eq(a.size(), c.ncol());
  mcnla_assert_eq(b.sizes(), c.sizes());

  auto da = a.vectorize();
  for ( index_t i = 0; i < da.length(); ++i ) {
    la::axpby(b("", i), c("", i), alpha / da(i), 0.0);
  }
}

// ========================================================================================================================== //
// Impl1 Left
//

template <typename _Scalar, Trans _transb>
inline void dismImpl1(
    const DenseDiagonalMatrix<_Scalar> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha
) noexcept {
  dismImpl2(a, b, c, alpha);
}

template <typename _Scalar, Trans _transb>
inline void dismImpl1(
    const DenseDiagonalMatrix<_Scalar> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, Trans::TRANS> &c,
    const _Scalar alpha
) noexcept {
  dismImpl2(b.t(), a.t(), c.t(), alpha);
}

template <typename _Scalar, Trans _transb, Trans _transc>
inline void dismImpl1(
    const DenseDiagonalMatrix<_Scalar> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, _transc> &c,
    const _Scalar alpha
) noexcept {
  static_cast<void>(a);
  static_cast<void>(b);
  static_cast<void>(c);
  static_cast<void>(alpha);
  static_assert(!isConj(_transc), "Conjugate version of DISM is not supported!");
}

// ========================================================================================================================== //
// Impl1 Right
//

template <typename _Scalar, Trans _transb>
inline void dismImpl1(
    const DenseMatrix<_Scalar, _transb> &b,
    const DenseDiagonalMatrix<_Scalar> &a,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha
) noexcept {
  dismImpl2(b, a, c, alpha);
}

template <typename _Scalar, Trans _transb>
inline void dismImpl1(
    const DenseMatrix<_Scalar, _transb> &b,
    const DenseDiagonalMatrix<_Scalar> &a,
          DenseMatrix<_Scalar, Trans::TRANS> &c,
    const _Scalar alpha
) noexcept {
  dismImpl2(a.t(), b.t(), c.t(), alpha);
}

template <typename _Scalar, Trans _transb, Trans _transc>
inline void dismImpl1(
    const DenseMatrix<_Scalar, _transb> &b,
    const DenseDiagonalMatrix<_Scalar> &a,
          DenseMatrix<_Scalar, _transc> &c,
    const _Scalar alpha
) noexcept {
  static_cast<void>(a);
  static_cast<void>(b);
  static_cast<void>(c);
  static_cast<void>(alpha);
  static_assert(!isConj(_transc), "Conjugate version of DISM is not supported!");
}

//@}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas3_module
/// @brief  Solves a system of linear equations with a diagonal coefficient matrix and multiple right-hand sides.
///
//@{
template <typename _Scalar, Trans _transb, Trans _transc>
inline void dism(
    const InverseView<DenseDiagonalMatrix<_Scalar>> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, _transc> &c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1
) noexcept {
  detail::dismImpl1(a.inv(), b, c, alpha);
}

template <typename _Scalar, Trans _transb, Trans _transc>
inline void dism(
    const DenseMatrix<_Scalar, _transb> &b,
    const InverseView<DenseDiagonalMatrix<_Scalar>> &a,
          DenseMatrix<_Scalar, _transc> &c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1
) noexcept {
  detail::dismImpl1(b, a.inv(), c, alpha);
}

template <typename _Scalar, Trans _transc>
inline void dism(
    const InverseView<DenseDiagonalMatrix<_Scalar>> &a,
    const char*,
          DenseMatrix<_Scalar, _transc> &c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1
) noexcept {
  detail::dismImpl1(a.inv(), c, c, alpha);
}

template <typename _Scalar, Trans _transc>
inline void dism(
    const char*,
    const InverseView<DenseDiagonalMatrix<_Scalar>> &a,
          DenseMatrix<_Scalar, _transc> &c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1
) noexcept {
  detail::dismImpl1(c, a.inv(), c, alpha);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Trans _transb, Trans _transc>
inline void dism(
    const InverseView<DenseDiagonalMatrix<_Scalar>> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, _transc> &&c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1
) noexcept {
  detail::dismImpl1(a.inv(), b, c, alpha);
}

template <typename _Scalar, Trans _transb, Trans _transc>
inline void dism(
    const DenseMatrix<_Scalar, _transb> &b,
    const InverseView<DenseDiagonalMatrix<_Scalar>> &a,
          DenseMatrix<_Scalar, _transc> &&c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1
) noexcept {
  detail::dismImpl1(b, a.inv(), c, alpha);
}

template <typename _Scalar, Trans _transc>
inline void dism(
    const InverseView<DenseDiagonalMatrix<_Scalar>> &a,
    const char*,
          DenseMatrix<_Scalar, _transc> &&c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1
) noexcept {
  detail::dismImpl1(a.inv(), c, c, alpha);
}

template <typename _Scalar, Trans _transc>
inline void dism(
    const char*,
    const InverseView<DenseDiagonalMatrix<_Scalar>> &a,
          DenseMatrix<_Scalar, _transc> &&c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1
) noexcept {
  detail::dismImpl1(c, a.inv(), c, alpha);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_wrapper_module
/// @brief  Solves a system of linear equations with multiple right-hand sides.
///
//@{
template <typename _Scalar, Trans _transb, Trans _transc>
inline void sm(
    const InverseView<DenseDiagonalMatrix<_Scalar>> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, _transc> &c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1
) noexcept {
  dism(a, b, c, alpha);
}

template <typename _Scalar, Trans _transb, Trans _transc>
inline void sm(
    const DenseMatrix<_Scalar, _transb> &b,
    const InverseView<DenseDiagonalMatrix<_Scalar>> &a,
          DenseMatrix<_Scalar, _transc> &c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1
) noexcept {
  dism(b, a, c, alpha);
}

template <typename _Scalar, Trans _transc>
inline void sm(
    const InverseView<DenseDiagonalMatrix<_Scalar>> &a,
    const char*,
          DenseMatrix<_Scalar, _transc> &c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1
) noexcept {
  dism(a, c, c, alpha);
}

template <typename _Scalar, Trans _transc>
inline void sm(
    const char*,
    const InverseView<DenseDiagonalMatrix<_Scalar>> &a,
          DenseMatrix<_Scalar, _transc> &c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1
) noexcept {
  dism(c, a, c, alpha);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Trans _transb, Trans _transc>
inline void sm(
    const InverseView<DenseDiagonalMatrix<_Scalar>> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, _transc> &&c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1
) noexcept {
  dism(a, b, c, alpha);
}

template <typename _Scalar, Trans _transb, Trans _transc>
inline void sm(
    const DenseMatrix<_Scalar, _transb> &b,
    const InverseView<DenseDiagonalMatrix<_Scalar>> &a,
          DenseMatrix<_Scalar, _transc> &&c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1
) noexcept {
  dism(b, a, c, alpha);
}

template <typename _Scalar, Trans _transc>
inline void sm(
    const InverseView<DenseDiagonalMatrix<_Scalar>> &a,
    const char*,
          DenseMatrix<_Scalar, _transc> &&c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1
) noexcept {
  dism(a, c, c, alpha);
}

template <typename _Scalar, Trans _transc>
inline void sm(
    const char*,
    const InverseView<DenseDiagonalMatrix<_Scalar>> &a,
          DenseMatrix<_Scalar, _transc> &&c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1
) noexcept {
  dism(c, a, c, alpha);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_DISM_HPP_
