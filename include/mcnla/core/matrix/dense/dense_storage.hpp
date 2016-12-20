////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_storage.hpp
/// @brief   The dense storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_STORAGE_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_STORAGE_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/matrix/kit/array.hpp>
#include <mcnla/core/utility/traits.hpp>

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
/// The dense storage.
///
/// @tparam  _Scalar  The scalar type.
///
template <class _Scalar>
class DenseStorage {

 private:

  using ScalarType     = _Scalar;
  using ValueArrayType = Array<ScalarType>;

 protected:

  /// The data storage
  ValueArrayType value_;

 protected:

  // Constructors
  inline DenseStorage() noexcept;
  inline DenseStorage( const index_t capacity ) noexcept;
  inline DenseStorage( const ValueArrayType &value ) noexcept;
  inline DenseStorage( const DenseStorage &other ) noexcept;
  inline DenseStorage( DenseStorage &&other ) noexcept;

  // Operators
  inline DenseStorage& operator=( const DenseStorage &other ) noexcept;
  inline DenseStorage& operator=( DenseStorage &&other ) noexcept;

 public:

  // Gets information
  inline bool    isEmpty() const noexcept;
  inline index_t getCapacity() const noexcept;
  inline index_t getOffset() const noexcept;

  // Gets array
  inline       ValueArrayType& getValue() noexcept;
  inline const ValueArrayType& getValue() const noexcept;
  inline       ScalarType* getValuePtr() noexcept;
  inline const ScalarType* getValuePtr() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_STORAGE_HPP_
