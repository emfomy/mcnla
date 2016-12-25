////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/blas/routine/gemm.hpp
/// @brief   The BLAS GEMM routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_BLAS_ROUTINE_GEMM_HPP_
#define MCNLA_CORE_BLAS_ROUTINE_GEMM_HPP_

#include <mcnla/core/matrix.hpp>
#include <mcnla/core/blas/blas/gemm.hpp>

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
template <typename _Scalar, Trans _transa, Trans _transb>
inline void gemmImpl2(
    const DenseMatrix<_Scalar, _transa> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  mcnla_assert_eq(c.getNrow(), a.getNrow());
  mcnla_assert_eq(c.getNcol(), b.getNcol());
  mcnla_assert_eq(a.getNcol(), b.getNrow());

  gemm(toTransChar<_Scalar>(_transa), toTransChar<_Scalar>(_transb), c.getNrow(), c.getNcol(), a.getNcol(),
       alpha, a.getValuePtr(), a.getPitch(), b.getValuePtr(), b.getPitch(), beta, c.getValuePtr(), c.getPitch());
}

// ========================================================================================================================== //
// Impl1
//

template <typename _Scalar, Trans _transa, Trans _transb>
inline void gemmImpl1(
    const DenseMatrix<_Scalar, _transa> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, Trans::NORMAL> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  gemmImpl2(a, b, c, alpha, beta);
}

template <typename _Scalar, Trans _transa, Trans _transb>
inline void gemmImpl1(
    const DenseMatrix<_Scalar, _transa> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, Trans::TRANS> &c,
    const _Scalar alpha,
    const _Scalar beta
) noexcept {
  gemmImpl2(b.transpose(), a.transpose(), c.transpose(), alpha, beta);
}

template <typename _Scalar, Trans _transa, Trans _transb, Trans _transc>
inline void gemmImpl1(
    const DenseMatrix<_Scalar, _transa> &a,
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
  static_assert(!isConj(_transc), "Conjugate version of GEMM is not supported!");
}

//@}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  blas3_module
/// @brief  Computes a matrix-matrix product with general matrices.
///
template <typename _Scalar, Trans _transa, Trans _transb, Trans _transc>
inline void gemm(
    const DenseMatrix<_Scalar, _transa> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, _transc> &c,
    const typename DenseMatrix<_Scalar, _transc>::ScalarType alpha = 1,
    const typename DenseMatrix<_Scalar, _transc>::ScalarType beta  = 0
) noexcept {
  detail::gemmImpl1(a, b, c, alpha, beta);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Trans _transa, Trans _transb, Trans _transc>
inline void gemm(
    const DenseMatrix<_Scalar, _transa> &a,
    const DenseMatrix<_Scalar, _transb> &b,
          DenseMatrix<_Scalar, _transc> &&c,
    const typename DenseMatrix<_Scalar, _transc>::ScalarType alpha = 1,
    const typename DenseMatrix<_Scalar, _transc>::ScalarType beta  = 0
) noexcept {
  detail::gemmImpl1(a, b, c, alpha, beta);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_ROUTINE_GEMM_HPP_
