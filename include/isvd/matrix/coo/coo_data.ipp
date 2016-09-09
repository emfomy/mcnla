////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/coo/coo_data.ipp
/// @brief   The implementation of COO data storage.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_COO_COO_DATA_IPP_
#define ISVD_MATRIX_COO_COO_DATA_IPP_

#include <isvd/matrix/coo/coo_data.hpp>
#include <isvd/utility/memory.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <typename _Scalar, index_t _ndim>
CooData<_Scalar, _ndim>::CooData() noexcept
  : capability_(0),
    value_(nullptr),
    idx_({nullptr}) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, index_t _ndim>
CooData<_Scalar, _ndim>::CooData(
    const index_t capability
) noexcept
  : capability_(capability),
    value_(malloc<_Scalar>(capability)) {
  assert(capability > 0);
  for ( index_t i = 0; i < _ndim; ++i ) {
    idx_[i] = std::shared_ptr<index_t>(malloc<index_t>(capability));
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar, index_t _ndim>
CooData<_Scalar, _ndim>::CooData(
    const index_t capability,
    std::shared_ptr<_Scalar> value,
    std::array<std::shared_ptr<index_t>, _ndim> idx
) noexcept
  : capability_(capability),
    value_(value),
    idx_(idx) {
  assert(capability > 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
template <typename _Scalar, index_t _ndim>
CooData<_Scalar, _ndim>::CooData( const CooData &other ) noexcept
  : capability_(other.capability_),
    value_(other.value_),
    idx_(other.idx_) {
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar, index_t _ndim>
CooData<_Scalar, _ndim>::CooData( CooData &&other ) noexcept
  : capability_(other.capability_),
    value_(std::move(other.value_)),
    idx_(std::move(other.idx_)) {
  other.capability_ = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses isvd::blas::copy.
///
template <typename _Scalar, index_t _ndim>
CooData<_Scalar, _ndim>& CooData<_Scalar, _ndim>::operator=( const CooData &other ) noexcept {
  capability_ = other.capability_; value_ = other.value_; idx_ = other.idx_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Scalar, index_t _ndim>
CooData<_Scalar, _ndim>& CooData<_Scalar, _ndim>::operator=( CooData &&other ) noexcept {
  capability_ = other.capability_; value_ = std::move(other.value_);  idx_ = std::move(other.idx_); other.capability_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar, index_t _ndim>
_Scalar* CooData<_Scalar, _ndim>::operator*() noexcept { return getValue(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar, index_t _ndim>
const _Scalar* CooData<_Scalar, _ndim>::operator*() const noexcept { return getValue(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Equal-to operator.
///
template <typename _Scalar, index_t _ndim>
bool CooData<_Scalar, _ndim>::operator==( const CooData& other ) const noexcept { return this->value_ == other.value_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Not-equal-to operator.
///
template <typename _Scalar, index_t _ndim>
bool CooData<_Scalar, _ndim>::operator!=( const CooData& other ) const noexcept { return this->value_ != other.value_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the length of data array.
///
template <typename _Scalar, index_t _ndim>
index_t CooData<_Scalar, _ndim>::getCapability() const noexcept { return capability_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw value array.
///
template <typename _Scalar, index_t _ndim>
_Scalar* CooData<_Scalar, _ndim>::getValue() noexcept { return value_.get(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar, index_t _ndim>
const _Scalar* CooData<_Scalar, _ndim>::getValue() const noexcept { return value_.get(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw value array.
///
template <typename _Scalar, index_t _ndim> template <index_t dim>
index_t* CooData<_Scalar, _ndim>::getIdx() const noexcept {
  static_assert(dim >= 0 && dim < _ndim, "Invalid dimension!");
  return idx_[dim].get();
}

}  // namespace isvd

#endif  // ISVD_MATRIX_COO_COO_DATA_IPP_
