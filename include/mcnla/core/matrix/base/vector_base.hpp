////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/base/vector_base.hpp
/// @brief   The vector interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_BASE_VECTOR_BASE_HPP_
#define MCNLA_CORE_MATRIX_BASE_VECTOR_BASE_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/utility/traits.hpp>
#include <mcnla/core/matrix/base/tensor_base.hpp>
#include <mcnla/core/matrix/kit/idx_range.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of vector type.
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

  // Operators
  inline VectorBase& operator=( const VectorBase &other ) noexcept;
  inline VectorBase& operator=( VectorBase &&other ) noexcept;

 public:

  // Gets information
  inline index_t getLength() const noexcept;
  template <index_t _dim> inline index_t getSize() const noexcept;
  inline index_t getNelem() const noexcept;
  inline index_t getSizes() const noexcept;

  // Gets derived class
  inline       _Derived& derived() noexcept;
  inline const _Derived& derived() const noexcept;

};

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_BASE_VECTOR_BASE_HPP_
