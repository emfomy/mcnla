////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/syrk.hpp
/// @brief   The BLAS SYRK routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_SYRK_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_SYRK_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/raw/blas/syrk.hpp>

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

template <typename _Val, Trans _transa, Trans _transc, Uplo _uplo>
inline void syrkImpl2(
    const DenseMatrix<_Val, _transa> &a,
          DenseSymmetricMatrix<_Val, _transc, _uplo> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  mcnla_assert_eq(c.size(), a.nrow());

  syrk(toUploChar(_uplo, _transc), toTransChar<_Val>(_transa), c.nrow(), a.ncol(),
       alpha, a.valPtr(), a.pitch(), beta, c.valPtr(), c.pitch());
}

// ========================================================================================================================== //
// Impl1
//

template <typename _Val, Trans _transa, Uplo _uplo>
inline void syrkImpl1(
    const DenseMatrix<_Val, _transa> &a,
          DenseSymmetricMatrix<_Val, Trans::NORMAL, _uplo> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  syrkImpl2(a, c, alpha, beta);
}

template <typename _Val, Trans _transa, Uplo _uplo>
inline void syrkImpl1(
    const DenseMatrix<_Val, _transa> &a,
          DenseSymmetricMatrix<_Val, Trans::TRANS, _uplo> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  syrkImpl2(a, c, alpha, beta);
}

template <typename _Val, Trans _transa, Trans _transc, Uplo _uplo, bool dummy = 0>
inline void syrkImpl1(
    const DenseMatrix<_Val, _transa> &a,
          DenseSymmetricMatrix<_Val, _transc, _uplo> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  static_cast<void>(a);
  static_cast<void>(c);
  static_cast<void>(alpha);
  static_cast<void>(beta);
  static_assert(dummy && false, "SYRK does not support conjugate matrices!");
}

//@}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas3_module
/// @brief  Performs a symmetric/Hermitian rank-k update.
///
template <typename _Val, Trans _transa, Trans _transc, Uplo _uplo>
inline void syrk(
    const DenseMatrix<_Val, _transa> &a,
          DenseSymmetricMatrix<_Val, _transc, _uplo> &c,
    const ValT<DenseSymmetricMatrix<_Val, _transc, _uplo>> alpha = 1,
    const ValT<DenseSymmetricMatrix<_Val, _transc, _uplo>> beta  = 0
) noexcept {
  detail::syrkImpl1(a, c, alpha, beta);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _transa, Trans _transc, Uplo _uplo>
inline void syrk(
    const DenseMatrix<_Val, _transa> &a,
          DenseSymmetricMatrix<_Val, _transc, _uplo> &&c,
    const ValT<DenseSymmetricMatrix<_Val, _transc, _uplo>> alpha = 1,
    const ValT<DenseSymmetricMatrix<_Val, _transc, _uplo>> beta  = 0
) noexcept {
  detail::syrkImpl1(a, c, alpha, beta);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::la::rk
///
template <typename _Val, Trans _transa, Trans _transc, Uplo _uplo>
inline void rk(
    const DenseMatrix<_Val, _transa> &a,
          DenseSymmetricMatrix<_Val, _transc, _uplo> &c,
    const ValT<DenseSymmetricMatrix<_Val, _transc, _uplo>> alpha = 1,
    const ValT<DenseSymmetricMatrix<_Val, _transc, _uplo>> beta  = 0
) noexcept {
  syrk(a, c, alpha, beta);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _transa, Trans _transc, Uplo _uplo>
inline void rk(
    const DenseMatrix<_Val, _transa> &a,
          DenseSymmetricMatrix<_Val, _transc, _uplo> &&c,
    const ValT<DenseSymmetricMatrix<_Val, _transc, _uplo>> alpha = 1,
    const ValT<DenseSymmetricMatrix<_Val, _transc, _uplo>> beta  = 0
) noexcept {
  syrk(a, c, alpha, beta);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_SYRK_HPP_
