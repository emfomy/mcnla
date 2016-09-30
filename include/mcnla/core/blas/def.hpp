////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/blas/def.hpp
/// @brief   The BLAS definitions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_BLAS_DEF_HPP_
#define MCNLA_CORE_BLAS_DEF_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  blas_module  BLAS Module
/// @ingroup   core_module
/// @brief     The BLAS Module
///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The BLAS namespace
/// @ingroup  blas_module
///
namespace blas {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The BLAS detail namespace.
///
namespace detail {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert transpose option to char.
///
template<typename _Scalar>
static constexpr char toTransChar( const TransOption trans ) {
  return !isTranspose(trans) ? ((!!isConjugate(trans) && traits::ScalarTraits<_Scalar>::is_complex) ? '?' : 'N')
                             : ((!!isConjugate(trans) && traits::ScalarTraits<_Scalar>::is_complex) ? 'C' : 'T');
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert upper/lower option to char.
///
static constexpr char toUploChar( UploOption uplo, Layout layout ) {
  return (isLower(uplo) ^ isRowMajor(layout)) ? 'L' : 'U';
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert diagonal option to char.
///
static constexpr char toDiagChar( UploOption uplo ) {
  return !isUnitDiag(uplo) ? 'N' : 'U';
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert side option to char.
///
static constexpr char toSideChar( SideOption side, Layout layout ) {
  return (isLeftSide(side) ^ isRowMajor(layout)) ? 'L' : 'R';
}

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_DEF_HPP_
