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
/// @ingroup  blas3_module
/// @brief  Computes a matrix-matrix product where one input matrix is symmetric/Hermitian.
///
template <Side _side, Uplo _uplo = Uplo::LOWER, typename _Scalar, Layout _layout>
inline void symm(
    const typename DenseMatrix<_Scalar, _layout>::ScalarType alpha,
    const DenseMatrix<_Scalar, _layout> &a,
    const DenseMatrix<_Scalar, _layout> &b,
    const typename DenseMatrix<_Scalar, _layout>::ScalarType beta,
          DenseMatrix<_Scalar, _layout> &c
) noexcept {
  mcnla_assert_eq(a.getNrow(),  a.getNcol());
  mcnla_assert_eq(b.getSizes(), c.getSizes());
  if ( isLeftSide(_side) ) {
    mcnla_assert_eq(a.getNrow(), c.getNrow());
  } else {
    mcnla_assert_eq(a.getNcol(), c.getNcol());
  }

  detail::symm(toSideChar(_side, _layout), toUploChar(_uplo, _layout), c.template getSize<0>(), c.template getSize<1>(),
               alpha, a.getValuePtr(), a.getPitch(), b.getValuePtr(), b.getPitch(), beta, c.getValuePtr(), c.getPitch());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <Side _side, Uplo _uplo = Uplo::LOWER, typename _Scalar, Layout _layout>
inline void symm(
    const typename DenseMatrix<_Scalar, _layout>::ScalarType alpha,
    const DenseMatrix<_Scalar, _layout> &a,
    const DenseMatrix<_Scalar, _layout> &b,
    const typename DenseMatrix<_Scalar, _layout>::ScalarType beta,
          DenseMatrix<_Scalar, _layout> &&c
) noexcept {
  symm<_side, _uplo>(alpha, a, b, beta, c);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_ROUTINE_SYMM_HPP_
