////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_vector.ipp
/// @brief   The implementation of dense vector.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_VECTOR_IPP_
#define ISVD_MATRIX_DENSE_VECTOR_IPP_

#include <isvd/matrix/dense_vector.hpp>
#include <iomanip>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector() noexcept
  : VectorBaseType(),
    DenseBaseType(),
    increment_(1) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector(
    const index_t length,
    const index_t increment
) noexcept
  : VectorBaseType(length),
    DenseBaseType(increment * length),
    increment_(increment) {
  assert(increment_ > 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector(
    const index_t length,
    const index_t increment,
    std::shared_ptr<_Scalar> value
) noexcept
  : VectorBaseType(length),
    DenseBaseType(length * increment, value),
    increment_(increment) {
  assert(increment_ > 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector(
    const index_t length,
    const index_t increment,
    std::shared_ptr<_Scalar> value,
    const index_t capability,
    const index_t offset
) noexcept
  : VectorBaseType(length),
    DenseBaseType(capability, value, offset),
    increment_(increment) {
  assert(increment_ > 0);
  assert(capability >= increment_ * (length_-1) + 1 + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct from data storage.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector(
    const index_t length,
    const index_t increment,
    const DenseData<_Scalar> &data,
    const index_t offset
) noexcept
  : VectorBaseType(length),
    DenseBaseType(data, offset),
    increment_(increment) {
  assert(increment_ > 0);
  assert(data.getCapability() >= increment_ * (length_-1) + 1 + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses isvd::blas::copy.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector( const DenseVector &other ) noexcept
  : VectorBaseType(other),
    DenseBaseType(other),
    increment_(other.increment_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector( DenseVector &&other ) noexcept
  : VectorBaseType(std::move(other)),
    DenseBaseType(std::move(other)),
    increment_(other.increment_) {
  other.increment_ = 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses isvd::blas::copy.
///
template <typename _Scalar>
DenseVector<_Scalar>& DenseVector<_Scalar>::operator=( const DenseVector &other ) noexcept {
  VectorBaseType::operator=(other), DenseBaseType::operator=(other), increment_ = other.increment_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Scalar>
DenseVector<_Scalar>& DenseVector<_Scalar>::operator=( DenseVector &&other ) noexcept {
  VectorBaseType::operator=(other), DenseBaseType::operator=(other), increment_ = other.increment_; other.increment_ = 1;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Print to stream.
///
template <typename __Scalar>
std::ostream& operator<< ( std::ostream &out, const DenseVector<__Scalar> &vector ) {
  for ( index_t i = 0; i < vector.length_; ++i ) {
    out << std::setw(ios_width) << vector(i);
  }
  out << std::endl;
  return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the increment.
///
template <typename _Scalar>
index_t DenseVector<_Scalar>::getIncrement() const noexcept { return increment_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the dimensions is equal to the sizes.
///
template <typename _Scalar>
bool DenseVector<_Scalar>::isShrunk() const noexcept {
  return (increment_ == 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the iterator to beginning.
///
template <typename _Scalar>
typename DenseVector<_Scalar>::IteratorType DenseVector<_Scalar>::begin() noexcept {
  IteratorType retval(this);
  return retval.setBegin();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  begin
///
template <typename _Scalar>
const typename DenseVector<_Scalar>::IteratorType DenseVector<_Scalar>::begin() const noexcept {
  const IteratorType retval(this);
  return retval.setBegin();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the iterator to end.
///
template <typename _Scalar>
typename DenseVector<_Scalar>::IteratorType DenseVector<_Scalar>::end() noexcept {
  IteratorType retval(this);
  return retval.setEnd();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  end
///
template <typename _Scalar>
const typename DenseVector<_Scalar>::IteratorType DenseVector<_Scalar>::end() const noexcept {
  const IteratorType retval(this);
  return retval.setEnd();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element of given index.
///
template <typename _Scalar>
_Scalar& DenseVector<_Scalar>::getElem(
    const index_t idx
) noexcept {
  assert(idx >= 0 && idx < length_);
  return this->getValue()[getIndexInternal(idx)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElem
///
template <typename _Scalar>
const _Scalar& DenseVector<_Scalar>::getElem(
    const index_t idx
) const noexcept {
  assert(idx >= 0 && idx < length_);
  return this->getValue()[getIndexInternal(idx)];
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
/// @brief  Resize the vector.
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
    const IndexRange range
) noexcept {
  assert(range.begin >= 0 && range.end <= length_ && range.getLength() >= 0);
  return DenseVector<_Scalar>(range.getLength(), increment_, data_, getIndexInternal(range.begin) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getSegment
///
template <typename _Scalar>
const DenseVector<_Scalar> DenseVector<_Scalar>::getSegment(
    const IndexRange range
) const noexcept {
  assert(range.begin >= 0 && range.end <= length_ && range.getLength() >= 0);
  return DenseVector<_Scalar>(range.getLength(), increment_, data_, getIndexInternal(range.begin) + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal index of given index.
///
template <typename _Scalar>
index_t DenseVector<_Scalar>::getIndexInternal(
    const index_t idx
) const noexcept {
  return idx * increment_;
}

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_VECTOR_IPP_
