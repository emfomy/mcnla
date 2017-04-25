////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_vector.hpp
/// @brief   The COO vector.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_VECTOR_HPP_
#define MCNLA_CORE_MATRIX_COO_COO_VECTOR_HPP_

#include <mcnla/core/matrix/coo/coo_vector.hh>

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
CooVector<_Val>::CooVector() noexcept
  : BaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
CooVector<_Val>::CooVector(
    const index_t length,
    const index_t nnz
) noexcept
  : BaseType(toDim0(length), nnz) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
CooVector<_Val>::CooVector(
    const SizesType sizes,
    const index_t nnz
) noexcept
  : BaseType(toDim0(sizes), nnz) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
CooVector<_Val>::CooVector(
    const index_t length,
    const index_t nnz,
    const index_t capacity
) noexcept
  : BaseType(toDim0(length), nnz, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
CooVector<_Val>::CooVector(
    const SizesType sizes,
    const index_t nnz,
    const index_t capacity
) noexcept
  : BaseType(toDim0(sizes), nnz, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Val>
CooVector<_Val>::CooVector(
    const index_t length,
    const index_t nnz,
    const ValArrayType &val,
    const IdxArrayType &idx0,
    const index_t offset
) noexcept
  : BaseType(toDim0(length), nnz, val, idx0, offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <typename _Val>
CooVector<_Val>::CooVector( const CooVector &other ) noexcept
  : BaseType(other) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Val>
CooVector<_Val>::CooVector( CooVector &&other ) noexcept
  : BaseType(std::move(other)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <typename _Val>
CooVector<_Val>& CooVector<_Val>::operator=(
    const CooVector &other
) noexcept {
  BaseType::operator=(other);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Val>
CooVector<_Val>& CooVector<_Val>::operator=(
    CooVector &&other
) noexcept {
  BaseType::operator=(std::move(other));
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copies the vector.
///
template <typename _Val>
CooVector<_Val> CooVector<_Val>::copy() const noexcept {
  CooVector retval(this->sizes(), this->nnz(), this->capacity());
  retval.val() = this->val().copy();
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the capacity of the index array.
///
template <typename _Val>
index_t CooVector<_Val>::idxCapacity() const noexcept {
  return this->idx0Capacity();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the offset of the index array.
///
template <typename _Val>
index_t CooVector<_Val>::idxOffset() const noexcept {
  return this->idx0Offset();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index array.
///
template <typename _Val>
Array<index_t>& CooVector<_Val>::idx() noexcept {
  return this->idx0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  idx
///
template <typename _Val>
const Array<index_t>& CooVector<_Val>::idx() const noexcept {
  return this->idx0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw index pointer.
///
template <typename _Val>
index_t* CooVector<_Val>::idxPtr() noexcept {
  return this->idx0Ptr();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  idxPtr
///
template <typename _Val>
const index_t* CooVector<_Val>::idxPtr() const noexcept {
  return this->idx0Ptr();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::CooVectorStorage::elemImpl
///
template <typename _Val>
_Val CooVector<_Val>::operator()(
    const index_t idx
) noexcept {
  return this->elemImpl(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::CooVectorStorage::elemImpl
///
template <typename _Val>
const _Val CooVector<_Val>::operator()(
    const index_t idx
) const noexcept {
  return this->elemImpl(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::CooVectorStorage::posImpl
///
template <typename _Val>
index_t CooVector<_Val>::pos(
    const index_t idx
) const noexcept {
  return this->posImpl(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the vector.
///
/// @attention  The data is also reallocated.
///
template <typename _Val> template <typename... Args>
void CooVector<_Val>::reconstruct(
    Args... args
) noexcept {
  *this = CooVector<_Val>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::CooVectorStorage::resizeImpl
///
template <typename _Val>
void CooVector<_Val>::resize(
    const index_t length,
    const index_t nnz
) noexcept {
  this->resizeImpl(length, nnz);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::VectorWrapper::length
///
template <typename _Val>
index_t CooVector<_Val>::lengthImpl() const noexcept {
  return this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the first dimension from sizes.
///
template <typename _Val>
index_t CooVector<_Val>::toDim0(
    const SizesType sizes
) const noexcept {
  return std::get<0>(sizes);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  toDim0
///
template <typename _Val>
index_t CooVector<_Val>::toDim0(
    const index_t length
) const noexcept {
  return length;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert to base class.
///
template <typename _Val>
CooVectorStorage<_Val>& CooVector<_Val>::base() noexcept {
  return static_cast<BaseType&>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  base
///
template <typename _Val>
const CooVectorStorage<_Val>& CooVector<_Val>::base() const noexcept {
  return static_cast<const BaseType&>(*this);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_VECTOR_HPP_
