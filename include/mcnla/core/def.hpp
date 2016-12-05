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
enum class Layout {
  COLMAJOR = 0x0,  ///< Column-major order.
  ROWMAJOR = 0x1,  ///< Row-major order.
};

static constexpr bool operator !( const Layout layout ) noexcept {
  return !static_cast<bool>(layout);
}

static constexpr Layout operator|( const Layout a, const Layout b ) noexcept {
  return static_cast<Layout>(static_cast<int>(a) | static_cast<int>(b));
}

static constexpr Layout operator&( const Layout a, const Layout b ) noexcept {
  return static_cast<Layout>(static_cast<int>(a) & static_cast<int>(b));
}

static constexpr Layout operator^( const Layout a, const Layout b ) noexcept {
  return static_cast<Layout>(static_cast<int>(a) ^ static_cast<int>(b));
}

static constexpr bool isColMajor( const Layout layout ) noexcept {
  return !(layout & Layout::ROWMAJOR);
}

static constexpr bool isRowMajor( const Layout layout ) noexcept {
  return !!(layout & Layout::ROWMAJOR);
}

static constexpr Layout changeLayout( const Layout layout ) noexcept {
  return layout ^ Layout::ROWMAJOR;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The enumeration of matrix storage layout.
///
enum class TransOption {
  NORMAL    = 0x0,           ///< No-transpose.
  TRANS     = 0x1,           ///< Transpose.
  CONJ      = 0x2,           ///< Conjugate.
  CONJTRANS = TRANS | CONJ,  ///< Conjugate transpose.
};

static constexpr bool operator !( const TransOption trans ) noexcept {
  return !static_cast<bool>(trans);
}

static constexpr TransOption operator|( const TransOption a, const TransOption b ) noexcept {
  return static_cast<TransOption>(static_cast<int>(a) | static_cast<int>(b));
}

static constexpr TransOption operator&( const TransOption a, const TransOption b ) noexcept {
  return static_cast<TransOption>(static_cast<int>(a) & static_cast<int>(b));
}

static constexpr TransOption operator^( const TransOption a, const TransOption b ) noexcept {
  return static_cast<TransOption>(static_cast<int>(a) ^ static_cast<int>(b));
}

static constexpr bool isTranspose( const TransOption trans ) noexcept {
  return !!(trans & TransOption::TRANS);
}

static constexpr bool isConjugate( const TransOption trans ) noexcept {
  return !!(trans & TransOption::CONJ);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The enumeration of matrix triangular storage.
///
enum class UploOption {
  LOWER     = 0x0, ///< Lower triangular storage.
  UPPER     = 0x1, ///< Upper triangular storage.
  UNITLOWER = 0x2, ///< Unit diagonal lower triangular storage.
  UNITUPPER = 0x3, ///< Unit diagonal upper triangular storage.
};

static constexpr bool operator!( const UploOption uplo ) noexcept {
  return !static_cast<bool>(uplo);
}

static constexpr UploOption operator|( const UploOption a, const UploOption b ) noexcept {
  return static_cast<UploOption>(static_cast<int>(a) | static_cast<int>(b));
}

static constexpr UploOption operator&( const UploOption a, const UploOption b ) noexcept {
  return static_cast<UploOption>(static_cast<int>(a) & static_cast<int>(b));
}

static constexpr UploOption operator^( const UploOption a, const UploOption b ) noexcept {
  return static_cast<UploOption>(static_cast<int>(a) ^ static_cast<int>(b));
}

static constexpr bool isLower( const UploOption uplo ) noexcept {
  return !(uplo & UploOption::UPPER);
}

static constexpr bool isUpper( const UploOption uplo ) noexcept {
  return !!(uplo & UploOption::UPPER);
}

static constexpr bool isUnitDiag( const UploOption uplo ) noexcept {
  return !!(uplo & UploOption::UNITLOWER);
}

static constexpr UploOption changeUplo( const UploOption uplo ) noexcept {
  return uplo ^ UploOption::UPPER;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The enumeration of matrix operation size.
///
enum class SideOption {
  LEFT  = 0x0,   ///< Left-hand side.
  RIGHT = 0x1,  ///< Right-hand side.
};

static constexpr bool operator!( const SideOption side ) noexcept {
  return !static_cast<bool>(side);
}

static constexpr SideOption operator|( const SideOption a, const SideOption b ) noexcept {
  return static_cast<SideOption>(static_cast<int>(a) | static_cast<int>(b));
}

static constexpr SideOption operator&( const SideOption a, const SideOption b ) noexcept {
  return static_cast<SideOption>(static_cast<int>(a) & static_cast<int>(b));
}

static constexpr SideOption operator^( const SideOption a, const SideOption b ) noexcept {
  return static_cast<SideOption>(static_cast<int>(a) ^ static_cast<int>(b));
}

static constexpr bool isLeftSide( const SideOption side ) noexcept {
  return !(side & SideOption::RIGHT);
}

static constexpr bool isRightSide( const SideOption side ) noexcept {
  return !!(side & SideOption::RIGHT);
}

static constexpr SideOption changeSide( const SideOption side ) noexcept {
  return side ^ SideOption::RIGHT;
}

}  // namespace mcnla

#endif  // MCNLA_CORE_DEF_HPP_
