////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/blas/routine/symm.hpp
/// @brief   The BLAS SYMM routine.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_BLAS_ROUTINE_SYMM_HPP_
#define ISVD_BLAS_ROUTINE_SYMM_HPP_

#include <isvd/matrix.hpp>
#include <isvd/blas/blas/symm.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The BLAS namespace
//
namespace blas {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes a matrix-matrix product where one input matrix is symmetric/Hermitian.
///
//@{
template <SideOption _side, UploOption _uplo = UploOption::LOWER, typename _Scalar, Layout _layout>
inline void symm(
    const typename DenseMatrix<_Scalar, _layout>::ScalarType alpha,
    const DenseMatrix<_Scalar, _layout> &a,
    const DenseMatrix<_Scalar, _layout> &b,
    const typename DenseMatrix<_Scalar, _layout>::ScalarType beta,
          DenseMatrix<_Scalar, _layout> &c
) noexcept {
  assert(a.getNrow()  == a.getNcol());
  assert(b.getSizes() == c.getSizes());
  if ( isLeftSide(_side) ) {
    assert(a.getNrow()  == c.getNrow());
  } else {
    assert(a.getNcol()  == c.getNcol());
  }

  detail::symm(SideChar<_side, _layout>::value, UploChar<_uplo, _layout>::value,
               c.template getSize<0>(), c.template getSize<1>(),
               alpha, a.getValue(), a.getPitch(), b.getValue(), b.getPitch(), beta, c.getValue(), c.getPitch());
}

template <SideOption _side, UploOption _uplo = UploOption::LOWER, typename _Scalar, Layout _layout>
inline void symm(
    const typename DenseMatrix<_Scalar, _layout>::ScalarType alpha,
    const DenseMatrix<_Scalar, _layout> &a,
    const DenseMatrix<_Scalar, _layout> &b,
    const typename DenseMatrix<_Scalar, _layout>::ScalarType beta,
          DenseMatrix<_Scalar, _layout> &&c
) noexcept {
  symm<_side, _uplo>(alpha, a, b, beta, c);
}
//@}

}  // namespace blas

}  // namespace isvd

#endif  // ISVD_BLAS_ROUTINE_SYMM_HPP_
