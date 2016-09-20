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
/// @copydoc  isvd::blas::detail::symm
///
//@{
template <SideOption _side,
          UploOption _uplo = UploOption::LOWER, typename _Scalar, Layout _layout>
inline void symm(
    const typename DenseMatrix<_Scalar, _layout>::ScalarType alpha,
    const DenseMatrix<_Scalar, _layout> &a,
    const DenseMatrix<_Scalar, _layout> &b,
    const typename DenseMatrix<_Scalar, _layout>::ScalarType beta,
          DenseMatrix<_Scalar, _layout> &c
) noexcept {
  if ( isColMajor(_layout) ) {
    if ( isLeftSide(_side) ) {
      assert(a.getNrow()  == a.getNcol());
      assert(a.getNrow()  == c.getNrow());
      assert(b.getSizes() == c.getSizes());
    } else {
      assert(b.getNrow()  == b.getNcol());
      assert(b.getNcol()  == c.getNcol());
      assert(a.getSizes() == c.getSizes());
    }
    detail::symm(SideChar<_side, _layout>::value, UploChar<_uplo, _layout>::value, c.getNrow(), c.getNcol(),
                   alpha, a.getValue(), a.getPitch(), b.getValue(), b.getPitch(),
                   beta, c.getValue(), c.getPitch());
  } else {
    if ( isRightSide(_side) ) {
      assert(b.getNcol()  == b.getNrow());
      assert(b.getNcol()  == c.getNcol());
      assert(a.getSizes() == c.getSizes());
    } else {
      assert(a.getNcol()  == a.getNrow());
      assert(a.getNrow()  == c.getNrow());
      assert(b.getSizes() == c.getSizes());
    }
    detail::symm(SideChar<_side, _layout>::value, UploChar<_uplo, _layout>::value, c.getNcol(), c.getNrow(),
                   alpha, b.getValue(), b.getPitch(), a.getValue(), a.getPitch(),
                   beta, c.getValue(), c.getPitch());
  }
}

template <SideOption _side,
          UploOption _uplo = UploOption::LOWER, typename _Scalar, Layout _layout>
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
