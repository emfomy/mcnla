////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/cube_base.hpp
/// @brief   The cube interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_CUBE_BASE_HPP_
#define ISVD_MATRIX_CUBE_BASE_HPP_

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
/// The interface of cube.
///
/// @tparam  _Derived  The derived class type.
///
template <class _Derived>
class CubeBase : public CrtpBase<_Derived, CubeBase<_Derived>> {

 public:

  // Gets information
  inline index_t getNrow() const noexcept;
  inline index_t getNcol() const noexcept;
  inline index_t getNpage() const noexcept;
  inline index_t getSize() const noexcept;

  // Resizes
  inline void resize( const index_t ncol, const index_t nrow, const index_t npage ) noexcept;

 protected:

  // Converts range
  inline IndexRange convertRowRange( const IndexRange range ) const noexcept;
  inline IndexRange convertColRange( const IndexRange range ) const noexcept;
  inline IndexRange convertPageRange( const IndexRange range ) const noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_CUBE_BASE_HPP_
