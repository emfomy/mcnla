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
#include <isvd/matrix/tensor_base.hpp>
#include <isvd/matrix/idx_range.hpp>

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
class CubeBase : public TensorBase<_Derived> {

 private:

  static constexpr Layout layout = Traits<_Derived>::layout;

 protected:

  /// The number of rows.
  index_t nrow_;

  /// The number of columns.
  index_t ncol_;

  /// The number of pages.
  index_t npage_;

  /// The leading size.
  index_t &size1_ = isColMajor(layout) ? nrow_ : ncol_;

  /// The second size.
  index_t &size2_ = isColMajor(layout) ? ncol_ : nrow_;

 public:

  // Constructors
  CubeBase() noexcept;
  CubeBase( const index_t nrow, const index_t ncol, const index_t npage ) noexcept;
  CubeBase( const std::tuple<index_t, index_t, index_t> sizes ) noexcept;
  CubeBase( const CubeBase &other ) noexcept;
  CubeBase( CubeBase &&other ) noexcept;

  // Operators
  inline CubeBase& operator=( const CubeBase &other ) noexcept;
  inline CubeBase& operator=( CubeBase &&other ) noexcept;

  // Gets information
  template <TransOption _trans = TransOption::NORMAL> inline index_t getNrow() const noexcept;
  template <TransOption _trans = TransOption::NORMAL> inline index_t getNcol() const noexcept;
  inline index_t getSize1() const noexcept;
  inline index_t getSize2() const noexcept;
  inline index_t getNpage() const noexcept;
  inline index_t getNelem() const noexcept;
  inline std::tuple<index_t, index_t, index_t> getSizes() const noexcept;

 protected:

  // Converts range
  inline IdxRange convertRowRange( const IdxRange range ) const noexcept;
  inline IdxRange convertColRange( const IdxRange range ) const noexcept;
  inline IdxRange convertPageRange( const IdxRange range ) const noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_CUBE_BASE_HPP_
