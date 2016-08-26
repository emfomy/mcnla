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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The implementation namespace.
//
namespace impl {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of matrix.
///
/// @tparam  _Derived  The derived class type.
///
template <class _Derived>
class MatrixBase : public CrtpBase<_Derived, MatrixBase<_Derived>> {

 public:

  // Gets information
  inline index_t getNrow() const noexcept;
  inline index_t getNcol() const noexcept;
  inline index_t getSize() const noexcept;

  // Resize
  inline void resize( const index_t ncol, const index_t nrow ) noexcept;

};

}  // namespace impl

}  // namespace isvd

#endif  // ISVD_MATRIX_MATRIX_BASE_HPP_
