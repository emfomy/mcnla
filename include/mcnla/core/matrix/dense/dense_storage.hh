////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_storage.hh
/// @brief   The definition of dense storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_STORAGE_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_STORAGE_HH_

#include <mcnla/core/matrix/def.hpp>
#include <mcnla/core/matrix/kit/array.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_module_detail
/// The dense storage.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
class DenseStorage {

 private:

  using ScalarType   = _Scalar;
  using ValArrayType = Array<ScalarType>;

 protected:

  /// The data storage
  ValArrayType val_;

 protected:

  // Constructors
  inline DenseStorage() noexcept;
  inline DenseStorage( const index_t capacity ) noexcept;
  inline DenseStorage( const ValArrayType &val ) noexcept;
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
  inline       ValArrayType& val() noexcept;
  inline const ValArrayType& val() const noexcept;
  inline       ScalarType* valPtr() noexcept;
  inline const ScalarType* valPtr() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_STORAGE_HH_
