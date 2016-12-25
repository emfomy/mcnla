////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_vector_storage.ipp
/// @brief   The implementation of dense vector storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_STORAGE_IPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_STORAGE_IPP_

#include <mcnla/core/matrix/dense/dense_vector_storage.hpp>

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
DenseVectorStorage<_Scalar>::DenseVectorStorage() noexcept
  : BaseType(),
    dim0_(0),
    stride_(1) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseVectorStorage<_Scalar>::DenseVectorStorage(
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
template <typename _Scalar>
DenseVectorStorage<_Scalar>::DenseVectorStorage(
    const index_t dim0,
    const index_t stride,
    const index_t capacity
) noexcept
  : BaseType(capacity),
    dim0_(dim0),
    stride_(stride) {
  mcnla_assert_ge(dim0_, 0);
  mcnla_assert_gt(stride_, 0);
  mcnla_assert_ge(value_.getCapacity(), stride_ * (dim0_-1) + 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar>
DenseVectorStorage<_Scalar>::DenseVectorStorage(
    const index_t dim0,
    const index_t stride,
    const ValueArrayType &value,
    const index_t offset
) noexcept
  : BaseType(value >> offset),
    dim0_(dim0),
    stride_(stride) {
  mcnla_assert_ge(dim0_, 0);
  mcnla_assert_gt(stride_, 0);
  mcnla_assert_ge(value_.getCapacity(), stride_ * (dim0_-1) + 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <typename _Scalar>
DenseVectorStorage<_Scalar>::DenseVectorStorage(
    const DenseVectorStorage &other
) noexcept
  : BaseType(other),
    dim0_(other.dim0_),
    stride_(other.stride_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar>
DenseVectorStorage<_Scalar>::DenseVectorStorage(
  DenseVectorStorage &&other
) noexcept
  : BaseType(std::move(other)),
    dim0_(other.dim0_),
    stride_(other.stride_) {
  other.dim0_  = 0;
  other.stride_ = 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <typename _Scalar>
DenseVectorStorage<_Scalar>& DenseVectorStorage<_Scalar>::operator=(
    const DenseVectorStorage &other
) noexcept {
  BaseType::operator=(other);
  dim0_  = other.dim0_;
  stride_ = other.stride_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Scalar>
DenseVectorStorage<_Scalar>& DenseVectorStorage<_Scalar>::operator=(
    DenseVectorStorage &&other
) noexcept {
  BaseType::operator=(std::move(other));
  dim0_  = other.dim0_;  other.dim0_  = 0;
  stride_ = other.stride_; other.stride_ = 1;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the dimensions are equal to the sizes.
///
template <typename _Scalar>
bool DenseVectorStorage<_Scalar>::isShrunk() const noexcept {
  return (stride_ == 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size in the first dimension.
///
template <typename _Scalar>
index_t DenseVectorStorage<_Scalar>::getDim0() const noexcept {
  return dim0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size of dimensions in storage order. [ dim0 ]
///
template <typename _Scalar>
std::tuple<index_t> DenseVectorStorage<_Scalar>::getDims() const noexcept {
  return std::make_tuple(dim0_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the stride.
///
template <typename _Scalar>
index_t DenseVectorStorage<_Scalar>::getStride() const noexcept {
  return stride_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element of given index.
///
template <typename _Scalar>
_Scalar& DenseVectorStorage<_Scalar>::getElemImpl(
    const index_t idx0
) noexcept {
  mcnla_assert_gelt(idx0, 0, dim0_);
  return this->getValuePtr()[getPosImpl(idx0)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElemImpl
///
template <typename _Scalar>
const _Scalar& DenseVectorStorage<_Scalar>::getElemImpl(
    const index_t idx0
) const noexcept {
  mcnla_assert_gelt(idx0, 0, dim0_);
  return this->getValuePtr()[getPosImpl(idx0)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position of given index.
///
template <typename _Scalar>
index_t DenseVectorStorage<_Scalar>::getPosImpl(
    const index_t idx0
) const noexcept {
  return idx0 * stride_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Resizes the vector.
///
/// @attention  The new space is kept but not initialized.
///
template <typename _Scalar>
void DenseVectorStorage<_Scalar>::resizeImpl(
    const index_t dim0,
    const index_t stride
) noexcept {
  mcnla_assert_ge(dim0, 0);
  mcnla_assert_gt(stride, 0);
  mcnla_assert_true(dim0 != 0 || stride != 0);
  mcnla_assert_ge(this->getCapacity(), stride * (dim0-1) + 1);
  dim0_   = dim0;
  stride_ = stride;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <typename _Scalar>
DenseVectorStorage<_Scalar> DenseVectorStorage<_Scalar>::getVectorImpl(
    const IdxRange &range0
) noexcept {
  mcnla_assert_ge(range0.begin, 0); mcnla_assert_le(range0.end, dim0_); mcnla_assert_ge(range0.getLength(), 0);
  return VectorStorageType(range0.getLength(), stride_, value_, this->getPosImpl(range0.begin));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getVectorImpl
///
template <typename _Scalar>
const DenseVectorStorage<_Scalar> DenseVectorStorage<_Scalar>::getVectorImpl(
    const IdxRange &range0
) const noexcept {
  mcnla_assert_ge(range0.begin, 0); mcnla_assert_le(range0.end, dim0_); mcnla_assert_ge(range0.getLength(), 0);
  return VectorStorageType(range0.getLength(), stride_, value_, this->getPosImpl(range0.begin));
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_STORAGE_IPP_
