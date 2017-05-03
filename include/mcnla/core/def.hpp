////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/def.hpp
/// @brief   The core definitions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_DEF_HPP_
#define MCNLA_CORE_DEF_HPP_

#include <mcnla/def.hpp>
#include <mpi.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  core_module
/// Initializes the environment (including MPI).
///
static inline void init( int &argc, char **&argv ) {
  MPI_Init(&argc, &argv);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  core_module
/// Finalizes the environment (including MPI).
///
static inline void finalize() {
  MPI_Finalize();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  core_module
/// The enumeration of matrix transpose storage.
///
enum class Trans {
  NORMAL = 0x0,           ///< No-transpose.
  TRANS  = 0x1,           ///< Transpose.
  CONJ   = 0x2,           ///< Conjugate.
  HERM   = TRANS | CONJ,  ///< Conjugate transpose.
};

/// @ingroup  core_module
static constexpr bool operator !( const Trans trans ) noexcept {
  return !static_cast<bool>(trans);
}

/// @ingroup  core_module
static constexpr Trans operator|( const Trans a, const Trans b ) noexcept {
  return static_cast<Trans>(static_cast<int>(a) | static_cast<int>(b));
}

/// @ingroup  core_module
static constexpr Trans operator&( const Trans a, const Trans b ) noexcept {
  return static_cast<Trans>(static_cast<int>(a) & static_cast<int>(b));
}

/// @ingroup  core_module
static constexpr Trans operator^( const Trans a, const Trans b ) noexcept {
  return static_cast<Trans>(static_cast<int>(a) ^ static_cast<int>(b));
}

/// @ingroup  core_module
static constexpr bool isTrans( const Trans trans ) noexcept {
  return !!(trans & Trans::TRANS);
}

/// @ingroup  core_module
static constexpr bool isConj( const Trans trans ) noexcept {
  return !!(trans & Trans::CONJ);
}

/// @ingroup  core_module
static constexpr Trans changeTrans( const Trans trans ) noexcept {
  return trans ^ Trans::TRANS;
}

/// @ingroup  core_module
static constexpr Trans changeConj( const Trans trans ) noexcept {
  return trans ^ Trans::CONJ;
}

/// @ingroup  core_module
static constexpr Trans changeHerm( const Trans trans ) noexcept {
  return trans ^ Trans::HERM;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  core_module
/// The enumeration of matrix triangular storage.
///
enum class Uplo {
  UPPER     = 0x0,  ///< Upper triangular storage.
  LOWER     = 0x1,  ///< Lower triangular storage.
  UNITUPPER = 0x2,  ///< Unit diagonal upper triangular storage.
  UNITLOWER = 0x3,  ///< Unit diagonal lower triangular storage.
};

/// @ingroup  core_module
static constexpr bool operator!( const Uplo uplo ) noexcept {
  return !static_cast<bool>(uplo);
}

/// @ingroup  core_module
static constexpr Uplo operator|( const Uplo a, const Uplo b ) noexcept {
  return static_cast<Uplo>(static_cast<int>(a) | static_cast<int>(b));
}

/// @ingroup  core_module
static constexpr Uplo operator&( const Uplo a, const Uplo b ) noexcept {
  return static_cast<Uplo>(static_cast<int>(a) & static_cast<int>(b));
}

/// @ingroup  core_module
static constexpr Uplo operator^( const Uplo a, const Uplo b ) noexcept {
  return static_cast<Uplo>(static_cast<int>(a) ^ static_cast<int>(b));
}

/// @ingroup  core_module
static constexpr bool isLower( const Uplo uplo ) noexcept {
  return !!(uplo & Uplo::LOWER);
}

/// @ingroup  core_module
static constexpr bool isUpper( const Uplo uplo ) noexcept {
  return !(uplo & Uplo::LOWER);
}

/// @ingroup  core_module
static constexpr bool isUnitDiag( const Uplo uplo ) noexcept {
  return !!(uplo & Uplo::UNITUPPER);
}

/// @ingroup  core_module
static constexpr Uplo changeUplo( const Uplo uplo ) noexcept {
  return uplo ^ Uplo::LOWER;
}

/// @ingroup  core_module
static constexpr Uplo changeDiag( const Uplo uplo ) noexcept {
  return uplo ^ Uplo::UNITUPPER;
}

/// @ingroup  core_module
static constexpr Uplo operator^( const Uplo uplo, const Trans trans ) noexcept {
  return static_cast<Uplo>(static_cast<int>(uplo) ^ isTrans(trans));
}

/// @ingroup  core_module
static constexpr Trans operator^( const Trans trans, const Uplo uplo ) noexcept {
  return static_cast<Trans>(static_cast<int>(trans) ^ isLower(uplo));
}

}  // namespace mcnla

#endif  // MCNLA_CORE_DEF_HPP_
