////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/symm.hpp
/// @brief   The BLAS SYMM routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_SYMM_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_SYMM_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/raw/blas/symm.hpp>

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

template <typename _Val, Trans _transa, Uplo _uplo>
inline void symmImpl3(
    const DenseSymmetricMatrix<_Val, _transa, _uplo> &a,
    const DenseMatrix<_Val, Trans::NORMAL> &b,
          DenseMatrix<_Val, Trans::NORMAL> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  mcnla_assert_eq(a.size(), c.nrow());
  mcnla_assert_eq(b.sizes(), c.sizes());

  symm('L', toUploChar(_uplo, _transa), c.nrow(), c.ncol(),
       alpha, a.valPtr(), a.pitch(), b.valPtr(), b.pitch(), beta, c.valPtr(), c.pitch());
}

template <typename _Val, Trans _transa, Uplo _uplo>
inline void symmImpl3(
    const DenseMatrix<_Val, Trans::NORMAL> &b,
    const DenseSymmetricMatrix<_Val, _transa, _uplo> &a,
          DenseMatrix<_Val, Trans::NORMAL> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  mcnla_assert_eq(a.size(), c.ncol());
  mcnla_assert_eq(b.sizes(), c.sizes());

  symm('R', toUploChar(_uplo, _transa), c.nrow(), c.ncol(),
       alpha, a.valPtr(), a.pitch(), b.valPtr(), b.pitch(), beta, c.valPtr(), c.pitch());
}

// ========================================================================================================================== //
// Impl2 Left
//

template <typename _Val, Trans _transa, Uplo _uplo>
inline void symmImpl2(
    const DenseSymmetricMatrix<_Val, _transa, _uplo> &a,
    const DenseMatrix<_Val, Trans::NORMAL> &b,
          DenseMatrix<_Val, Trans::NORMAL> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  symmImpl3(a, b, c, alpha, beta);
}

template <typename _Val, Trans _transa, Trans _transb, Uplo _uplo, bool dummy = 0>
inline void symmImpl2(
    const DenseSymmetricMatrix<_Val, _transa, _uplo> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseMatrix<_Val, Trans::NORMAL> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  static_cast<void>(a);
  static_cast<void>(b);
  static_cast<void>(c);
  static_cast<void>(alpha);
  static_cast<void>(beta);
  static_assert(dummy && false, "The layout of B and C in SYMM must be the same!");
}

// ========================================================================================================================== //
// Impl2 Right
//

template <typename _Val, Trans _transa, Uplo _uplo>
inline void symmImpl2(
    const DenseMatrix<_Val, Trans::NORMAL> &b,
    const DenseSymmetricMatrix<_Val, _transa, _uplo> &a,
          DenseMatrix<_Val, Trans::NORMAL> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  symmImpl3(b, a, c, alpha, beta);
}

template <typename _Val, Trans _transa, Trans _transb, Uplo _uplo, bool dummy = 0>
inline void symmImpl2(
    const DenseMatrix<_Val, _transb> &b,
    const DenseSymmetricMatrix<_Val, _transa, _uplo> &a,
          DenseMatrix<_Val, Trans::NORMAL> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  static_cast<void>(a);
  static_cast<void>(b);
  static_cast<void>(c);
  static_cast<void>(alpha);
  static_cast<void>(beta);
  static_assert(dummy && false, "The layout of B and C in SYMM must be the same!");
}

// ========================================================================================================================== //
// Impl1 Left
//

template <typename _Val, Trans _transa, Trans _transb, Uplo _uplo>
inline void symmImpl1(
    const DenseSymmetricMatrix<_Val, _transa, _uplo> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseMatrix<_Val, Trans::NORMAL> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  symmImpl2(a, b, c, alpha, beta);
}

template <typename _Val, Trans _transa, Trans _transb, Uplo _uplo>
inline void symmImpl1(
    const DenseSymmetricMatrix<_Val, _transa, _uplo> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseMatrix<_Val, Trans::TRANS> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  symmImpl2(b.t(), a.t(), c.t(), alpha, beta);
}

template <typename _Val, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo, bool dummy = 0>
inline void symmImpl1(
    const DenseSymmetricMatrix<_Val, _transa, _uplo> &a,
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
  static_assert(dummy && false, "SYMM for conjugate matrices is not implemented!");
}

