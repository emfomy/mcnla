////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/matrix_base.hpp
/// @brief   The matrix interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_MATRIX_BASE_HPP_
#define ISVD_MATRIX_MATRIX_BASE_HPP_

#include <isvd/isvd.hpp>
#include <isvd/utility/crtp.hpp>
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
/// @tparam  _Derived  The derived class type.
///
template <class _Derived>
class MatrixBase : public CrtpBase<_Derived, MatrixBase<_Derived>> {

 public:

  // Gets information
  template <TransOption _trans = TransOption::NORMAL> inline index_t getNrow() const noexcept;
  template <TransOption _trans = TransOption::NORMAL> inline index_t getNcol() const noexcept;
  inline index_t getSize() const noexcept;

  // Resizes
  inline void resize( const index_t ncol, const index_t nrow ) noexcept;

 protected:

  // Converts range
  inline IndexRange convertRowRange( const IndexRange range ) const noexcept;
  inline IndexRange convertColRange( const IndexRange range ) const noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_MATRIX_BASE_HPP_
