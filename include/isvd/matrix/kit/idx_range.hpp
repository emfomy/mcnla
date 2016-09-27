////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/kit/idx_range.hpp
/// @brief   The index range class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef ISVD_MATRIX_KIT_INDEX_RANGE_HPP_
#define ISVD_MATRIX_KIT_INDEX_RANGE_HPP_

#include <isvd/isvd.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

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

}  // namespace isvd

#endif  // ISVD_MATRIX_KIT_INDEX_RANGE_HPP_
