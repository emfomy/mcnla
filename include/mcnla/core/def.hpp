////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/def.hpp
/// @brief   The core definitions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_DEF_HPP_
#define MCNLA_CORE_DEF_HPP_

#include <mcnla/def.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  core_module  Core Module
/// @brief     The Core Module
///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The enumeration of matrix storage layout.
///
enum class Trans {
  NORMAL    = 0x0,           ///< No-transpose.
  TRANS     = 0x1,           ///< Transpose.
  CONJ      = 0x2,           ///< Conjugate.
  CONJTRANS = TRANS | CONJ,  ///< Conjugate transpose.
};

static constexpr bool operator !( const Trans trans ) noexcept {
  return !static_cast<bool>(trans);
}

static constexpr Trans operator|( const Trans a, const Trans b ) noexcept {
  return static_cast<Trans>(static_cast<int>(a) | static_cast<int>(b));
}

static constexpr Trans operator&( const Trans a, const Trans b ) noexcept {
  return static_cast<Trans>(static_cast<int>(a) & static_cast<int>(b));
}

static constexpr Trans operator^( const Trans a, const Trans b ) noexcept {
  return static_cast<Trans>(static_cast<int>(a) ^ static_cast<int>(b));
}

static constexpr bool isTrans( const Trans trans ) noexcept {
  return !!(trans & Trans::TRANS);
}

static constexpr bool isConj( const Trans trans ) noexcept {
  return !!(trans & Trans::CONJ);
}

static constexpr Trans changeTrans( const Trans trans ) noexcept {
  return trans ^ Trans::TRANS;
}

static constexpr Trans changeConj( const Trans trans ) noexcept {
  return trans ^ Trans::CONJ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The enumeration of matrix triangular storage.
///
enum class Uplo {
  UPPER     = 0x0,  ///< Upper triangular storage.
  LOWER     = 0x1,  ///< Lower triangular storage.
  UNITUPPER = 0x2,  ///< Unit diagonal upper triangular storage.
  UNITLOWER = 0x3,  ///< Unit diagonal lower triangular storage.
};

static constexpr bool operator!( const Uplo uplo ) noexcept {
  return !static_cast<bool>(uplo);
}

static constexpr Uplo operator|( const Uplo a, const Uplo b ) noexcept {
  return static_cast<Uplo>(static_cast<int>(a) | static_cast<int>(b));
}

static constexpr Uplo operator&( const Uplo a, const Uplo b ) noexcept {
  return static_cast<Uplo>(static_cast<int>(a) & static_cast<int>(b));
}

static constexpr Uplo operator^( const Uplo a, const Uplo b ) noexcept {
  return static_cast<Uplo>(static_cast<int>(a) ^ static_cast<int>(b));
}

static constexpr bool isLower( const Uplo uplo ) noexcept {
  return !!(uplo & Uplo::LOWER);
}

static constexpr bool isUpper( const Uplo uplo ) noexcept {
  return !(uplo & Uplo::LOWER);
}

static constexpr bool isUnitDiag( const Uplo uplo ) noexcept {
  return !!(uplo & Uplo::UNITUPPER);
}

static constexpr Uplo changeUplo( const Uplo uplo ) noexcept {
  return uplo ^ Uplo::LOWER;
}

static constexpr Uplo changeDiag( const Uplo uplo ) noexcept {
  return uplo ^ Uplo::UNITUPPER;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The enumeration of matrix operation side.
///
enum class Side {
  LEFT  = 0x0,  ///< Left-hand side.
  RIGHT = 0x1,  ///< Right-hand side.
};

static constexpr bool operator!( const Side side ) noexcept {
  return !static_cast<bool>(side);
}

static constexpr Side operator|( const Side a, const Side b ) noexcept {
  return static_cast<Side>(static_cast<int>(a) | static_cast<int>(b));
}

static constexpr Side operator&( const Side a, const Side b ) noexcept {
  return static_cast<Side>(static_cast<int>(a) & static_cast<int>(b));
}

static constexpr Side operator^( const Side a, const Side b ) noexcept {
  return static_cast<Side>(static_cast<int>(a) ^ static_cast<int>(b));
}

static constexpr bool isLeftSide( const Side side ) noexcept {
  return !(side & Side::RIGHT);
}

static constexpr bool isRightSide( const Side side ) noexcept {
  return !!(side & Side::RIGHT);
}

static constexpr Side changeSide( const Side side ) noexcept {
  return side ^ Side::RIGHT;
}

}  // namespace mcnla

#endif  // MCNLA_CORE_DEF_HPP_
