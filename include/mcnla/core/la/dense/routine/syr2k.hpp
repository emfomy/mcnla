////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/syr2k.hpp
/// @brief   The BLAS SYR2K routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_SYR2K_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_SYR2K_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/raw/blas/syr2k.hpp>

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

template <typename _Val, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void syr2kImpl2(
    const DenseMatrix<_Val, _transa> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseSymmetricMatrix<_Val, _transc, _uplo> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  static_assert(_transa == _transb, "The layout of A and B must be the same!");

  mcnla_assert_eq(c.size(), a.nrow());
  mcnla_assert_eq(a.sizes(), b.sizes());

  syr2k(toUploChar(_uplo, _transc), toTransChar<_Val>(_transa), c.nrow(), a.ncol(),
        alpha, a.valPtr(), a.pitch(), b.valPtr(), b.pitch(), beta, c.valPtr(), c.pitch());
}

// ========================================================================================================================== //
// Impl1
//

template <typename _Val, Trans _transa, Trans _transb, Uplo _uplo>
inline void syr2kImpl1(
    const DenseMatrix<_Val, _transa> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseSymmetricMatrix<_Val, Trans::NORMAL, _uplo> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  syr2kImpl2(a, b, c, alpha, beta);
}

template <typename _Val, Trans _transa, Trans _transb, Uplo _uplo>
inline void syr2kImpl1(
    const DenseMatrix<_Val, _transa> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseSymmetricMatrix<_Val, Trans::TRANS, _uplo> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  syr2kImpl2(a, b, c, alpha, beta);
}

template <typename _Val, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo, bool dummy = 0>
inline void syr2kImpl1(
    const DenseMatrix<_Val, _transa> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseSymmetricMatrix<_Val, _transc, _uplo> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  static_cast<void>(a);
  static_cast<void>(c);
  static_cast<void>(alpha);
  static_cast<void>(beta);
  static_assert(dummy && false, "SYR2K does not support conjugate matrices!");
}

//@}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas3_module
/// @brief  Performs a symmetric/Hermitian rank-2k update.
///
template <typename _Val, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void syr2k(
    const DenseMatrix<_Val, _transa> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseSymmetricMatrix<_Val, _transc, _uplo> &c,
    const ValT<DenseSymmetricMatrix<_Val, _transc, _uplo>> alpha = 1,
    const ValT<DenseSymmetricMatrix<_Val, _transc, _uplo>> beta  = 0
) noexcept {
  detail::syr2kImpl1(a, b, c, alpha, beta);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void syr2k(
    const DenseMatrix<_Val, _transa> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseSymmetricMatrix<_Val, _transc, _uplo> &&c,
    const ValT<DenseSymmetricMatrix<_Val, _transc, _uplo>> alpha = 1,
    const ValT<DenseSymmetricMatrix<_Val, _transc, _uplo>> beta  = 0
) noexcept {
  detail::syr2kImpl1(a, b, c, alpha, beta);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::la::r2k
///
template <typename _Val, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void r2k(
    const DenseMatrix<_Val, _transa> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseSymmetricMatrix<_Val, _transc, _uplo> &c,
    const ValT<DenseSymmetricMatrix<_Val, _transc, _uplo>> alpha = 1,
    const ValT<DenseSymmetricMatrix<_Val, _transc, _uplo>> beta  = 0
) noexcept {
  syr2k(a, b, c, alpha, beta);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void r2k(
    const DenseMatrix<_Val, _transa> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseSymmetricMatrix<_Val, _transc, _uplo> &&c,
    const ValT<DenseSymmetricMatrix<_Val, _transc, _uplo>> alpha = 1,
    const ValT<DenseSymmetricMatrix<_Val, _transc, _uplo>> beta  = 0
) noexcept {
  syr2k(a, b, c, alpha, beta);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_SYR2K_HPP_
