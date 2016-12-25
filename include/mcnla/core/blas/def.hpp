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
#include <mcnla/core/matrix/def.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  blas_module  BLAS Module
/// @ingroup   core_module
/// @brief     The BLAS Module
///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  blas1_module  BLAS 1 Module
/// @ingroup   blas_module
/// @brief     The BLAS 1 Module
///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  blas2_module  BLAS 2 Module
/// @ingroup   blas_module
/// @brief     The BLAS 2 Module
///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  blas3_module  BLAS 3 Module
/// @ingroup   blas_module
/// @brief     The BLAS 3 Module
///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  blas0_module  BLAS-Like Module
/// @ingroup   blas_module
/// @brief     The BLAS-Like Module
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

using namespace matrix;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The BLAS detail namespace.
///
namespace detail {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert transpose option to char.
///
template<typename _Scalar>
static constexpr char toTransChar( const Trans trans ) {
  return !isTrans(trans) ? ((isConj(trans) && traits::ScalarTraits<_Scalar>::is_complex) ? 'R' : 'N')
                         : ((isConj(trans) && traits::ScalarTraits<_Scalar>::is_complex) ? 'C' : 'T');
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert upper/lower option to char.
///
static constexpr char toUploChar( Uplo uplo ) {
  return isLower(uplo) ? 'L' : 'U';
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert diagonal option to char.
///
static constexpr char toDiagChar( Uplo uplo ) {
  return !isUnitDiag(uplo) ? 'N' : 'U';
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert side option to char.
///
static constexpr char toSideChar( Side side ) {
  return isLeftSide(side) ? 'L' : 'R';
}

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_DEF_HPP_
