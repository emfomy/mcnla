////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/coo/coo_data.ipp
/// @brief   The implementation of COO data storage.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_COO_COO_DATA_IPP_
#define ISVD_MATRIX_COO_COO_DATA_IPP_

#include <isvd/matrix/coo/coo_data.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <typename _Scalar, index_t _ndim>
CooData<_Scalar, _ndim>::CooData() noexcept
  : value_(kNullValue),
    idx_({kNullIdx}) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, index_t _ndim>
CooData<_Scalar, _ndim>::CooData(
    const index_t capability
) noexcept
  : value_(new std::valarray<_Scalar>(capability)) {
  assert(capability > 0);
  for ( index_t i = 0; i < _ndim; ++i ) {
    idx_[i] = new std::valarray<index_t>(capability);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
/// @attention  The size of @p value and each element in @p idx should be the same.
///
template <typename _Scalar, index_t _ndim>
CooData<_Scalar, _ndim>::CooData(
    ValuePtrType value,
    std::array<IdxPtrType, _ndim> idx
) noexcept
  : value_(value),
    idx_(idx) {
  for ( index_t i = 0; i < _ndim; ++i ) {
    assert(value->size() == idx_[i]->size());
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses isvd::blas::copy.
///
template <typename _Scalar, index_t _ndim>
CooData<_Scalar, _ndim>::CooData( const CooData &other ) noexcept
  : value_(other.value_),
    idx_(other.idx_) {
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar, index_t _ndim>
CooData<_Scalar, _ndim>::CooData( CooData &&other ) noexcept
  : value_(std::move(other.value_)),
    idx_(std::move(other.idx_)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses isvd::blas::copy.
///
template <typename _Scalar, index_t _ndim>
CooData<_Scalar, _ndim>& CooData<_Scalar, _ndim>::operator=( const CooData &other ) noexcept {
  value_ = other.value_; idx_ = other.idx_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Scalar, index_t _ndim>
CooData<_Scalar, _ndim>& CooData<_Scalar, _ndim>::operator=( CooData &&other ) noexcept {
  value_ = std::move(other.value_); idx_ = std::move(other.idx_);
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
index_t CooData<_Scalar, _ndim>::getCapability() const noexcept { return value_.size(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw value array.
///
template <typename _Scalar, index_t _ndim>
_Scalar* CooData<_Scalar, _ndim>::getValue() noexcept { return &((*value_)[0]); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar, index_t _ndim>
const _Scalar* CooData<_Scalar, _ndim>::getValue() const noexcept { return &((*value_)[0]); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw value array.
///
template <typename _Scalar, index_t _ndim> template <index_t dim>
const index_t* CooData<_Scalar, _ndim>::getIdx() const noexcept {
  static_assert(dim >= 0 && dim < _ndim, "Invalid dimension!");
  return (idx_[dim] != nullptr) ? &((*idx_[dim])[0]) : nullptr;
}

}  // namespace isvd

#endif  // ISVD_MATRIX_COO_COO_DATA_IPP_
