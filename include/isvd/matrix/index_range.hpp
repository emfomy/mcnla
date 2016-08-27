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

  /// The last index.
  static const index_t END = -1;

  /// The full-range index.
  /// @note It can be represented by @c {} since C++14.
  static const IndexRange FULL;

  /// The starting index.
#if __cplusplus < 201402L
  index_t start;
#else
  index_t start = 0;
#endif

  /// The ending index.
#if __cplusplus < 201402L
  index_t end;
#else
  index_t end = END;
#endif

  // Operators
  bool operator==( const IndexRange& other ) const noexcept;

  // Gets data
  inline index_t getLength() const noexcept;

  // Converts range
  inline IndexRange convert( const index_t last ) const noexcept;
};

const IndexRange IndexRange::FULL = {0, IndexRange::END};

}  // namespace isvd

#endif  // ISVD_MATRIX_INDEX_RANGE_HPP_
