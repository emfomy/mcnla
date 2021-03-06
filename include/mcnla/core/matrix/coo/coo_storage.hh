////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_storage.hh
/// @brief   The definition of COO storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_STORAGE_HH_
#define MCNLA_CORE_MATRIX_COO_COO_STORAGE_HH_

#include <mcnla/core/matrix/coo/def.hpp>
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
/// @tparam  _Val     The value type.
/// @tparam  _ArrayT  The array template.
///
template <class _Core, typename _Val>
class CooStorage : private DenseStorage<_Core, _Val> {

 private:

  using ValType      = _Val;
  using ValArrayType = ArrS<_Core, _Val>;

  using BaseType     = DenseStorage<_Core, _Val>;

 protected:

  /// The number of nonzero elements
  index_t nnz_;

 protected:

  using BaseType::val;
  using BaseType::valPtr;

  // Constructors
  inline CooStorage() noexcept;
  inline CooStorage( const index_t capacity, const index_t nnz = 0 ) noexcept;
  inline CooStorage( const ValArrayType &val, const index_t nnz = 0 ) noexcept;
  inline CooStorage( const CooStorage &other ) noexcept;

  // Operators
  inline CooStorage& operator=( const CooStorage &other ) noexcept;

 public:

  // Gets information
  inline index_t nnz() const noexcept;
  inline index_t valCapacity() const noexcept;
  inline index_t valOffset() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_STORAGE_HH_
