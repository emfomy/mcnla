////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_storage.hh
/// @brief   The definition of dense storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_STORAGE_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_STORAGE_HH_

#include <mcnla/core/matrix/dense/def.hpp>

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
/// @tparam  _Core  The core tag.
/// @tparam  _Val   The value type.
///
template <typename _Core, typename _Val>
class DenseStorage {

 private:

  using ValType      = _Val;
  using ValArrayType = ArrI<_Core, _Val>;

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