// ========================================================================================================================== //
// Impl1 Right
//

template <typename _Val, Trans _transa, Trans _transb, Uplo _uplo>
inline void symmImpl1(
    const DenseMatrix<_Val, _transb> &b,
    const DenseSymmetricMatrix<_Val, _transa, _uplo> &a,
          DenseMatrix<_Val, Trans::NORMAL> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  symmImpl2(b, a, c, alpha, beta);
}

template <typename _Val, Trans _transa, Trans _transb, Uplo _uplo>
inline void symmImpl1(
    const DenseMatrix<_Val, _transb> &b,
    const DenseSymmetricMatrix<_Val, _transa, _uplo> &a,
          DenseMatrix<_Val, Trans::TRANS> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  symmImpl2(a.t(), b.t(), c.t(), alpha, beta);
}

template <typename _Val, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo, bool dummy = 0>
inline void symmImpl1(
    const DenseMatrix<_Val, _transb> &b,
    const DenseSymmetricMatrix<_Val, _transa, _uplo> &a,
          DenseMatrix<_Val, _transc> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  static_cast<void>(a);
  static_cast<void>(b);
  static_cast<void>(c);
  static_cast<void>(alpha);
  static_cast<void>(beta);
  static_assert(dummy && false, "SYMM for conjugate matrices is not implemented!");
}

//@}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas3_module
/// @brief  Computes a matrix-matrix product where one input matrix is symmetric/Hermitian.
///
//@{
template <typename _Val, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void symm(
    const DenseSymmetricMatrix<_Val, _transa, _uplo> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseMatrix<_Val, _transc> &c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1,
    const ValT<DenseMatrix<_Val, _transc>> beta  = 0
) noexcept {
  detail::symmImpl1(a, b, c, alpha, beta);
}

template <typename _Val, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void symm(
    const DenseMatrix<_Val, _transb> &b,
    const DenseSymmetricMatrix<_Val, _transa, _uplo> &a,
          DenseMatrix<_Val, _transc> &c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1,
    const ValT<DenseMatrix<_Val, _transc>> beta  = 0
) noexcept {
  detail::symmImpl1(b, a, c, alpha, beta);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void symm(
    const DenseSymmetricMatrix<_Val, _transa, _uplo> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseMatrix<_Val, _transc> &&c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1,
    const ValT<DenseMatrix<_Val, _transc>> beta  = 0
) noexcept {
  detail::symmImpl1(a, b, c, alpha, beta);
}

template <typename _Val, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void symm(
    const DenseMatrix<_Val, _transb> &b,
    const DenseSymmetricMatrix<_Val, _transa, _uplo> &a,
          DenseMatrix<_Val, _transc> &&c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1,
    const ValT<DenseMatrix<_Val, _transc>> beta  = 0
) noexcept {
  detail::symmImpl1(b, a, c, alpha, beta);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::la::mm
///
//@{
template <typename _Val, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void mm(
    const DenseSymmetricMatrix<_Val, _transa, _uplo> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseMatrix<_Val, _transc> &c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1,
    const ValT<DenseMatrix<_Val, _transc>> beta  = 0
) noexcept {
  symm(a, b, c, alpha, beta);
}

template <typename _Val, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void mm(
    const DenseMatrix<_Val, _transb> &b,
    const DenseSymmetricMatrix<_Val, _transa, _uplo> &a,
          DenseMatrix<_Val, _transc> &c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1,
    const ValT<DenseMatrix<_Val, _transc>> beta  = 0
) noexcept {
  symm(b, a, c, alpha, beta);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void mm(
    const DenseSymmetricMatrix<_Val, _transa, _uplo> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseMatrix<_Val, _transc> &&c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1,
    const ValT<DenseMatrix<_Val, _transc>> beta  = 0
) noexcept {
  symm(a, b, c, alpha, beta);
}

template <typename _Val, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void mm(
    const DenseMatrix<_Val, _transb> &b,
    const DenseSymmetricMatrix<_Val, _transa, _uplo> &a,
          DenseMatrix<_Val, _transc> &&c,
    const ValT<DenseMatrix<_Val, _transc>> alpha = 1,
    const ValT<DenseMatrix<_Val, _transc>> beta  = 0
) noexcept {
  symm(b, a, c, alpha, beta);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_SYMM_HPP_
