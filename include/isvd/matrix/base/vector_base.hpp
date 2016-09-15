////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/base/vector_base.hpp
/// @brief   The vector interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_BASE_VECTOR_BASE_HPP_
#define ISVD_MATRIX_BASE_VECTOR_BASE_HPP_

#include <isvd/isvd.hpp>
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
/// The interface of vector.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class VectorBase : public TensorBase<_Derived> {

 protected:

  /// The number of entries.
  index_t length_;

 protected:

  // Constructors
  inline VectorBase() noexcept;
  inline VectorBase( const index_t length ) noexcept;
  inline VectorBase( const VectorBase &other ) noexcept;
  inline VectorBase( VectorBase &&other ) noexcept;

 public:

  // Operators
  inline VectorBase& operator=( const VectorBase &other ) noexcept;
  inline VectorBase& operator=( VectorBase &&other ) noexcept;

  // Gets information
  inline index_t getLength() const noexcept;
  inline index_t getNelem() const noexcept;
  inline index_t getSizes() const noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_BASE_VECTOR_BASE_HPP_
