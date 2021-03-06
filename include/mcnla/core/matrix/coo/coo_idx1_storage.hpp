////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_idx1_storage.hpp
/// @brief   The COO idx1 storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_IDX1_STORAGE_HPP_
#define MCNLA_CORE_MATRIX_COO_COO_IDX1_STORAGE_HPP_

#include <mcnla/core/matrix/coo/coo_idx1_storage.hh>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the capacity of the second dimension index array.
///
template <class _Core, typename _Idx>
index_t CooIdx1Storage<_Core, _Idx>::idx1Capacity() const noexcept {
  return this->capacity();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the offset of the second dimension index array.
///
template <class _Core, typename _Idx>
index_t CooIdx1Storage<_Core, _Idx>::idx1Offset() const noexcept {
  return this->offset();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the second dimension index array.
///
template <class _Core, typename _Idx>
typename CooIdx1Storage<_Core, _Idx>::IdxArrayType& CooIdx1Storage<_Core, _Idx>::idx1() noexcept {
  return this->val();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  idx1
///
template <class _Core, typename _Idx>
const typename CooIdx1Storage<_Core, _Idx>::IdxArrayType& CooIdx1Storage<_Core, _Idx>::idx1() const noexcept {
  return this->val();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw second dimension index pointer.
///
template <class _Core, typename _Idx>
_Idx* CooIdx1Storage<_Core, _Idx>::idx1Ptr() noexcept {
  return this->valPtr();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  idx1Ptr
///
template <class _Core, typename _Idx>
const _Idx* CooIdx1Storage<_Core, _Idx>::idx1Ptr() const noexcept {
  return this->valPtr();
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_IDX1_STORAGE_HPP_
