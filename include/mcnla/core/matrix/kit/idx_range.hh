////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/kit/idx_range.hh
/// @brief   The definition of index range class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_KIT_INDEX_RANGE_HH_
#define MCNLA_CORE_MATRIX_KIT_INDEX_RANGE_HH_

#include <mcnla/core/matrix/kit/def.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_kit_module
/// The index range.
///
struct IdxRange {

  /// The beginning index.
  index_t begin;

  /// The end index.
  index_t end;

  // Operators
  inline bool operator==( const IdxRange& other ) const noexcept;
  inline bool operator!=( const IdxRange& other ) const noexcept;
  inline IdxRange operator+( const index_t idx ) const noexcept;
  inline IdxRange operator-( const index_t idx ) const noexcept;
  inline IdxRange operator*( const index_t idx ) const noexcept;
  inline IdxRange operator/( const index_t idx ) const noexcept;

  inline IdxRange& operator+=( const index_t idx ) noexcept;
  inline IdxRange& operator-=( const index_t idx ) noexcept;
  inline IdxRange& operator*=( const index_t idx ) noexcept;
  inline IdxRange& operator/=( const index_t idx ) noexcept;

  // Gets data
  inline index_t len() const noexcept;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_kit_module
/// The full index range.
///
struct FullRange {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Output to stream.
///
static inline std::ostream& operator<<( std::ostream &os, const IdxRange &range ) {
  return os << "[" << range.begin << ", " << range.end << ")";
}

}  // namespace matrix

/// @ingroup  matrix_kit_module
/// The full index range literal.
static inline matrix::FullRange operator""_( const char*, size_t ) { return matrix::FullRange(); }

/// @ingroup  matrix_kit_module
/// The index range literal.
using I_ = matrix::IdxRange;

}  // namespace mcnla

#ifndef MCNLA_DISABLE_LITERAL
using mcnla::operator""_;
using mcnla::I_;
#endif  // MCNLA_DISABLE_LITERAL

#endif  // MCNLA_CORE_MATRIX_KIT_INDEX_RANGE_HH_
