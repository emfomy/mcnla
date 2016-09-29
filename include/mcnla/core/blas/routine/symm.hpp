////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/blas/routine/symm.hpp
/// @brief   The BLAS SYMM routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_BLAS_ROUTINE_SYMM_HPP_
#define MCNLA_CORE_BLAS_ROUTINE_SYMM_HPP_

#include <mcnla/core/matrix.hpp>
#include <mcnla/core/blas/blas/symm.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

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

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_ROUTINE_SYMM_HPP_
