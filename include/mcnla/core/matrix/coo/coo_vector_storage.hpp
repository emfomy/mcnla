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
template <typename _Scalar>
CooVectorStorage<_Scalar>::CooVectorStorage() noexcept
  : BaseType(),
    Idx0BaseType(),
    dim0_(0),
    nnz_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
CooVectorStorage<_Scalar>::CooVectorStorage(
    const index_t dim0,
    const index_t nnz
) noexcept
  : BaseType(nnz),
    Idx0BaseType(nnz),
    dim0_(dim0),
    nnz_(nnz) {
  mcnla_assert_ge(dim0_, nnz_);
  mcnla_assert_ge(nnz_, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
CooVectorStorage<_Scalar>::CooVectorStorage(
    const index_t dim0,
    const index_t nnz,
    const index_t capacity
) noexcept
  : BaseType(capacity),
    Idx0BaseType(capacity),
    dim0_(dim0),
    nnz_(nnz) {
  mcnla_assert_ge(dim0_, nnz_);
  mcnla_assert_ge(nnz_, 0);
  mcnla_assert_ge(valCapacity(), nnz_);
  mcnla_assert_ge(idx0Capacity(), nnz_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar>
CooVectorStorage<_Scalar>::CooVectorStorage(
    const index_t dim0,
    const index_t nnz,
    const ValArrayType &val,
    const IdxArrayType &idx0,
    const index_t offset
) noexcept
  : BaseType(val >> offset),
    Idx0BaseType(idx0 >> offset),
    dim0_(dim0),
    nnz_(nnz) {
  mcnla_assert_ge(dim0_, nnz_);
  mcnla_assert_ge(nnz_, 0);
  mcnla_assert_ge(valCapacity(), nnz_);
  mcnla_assert_ge(idx0Capacity(), nnz_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::la::copy.
///
template <typename _Scalar>
CooVectorStorage<_Scalar>::CooVectorStorage(
    const CooVectorStorage &other
) noexcept
  : BaseType(other),
    Idx0BaseType(other),
    dim0_(other.dim0_),
    nnz_(other.nnz_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar>
CooVectorStorage<_Scalar>::CooVectorStorage(
  CooVectorStorage &&other
) noexcept
  : BaseType(std::move(other)),
    Idx0BaseType(std::move(other)),
    dim0_(other.dim0_),
    nnz_(other.nnz_) {
  other.dim0_ = 0;
  other.nnz_  = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::la::copy.
///
template <typename _Scalar>
CooVectorStorage<_Scalar>& CooVectorStorage<_Scalar>::operator=(
    const CooVectorStorage &other
) noexcept {
  BaseType::operator=(other);
  Idx0BaseType::operator=(other);
  dim0_ = other.dim0_;
  nnz_  = other.nnz_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Scalar>
CooVectorStorage<_Scalar>& CooVectorStorage<_Scalar>::operator=(
    CooVectorStorage &&other
) noexcept {
  BaseType::operator=(std::move(other));
  Idx0BaseType::operator=(std::move(other));
  dim0_ = other.dim0_;  other.dim0_  = 0;
  nnz_  = other.nnz_;   other.nnz_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the dimensions are equal to the sizes.
///
template <typename _Scalar>
bool CooVectorStorage<_Scalar>::isEmpty() const noexcept {
  return val_.isEmpty() && this->idx0().isEmpty();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size in the first dimension.
///
template <typename _Scalar>
index_t CooVectorStorage<_Scalar>::dim0() const noexcept {
  return dim0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size of dimensions in storage order. [ dim0 ]
///
template <typename _Scalar>
std::tuple<index_t> CooVectorStorage<_Scalar>::dims() const noexcept {
  return std::make_tuple(dim0_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of nonzero elements
///
template <typename _Scalar>
index_t CooVectorStorage<_Scalar>::nnz() const noexcept {
  return nnz_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element of given index.
///
template <typename _Scalar>
_Scalar CooVectorStorage<_Scalar>::getElemImpl(
    const index_t idx0
) noexcept {
  mcnla_assert_gelt(idx0, 0, dim0_);
  index_t pos = posImpl(idx0);
  return (pos >= 0) ? this->valPtr()[pos] : 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElemImpl
///
template <typename _Scalar>
const _Scalar CooVectorStorage<_Scalar>::getElemImpl(
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
template <typename _Scalar>
index_t CooVectorStorage<_Scalar>::posImpl(
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
template <typename _Scalar>
void CooVectorStorage<_Scalar>::resizeImpl(
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
