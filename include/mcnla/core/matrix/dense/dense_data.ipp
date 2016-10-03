////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_data.ipp
/// @brief   The implementation of dense data storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_DATA_IPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_DATA_IPP_

#include <mcnla/core/matrix/dense/dense_data.hpp>

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
DenseData<_Scalar>::DenseData() noexcept
  : value_() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseData<_Scalar>::DenseData(
    const index_t capability
) noexcept
  : value_(capability) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar>
DenseData<_Scalar>::DenseData(
    const ValueArrayType &value
) noexcept
  : value_(value) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <typename _Scalar>
DenseData<_Scalar>::DenseData( const DenseData &other ) noexcept
  : value_(other.value_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar>
DenseData<_Scalar>::DenseData( DenseData &&other ) noexcept
  : value_(std::move(other.value_)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <typename _Scalar>
DenseData<_Scalar>& DenseData<_Scalar>::operator=( const DenseData &other ) noexcept {
  value_ = other.value_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Scalar>
DenseData<_Scalar>& DenseData<_Scalar>::operator=( DenseData &&other ) noexcept {
  value_ = std::move(other.value_);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Right-shift the offset.
///
template <typename _Scalar>
void DenseData<_Scalar>::operator>>=( const index_t offset ) noexcept {
  value_ >>= offset;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Left-shift the offset.
///
template <typename _Scalar>
void DenseData<_Scalar>::operator<<=( const index_t offset ) noexcept {
  value_ <<= offset;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Right-shift the offset.
///
template <typename _Scalar>
DenseData<_Scalar> DenseData<_Scalar>::operator>>( const index_t offset ) noexcept {
  return DenseData(value_ >> offset);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Right-shift the offset.
///
template <typename _Scalar>
const DenseData<_Scalar> DenseData<_Scalar>::operator>>( const index_t offset ) const noexcept {
  return DenseData(value_ >> offset);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Left-shift the offset.
///
template <typename _Scalar>
DenseData<_Scalar> DenseData<_Scalar>::operator<<( const index_t offset ) noexcept {
  return DenseData(value_ << offset);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Left-shift the offset.
///
template <typename _Scalar>
const DenseData<_Scalar> DenseData<_Scalar>::operator<<( const index_t offset ) const noexcept {
  return DenseData(value_ << offset);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the length of value array.
///
template <typename _Scalar>
index_t DenseData<_Scalar>::getCapability() const noexcept { return value_.getCapability(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the offset of value array.
///
template <typename _Scalar>
index_t DenseData<_Scalar>::getOffset() const noexcept { return value_.getOffset(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw value array.
///
template <typename _Scalar>
_Scalar* DenseData<_Scalar>::getValue() noexcept { return *value_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar>
const _Scalar* DenseData<_Scalar>::getValue() const noexcept { return *value_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value array.
///
template <typename _Scalar>
Array<_Scalar>& DenseData<_Scalar>::getValueArray() noexcept { return value_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValueArray
///
template <typename _Scalar>
const Array<_Scalar>& DenseData<_Scalar>::getValueArray() const noexcept { return value_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value valarray.
///
template <typename _Scalar>
std::valarray<_Scalar>& DenseData<_Scalar>::getValueValarray() noexcept { return value_.getValarray(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValueValarray
///
template <typename _Scalar>
const std::valarray<_Scalar>& DenseData<_Scalar>::getValueValarray() const noexcept { return value_.getValarray(); }

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_DATA_IPP_
