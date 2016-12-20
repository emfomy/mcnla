////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/kit/idx_range.hpp
/// @brief   The index range class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_KIT_INDEX_RANGE_HPP_
#define MCNLA_CORE_MATRIX_KIT_INDEX_RANGE_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>

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

  // Operators
  inline bool operator==( const IdxRange& other ) const noexcept;
  inline bool operator!=( const IdxRange& other ) const noexcept;
  inline IdxRange operator+( const index_t scalar ) const noexcept;
  inline IdxRange operator-( const index_t scalar ) const noexcept;
  inline IdxRange operator*( const index_t scalar ) const noexcept;
  inline IdxRange operator/( const index_t scalar ) const noexcept;

  // Gets data
  inline index_t getLength() const noexcept;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Print to stream.
///
static inline std::ostream& operator<<( std::ostream &out, const IdxRange &range ) {
  return out << "[" << range.begin << ", " << range.end << ")";
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_KIT_INDEX_RANGE_HPP_
