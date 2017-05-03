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
template <typename _Val, template <typename> class _ArrayT>
CooStorage<_Val, _ArrayT>::CooStorage() noexcept
  : BaseType(),
    nnz_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, template <typename> class _ArrayT>
CooStorage<_Val, _ArrayT>::CooStorage(
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
template <typename _Val, template <typename> class _ArrayT>
CooStorage<_Val, _ArrayT>::CooStorage(
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
template <typename _Val, template <typename> class _ArrayT>
CooStorage<_Val, _ArrayT>::CooStorage(
    const CooStorage &other
) noexcept
  : BaseType(other),
    nnz_(other.nnz_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <typename _Val, template <typename> class _ArrayT>
CooStorage<_Val, _ArrayT>& CooStorage<_Val, _ArrayT>::operator=(
    const CooStorage &other
) noexcept {
  BaseType::operator=(other);
  nnz_ = other.nnz_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of nonzero elements.
///
template <typename _Val, template <typename> class _ArrayT>
index_t CooStorage<_Val, _ArrayT>::nnz() const noexcept {
  return nnz_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the capacity of the value array.
///
template <typename _Val, template <typename> class _ArrayT>
index_t CooStorage<_Val, _ArrayT>::valCapacity() const noexcept {
  return this->capacity();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the offset of the value array.
///
template <typename _Val, template <typename> class _ArrayT>
index_t CooStorage<_Val, _ArrayT>::valOffset() const noexcept {
  return this->offset();
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_STORAGE_HPP_
