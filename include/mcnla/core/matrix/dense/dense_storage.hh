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
/// The dense storage.
///
/// @tparam  _Val    The value type.
/// @tparam  _Array  The array template.
///
template <typename _Val, template <typename> class _Array = Array>
class DenseStorage {

 private:

  using ValType      = _Val;
  using ValArrayType = _Array<_Val>;

 protected:

  /// The data storage
  ValArrayType val_;

 protected:

  // Constructors
  inline DenseStorage() noexcept;
  inline DenseStorage( const index_t capacity ) noexcept;
  inline DenseStorage( const ValArrayType &val ) noexcept;
  inline DenseStorage( const DenseStorage &other ) noexcept;

  // Operators
  inline DenseStorage& operator=( const DenseStorage &other ) noexcept;

 public:

  // Gets information
  inline bool    isEmpty() const noexcept;
  inline index_t capacity() const noexcept;
  inline index_t offset() const noexcept;

  // Gets array
  inline       ValArrayType& val() noexcept;
  inline const ValArrayType& val() const noexcept;
  inline       ValType* valPtr() noexcept;
  inline const ValType* valPtr() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_STORAGE_HH_
