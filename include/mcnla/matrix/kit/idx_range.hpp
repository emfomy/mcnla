////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/matrix/kit/idx_range.hpp
/// @brief   The index range class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_MATRIX_KIT_INDEX_RANGE_HPP_
#define MCNLA_MATRIX_KIT_INDEX_RANGE_HPP_

#include <mcnla/mcnla.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

  // Gets data
  inline index_t getLength() const noexcept;
};

}  // namespace mcnla

#endif  // MCNLA_MATRIX_KIT_INDEX_RANGE_HPP_
