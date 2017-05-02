////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_idx1_storage.hh
/// @brief   The definition of COO idx1 storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_IDX1_STORAGE_HH_
#define MCNLA_CORE_MATRIX_COO_COO_IDX1_STORAGE_HH_

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
/// The coordinate list (COO) storage of the second dimension index.
///
/// @tparam  _Idx  The index type.
///
template <typename _Idx = index_t, template <typename> class _Array = Array>
class CooIdx1Storage : protected DenseStorage<_Idx, _Array> {

 private:

  using IdxType      = _Idx;
  using IdxArrayType = _Array<_Idx>;

  using BaseType     = DenseStorage<_Idx, _Array>;

 protected:

  using BaseType::DenseStorage;
  using BaseType::operator=;

 public:

  // Gets information
  inline index_t idx1Capacity() const noexcept;
  inline index_t idx1Offset() const noexcept;

  // Gets array
  inline       IdxArrayType& idx1() noexcept;
  inline const IdxArrayType& idx1() const noexcept;
  inline       IdxType* idx1Ptr() noexcept;
  inline const IdxType* idx1Ptr() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_IDX1_STORAGE_HH_
