////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_storage.hh
/// @brief   The definition of COO storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_STORAGE_HH_
#define MCNLA_CORE_MATRIX_COO_COO_STORAGE_HH_

#include <mcnla/core/matrix/def.hpp>
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
/// @ingroup  matrix_coo_module
/// The coordinate list (COO) storage.
///
/// @tparam  _Scalar  The scalar type.
///
template <class _Scalar>
class CooStorage {

 private:

  using ScalarType   = _Scalar;
  using ValArrayType = Array<ScalarType>;

 protected:

  /// The data storage
  ValArrayType val_;

 protected:

  // Constructors
  inline CooStorage() noexcept;
  inline CooStorage( const index_t capacity ) noexcept;
  inline CooStorage( const ValArrayType &val ) noexcept;
  inline CooStorage( const CooStorage &other ) noexcept;
  inline CooStorage( CooStorage &&other ) noexcept;

  // Operators
  inline CooStorage& operator=( const CooStorage &other ) noexcept;
  inline CooStorage& operator=( CooStorage &&other ) noexcept;

 public:

  // Gets information
  inline index_t valCapacity() const noexcept;
  inline index_t valOffset() const noexcept;

  // Gets array
  inline       ValArrayType& val() noexcept;
  inline const ValArrayType& val() const noexcept;
  inline       ScalarType* valPtr() noexcept;
  inline const ScalarType* valPtr() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_STORAGE_HH_
