////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_base.hpp
/// @brief   The dense container interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_BASE_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_BASE_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/utility/traits.hpp>
#include <mcnla/core/matrix/dense/dense_data.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_module
/// The interface of dense container.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class DenseBase {

 private:

  using ScalarType        = typename traits::Traits<_Derived>::ScalarType;
  using ValueArrayType    = Array<ScalarType>;
  using ValueValarrayType = std::valarray<ScalarType>;
  using DataType          = DenseData<ScalarType>;

 protected:

  /// The data storage
  DataType data_;

 protected:

  // Constructors
  inline DenseBase() noexcept;
  inline DenseBase( const index_t capacity ) noexcept;
  inline DenseBase( const ValueArrayType &value ) noexcept;
  inline DenseBase( const DataType &data ) noexcept;
  inline DenseBase( const DenseBase &other ) noexcept;
  inline DenseBase( DenseBase &&other ) noexcept;

  // Operators
  inline DenseBase& operator=( const DenseBase &other ) noexcept;
  inline DenseBase& operator=( DenseBase &&other ) noexcept;

 public:

  // Gets data storage
  inline       DataType& getData() noexcept;
  inline const DataType& getData() const noexcept;

  // Gets information
  inline index_t getCapacity() const noexcept;
  inline index_t getOffset() const noexcept;

  // Gets array
  inline       ScalarType* getValue() noexcept;
  inline const ScalarType* getValue() const noexcept;
  inline       ValueArrayType& getValueArray() noexcept;
  inline const ValueArrayType& getValueArray() const noexcept;
  inline       ValueValarrayType& getValueValarray() noexcept;
  inline const ValueValarrayType& getValueValarray() const noexcept;

  // Gets derived class
  inline       _Derived& derived() noexcept;
  inline const _Derived& derived() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_BASE_HPP_
