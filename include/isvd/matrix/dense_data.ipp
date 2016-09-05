////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_data.ipp
/// @brief   The implementation of dense data storage.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DATA_IPP_
#define ISVD_MATRIX_DENSE_DATA_IPP_

#include <isvd/matrix/dense_data.hpp>
#include <isvd/utility/memory.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <typename _Scalar>
DenseData<_Scalar>::DenseData() noexcept
  : capability_(0),
    value_(nullptr) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar>
DenseData<_Scalar>::DenseData(
    const index_t capability
) noexcept
  : capability_(capability),
    value_(malloc<_Scalar>(capability)) {
  assert(capability > 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar>
DenseData<_Scalar>::DenseData(
    const index_t capability,
    std::shared_ptr<_Scalar> value
) noexcept
  : capability_(capability),
    value_(value) {
  assert(capability > 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
template <typename _Scalar>
DenseData<_Scalar>::DenseData( const DenseData &other ) noexcept
  : capability_(other.capability_),
    value_(other.value_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar>
DenseData<_Scalar>::DenseData( DenseData &&other ) noexcept
  : capability_(other.capability_),
    value_(std::move(other.value_)) {
  other.capability_ = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses isvd::blas::copy.
///
template <typename _Scalar>
DenseData<_Scalar>& DenseData<_Scalar>::operator=( const DenseData &other ) noexcept {
  capability_ = other.capability_; value_ = other.value_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Scalar>
DenseData<_Scalar>& DenseData<_Scalar>::operator=( DenseData &&other ) noexcept {
  capability_ = other.capability_; value_ = std::move(other.value_); other.capability_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The equal-to operator
///
template <typename _Scalar>
bool DenseData<_Scalar>::operator==( const DenseData& other ) const noexcept { return this->value_ == other.value_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The not-equal-to operator
///
template <typename _Scalar>
bool DenseData<_Scalar>::operator!=( const DenseData& other ) const noexcept { return this->value_ != other.value_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the length of data array.
///
template <typename _Scalar>
index_t DenseData<_Scalar>::getCapability() const noexcept { return capability_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw value array.
///
template <typename _Scalar>
_Scalar* DenseData<_Scalar>::getValue() noexcept { return value_.get(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar>
const _Scalar* DenseData<_Scalar>::getValue() const noexcept { return value_.get(); }

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DATA_IPP_
