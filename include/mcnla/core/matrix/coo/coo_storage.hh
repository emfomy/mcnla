////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_storage.hh
/// @brief   The definition of COO storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_STORAGE_HH_
#define MCNLA_CORE_MATRIX_COO_COO_STORAGE_HH_

#include <mcnla/core/matrix/def.hpp>
#include <mcnla/core/matrix/dense/dense_storage.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) storage.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class CooStorage : protected DenseStorage<_Val> {

 private:

  using ValType      = _Val;
  using ValArrayType = Array<ValType>;

  using BaseType     = DenseStorage<_Val>;

 protected:

  /// The number of nonzero elements
  index_t nnz_;

 protected:

  using BaseType::val;
  using BaseType::valPtr;

 protected:

  // Constructors
  inline CooStorage() noexcept;
  inline CooStorage( const index_t capacity, const index_t nnz = 0 ) noexcept;
  inline CooStorage( const ValArrayType &val, const index_t nnz = 0 ) noexcept;
  inline CooStorage( const CooStorage &other ) noexcept;
  inline CooStorage( CooStorage &&other ) noexcept;

  // Operators
  inline CooStorage& operator=( const CooStorage &other ) noexcept;
  inline CooStorage& operator=( CooStorage &&other ) noexcept;

 public:

  // Gets information
  inline index_t nnz() const noexcept;
  inline index_t valCapacity() const noexcept;
  inline index_t valOffset() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_STORAGE_HH_
