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
template <typename _Val>
inline void dismImpl2(
    const DenseDiagonalMatrix<_Val> &a,
          DenseMatrix<_Val, Trans::NORMAL> &b,
    const _Val alpha
) noexcept {
  mcnla_assert_eq(a.size(), b.nrow());

  index_t idiag[1] = {0};
  diasm('N', b.nrow(), b.ncol(), alpha, "TLNC",
        a.valPtr(), a.size(), idiag, 1, b.valPtr(), b.pitch(), b.valPtr(), b.pitch());
}
#else  // MCNLA_USE_MKL
template <typename _Val>
inline void dismImpl2(
    const DenseDiagonalMatrix<_Val> &a,
          DenseMatrix<_Val, Trans::NORMAL> &b,
    const _Val alpha
) noexcept {
  mcnla_assert_eq(a.size(), b.nrow());

  auto da = a.viewVector();
  for ( index_t i = 0; i < da.length(); ++i ) {
    la::scal(b(i, ""_), alpha / da(i));
  }
}
#endif  // MCNLA_USE_MKL

template <typename _Val>
inline void dismImpl2(
          DenseMatrix<_Val, Trans::NORMAL> &b,
    const DenseDiagonalMatrix<_Val> &a,
    const _Val alpha
) noexcept {
  mcnla_assert_eq(a.size(), b.ncol());

  auto da = a.viewVector();
  for ( index_t i = 0; i < da.length(); ++i ) {
    la::scal(b(""_, i), alpha / da(i));
  }
}

// ========================================================================================================================== //
// Impl1 Left
//

template <typename _Val>
inline void dismImpl1(
    const DenseDiagonalMatrix<_Val> &a,
          DenseMatrix<_Val, Trans::NORMAL> &b,
    const _Val alpha
) noexcept {
  dismImpl2(a, b, alpha);
}

template <typename _Val>
inline void dismImpl1(
    const DenseDiagonalMatrix<_Val> &a,
          DenseMatrix<_Val, Trans::TRANS> &b,
    const _Val alpha
) noexcept {
  dismImpl2(b.t(), a.t(), alpha);
}

template <typename _Val, Trans _transb, bool dummy = 0>
inline void dismImpl1(
    const DenseDiagonalMatrix<_Val> &a,
          DenseMatrix<_Val, _transb> &b,
    const _Val alpha
) noexcept {
  static_cast<void>(a);
  static_cast<void>(b);
  static_cast<void>(alpha);
  static_assert(dummy && false, "DISM does not support conjugate matrices!");
}

// ========================================================================================================================== //
// Impl1 Right
//

template <typename _Val>
inline void dismImpl1(
          DenseMatrix<_Val, Trans::NORMAL> &b,
    const DenseDiagonalMatrix<_Val> &a,
    const _Val alpha
) noexcept {
  dismImpl2(b, a, alpha);
}

template <typename _Val>
inline void dismImpl1(
          DenseMatrix<_Val, Trans::TRANS> &b,
    const DenseDiagonalMatrix<_Val> &a,
    const _Val alpha
) noexcept {
  dismImpl2(a.t(), b.t(), alpha);
}

template <typename _Val, Trans _transb, bool dummy = 0>
inline void dismImpl1(
          DenseMatrix<_Val, _transb> &b,
    const DenseDiagonalMatrix<_Val> &a,
    const _Val alpha
) noexcept {
  static_cast<void>(a);
  static_cast<void>(b);
  static_cast<void>(alpha);
  static_assert(dummy && false, "DISM does not support conjugate matrices!");
}

//@}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas3_module
/// @brief  Solves a system of linear equations with a diagonal coefficient matrix and multiple right-hand sides.
///
//@{
template <typename _Val, Trans _transb>
inline void dism(
    const InverseView<DenseDiagonalMatrix<_Val>> &a,
          DenseMatrix<_Val, _transb> &b,
    const ValT<DenseMatrix<_Val, _transb>> alpha = 1
) noexcept {
  detail::dismImpl1(a.inv(), b, alpha);
}

template <typename _Val, Trans _transb>
inline void dism(
          DenseMatrix<_Val, _transb> &b,
    const InverseView<DenseDiagonalMatrix<_Val>> &a,
    const ValT<DenseMatrix<_Val, _transb>> alpha = 1
) noexcept {
  detail::dismImpl1(b, a.inv(), alpha);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _transb>
inline void dism(
    const InverseView<DenseDiagonalMatrix<_Val>> &a,
          DenseMatrix<_Val, _transb> &&b,
    const ValT<DenseMatrix<_Val, _transb>> alpha = 1
) noexcept {
  detail::dismImpl1(a.inv(), b, alpha);
}

template <typename _Val, Trans _transb>
inline void dism(
          DenseMatrix<_Val, _transb> &&b,
    const InverseView<DenseDiagonalMatrix<_Val>> &a,
    const ValT<DenseMatrix<_Val, _transb>> alpha = 1
) noexcept {
  detail::dismImpl1(b, a.inv(), alpha);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::la::sm
///
//@{
template <typename _Val, Trans _transb>
inline void sm(
    const InverseView<DenseDiagonalMatrix<_Val>> &a,
          DenseMatrix<_Val, _transb> &b,
    const ValT<DenseMatrix<_Val, _transb>> alpha = 1
) noexcept {
  dism(a, b, alpha);
}

template <typename _Val, Trans _transb>
inline void sm(
          DenseMatrix<_Val, _transb> &b,
    const InverseView<DenseDiagonalMatrix<_Val>> &a,
    const ValT<DenseMatrix<_Val, _transb>> alpha = 1
) noexcept {
  dism(b, a, alpha);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _transb>
inline void sm(
    const InverseView<DenseDiagonalMatrix<_Val>> &a,
          DenseMatrix<_Val, _transb> &&b,
    const ValT<DenseMatrix<_Val, _transb>> alpha = 1
) noexcept {
  dism(a, b, alpha);
}

template <typename _Val, Trans _transb>
inline void sm(
          DenseMatrix<_Val, _transb> &&b,
    const InverseView<DenseDiagonalMatrix<_Val>> &a,
    const ValT<DenseMatrix<_Val, _transb>> alpha = 1
) noexcept {
  dism(b, a, alpha);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_DISM_HPP_
