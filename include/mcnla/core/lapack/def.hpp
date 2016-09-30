////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/lapack/def.hpp
/// @brief   The LAPACK definitions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LAPACK_DEF_HPP_
#define MCNLA_CORE_LAPACK_DEF_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/blas/def.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  lapack_module  LAPACK Module
/// @ingroup   core_module
/// @brief     The LAPACK Module
///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  lapack_module
/// The LAPACK namespace
///
namespace lapack {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The LAPACK detail namespace.
///
namespace detail {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  The job option.
///
using JobOption = char;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::blas::toTransChar
///
template<typename _Scalar>
static constexpr char toTransChar( const TransOption trans ) {
  return blas::toTransChar<_Scalar>(trans);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::blas::toUploChar
///
static constexpr char toUploChar( UploOption uplo, Layout layout ) {
  return blas::toUploChar(uplo, layout);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::blas::toDiagChar
///
static constexpr char toDiagChar( UploOption uplo ) {
  return blas::toDiagChar(uplo);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::blas::toSideChar
///
static constexpr char toSideChar( SideOption uplo, Layout layout ) {
  return blas::toSideChar(uplo, layout);
}

}  // namespace lapack

}  // namespace mcnla

#endif  // MCNLA_CORE_LAPACK_DEF_HPP_
