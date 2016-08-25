////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_vector.ipp
/// @brief   The implementation of dense vector.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_VECTOR_IPP_
#define ISVD_MATRIX_DENSE_VECTOR_IPP_

#include <isvd/matrix/dense_matrix.hpp>
#include <isvd/utility/memory.hpp>

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
    capability_(0),
    value_(nullptr) {}

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
    capability_(increment_ * length_),
    value_(Malloc<_Scalar>(capability_)) {}

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
    capability_(increment_ * length_),
    value_(value) {}

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
    capability_(capability),
    value_(value) {
  assert(capability_ >= increment_ * length_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct from another vector.
///
template <typename _Scalar>
DenseVector<_Scalar>::DenseVector(
    const DenseVector &other,
    const index_t length,
    const index_t offset
) noexcept
  : length_(length),
    increment_(other.increment_),
    offset_(offset),
    capability_(other.capability_),
    value_(other.value_) {}

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
    out << vector.getValueImpl(i) << '\t';
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
/// @brief  Gets the length of data array.
///
template <typename _Scalar>
index_t DenseVector<_Scalar>::getCapabilityImpl() const noexcept { return capability_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw value array.
///
template <typename _Scalar>
_Scalar* DenseVector<_Scalar>::getValueImpl() noexcept { return value_.get() + offset_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw value array.
///
template <typename _Scalar>
const _Scalar* DenseVector<_Scalar>::getValueImpl() const noexcept { return value_.get() + offset_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value of given index.
///
template <typename _Scalar>
_Scalar& DenseVector<_Scalar>::getValueImpl(
    const index_t idx
) noexcept {
  assert(idx >= 0 && idx < length_);
  return getValueImpl()[idx * increment_];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value of given index.
///
template <typename _Scalar>
const _Scalar& DenseVector<_Scalar>::getValueImpl(
    const index_t idx
) const noexcept {
  assert(idx >= 0 && idx < length_);
  return getValueImpl()[idx * increment_];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a segment vector.
///
template <typename _Scalar>
DenseVector<_Scalar> DenseVector<_Scalar>::getSegmentImpl(
    const index_t idx,
    const index_t length
) noexcept {
  assert(idx >= 0 && idx + length <= length_);
  return DenseVector<_Scalar>(*this, length, &getValueImpl(idx) - getValueImpl());
}

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_VECTOR_IPP_
