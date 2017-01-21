////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_idx0_storage.hh
/// @brief   The definition of COO idx0 storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_IDX0_STORAGE_HH_
#define MCNLA_CORE_MATRIX_COO_COO_IDX0_STORAGE_HH_

#include <mcnla/core/matrix/def.hpp>
#include <mcnla/core/matrix/coo/coo_storage.hpp>

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
/// The coordinate list (COO) storage of the first dimension index.
///
/// @tparam  _Idx  The index type.
///
template <class _Idx = index_t>
class CooIdx0Storage : protected CooStorage<_Idx> {

 private:

  using IdxType      = _Idx;
  using IdxArrayType = Array<_Idx>;

  using BaseType     = CooStorage<_Idx>;

 protected:

  using BaseType::CooStorage;
  using BaseType::operator=;

 public:

  // Gets information
  inline index_t idx0Capacity() const noexcept;
  inline index_t idx0Offset() const noexcept;

  // Gets array
  inline       IdxArrayType& idx0() noexcept;
  inline const IdxArrayType& idx0() const noexcept;
  inline       IdxType* idx0Ptr() noexcept;
  inline const IdxType* idx0Ptr() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_IDX0_STORAGE_HH_
