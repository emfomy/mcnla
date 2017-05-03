////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_idx0_storage.hh
/// @brief   The definition of COO idx0 storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_IDX0_STORAGE_HH_
#define MCNLA_CORE_MATRIX_COO_COO_IDX0_STORAGE_HH_

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
/// The coordinate list (COO) storage of the first dimension index.
///
/// @tparam  _Idx    The index type.
/// @tparam  _Array  The array template.
///
template <typename _Idx, template <typename> class _Array>
class CooIdx0Storage : protected DenseStorage<_Idx, _Array> {

 private:

  using IdxType      = _Idx;
  using IdxArrayType = _Array<_Idx>;

  using BaseType     = DenseStorage<_Idx, _Array>;

 protected:

  using BaseType::DenseStorage;
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
