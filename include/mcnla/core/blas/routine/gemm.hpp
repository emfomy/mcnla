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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes a matrix-matrix product with general matrices.
///
//@{
template <Trans _transa = Trans::NORMAL, Trans _transb = Trans::NORMAL,
          typename _Scalar, Layout _layouta, Layout _layoutb>
inline void gemm(
    const _Scalar alpha,
    const DenseMatrix<_Scalar, _layouta> &a,
    const DenseMatrix<_Scalar, _layoutb> &b,
    const _Scalar beta,
          DenseMatrix<_Scalar, Layout::COLMAJOR> &c
) noexcept {
  constexpr Trans transa = isColMajor(_layouta) ? _transa : _transa ^ Trans::TRANS;
  constexpr Trans transb = isColMajor(_layoutb) ? _transb : _transb ^ Trans::TRANS;

  mcnla_assert_eq(c.getNrow(),                   a.template getNrow<_transa>());
  mcnla_assert_eq(c.getNcol(),                   b.template getNcol<_transb>());
  mcnla_assert_eq(a.template getNcol<_transa>(), b.template getNrow<_transb>());

  gemm(toTransChar<_Scalar>(transa), toTransChar<_Scalar>(transb),
       c.getNrow(), c.getNcol(), a.template getNcol<_transa>(),
       alpha, a.getValuePtr(), a.getPitch(), b.getValuePtr(), b.getPitch(), beta, c.getValuePtr(), c.getPitch());
}

template <Trans _transa = Trans::NORMAL,
          Trans _transb = Trans::NORMAL,
          typename _Scalar, Layout _layouta, Layout _layoutb>
inline void gemm(
    const _Scalar alpha,
    const DenseMatrix<_Scalar, _layouta> &a,
    const DenseMatrix<_Scalar, _layoutb> &b,
    const _Scalar beta,
          DenseMatrix<_Scalar, Layout::ROWMAJOR> &c
) noexcept {
  constexpr Trans transa = isRowMajor(_layouta) ? _transa : _transa ^ Trans::TRANS;
  constexpr Trans transb = isRowMajor(_layoutb) ? _transb : _transb ^ Trans::TRANS;

  mcnla_assert_eq(c.getNrow(),                   a.template getNrow<_transa>());
  mcnla_assert_eq(c.getNcol(),                   b.template getNcol<_transb>());
  mcnla_assert_eq(a.template getNcol<_transa>(), b.template getNrow<_transb>());

  gemm(toTransChar<_Scalar>(transb), toTransChar<_Scalar>(transa),
       c.getNcol(), c.getNrow(), a.template getNcol<_transa>(),
       alpha, b.getValuePtr(), b.getPitch(), a.getValuePtr(), a.getPitch(), beta, c.getValuePtr(), c.getPitch());
}
//@}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  blas3_module
/// @brief  Computes a matrix-matrix product with general matrices.
///
template <Trans _transa = Trans::NORMAL, Trans _transb = Trans::NORMAL,
          typename _Scalar, Layout _layouta, Layout _layoutb, Layout _layoutc>
inline void gemm(
    const typename DenseMatrix<_Scalar, _layoutc>::ScalarType alpha,
    const DenseMatrix<_Scalar, _layouta> &a,
    const DenseMatrix<_Scalar, _layoutb> &b,
    const typename DenseMatrix<_Scalar, _layoutc>::ScalarType beta,
          DenseMatrix<_Scalar, _layoutc> &c
) noexcept {
  detail::gemm<_transa, _transb>(alpha, a, b, beta, c);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <Trans _transa = Trans::NORMAL, Trans _transb = Trans::NORMAL,
          typename _Scalar, Layout _layouta, Layout _layoutb, Layout _layoutc>
inline void gemm(
    const typename DenseMatrix<_Scalar, _layoutc>::ScalarType alpha,
    const DenseMatrix<_Scalar, _layouta> &a,
    const DenseMatrix<_Scalar, _layoutb> &b,
    const typename DenseMatrix<_Scalar, _layoutc>::ScalarType beta,
          DenseMatrix<_Scalar, _layoutc> &&c
) noexcept {
  detail::gemm<_transa, _transb>(alpha, a, b, beta, c);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_ROUTINE_GEMM_HPP_
