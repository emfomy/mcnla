////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_matrix_storage.ipp
/// @brief   The implementation of dense matrix storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_STORAGE_IPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_STORAGE_IPP_

#include <mcnla/core/matrix/dense/dense_matrix_storage.hpp>
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
DenseMatrixStorage<_Scalar>::DenseMatrixStorage() noexcept
  : BaseType(),
    size0_(0),
    size1_(0),
    pitch0_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseMatrixStorage<_Scalar>::DenseMatrixStorage(
    const index_t size0,
    const index_t size1,
) noexcept
  : BaseType(size0 * size1),
    size0_(size0),
    size1_(size1),
    pitch0_(size0) {
  mcnla_assert_ge(size0_, 0);
  mcnla_assert_ge(size1_, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseMatrixStorage<_Scalar>::DenseMatrixStorage(
    const index_t size0,
    const index_t size1,
    const index_t pitch0
) noexcept
  : BaseType(size0 * pitch0),
    size0_(size0),
    size1_(size1),
    pitch0_(pitch0) {
  mcnla_assert_ge(size0_, 0);
  mcnla_assert_ge(size1_, 0);
  mcnla_assert_ge(pitch_, size0_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseMatrixStorage<_Scalar>::DenseMatrixStorage(
    const index_t size0,
    const index_t size1,
    const index_t pitch0,
    const index_t capacity
) noexcept
  : BaseType(capacity),
    size0_(size0),
    size1_(size1),
    pitch0_(pitch0) {
  mcnla_assert_ge(size0_, 0);
  mcnla_assert_ge(size1_, 0);
  mcnla_assert_ge(pitch_, size0_);
  mcnla_assert_ge(capacity, pitch_ * (size1_-1) + size0_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar>
DenseMatrixStorage<_Scalar>::DenseMatrixStorage(
    const index_t size0,
    const index_t size1,
    const index_t pitch0,
    const ValueArrayType &value,
    const index_t offset
) noexcept
  : BaseType(value >> offset),
    size0_(size0),
    size1_(size1),
    pitch0_(pitch0) {
  mcnla_assert_ge(size0_, 0);
  mcnla_assert_ge(size1_, 0);
  mcnla_assert_ge(pitch_, size0_);
  mcnla_assert_ge(this->getCapacity(), pitch_ * (size1_-1) + size0_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <typename _Scalar>
DenseMatrixStorage<_Scalar>::DenseMatrixStorage(
    const DenseMatrixStorage &other
) noexcept
  : BaseType(other),
    size0_(other.size0_),
    size1_(other.size1_),
    pitch0_(other.pitch0_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar>
DenseMatrixStorage<_Scalar>::DenseMatrixStorage(
  DenseMatrixStorage &&other
) noexcept
  : BaseType(std::move(other)),
    size0_(other.size0_),
    size1_(other.size1_),
    pitch0_(other.pitch0_) {
  other.size0_  = 0;
  other.size1_  = 0;
  other.pitch0_ = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <typename _Scalar>
DenseMatrixStorage<_Scalar>& DenseMatrixStorage<_Scalar>::operator=(
    const DenseMatrixStorage &other
) noexcept {
  BaseType::operator=(other);
  size0_  = other.size0_;
  size1_  = other.size1_;
  pitch0_ = other.pitch0_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Scalar>
DenseMatrixStorage<_Scalar>& DenseMatrixStorage<_Scalar>::operator=(
    DenseMatrixStorage &&other
) noexcept {
  BaseType::operator=(std::move(other));
  size0_  = other.size0_;  other.size0_  = 0;
  pitch0_ = other.size1_;  other.size1_ = 0;
  pitch0_ = other.pitch0_; other.pitch0_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the dimensions are equal to the sizes.
///
template <typename _Scalar>
bool DenseMatrixStorage<_Scalar>::isShrunk() const noexcept {
  return (pitch0_ == pitch_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the matrix is square.
///
template <typename _Scalar>
bool DenseMatrixStorage<_Scalar>::isSquare() const noexcept {
  return (size0_ == size1_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size of the first dimension.
///
template <typename _Scalar>
index_t DenseMatrixStorage<_Scalar>::getSize0() const noexcept {
  return size0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size of the second dimension.
///
template <typename _Scalar>
index_t DenseMatrixStorage<_Scalar>::getSize1() const noexcept {
  return size1_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the leading dimension.
///
template <typename _Scalar>
index_t DenseMatrixStorage<_Scalar>::getPitch0() const noexcept {
  return pitch0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element of given index.
///
template <typename _Scalar>
_Scalar& DenseMatrixStorage<_Scalar>::getElem(
    const index_t idx0,
    const index_t idx1
) noexcept {
  mcnla_assert_gelt(idx0, 0, size0_);
  mcnla_assert_gelt(idx1, 0, size1_);
  return this->getValuePtr()[getPos(idx0, idx1)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElem
///
template <typename _Scalar>
const _Scalar& DenseMatrixStorage<_Scalar>::getElem(
    const index_t idx0,
    const index_t idx1
) const noexcept {
  mcnla_assert_gelt(idx0, 0, size0_);
  mcnla_assert_gelt(idx1, 0, size1_);
  return this->getValuePtr()[getPos(idx0, idx1)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElem
///
template <typename _Scalar>
_Scalar& DenseMatrixStorage<_Scalar>::operator()(
    const index_t idx0,
    const index_t idx1
) noexcept {
  return getElem(idx0, idx1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElem
///
template <typename _Scalar>
const _Scalar& DenseMatrixStorage<_Scalar>::operator()(
    const index_t idx0,
    const index_t idx1
) const noexcept {
  return getElem(idx0, idx1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position of given index.
///
template <typename _Scalar>
index_t DenseMatrixStorage<_Scalar>::getPos(
    const index_t idx0,
    const index_t idx1
) const noexcept {
  return idx0 + idx1 * pitch0_;
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_STORAGE_IPP_
