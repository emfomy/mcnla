////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_vector_storage.hpp
/// @brief   The COO vector storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_VECTOR_STORAGE_HPP_
#define MCNLA_CORE_MATRIX_COO_COO_VECTOR_STORAGE_HPP_

#include <mcnla/core/matrix/coo/coo_vector_storage.hh>
#include <algorithm>

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
CooVectorStorage<_Core, _Val>::CooVectorStorage() noexcept
  : BaseType(),
    Base0Type(),
    dim0_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val>
CooVectorStorage<_Core, _Val>::CooVectorStorage(
    const index_t dim0,
    const index_t nnz
) noexcept
  : BaseType(nnz, nnz),
    Base0Type(nnz),
    dim0_(dim0) {
  mcnla_assert_ge(dim0_, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Core, typename _Val>
CooVectorStorage<_Core, _Val>::CooVectorStorage(
    const index_t dim0,
    const index_t nnz,
    const index_t capacity
) noexcept
  : BaseType(capacity, nnz),
    Base0Type(capacity),
    dim0_(dim0) {
  mcnla_assert_ge(dim0_, 0);
  mcnla_assert_ge(this->valCapacity(), nnz_);
  mcnla_assert_ge(this->idx0Capacity(), nnz_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <class _Core, typename _Val>
CooVectorStorage<_Core, _Val>::CooVectorStorage(
    const index_t dim0,
    const index_t nnz,
    const ValArrayType &val,
    const IdxArrayType &idx0,
    const index_t offset
) noexcept
  : BaseType(val >> offset, nnz),
    Base0Type(idx0 >> offset),
    dim0_(dim0) {
  mcnla_assert_ge(dim0_, 0);
  mcnla_assert_ge(this->valCapacity(), nnz_);
  mcnla_assert_ge(this->idx0Capacity(), nnz_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <class _Core, typename _Val>
CooVectorStorage<_Core, _Val>::CooVectorStorage(
    const CooVectorStorage &other
) noexcept
  : BaseType(other),
    Base0Type(other),
    dim0_(other.dim0_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <class _Core, typename _Val>
CooVectorStorage<_Core, _Val>& CooVectorStorage<_Core, _Val>::operator=(
    const CooVectorStorage &other
) noexcept {
  BaseType::operator=(other);
  Base0Type::operator=(other);
  dim0_ = other.dim0_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the memory size is zero.
///
template <class _Core, typename _Val>
bool CooVectorStorage<_Core, _Val>::isEmpty() const noexcept {
  return BaseType::isEmpty() && Base0Type::isEmpty();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size in the first dimension.
///
template <class _Core, typename _Val>
index_t CooVectorStorage<_Core, _Val>::dim0() const noexcept {
  return dim0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size of dimensions in storage order. [ dim0 ]
///
template <class _Core, typename _Val>
std::tuple<index_t> CooVectorStorage<_Core, _Val>::dims() const noexcept {
  return std::make_tuple(dim0_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element of given index.
///
template <class _Core, typename _Val>
_Val CooVectorStorage<_Core, _Val>::elemImpl(
    const index_t idx0
) noexcept {
  mcnla_assert_gelt(idx0, 0, dim0_);
  index_t pos = posImpl(idx0);
  return (pos >= 0) ? this->valPtr()[pos] : 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  elemImpl
///
template <class _Core, typename _Val>
const _Val CooVectorStorage<_Core, _Val>::elemImpl(
    const index_t idx0
) const noexcept {
  mcnla_assert_gelt(idx0, 0, dim0_);
  index_t pos = posImpl(idx0);
  return (pos >= 0) ? this->valPtr()[pos] : 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position of given index.
//
/// @attention  Returns `-1` if the index does not exist!
///
template <class _Core, typename _Val>
index_t CooVectorStorage<_Core, _Val>::posImpl(
    const index_t idx0
) const noexcept {
  index_t pos = std::find(idx0Ptr(), idx0Ptr() + nnz_, idx0) - idx0Ptr();
  return (pos < nnz_) ? pos : -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Resizes the vector.
///
/// @attention  The new space is kept but not initialized.
///
template <class _Core, typename _Val>
void CooVectorStorage<_Core, _Val>::resizeImpl(
    const index_t dim0,
    const index_t nnz
) noexcept {
  mcnla_assert_ge(dim0, 0);
  mcnla_assert_ge(nnz, 0);
  mcnla_assert_ge(this->valCapacity(), nnz);
  mcnla_assert_ge(this->idx0Capacity(), nnz);
  dim0_ = dim0;
  nnz_  = nnz;
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_VECTOR_STORAGE_HPP_
