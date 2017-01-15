////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/container/kit/idx_range.hh
/// @brief   The definition of index range class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_CONTAINER_KIT_INDEX_RANGE_HH_
#define MCNLA_CORE_CONTAINER_KIT_INDEX_RANGE_HH_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The container namespace.
//
namespace container {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  container_module
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

  // Gets data
  inline index_t length() const noexcept;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Print to stream.
///
static inline std::ostream& operator<<( std::ostream &out, const IdxRange &range ) {
  return out << "[" << range.begin << ", " << range.end << ")";
}

}  // namespace container

}  // namespace mcnla

#endif  // MCNLA_CORE_CONTAINER_KIT_INDEX_RANGE_HH_
