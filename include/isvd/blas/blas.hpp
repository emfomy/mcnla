////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/blas/blas.hpp
/// @brief   The BLAS definitions.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_BLAS_BLAS_HPP_
#define ISVD_BLAS_BLAS_HPP_

#include <isvd/isvd.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The BLAS namespace
//
namespace blas {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert transpose option to char.
///
template <TransOption _trans, typename _Scalar>
struct TransChar {
  static const char value = !isTranspose(_trans)
      ? ((!!isConjugate(_trans) && isvd::internal::ScalarTraits<_Scalar>::is_complex) ? '?' : 'N')
      : ((!!isConjugate(_trans) && isvd::internal::ScalarTraits<_Scalar>::is_complex) ? 'C' : 'T');
  static_assert(value != '?', "Conjugate no-transpose is nor supported!");
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert upper/lower option to char.
///
template <UploOption _uplo, Layout _layout>
struct UploChar {
  static const char value = (isLower(_uplo) ^ isRowMajor(_layout)) ? 'L' : 'U';
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert diagonal option to char.
///
template <UploOption _uplo>
struct DiagChar {
  static const char value = !isUnitDiag(_uplo) ? 'N' : 'U';
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert side option to char.
///
template <SideOption _side, Layout _layout>
struct SideChar {
  static const char value = (isLeftSide(_side) ^ isRowMajor(_layout)) ? 'L' : 'R';
};

}  // namespace blas

}  // namespace isvd

#endif  // ISVD_BLAS_BLAS_HPP_
