////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense/dense_data.ipp
/// @brief   The implementation of dense data storage.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DENSE_DATA_IPP_
#define ISVD_MATRIX_DENSE_DENSE_DATA_IPP_

#include <isvd/matrix/dense/dense_data.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <typename _Scalar>
DenseData<_Scalar>::DenseData() noexcept
  : value_(nullptr) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseData<_Scalar>::DenseData(
    const index_t capability
) noexcept
  : value_(new std::valarray<_Scalar>(capability)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar>
DenseData<_Scalar>::DenseData(
    const ValuePtrType &value
) noexcept
  : value_(value) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
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
/// @attention  It is shallow copy. For deep copy, uses isvd::blas::copy.
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
/// @brief  Equal-to operator.
///
template <typename _Scalar>
bool DenseData<_Scalar>::operator==( const DenseData& other ) const noexcept { return this->value_ == other.value_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Not-equal-to operator.
///
template <typename _Scalar>
bool DenseData<_Scalar>::operator!=( const DenseData& other ) const noexcept { return this->value_ != other.value_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar>
_Scalar* DenseData<_Scalar>::operator*() noexcept { return getValue(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar>
const _Scalar* DenseData<_Scalar>::operator*() const noexcept { return getValue(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw value array.
///
template <typename _Scalar>
_Scalar* DenseData<_Scalar>::getValue() noexcept { return (value_ != nullptr) ? &((*value_)[0]) : nullptr; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar>
const _Scalar* DenseData<_Scalar>::getValue() const noexcept { return (value_ != nullptr) ? &((*value_)[0]) : nullptr; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the length of data array.
///
template <typename _Scalar>
index_t DenseData<_Scalar>::getCapability() const noexcept { return value_->size(); }

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_DATA_IPP_
