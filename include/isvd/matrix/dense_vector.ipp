////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_vector.ipp
/// @brief   The implementation of dense vector.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_VECTOR_IPP_
#define ISVD_MATRIX_DENSE_VECTOR_IPP_

#include <isvd/matrix/dense_vector.hpp>

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
  assert(capability >= increment_ * length_);
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
  assert(data.getCapability() >= increment_ * length_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector( const DenseVector &other ) noexcept
  : VectorBaseType(other),
    DenseBaseType(other),
    increment_(other.increment_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector( DenseVector &&other ) noexcept
  : VectorBaseType(std::move(other)),
    DenseBaseType(std::move(other)),
    increment_(other.increment_) {
  other.increment_ = 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses isvd::blas::copy.
///
template <typename _Scalar>
DenseVector<_Scalar>& DenseVector<_Scalar>::operator=( const DenseVector &other ) noexcept {
  VectorBaseType::operator=(other), DenseBaseType::operator=(other), increment_ = other.increment_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
  for ( auto i = 0; i < vector.length_; ++i ) {
    out << std::setw(ios_width) << vector(i) << '\t';
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
/// @brief  Gets the element of given index.
///
template <typename _Scalar>
_Scalar& DenseVector<_Scalar>::getElement(
    const index_t idx
) noexcept {
  assert(idx >= 0 && idx < length_);
  return this->getValue()[getIndexInternal(idx)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElement
///
template <typename _Scalar>
const _Scalar& DenseVector<_Scalar>::getElement(
    const index_t idx
) const noexcept {
  assert(idx >= 0 && idx < length_);
  return this->getValue()[getIndexInternal(idx)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElement
///
template <typename _Scalar>
_Scalar& DenseVector<_Scalar>::operator()(
    const index_t idx
) noexcept { return getElement(idx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElement
///
template <typename _Scalar>
const _Scalar& DenseVector<_Scalar>::operator()(
    const index_t idx
) const noexcept { return getElement(idx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Resize the vector.
///
/// @attention  THE NEW SPACE IS NOT INITIALIZED.
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
  assert(range.start >= 0 && range.end <= length_ && range.getLength() > 0);
  return DenseVector<_Scalar>(range.getLength(), increment_, data_, getIndexInternal(range.start));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal index of given index.
///
template <typename _Scalar>
index_t DenseVector<_Scalar>::getIndexInternal(
    const index_t idx
) const noexcept {
  assert(idx >= 0 && idx <= length_);
  return idx * increment_ + offset_;
}

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_VECTOR_IPP_
