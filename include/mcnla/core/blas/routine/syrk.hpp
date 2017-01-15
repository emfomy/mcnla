////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/blas/routine/syrk.hpp
/// @brief   The BLAS SYRK routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_BLAS_ROUTINE_SYRK_HPP_
#define MCNLA_CORE_BLAS_ROUTINE_SYRK_HPP_

#include <mcnla/core/container.hpp>
#include <mcnla/core/blas/blas/syrk.hpp>

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
// Impl2
//

template <typename _Scalar, Trans _transa, Trans _transc, Uplo _uplo>
inline void syrkImpl2(
    const DenseMatrix<_Scalar, _transa> &a,
          DenseSymmetricMatrix<_Scalar, _transc, _uplo> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  mcnla_assert_eq(c.size(), a.nrow());

  detail::syrk(toUploChar(_uplo, _transc), toTransChar<_Scalar>(_transa), c.nrow(), a.ncol(),
               alpha, a.valuePtr(), a.pitch(), beta, c.valuePtr(), c.pitch());
}

// ========================================================================================================================== //
// Impl1
//

template <typename _Scalar, Trans _transa, Uplo _uplo>
inline void syrkImpl1(
    const DenseMatrix<_Scalar, _transa> &a,
          DenseSymmetricMatrix<_Scalar, Trans::NORMAL, _uplo> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  syrkImpl2(a, c, alpha, beta);
}

template <typename _Scalar, Trans _transa, Uplo _uplo>
inline void syrkImpl1(
    const DenseMatrix<_Scalar, _transa> &a,
          DenseSymmetricMatrix<_Scalar, Trans::TRANS, _uplo> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  syrkImpl2(a, c, alpha, beta);
}

template <typename _Scalar, Trans _transa, Trans _transc, Uplo _uplo>
inline void syrkImpl1(
    const DenseMatrix<_Scalar, _transa> &a,
          DenseSymmetricMatrix<_Scalar, _transc, _uplo> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  static_cast<void>(a);
  static_cast<void>(c);
  static_cast<void>(alpha);
  static_cast<void>(beta);
  static_assert(!isConj(_transc), "Conjugate version of SYRK is not supported!");
}

//@}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  blas3_module
/// @brief  Performs a symmetric/Hermitian rank-k update.
///
template <typename _Scalar, Trans _transa, Trans _transc, Uplo _uplo>
inline void syrk(
    const DenseMatrix<_Scalar, _transa> &a,
          DenseSymmetricMatrix<_Scalar, _transc, _uplo> &c,
    const ScalarT<DenseSymmetricMatrix<_Scalar, _transc, _uplo>> alpha = 1,
    const ScalarT<DenseSymmetricMatrix<_Scalar, _transc, _uplo>> beta  = 0
) noexcept {
  detail::syrkImpl1(a, c, alpha, beta);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Trans _transa, Trans _transc, Uplo _uplo>
inline void syrk(
    const DenseMatrix<_Scalar, _transa> &a,
          DenseSymmetricMatrix<_Scalar, _transc, _uplo> &&c,
    const ScalarT<DenseSymmetricMatrix<_Scalar, _transc, _uplo>> alpha = 1,
    const ScalarT<DenseSymmetricMatrix<_Scalar, _transc, _uplo>> beta  = 0
) noexcept {
  detail::syrkImpl1(a, c, alpha, beta);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  blas_module
/// @brief  Performs a rank-k update.
///
template <typename _Scalar, Trans _transa, Trans _transc, Uplo _uplo>
inline void rk(
    const DenseMatrix<_Scalar, _transa> &a,
          DenseSymmetricMatrix<_Scalar, _transc, _uplo> &c,
    const ScalarT<DenseSymmetricMatrix<_Scalar, _transc, _uplo>> alpha = 1,
    const ScalarT<DenseSymmetricMatrix<_Scalar, _transc, _uplo>> beta  = 0
) noexcept {
  syrk(a, c, alpha, beta);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Trans _transa, Trans _transc, Uplo _uplo>
inline void rk(
    const DenseMatrix<_Scalar, _transa> &a,
          DenseSymmetricMatrix<_Scalar, _transc, _uplo> &&c,
    const ScalarT<DenseSymmetricMatrix<_Scalar, _transc, _uplo>> alpha = 1,
    const ScalarT<DenseSymmetricMatrix<_Scalar, _transc, _uplo>> beta  = 0
) noexcept {
  syrk(a, c, alpha, beta);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_ROUTINE_SYRK_HPP_
