////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/def.hpp
/// @brief   The linear algebra definitions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DEF_HPP_
#define MCNLA_CORE_LA_DEF_HPP_

#include <mcnla/core/def.hpp>
#include <mcnla/core/matrix/def.hpp>
#include <mcnla/core/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_module
/// The linear algebra namespace.
///
namespace la {

using namespace matrix;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The linear algebra detail namespace.
///
namespace detail {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert transpose option to char.
///
template <typename _Val>
static constexpr char toTransChar( const Trans trans ) {
  return !isTrans(trans) ? ((isConj(trans) && traits::ValTraits<_Val>::is_complex) ? 'R' : 'N')
                         : ((isConj(trans) && traits::ValTraits<_Val>::is_complex) ? 'C' : 'T');
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert upper/lower option to char.
///
static constexpr char toUploChar( Uplo uplo, Trans trans = Trans::NORMAL ) {
  return (isLower(uplo) ^ isTrans(trans)) ? 'L' : 'U';
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert diagonal option to char.
///
static constexpr char toDiagChar( Uplo uplo ) {
  return !isUnitDiag(uplo) ? 'N' : 'U';
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  The job option.
///
using JobOption = char;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_module
/// The enumeration VECT used in LAPACK.
///
enum class Vect {
  Q  = 0x0,     ///< Matrix Q
  P  = 0x1,     ///< Matrix P
  QT = 0x2,     ///< Matrix Qt
  PT = P | QT,  ///< Matrix Pt
};

/// @ingroup  la_module
static constexpr bool operator !( const Vect vect ) noexcept {
  return !static_cast<bool>(vect);
}

/// @ingroup  la_module
static constexpr Vect operator|( const Vect a, const Vect b ) noexcept {
  return static_cast<Vect>(static_cast<int>(a) | static_cast<int>(b));
}

/// @ingroup  la_module
static constexpr Vect operator&( const Vect a, const Vect b ) noexcept {
  return static_cast<Vect>(static_cast<int>(a) & static_cast<int>(b));
}

/// @ingroup  la_module
static constexpr Vect operator^( const Vect a, const Vect b ) noexcept {
  return static_cast<Vect>(static_cast<int>(a) ^ static_cast<int>(b));
}

/// @ingroup  la_module
static constexpr bool isQ( const Vect vect ) noexcept {
  return !(vect & Vect::P);
}

/// @ingroup  la_module
static constexpr bool isP( const Vect vect ) noexcept {
  return !!(vect & Vect::P);
}

/// @ingroup  la_module
static constexpr bool isTrans( const Vect vect ) noexcept {
  return !!(vect & Vect::QT);
}

/// @ingroup  la_module
static constexpr Vect changeQP( const Vect vect ) noexcept {
  return vect ^ Vect::P;
}

/// @ingroup  la_module
static constexpr Vect changeTrans( const Vect vect ) noexcept {
  return vect ^ Vect::QT;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert VECT option to char.
///
//@{
static constexpr char toVectChar( const Vect vect ) {
  return isQ(vect) ? 'Q' : 'P';
}

static constexpr char toTransChar( const Vect vect ) {
  return !isTrans(vect) ? 'N' : 'T';
}
//@}

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DEF_HPP
