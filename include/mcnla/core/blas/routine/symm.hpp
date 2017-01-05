////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/blas/routine/symm.hpp
/// @brief   The BLAS SYMM routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_BLAS_ROUTINE_SYMM_HPP_
#define MCNLA_CORE_BLAS_ROUTINE_SYMM_HPP_

#include <mcnla/core/matrix.hpp>
#include <mcnla/core/blas/blas/symm.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The BLAS namespace
//
namespace blas {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace
//
namespace detail {

//@{

// ========================================================================================================================== //
// Impl3
//

template <typename _Scalar, Trans _transa, Trans _transb, Uplo _uplo>
inline void symmImpl3(
    const DenseSymmetricMatrix<_Scalar, _transa, _uplo> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  mcnla_assert_eq(a.size(), c.nrow());
  mcnla_assert_eq(b.sizes(), c.sizes());

  detail::symm('L', toUploChar(_uplo, _transa), c.nrow(), c.ncol(),
               alpha, a.valuePtr(), a.pitch(), b.valuePtr(), b.pitch(), beta, c.valuePtr(), c.pitch());
}

template <typename _Scalar, Trans _transa, Trans _transb, Uplo _uplo>
inline void symmImpl3(
    const DenseMatrix<_Scalar, _transb> &b,
    const DenseSymmetricMatrix<_Scalar, _transa, _uplo> &a,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  mcnla_assert_eq(a.size(), c.ncol());
  mcnla_assert_eq(b.sizes(), c.sizes());

  detail::symm('R', toUploChar(_uplo, _transa), c.nrow(), c.ncol(),
               alpha, a.valuePtr(), a.pitch(), b.valuePtr(), b.pitch(), beta, c.valuePtr(), c.pitch());
}

// ========================================================================================================================== //
// Impl2 Left
//

template <typename _Scalar, Trans _transa, Uplo _uplo>
inline void symmImpl2(
    const DenseSymmetricMatrix<_Scalar, _transa, _uplo> &a,
    const DenseMatrix<_Scalar, Trans::NORMAL> &b,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  symmImpl3(a, b, c, alpha, beta);
}

template <typename _Scalar, Trans _transa, Trans _transb, Uplo _uplo>
inline void symmImpl2(
    const DenseSymmetricMatrix<_Scalar, _transa, _uplo> &a,
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
  static_assert(_transb == Trans::NORMAL, "The layout of B and C must be the same!");
}

// ========================================================================================================================== //
// Impl2 Right
//

template <typename _Scalar, Trans _transa, Uplo _uplo>
inline void symmImpl2(
    const DenseMatrix<_Scalar, Trans::NORMAL> &b,
    const DenseSymmetricMatrix<_Scalar, _transa, _uplo> &a,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  symmImpl3(b, a, c, alpha, beta);
}

template <typename _Scalar, Trans _transa, Trans _transb, Uplo _uplo>
inline void symmImpl2(
    const DenseMatrix<_Scalar, _transb> &b,
    const DenseSymmetricMatrix<_Scalar, _transa, _uplo> &a,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  static_cast<void>(a);
  static_cast<void>(b);
  static_cast<void>(c);
  static_cast<void>(alpha);
  static_cast<void>(beta);
  static_assert(_transb == Trans::NORMAL, "The layout of B and C must be the same!");
}

// ========================================================================================================================== //
// Impl1 Left
//

template <typename _Scalar, Trans _transa, Trans _transb, Uplo _uplo>
inline void symmImpl1(
    const DenseSymmetricMatrix<_Scalar, _transa, _uplo> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  symmImpl2(a, b, c, alpha, beta);
}

template <typename _Scalar, Trans _transa, Trans _transb, Uplo _uplo>
inline void symmImpl1(
    const DenseSymmetricMatrix<_Scalar, _transa, _uplo> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, Trans::TRANS> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  symmImpl2(b.t(), a.t(), c.t(), alpha, beta);
}

template <typename _Scalar, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void symmImpl1(
    const DenseSymmetricMatrix<_Scalar, _transa, _uplo> &a,
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
  static_assert(!isConj(_transc), "Conjugate version of SYMM is not supported!");
}

// ========================================================================================================================== //
// Impl1 Right
//

template <typename _Scalar, Trans _transa, Trans _transb, Uplo _uplo>
inline void symmImpl1(
    const DenseMatrix<_Scalar, _transb> &b,
    const DenseSymmetricMatrix<_Scalar, _transa, _uplo> &a,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  symmImpl2(b, a, c, alpha, beta);
}

template <typename _Scalar, Trans _transa, Trans _transb, Uplo _uplo>
inline void symmImpl1(
    const DenseMatrix<_Scalar, _transb> &b,
    const DenseSymmetricMatrix<_Scalar, _transa, _uplo> &a,
          DenseMatrix<_Scalar, Trans::TRANS> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  symmImpl2(a.t(), b.t(), c.t(), alpha, beta);
}

template <typename _Scalar, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void symmImpl1(
    const DenseMatrix<_Scalar, _transb> &b,
    const DenseSymmetricMatrix<_Scalar, _transa, _uplo> &a,
          DenseMatrix<_Scalar, _transc> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  static_cast<void>(a);
  static_cast<void>(b);
  static_cast<void>(c);
  static_cast<void>(alpha);
  static_cast<void>(beta);
  static_assert(!isConj(_transc), "Conjugate version of SYMM is not supported!");
}

//@}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  blas3_module
/// @brief  Computes a matrix-matrix product where one input matrix is symmetric/Hermitian.
///
//@{
template <typename _Scalar, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void symm(
    const DenseSymmetricMatrix<_Scalar, _transa, _uplo> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, _transc> &c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  detail::symmImpl1(a, b, c, alpha, beta);
}

template <typename _Scalar, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void symm(
    const DenseMatrix<_Scalar, _transb> &b,
    const DenseSymmetricMatrix<_Scalar, _transa, _uplo> &a,
          DenseMatrix<_Scalar, _transc> &c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  detail::symmImpl1(b, a, c, alpha, beta);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void symm(
    const DenseSymmetricMatrix<_Scalar, _transa, _uplo> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, _transc> &&c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  detail::symmImpl1(a, b, c, alpha, beta);
}

template <typename _Scalar, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void symm(
    const DenseMatrix<_Scalar, _transb> &b,
    const DenseSymmetricMatrix<_Scalar, _transa, _uplo> &a,
          DenseMatrix<_Scalar, _transc> &&c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  detail::symmImpl1(b, a, c, alpha, beta);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  blas_module
/// @copydoc  mm
///
//@{
template <typename _Scalar, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void mm(
    const DenseSymmetricMatrix<_Scalar, _transa, _uplo> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, _transc> &c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  symm(a, b, c, alpha, beta);
}

template <typename _Scalar, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void mm(
    const DenseMatrix<_Scalar, _transb> &b,
    const DenseSymmetricMatrix<_Scalar, _transa, _uplo> &a,
          DenseMatrix<_Scalar, _transc> &c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  symm(b, a, c, alpha, beta);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void mm(
    const DenseSymmetricMatrix<_Scalar, _transa, _uplo> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, _transc> &&c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  symm(a, b, c, alpha, beta);
}

template <typename _Scalar, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void mm(
    const DenseMatrix<_Scalar, _transb> &b,
    const DenseSymmetricMatrix<_Scalar, _transa, _uplo> &a,
          DenseMatrix<_Scalar, _transc> &&c,
    const ScalarT<DenseMatrix<_Scalar, _transc>> alpha = 1,
    const ScalarT<DenseMatrix<_Scalar, _transc>> beta  = 0
) noexcept {
  symm(b, a, c, alpha, beta);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_ROUTINE_SYMM_HPP_
