////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_vector.ipp
/// @brief   The implementation of dense vector.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_VECTOR_IPP_
#define ISVD_MATRIX_DENSE_VECTOR_IPP_

#include <isvd/matrix/dense_matrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector() noexcept
  : length_(0),
    increment_(0),
    offset_(0),
    data_() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector(
    const index_t length,
    const index_t increment
) noexcept
  : length_(length),
    increment_(increment),
    offset_(0),
    data_(increment_ * length_) {
  assert(length_ > 0);
  assert(increment_ > 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
/// @attention  DO NOT FREE @a value!!
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector(
    const index_t length,
    const index_t increment,
    _Scalar *value
) noexcept
  : length_(length),
    increment_(increment),
    offset_(0),
    data_(increment_ * length_, value) {
  assert(length_ > 0);
  assert(increment_ > 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
/// @attention  DO NOT FREE @a value!!
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector(
    const index_t length,
    const index_t increment,
    _Scalar *value,
    const index_t capability,
    const index_t offset
) noexcept
  : length_(length),
    increment_(increment),
    offset_(offset),
    data_(capability, value) {
  assert(length_ > 0);
  assert(increment_ > 0);
  assert(capability >= increment_ * length_);
  assert(offset_ >= 0);
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
  : length_(length),
    increment_(increment),
    offset_(offset),
    data_(data) {
  assert(length_ > 0);
  assert(increment_ > 0);
  assert(data.getCapability() >= increment_ * length_);
  assert(offset_ >= 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default destructor.
///
template <typename _Scalar>
DenseVector<_Scalar>::~DenseVector() noexcept {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Print to stream.
///
template <typename __Scalar>
std::ostream& operator<< ( std::ostream &out, const DenseVector<__Scalar> &vector ) {
  for ( auto i = 0; i < vector.length_; ++i ) {
    out << vector(i) << '\t';
  }
  out << std::endl;
  return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of entries.
///
template <typename _Scalar>
index_t DenseVector<_Scalar>::getLengthImpl() const noexcept { return length_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the increment.
///
template <typename _Scalar>
index_t DenseVector<_Scalar>::getIncrementImpl() const noexcept { return increment_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the offset of starting position.
///
template <typename _Scalar>
index_t DenseVector<_Scalar>::getOffsetImpl() const noexcept { return offset_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the data storage.
///
template <typename _Scalar>
DenseData<_Scalar>& DenseVector<_Scalar>::getDataImpl() noexcept { return data_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the data storage.
///
template <typename _Scalar>
const DenseData<_Scalar>& DenseVector<_Scalar>::getDataImpl() const noexcept { return data_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element.
///
template <typename _Scalar>
_Scalar& DenseVector<_Scalar>::getElementImpl(
    const index_t idx
) noexcept {
  assert(idx >= 0 && idx < length_);
  return this->getValue()[getIndexInternal(idx)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element.
///
template <typename _Scalar>
const _Scalar& DenseVector<_Scalar>::getElementImpl(
    const index_t idx
) const noexcept {
  assert(idx >= 0 && idx < length_);
  return this->getValue()[getIndexInternal(idx)];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Resize the vector.
///
/// @attention  THE NEW SPACE IS NOT INITIALIZED.
///
template <typename _Scalar>
void DenseVector<_Scalar>::resizeImpl(
    const index_t length
) noexcept {
  assert(length >= 0 && length <= data_.getCapability());
  length_ = length;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a segment vector.
///
template <typename _Scalar>
DenseVector<_Scalar> DenseVector<_Scalar>::getSegmentImpl(
    const IndexRange range
) noexcept {
  assert(range.start >= 0 && range.end <= length_ && range.getLength() >= 0);
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
  return idx * increment_;
}

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_VECTOR_IPP_
