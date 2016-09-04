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
/// @copydoc  isvd::blas::internal::syrk
///
//@{
template <TransOption _trans = TransOption::NORMAL,
          UploOption _uplo = UploOption::LOWER, typename _Scalar, Layout _layout>
inline void syrk(
    const _Scalar alpha,
    const DenseMatrix<_Scalar, _layout> &a,
    const _Scalar beta,
          DenseMatrix<_Scalar, _layout> &c
) noexcept {
  assert(c.getNrow() == c.getNcol());
  if ( isColMajor(_layout) ) {
    assert(c.getNrow() == a.template getNrow<_trans>());
    internal::syrk(UploChar<_uplo, _layout>::value, TransChar<_trans, _Scalar>::value,
                   c.template getNrow(), a.template getNcol<_trans>(),
                   alpha, a.getValue(), a.getPitch(), beta, c.getValue(), c.getPitch());
  } else {
    assert(c.getNcol() == a.template getNcol<_trans>());
    internal::syrk(UploChar<_uplo, _layout>::value, TransChar<_trans, _Scalar>::value,
                   c.template getNcol(), a.template getNrow<_trans>(),
                   alpha, a.getValue(), a.getPitch(), beta, c.getValue(), c.getPitch());
  }
}

template <TransOption _trans = TransOption::NORMAL,
          UploOption _uplo = UploOption::LOWER, typename _Scalar, Layout _layout>
inline void syrk(
    const _Scalar alpha,
    const DenseMatrix<_Scalar, _layout> &a,
    const _Scalar beta,
          DenseMatrix<_Scalar, _layout> &&c
) noexcept {
  syrk<_trans, _uplo>(alpha, a, beta, c);
}
//@}

}  // namespace blas

}  // namespace isvd

#endif  // ISVD_BLAS_ROUTINE_SYRK_HPP_
