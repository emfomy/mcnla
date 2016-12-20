////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_vector_storage.ipp
/// @brief   The implementation of dense vector storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_STORAGE_IPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_STORAGE_IPP_

#include <mcnla/core/matrix/dense/dense_vector_storage.hpp>
#include <iomanip>

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
    size0_(0),
    stride_(1) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseVectorStorage<_Scalar>::DenseVectorStorage(
    const index_t size0,
    const index_t stride
) noexcept
  : BaseType(size0 * stride),
    size0_(size0),
    stride_(stride) {
  mcnla_assert_ge(size0_, 0);
  mcnla_assert_gt(stride_, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseVectorStorage<_Scalar>::DenseVectorStorage(
    const index_t size0,
    const index_t stride,
    const index_t capacity
) noexcept
  : BaseType(capacity),
    size0_(size0),
    stride_(stride) {
  mcnla_assert_ge(size0_, 0);
  mcnla_assert_gt(stride_, 0);
  mcnla_assert_ge(value_.getCapacity(), stride_ * (size0_-1) + 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar>
DenseVectorStorage<_Scalar>::DenseVectorStorage(
    const index_t size0,
    const index_t stride,
    const ValueArrayType &value,
    const index_t offset
) noexcept
  : BaseType(value >> offset),
    size0_(size0),
    stride_(stride) {
  mcnla_assert_ge(size0_, 0);
  mcnla_assert_gt(stride_, 0);
  mcnla_assert_ge(value_.getCapacity(), stride_ * (size0_-1) + 1);
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
    size0_(other.size0_),
    stride_(other.stride_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar>
DenseVectorStorage<_Scalar>::DenseVectorStorage(
  DenseVectorStorage &&other
) noexcept
  : BaseType(std::move(other)),
    size0_(other.size0_),
    stride_(other.stride_) {
  other.size0_  = 0;
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
  size0_  = other.size0_;
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
  size0_  = other.size0_;  other.size0_  = 0;
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
/// @brief  Gets the size of the first dimension.
///
template <typename _Scalar>
index_t DenseVectorStorage<_Scalar>::getSize0() const noexcept {
  return size0_;
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
_Scalar& DenseVectorStorage<_Scalar>::getElem(
    const index_t idx0
) noexcept {
  mcnla_assert_gelt(idx0, 0, size0_);
  return this->getValuePtr()[getPos(idx0)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElem
///
template <typename _Scalar>
const _Scalar& DenseVectorStorage<_Scalar>::getElem(
    const index_t idx0
) const noexcept {
  mcnla_assert_gelt(idx0, 0, size0_);
  return this->getValuePtr()[getPos(idx0)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElem
///
template <typename _Scalar>
_Scalar& DenseVectorStorage<_Scalar>::operator()(
    const index_t idx0
) noexcept {
  return getElem(idx0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElem
///
template <typename _Scalar>
const _Scalar& DenseVectorStorage<_Scalar>::operator()(
    const index_t idx0
) const noexcept {
  return getElem(idx0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position of given index.
///
template <typename _Scalar>
index_t DenseVectorStorage<_Scalar>::getPos(
    const index_t idx0
) const noexcept {
  return idx0 * stride_;
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_STORAGE_IPP_
