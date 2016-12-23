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
    dim0_(0),
    dim1_(0),
    pitch_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseMatrixStorage<_Scalar>::DenseMatrixStorage(
    const index_t dim0,
    const index_t dim1
) noexcept
  : BaseType(dim0 * dim1),
    dim0_(dim0),
    dim1_(dim1),
    pitch_(dim0) {
  mcnla_assert_ge(dim0_, 0);
  mcnla_assert_ge(dim1_, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseMatrixStorage<_Scalar>::DenseMatrixStorage(
    const index_t dim0,
    const index_t dim1,
    const index_t pitch
) noexcept
  : BaseType(dim0 * pitch),
    dim0_(dim0),
    dim1_(dim1),
    pitch_(pitch) {
  mcnla_assert_ge(dim0_, 0);
  mcnla_assert_ge(dim1_, 0);
  mcnla_assert_ge(pitch_, dim0_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseMatrixStorage<_Scalar>::DenseMatrixStorage(
    const index_t dim0,
    const index_t dim1,
    const index_t pitch,
    const index_t capacity
) noexcept
  : BaseType(capacity),
    dim0_(dim0),
    dim1_(dim1),
    pitch_(pitch) {
  mcnla_assert_ge(dim0_, 0);
  mcnla_assert_ge(dim1_, 0);
  mcnla_assert_ge(pitch_, dim0_);
  mcnla_assert_ge(capacity, pitch_ * (dim1_-1) + dim0_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar>
DenseMatrixStorage<_Scalar>::DenseMatrixStorage(
    const index_t dim0,
    const index_t dim1,
    const index_t pitch,
    const ValueArrayType &value,
    const index_t offset
) noexcept
  : BaseType(value >> offset),
    dim0_(dim0),
    dim1_(dim1),
    pitch_(pitch) {
  mcnla_assert_ge(dim0_, 0);
  mcnla_assert_ge(dim1_, 0);
  mcnla_assert_ge(pitch_, dim0_);
  mcnla_assert_ge(this->getCapacity(), pitch_ * (dim1_-1) + dim0_);
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
    dim0_(other.dim0_),
    dim1_(other.dim1_),
    pitch_(other.pitch_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar>
DenseMatrixStorage<_Scalar>::DenseMatrixStorage(
  DenseMatrixStorage &&other
) noexcept
  : BaseType(std::move(other)),
    dim0_(other.dim0_),
    dim1_(other.dim1_),
    pitch_(other.pitch_) {
  other.dim0_  = 0;
  other.dim1_  = 0;
  other.pitch_ = 0;
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
  dim0_  = other.dim0_;
  dim1_  = other.dim1_;
  pitch_ = other.pitch_;
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
  dim0_  = other.dim0_;  other.dim0_  = 0;
  dim1_  = other.dim1_;  other.dim1_  = 0;
  pitch_ = other.pitch_; other.pitch_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the dimensions are equal to the sizes.
///
template <typename _Scalar>
bool DenseMatrixStorage<_Scalar>::isShrunk() const noexcept {
  return (dim0_ == pitch_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the matrix is square.
///
template <typename _Scalar>
bool DenseMatrixStorage<_Scalar>::isSquare() const noexcept {
  return (dim0_ == dim1_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size in the first dimension.
///
template <typename _Scalar>
index_t DenseMatrixStorage<_Scalar>::getDim0() const noexcept {
  return dim0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size in the second dimension.
///
template <typename _Scalar>
index_t DenseMatrixStorage<_Scalar>::getDim1() const noexcept {
  return dim1_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size of dimensions in storage order. [ dim0, dim1 ]
///
template <typename _Scalar>
std::tuple<index_t, index_t> DenseMatrixStorage<_Scalar>::getDims() const noexcept {
  return std::make_tuple(dim0_, dim1_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the maximum size in the first dimension.
///
template <typename _Scalar>
index_t DenseMatrixStorage<_Scalar>::getPitch() const noexcept {
  return pitch_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element of given index.
///
template <typename _Scalar>
_Scalar& DenseMatrixStorage<_Scalar>::getElem(
    const index_t idx0,
    const index_t idx1
) noexcept {
  mcnla_assert_gelt(idx0, 0, dim0_);
  mcnla_assert_gelt(idx1, 0, dim1_);
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
  mcnla_assert_gelt(idx0, 0, dim0_);
  mcnla_assert_gelt(idx1, 0, dim1_);
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
  return idx0 + idx1 * pitch_;
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_STORAGE_IPP_
