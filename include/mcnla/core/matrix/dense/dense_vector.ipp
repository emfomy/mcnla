////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_vector.ipp
/// @brief   The implementation of dense vector.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_IPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_IPP_

#include <mcnla/core/matrix/dense/dense_vector.hpp>
#include <iomanip>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector() noexcept
  : VectorBaseType(),
    DenseBaseType(),
    stride_(1) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector(
    const index_t length,
    const index_t stride
) noexcept
  : VectorBaseType(length),
    DenseBaseType(stride * length),
    stride_(stride) {
  assert(stride_ > 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector(
    const index_t length,
    const index_t stride,
    const index_t capability,
    const index_t offset
) noexcept
  : VectorBaseType(length),
    DenseBaseType(capability, offset),
    stride_(stride) {
  assert(stride_ > 0);
  assert(capability >= stride_ * (length_-1) + 1 + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector(
    const index_t length,
    const index_t stride,
    const ValuePtrType &value,
    const index_t offset
) noexcept
  : VectorBaseType(length),
    DenseBaseType(value, offset),
    stride_(stride) {
  assert(stride_ > 0);
  assert(this->getCapability() >= stride_ * (length_-1) + 1 + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct from data storage.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector(
    const index_t length,
    const index_t stride,
    const DataType &data,
    const index_t offset
) noexcept
  : VectorBaseType(length),
    DenseBaseType(data, offset),
    stride_(stride) {
  assert(stride_ > 0);
  assert(this->getCapability() >= stride_ * (length_-1) + 1 + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector( const DenseVector &other ) noexcept
  : VectorBaseType(other),
    DenseBaseType(other),
    stride_(other.stride_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector( DenseVector &&other ) noexcept
  : VectorBaseType(std::move(other)),
    DenseBaseType(std::move(other)),
    stride_(other.stride_) {
  other.stride_ = 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <typename _Scalar>
DenseVector<_Scalar>& DenseVector<_Scalar>::operator=( const DenseVector &other ) noexcept {
  VectorBaseType::operator=(other); DenseBaseType::operator=(other); stride_ = other.stride_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Scalar>
DenseVector<_Scalar>& DenseVector<_Scalar>::operator=( DenseVector &&other ) noexcept {
  VectorBaseType::operator=(std::move(other)); DenseBaseType::operator=(std::move(other));
  stride_ = other.stride_; other.stride_ = 1;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Print to stream.
///
template <typename __Scalar>
std::ostream& operator<< ( std::ostream &out, const DenseVector<__Scalar> &vector ) {
  for ( index_t i = 0; i < vector.length_; ++i ) {
    out << std::setw(ios_width) << vector(i) << "  ";
  }
  return out << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the stride.
///
template <typename _Scalar>
index_t DenseVector<_Scalar>::getStride() const noexcept { return stride_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the dimensions is equal to the sizes.
///
template <typename _Scalar>
bool DenseVector<_Scalar>::isShrunk() const noexcept {
  return (stride_ == 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element of given index.
///
template <typename _Scalar>
_Scalar& DenseVector<_Scalar>::getElem(
    const index_t idx
) noexcept {
  assert(idx >= 0 && idx < length_);
  return this->getValue()[getPos(idx)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElem
///
template <typename _Scalar>
const _Scalar& DenseVector<_Scalar>::getElem(
    const index_t idx
) const noexcept {
  assert(idx >= 0 && idx < length_);
  return this->getValue()[getPos(idx)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElem
///
template <typename _Scalar>
_Scalar& DenseVector<_Scalar>::operator()(
    const index_t idx
) noexcept { return getElem(idx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElem
///
template <typename _Scalar>
const _Scalar& DenseVector<_Scalar>::operator()(
    const index_t idx
) const noexcept { return getElem(idx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position of given index.
///
template <typename _Scalar>
index_t DenseVector<_Scalar>::getPos(
    const index_t idx
) const noexcept {
  return idx * stride_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Finds the iterator to element
///
template <typename _Scalar>
typename DenseVector<_Scalar>::IteratorType DenseVector<_Scalar>::find(
    const index_t idx
) noexcept {
  assert(idx >= 0 && idx < length_);
  return IteratorType(this, idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  find
///
template <typename _Scalar>
typename DenseVector<_Scalar>::ConstIteratorType DenseVector<_Scalar>::find(
    const index_t idx
) const noexcept {
  assert(idx >= 0 && idx < length_);
  return ConstIteratorType(this, idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  find
///
template <typename _Scalar>
typename DenseVector<_Scalar>::ConstIteratorType DenseVector<_Scalar>::cfind(
    const index_t idx
) const noexcept {
  return find(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Resizes the vector.
///
/// @attention  The new space is not initialized.
///
template <typename _Scalar>
void DenseVector<_Scalar>::resize(
    const index_t length
) noexcept {
  assert(length > 0 && length <= data_.getCapability());
  length_ = length;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the vector segment.
///
template <typename _Scalar>
DenseVector<_Scalar> DenseVector<_Scalar>::getSegment(
    const IdxRange range
) noexcept {
  assert(range.begin >= 0 && range.end <= length_ && range.getLength() >= 0);
  return DenseVector<_Scalar>(range.getLength(), stride_, data_, getPos(range.begin) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getSegment
///
template <typename _Scalar>
const DenseVector<_Scalar> DenseVector<_Scalar>::getSegment(
    const IdxRange range
) const noexcept {
  assert(range.begin >= 0 && range.end <= length_ && range.getLength() >= 0);
  return DenseVector<_Scalar>(range.getLength(), stride_, data_, getPos(range.begin) + offset_);
}

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_IPP_