////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/container/dense/dense_storage.hh
/// @brief   The definition of dense storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_CONTAINER_DENSE_DENSE_STORAGE_HH_
#define MCNLA_CORE_CONTAINER_DENSE_DENSE_STORAGE_HH_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/container/kit/array.hpp>
#include <mcnla/core/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The container namespace.
//
namespace container {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  container_dense_module
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
  inline index_t capacity() const noexcept;
  inline index_t offset() const noexcept;

  // Gets array
  inline       ValueArrayType& value() noexcept;
  inline const ValueArrayType& value() const noexcept;
  inline       ScalarType* valuePtr() noexcept;
  inline const ScalarType* valuePtr() const noexcept;

};

}  // namespace container

}  // namespace mcnla

#endif  // MCNLA_CORE_CONTAINER_DENSE_DENSE_STORAGE_HH_
