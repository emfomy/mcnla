////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_vector_storage.hpp
/// @brief   The dense vector storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_STORAGE_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_STORAGE_HPP_

#include <mcnla/core/matrix/dense/dense_vector_storage.hh>

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
DenseVectorStorage<_Val>::DenseVectorStorage() noexcept
  : BaseType(),
    dim0_(0),
    stride_(1) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
DenseVectorStorage<_Val>::DenseVectorStorage(
    const index_t dim0,
    const index_t stride
) noexcept
  : BaseType(dim0 * stride),
    dim0_(dim0),
    stride_(stride) {
  mcnla_assert_ge(dim0_, 0);
  mcnla_assert_gt(stride_, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
DenseVectorStorage<_Val>::DenseVectorStorage(
    const index_t dim0,
    const index_t stride,
    const index_t capacity
) noexcept
  : BaseType(capacity),
    dim0_(dim0),
    stride_(stride) {
  mcnla_assert_ge(dim0_, 0);
  mcnla_assert_gt(stride_, 0);
  mcnla_assert_ge(this->capacity(), stride_ * (dim0_-1) + 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Val>
DenseVectorStorage<_Val>::DenseVectorStorage(
    const index_t dim0,
    const index_t stride,
    const ValArrayType &val,
    const index_t offset
) noexcept
  : BaseType(val >> offset),
    dim0_(dim0),
    stride_(stride) {
  mcnla_assert_ge(dim0_, 0);
  mcnla_assert_gt(stride_, 0);
  mcnla_assert_ge(this->capacity(), stride_ * (dim0_-1) + 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <typename _Val>
DenseVectorStorage<_Val>::DenseVectorStorage(
    const DenseVectorStorage &other
) noexcept
  : BaseType(other),
    dim0_(other.dim0_),
    stride_(other.stride_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <typename _Val>
DenseVectorStorage<_Val>& DenseVectorStorage<_Val>::operator=(
    const DenseVectorStorage &other
) noexcept {
  BaseType::operator=(other);
  dim0_   = other.dim0_;
  stride_ = other.stride_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the dimensions are equal to the sizes.
///
template <typename _Val>
bool DenseVectorStorage<_Val>::isShrunk() const noexcept {
  return (stride_ == 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size in the first dimension.
///
template <typename _Val>
index_t DenseVectorStorage<_Val>::dim0() const noexcept {
  return dim0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size of dimensions in storage order. [ dim0 ]
///
template <typename _Val>
std::tuple<index_t> DenseVectorStorage<_Val>::dims() const noexcept {
  return std::make_tuple(dim0_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of positions between successive elements.
///
template <typename _Val>
index_t DenseVectorStorage<_Val>::stride() const noexcept {
  return stride_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element of given index.
///
template <typename _Val>
_Val& DenseVectorStorage<_Val>::elemImpl(
    const index_t idx0
) noexcept {
  mcnla_assert_gelt(idx0, 0, dim0_);
  return this->valPtr()[posImpl(idx0)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  elemImpl
///
template <typename _Val>
const _Val& DenseVectorStorage<_Val>::elemImpl(
    const index_t idx0
) const noexcept {
  mcnla_assert_gelt(idx0, 0, dim0_);
  return this->valPtr()[posImpl(idx0)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position of given index.
///
template <typename _Val>
index_t DenseVectorStorage<_Val>::posImpl(
    const index_t idx0
) const noexcept {
  return idx0 * stride_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Resizes the vector.
///
/// @attention  The new space is kept but not initialized.
///
template <typename _Val>
void DenseVectorStorage<_Val>::resizeImpl(
    const index_t dim0,
    const index_t stride
) noexcept {
  mcnla_assert_ge(dim0, 0);
  mcnla_assert_gt(stride, 0);
  mcnla_assert_true(dim0 != 0 || stride != 0);
  mcnla_assert_ge(this->capacity(), stride * (dim0-1) + 1);
  dim0_   = dim0;
  stride_ = stride;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <typename _Val>
DenseVectorStorage<_Val> DenseVectorStorage<_Val>::getVectorImpl(
    const IdxRange &range0
) noexcept {
  mcnla_assert_ge(range0.begin, 0); mcnla_assert_le(range0.end, dim0_); mcnla_assert_ge(range0.length(), 0);
  return VectorStorageType(range0.length(), stride_, val_, this->posImpl(range0.begin));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getVectorImpl
///
template <typename _Val>
const DenseVectorStorage<_Val> DenseVectorStorage<_Val>::getVectorImpl(
    const IdxRange &range0
) const noexcept {
  mcnla_assert_ge(range0.begin, 0); mcnla_assert_le(range0.end, dim0_); mcnla_assert_ge(range0.length(), 0);
  return VectorStorageType(range0.length(), stride_, val_, this->posImpl(range0.begin));
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_STORAGE_HPP_
