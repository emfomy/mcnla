////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/cube_base.hpp
/// @brief   The cube interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_CUBE_BASE_HPP_
#define ISVD_MATRIX_CUBE_BASE_HPP_

#include <tuple>
#include <isvd/isvd.hpp>
#include <isvd/utility/traits.hpp>
#include <isvd/matrix/index_range.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of cube.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class CubeBase {

 private:

  static const Layout layout = Traits<_Derived>::layout;

 protected:

  /// The number of rows.
  index_t nrow_;

  /// The number of columns.
  index_t ncol_;

  /// The number of pages.
  index_t npage_;

  /// The size of major dimension.
  index_t &dim1_ = isColMajor(layout) ? nrow_ : ncol_;

  /// The size of minor dimension.
  index_t &dim2_ = isColMajor(layout) ? ncol_ : nrow_;

 public:

  // Constructors
  CubeBase() noexcept;
  CubeBase( const index_t nrow, const index_t ncol, const index_t npage ) noexcept;
  CubeBase( const CubeBase &other ) noexcept;
  CubeBase( CubeBase &&other ) noexcept;

  // Operators
  inline CubeBase& operator=( const CubeBase &other ) noexcept;
  inline CubeBase& operator=( CubeBase &&other ) noexcept;

  // Gets information
  template <TransOption _trans = TransOption::NORMAL> inline index_t getNrow() const noexcept;
  template <TransOption _trans = TransOption::NORMAL> inline index_t getNcol() const noexcept;
  inline index_t getNpage() const noexcept;
  inline index_t getSize() const noexcept;
  inline std::tuple<index_t, index_t, index_t> getSizes() const noexcept;

 protected:

  // Converts range
  inline IndexRange convertRowRange( const IndexRange range ) const noexcept;
  inline IndexRange convertColRange( const IndexRange range ) const noexcept;
  inline IndexRange convertPageRange( const IndexRange range ) const noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_CUBE_BASE_HPP_
