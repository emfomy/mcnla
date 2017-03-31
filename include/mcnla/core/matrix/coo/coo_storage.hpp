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
template <typename _Val>
CooStorage<_Val>::CooStorage() noexcept
  : BaseType(),
    nnz_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
CooStorage<_Val>::CooStorage(
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
template <typename _Val>
CooStorage<_Val>::CooStorage(
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
template <typename _Val>
CooStorage<_Val>::CooStorage(
    const CooStorage &other
) noexcept
  : BaseType(other),
    nnz_(other.nnz_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Val>
CooStorage<_Val>::CooStorage(
    CooStorage &&other
) noexcept
  : BaseType(std::move(other)),
    nnz_(other.nnz_) {
  other.nnz_ = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <typename _Val>
CooStorage<_Val>& CooStorage<_Val>::operator=(
    const CooStorage &other
) noexcept {
  BaseType::operator=(other);
  nnz_ = other.nnz_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Val>
CooStorage<_Val>& CooStorage<_Val>::operator=(
    CooStorage &&other
) noexcept {
  BaseType::operator=(std::move(other));
  nnz_ = other.nnz_;  other.nnz_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of nonzero elements.
///
template <typename _Val>
index_t CooStorage<_Val>::nnz() const noexcept {
  return nnz_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the capacity of the value array.
///
template <typename _Val>
index_t CooStorage<_Val>::valCapacity() const noexcept {
  return this->capacity();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the offset of the value array.
///
template <typename _Val>
index_t CooStorage<_Val>::valOffset() const noexcept {
  return this->offset();
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_STORAGE_HPP_
