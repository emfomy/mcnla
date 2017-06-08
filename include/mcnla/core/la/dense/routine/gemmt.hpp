////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/gemmt.hpp
/// @brief   The BLAS GEMMT routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_GEMMT_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_GEMMT_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/raw/blas/gemmt.hpp>

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
// Impl1
//
template <typename _Val, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void gemmtImpl1(
    const DenseMatrix<_Val, _transa> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseSymmetricMatrix<_Val, _transc, _uplo> &c,
    const _Val alpha,
    const _Val beta
) noexcept {
  mcnla_assert_eq(c.size(), a.nrow());
  mcnla_assert_eq(c.size(), b.ncol());
  mcnla_assert_eq(a.ncol(), b.nrow());

  gemmt(toUploChar(_uplo, _transc), toTransChar<_Val>(_transa), toTransChar<_Val>(_transb), c.size(), a.ncol(),
        alpha, a.valPtr(), a.pitch(), b.valPtr(), b.pitch(), beta, c.valPtr(), c.pitch());
}

//@}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas3_module
/// @brief  Computes a matrix-matrix product with general matrices but updates only the upper or lower triangular part of the
///         result matrix.
///
/// @note  The routine calls mcnla::la::gemm instead if there is no MKL support.
///
template <typename _Val, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void gemmt(
    const DenseMatrix<_Val, _transa> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseSymmetricMatrix<_Val, _transc, _uplo> &c,
    const ValT<DenseSymmetricMatrix<_Val, _transc, _uplo>> alpha = 1,
    const ValT<DenseSymmetricMatrix<_Val, _transc, _uplo>> beta  = 0
) noexcept {
  detail::gemmtImpl1(a, b, c, alpha, beta);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void gemmt(
    const DenseMatrix<_Val, _transa> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseSymmetricMatrix<_Val, _transc, _uplo> &&c,
    const ValT<DenseSymmetricMatrix<_Val, _transc, _uplo>> alpha = 1,
    const ValT<DenseSymmetricMatrix<_Val, _transc, _uplo>> beta  = 0
) noexcept {
  detail::gemmtImpl1(a, b, c, alpha, beta);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::la::mm
///
template <typename _Val, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void mm(
    const DenseMatrix<_Val, _transa> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseSymmetricMatrix<_Val, _transc, _uplo> &c,
    const ValT<DenseSymmetricMatrix<_Val, _transc, _uplo>> alpha = 1,
    const ValT<DenseSymmetricMatrix<_Val, _transc, _uplo>> beta  = 0
) noexcept {
  gemmt(a, b, c, alpha, beta);
}
#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _transa, Trans _transb, Trans _transc, Uplo _uplo>
inline void mm(
    const DenseMatrix<_Val, _transa> &a,
    const DenseMatrix<_Val, _transb> &b,
          DenseSymmetricMatrix<_Val, _transc, _uplo> &&c,
    const ValT<DenseSymmetricMatrix<_Val, _transc, _uplo>> alpha = 1,
    const ValT<DenseSymmetricMatrix<_Val, _transc, _uplo>> beta  = 0
) noexcept {
  gemmt(a, b, c, alpha, beta);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_GEMMT_HPP_
