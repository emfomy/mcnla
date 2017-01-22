////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/kit/idx_range.hh
/// @brief   The definition of index range class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_KIT_INDEX_RANGE_HH_
#define MCNLA_CORE_MATRIX_KIT_INDEX_RANGE_HH_

#include <mcnla/core/matrix/def.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_module
/// The index range.
///
struct IdxRange {

  /// The beginning index.
  index_t begin;

  /// The end index.
  index_t end;

  // Constructors
  inline IdxRange( const index_t begin, const index_t end ) noexcept;

  // Operators
  inline bool operator==( const IdxRange& other ) const noexcept;
  inline bool operator!=( const IdxRange& other ) const noexcept;
  inline IdxRange operator+( const index_t scalar ) const noexcept;
  inline IdxRange operator-( const index_t scalar ) const noexcept;
  inline IdxRange operator*( const index_t scalar ) const noexcept;
  inline IdxRange operator/( const index_t scalar ) const noexcept;

  inline IdxRange& operator+=( const index_t scalar ) noexcept;
  inline IdxRange& operator-=( const index_t scalar ) noexcept;
  inline IdxRange& operator*=( const index_t scalar ) noexcept;
  inline IdxRange& operator/=( const index_t scalar ) noexcept;

  // Gets data
  inline index_t length() const noexcept;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Output to stream.
///
static inline std::ostream& operator<<( std::ostream &os, const IdxRange &range ) {
  return os << "[" << range.begin << ", " << range.end << ")";
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_KIT_INDEX_RANGE_HH_
