////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_storage.hpp
/// @brief   The COO storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_STORAGE_HPP_
#define MCNLA_CORE_MATRIX_COO_COO_STORAGE_HPP_

#include <mcnla/core/matrix/coo/coo_storage.hh>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <class _Core, typename _Val>
CooStorage<_Core, _Val>::CooStorage() noexcept
  : BaseType(),
    nnz_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val>
CooStorage<_Core, _Val>::CooStorage(
    const index_t capacity,
    const index_t nnz
) noexcept
  : BaseType(capacity),
    nnz_(nnz) {
  mcnla_assert_ge(nnz_, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <class _Core, typename _Val>
CooStorage<_Core, _Val>::CooStorage(
    const ValArrayType &val,
    const index_t nnz
) noexcept
  : BaseType(val),
    nnz_(nnz) {
  mcnla_assert_ge(nnz_, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <class _Core, typename _Val>
CooStorage<_Core, _Val>::CooStorage(
    const CooStorage &other
) noexcept
  : BaseType(other),
    nnz_(other.nnz_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <class _Core, typename _Val>
CooStorage<_Core, _Val>& CooStorage<_Core, _Val>::operator=(
    const CooStorage &other
) noexcept {
  BaseType::operator=(other);
  nnz_ = other.nnz_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of nonzero elements.
///
template <class _Core, typename _Val>
index_t CooStorage<_Core, _Val>::nnz() const noexcept {
  return nnz_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the capacity of the value array.
///
template <class _Core, typename _Val>
index_t CooStorage<_Core, _Val>::valCapacity() const noexcept {
  return this->capacity();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the offset of the value array.
///
template <class _Core, typename _Val>
index_t CooStorage<_Core, _Val>::valOffset() const noexcept {
  return this->offset();
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_STORAGE_HPP_
