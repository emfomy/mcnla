////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/base/matrix_base.hpp
/// @brief   The matrix interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_BASE_MATRIX_BASE_HPP_
#define ISVD_MATRIX_BASE_MATRIX_BASE_HPP_

#include <isvd/isvd.hpp>
#include <utility>
#include <isvd/utility/traits.hpp>
#include <isvd/matrix/base/tensor_base.hpp>
#include <isvd/matrix/kit/idx_range.hpp>

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
class MatrixBase : public TensorBase<_Derived> {

 private:

  static constexpr Layout layout = Traits<_Derived>::layout;

 protected:

  /// The number of rows.
  index_t nrow_;

  /// The number of columns.
  index_t ncol_;

  /// The leading size.
  index_t &size1_ = isColMajor(layout) ? nrow_ : ncol_;

  /// The second size.
  index_t &size2_ = isColMajor(layout) ? ncol_ : nrow_;

 protected:

  // Constructors
  inline MatrixBase() noexcept;
  inline MatrixBase( const index_t nrow, const index_t ncol ) noexcept;
  inline MatrixBase( const std::pair<index_t, index_t> sizes ) noexcept;
  inline MatrixBase( const MatrixBase &other ) noexcept;
  inline MatrixBase( MatrixBase &&other ) noexcept;

 public:

  // Operators
  inline MatrixBase& operator=( const MatrixBase &other ) noexcept;
  inline MatrixBase& operator=( MatrixBase &&other ) noexcept;

  // Gets information
  template <TransOption _trans = TransOption::NORMAL> inline index_t getNrow() const noexcept;
  template <TransOption _trans = TransOption::NORMAL> inline index_t getNcol() const noexcept;
  inline index_t getSize1() const noexcept;
  inline index_t getSize2() const noexcept;
  inline index_t getNelem() const noexcept;
  inline std::pair<index_t, index_t> getSizes() const noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_BASE_MATRIX_BASE_HPP_