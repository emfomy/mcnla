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
/// @copydoc  isvd::blas::internal::gemm
///
//@{
template <TransOption _transa = isvd::TransOption::NORMAL,
          TransOption _transb = isvd::TransOption::NORMAL, typename _Scalar, Layout _layout>
inline void gemm(
    const typename DenseMatrix<_Scalar, _layout>::ScalarType alpha,
    const DenseMatrix<_Scalar, _layout> &a,
    const DenseMatrix<_Scalar, _layout> &b,
    const typename DenseMatrix<_Scalar, _layout>::ScalarType beta,
          DenseMatrix<_Scalar, _layout> &c
) noexcept {
  if ( isColMajor(_layout) ) {
    assert(c.getNrow() == a.template getNrow<_transa>());
    assert(c.getNcol() == b.template getNcol<_transb>());
    assert(a.template getNcol<_transa>() == b.template getNrow<_transb>());
    internal::gemm(TransChar<_transa, _Scalar>::value, TransChar<_transb, _Scalar>::value,
                   c.getNrow(), c.getNcol(), a.template getNcol<_transa>(),
                   alpha, a.getValue(), a.getPitch(), b.getValue(), b.getPitch(),
                   beta, c.getValue(), c.getPitch());
  } else {
    assert(c.getNcol() == b.template getNcol<_transb>());
    assert(c.getNrow() == a.template getNrow<_transa>());
    assert(b.template getNrow<_transb>() == a.template getNcol<_transa>());
    internal::gemm(TransChar<_transb, _Scalar>::value, TransChar<_transa, _Scalar>::value,
                   c.getNcol(), c.getNrow(), a.template getNcol<_transa>(),
                   alpha, b.getValue(), b.getPitch(), a.getValue(), a.getPitch(),
                   beta, c.getValue(), c.getPitch());
  }
}

template <TransOption _transa = isvd::TransOption::NORMAL,
          TransOption _transb = isvd::TransOption::NORMAL, typename _Scalar, Layout _layout>
inline void gemm(
    const typename DenseMatrix<_Scalar, _layout>::ScalarType alpha,
    const DenseMatrix<_Scalar, _layout> &a,
    const DenseMatrix<_Scalar, _layout> &b,
    const typename DenseMatrix<_Scalar, _layout>::ScalarType beta,
          DenseMatrix<_Scalar, _layout> &&c
) noexcept {
  gemm<_transa, _transb>(alpha, a, b, beta, c);
}
//@}

}  // namespace blas

}  // namespace isvd

#endif  // ISVD_BLAS_ROUTINE_GEMM_HPP_
