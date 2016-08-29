////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/index_range.hpp
/// @brief   The index range class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_INDEX_RANGE_HPP_
#define ISVD_MATRIX_INDEX_RANGE_HPP_

#include <initializer_list>
#include <isvd/isvd.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The index range.
///
struct IndexRange {

  /// The starting index.
  index_t start;

  /// The ending index.
  index_t end;

  // Operators
  inline bool operator==( const IndexRange& other ) const noexcept;
  inline bool operator!=( const IndexRange& other ) const noexcept;

  // Gets data
  inline index_t getLength() const noexcept;
};

}  // namespace isvd

#endif  // ISVD_MATRIX_INDEX_RANGE_HPP_
