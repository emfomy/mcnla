////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/blas/routine/gemm.hpp
/// @brief   The BLAS GEMM routine.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_BLAS_ROUTINE_GEMM_HPP_
#define ISVD_BLAS_ROUTINE_GEMM_HPP_

#include <isvd/matrix.hpp>
#include <isvd/blas/blas/gemm.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The BLAS namespace
//
namespace blas {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace
//
namespace detail {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::blas::gemm
///
//@{
template <TransOption _transa = TransOption::NORMAL,
          TransOption _transb = TransOption::NORMAL,
          typename _Scalar, Layout _layouta, Layout _layoutb>
inline void gemm(
    const _Scalar alpha,
    const DenseMatrix<_Scalar, _layouta> &a,
    const DenseMatrix<_Scalar, _layoutb> &b,
    const _Scalar beta,
          DenseMatrix<_Scalar, Layout::COLMAJOR> &c
) noexcept {
  const TransOption transa = isColMajor(_layouta) ? _transa : _transa ^ TransOption::TRANS;
  const TransOption transb = isColMajor(_layoutb) ? _transb : _transb ^ TransOption::TRANS;

  assert(c.getNrow()                   == a.template getNrow<_transa>());
  assert(c.getNcol()                   == b.template getNcol<_transb>());
  assert(a.template getNcol<_transa>() == b.template getNrow<_transb>());

  gemm(TransChar<transa, _Scalar>::value, TransChar<transb, _Scalar>::value,
       c.getNrow(), c.getNcol(), a.template getNcol<_transa>(),
       alpha, a.getValue(), a.getPitch(), b.getValue(), b.getPitch(), beta, c.getValue(), c.getPitch());
}

template <TransOption _transa = TransOption::NORMAL,
          TransOption _transb = TransOption::NORMAL,
          typename _Scalar, Layout _layouta, Layout _layoutb>
inline void gemm(
    const _Scalar alpha,
    const DenseMatrix<_Scalar, _layouta> &a,
    const DenseMatrix<_Scalar, _layoutb> &b,
    const _Scalar beta,
          DenseMatrix<_Scalar, Layout::ROWMAJOR> &c
) noexcept {
  const TransOption transa = isRowMajor(_layouta) ? _transa : _transa ^ TransOption::TRANS;
  const TransOption transb = isRowMajor(_layoutb) ? _transb : _transb ^ TransOption::TRANS;

  assert(c.getNrow()                   == a.template getNrow<_transa>());
  assert(c.getNcol()                   == b.template getNcol<_transb>());
  assert(a.template getNcol<_transa>() == b.template getNrow<_transb>());

  gemm(TransChar<transb, _Scalar>::value, TransChar<transa, _Scalar>::value,
       c.getNcol(), c.getNrow(), a.template getNcol<_transa>(),
       alpha, b.getValue(), b.getPitch(), a.getValue(), a.getPitch(), beta, c.getValue(), c.getPitch());
}
//@}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes a matrix-matrix product with general matrices.
///
//@{
template <TransOption _transa = isvd::TransOption::NORMAL,
          TransOption _transb = isvd::TransOption::NORMAL,
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

template <TransOption _transa = isvd::TransOption::NORMAL,
          TransOption _transb = isvd::TransOption::NORMAL,
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
//@}

}  // namespace blas

}  // namespace isvd

#endif  // ISVD_BLAS_ROUTINE_GEMM_HPP_
