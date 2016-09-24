////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/blas/routine/syrk.hpp
/// @brief   The BLAS SYRK routine.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_BLAS_ROUTINE_SYRK_HPP_
#define ISVD_BLAS_ROUTINE_SYRK_HPP_

#include <isvd/matrix.hpp>
#include <isvd/blas/blas/syrk.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The BLAS namespace
//
namespace blas {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Performs a symmetric/Hermitian rank-k update.
///
//@{
template <TransOption _trans = TransOption::NORMAL,
          UploOption _uplo = UploOption::LOWER, typename _Scalar, Layout _layout>
inline void syrk(
    const typename DenseMatrix<_Scalar, _layout>::ScalarType alpha,
    const DenseMatrix<_Scalar, _layout> &a,
    const typename DenseMatrix<_Scalar, _layout>::ScalarType beta,
          DenseMatrix<_Scalar, _layout> &c
) noexcept {
  const TransOption trans = isColMajor(_layout) ? _trans : _trans ^ TransOption::TRANS;

  assert(c.getNrow() == c.getNcol());
  assert(c.getNrow() == a.template getNrow<_trans>());

  detail::syrk(UploChar<_uplo, _layout>::value, TransChar<trans, _Scalar>::value,
                 c.getNrow(), a.template getNcol<trans>(),
                 alpha, a.getValue(), a.getPitch(), beta, c.getValue(), c.getPitch());
}

template <TransOption _trans = TransOption::NORMAL,
          UploOption _uplo = UploOption::LOWER, typename _Scalar, Layout _layout>
inline void syrk(
    const typename DenseMatrix<_Scalar, _layout>::ScalarType alpha,
    const DenseMatrix<_Scalar, _layout> &a,
    const typename DenseMatrix<_Scalar, _layout>::ScalarType beta,
          DenseMatrix<_Scalar, _layout> &&c
) noexcept {
  syrk<_trans, _uplo>(alpha, a, beta, c);
}
//@}

}  // namespace blas

}  // namespace isvd

#endif  // ISVD_BLAS_ROUTINE_SYRK_HPP_
