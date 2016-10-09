////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/blas/routine/syrk.hpp
/// @brief   The BLAS SYRK routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_BLAS_ROUTINE_SYRK_HPP_
#define MCNLA_CORE_BLAS_ROUTINE_SYRK_HPP_

#include <mcnla/core/matrix.hpp>
#include <mcnla/core/blas/blas/syrk.hpp>

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
/// @brief  Performs a symmetric/Hermitian rank-k update.
///
template <TransOption _trans = TransOption::NORMAL, UploOption _uplo = UploOption::LOWER, typename _Scalar, Layout _layout>
inline void syrk(
    const typename DenseMatrix<_Scalar, _layout>::ScalarType alpha,
    const DenseMatrix<_Scalar, _layout> &a,
    const typename DenseMatrix<_Scalar, _layout>::ScalarType beta,
          DenseMatrix<_Scalar, _layout> &c
) noexcept {
  constexpr TransOption trans = isColMajor(_layout) ? _trans : _trans ^ TransOption::TRANS;

  assert(c.getNrow() == c.getNcol());
  assert(c.getNrow() == a.template getNrow<_trans>());

  detail::syrk(toUploChar(_uplo, _layout), toTransChar<_Scalar>(trans), c.getNrow(), a.template getNcol<_trans>(),
               alpha, a.getValue(), a.getPitch(), beta, c.getValue(), c.getPitch());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <TransOption _trans = TransOption::NORMAL, UploOption _uplo = UploOption::LOWER, typename _Scalar, Layout _layout>
inline void syrk(
    const typename DenseMatrix<_Scalar, _layout>::ScalarType alpha,
    const DenseMatrix<_Scalar, _layout> &a,
    const typename DenseMatrix<_Scalar, _layout>::ScalarType beta,
          DenseMatrix<_Scalar, _layout> &&c
) noexcept {
  syrk<_trans, _uplo>(alpha, a, beta, c);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_ROUTINE_SYRK_HPP_
