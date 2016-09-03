////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/matrix_base.hpp
/// @brief   The matrix interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_MATRIX_BASE_HPP_
#define ISVD_MATRIX_MATRIX_BASE_HPP_

#include <utility>
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
/// The interface of matrix.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class MatrixBase {

 private:

  static const Layout layout = Traits<_Derived>::layout;

 protected:

  /// The number of rows.
  index_t nrow_;

  /// The number of columns.
  index_t ncol_;

  /// The size of major dimension.
  index_t &dim1_ = isColMajor(layout) ? nrow_ : ncol_;

  /// The size of minor dimension.
  index_t &dim2_ = isColMajor(layout) ? ncol_ : nrow_;

 public:

  // Constructors
  MatrixBase() noexcept;
  MatrixBase( const index_t nrow, const index_t ncol ) noexcept;
  MatrixBase( const std::pair<index_t, index_t> sizes ) noexcept;
  MatrixBase( const MatrixBase &other ) noexcept;
  MatrixBase( MatrixBase &&other ) noexcept;

  // Operators
  inline MatrixBase& operator=( const MatrixBase &other ) noexcept;
  inline MatrixBase& operator=( MatrixBase &&other ) noexcept;

  // Gets information
  template <TransOption _trans = TransOption::NORMAL> inline index_t getNrow() const noexcept;
  template <TransOption _trans = TransOption::NORMAL> inline index_t getNcol() const noexcept;
  inline index_t getSize() const noexcept;
  inline std::pair<index_t, index_t> getSizes() const noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_MATRIX_BASE_HPP_
