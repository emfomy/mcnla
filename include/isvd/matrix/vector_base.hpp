////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/vector_base.hpp
/// @brief   The vector interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_VECTOR_BASE_HPP_
#define ISVD_MATRIX_VECTOR_BASE_HPP_

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
/// The interface of vector.
///
/// @tparam  _Derived  The derived class type.
///
template <class _Derived>
class VectorBase {

 protected:

  /// The number of entries.
  index_t length_;

 public:

  // Constructors
  VectorBase() noexcept;
  VectorBase( const index_t length ) noexcept;

  // Gets information
  inline index_t getLength() const noexcept;
  inline index_t getSize() const noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_VECTOR_BASE_HPP_
