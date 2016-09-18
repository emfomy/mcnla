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
//  The internal namespace.
//
namespace internal {

template <index_t _ndim, typename _Scalar, index_t _dim> template <typename... _Args>
typename CooDataHelper<_ndim, _Scalar, _dim>::TupleType CooDataHelper<_ndim, _Scalar, _dim>::getTuple(
    DataType &data, const index_t pos, _Args&... args
) noexcept {
  return CooTupleHelper<_ndim, _dim-1>::getTuple(data, pos, data.template getIdx<_dim>()[pos], args...);
}

template <index_t _ndim, typename _Scalar, index_t _dim> template <typename... _Args>
typename CooDataHelper<_ndim, _Scalar, _dim>::ConstTupleType CooDataHelper<_ndim, _Scalar, _dim>::getConstTuple(
    const DataType &data, const index_t pos, _Args&... args
) noexcept {
  return CooTupleHelper<_ndim, _dim-1>::getConstTuple(data, pos, data.template getIdx<_dim>()[pos], args...);
}

template <index_t _ndim, typename _Scalar> template <typename... _Args>
typename CooDataHelper<_ndim, _Scalar, 0>::TupleType CooDataHelper<_ndim, _Scalar, 0>::getTuple(
    DataType &data, const index_t pos, _Args&... args
) noexcept {
  return makeCooRefTuple(data.getValue()[pos], data.template getIdx<0>()[pos], args...);
}

template <index_t _ndim, typename _Scalar> template <typename... _Args>
typename CooDataHelper<_ndim, _Scalar, 0>::ConstTupleType CooDataHelper<_ndim, _Scalar, 0>::getConstTuple(
    const DataType &data, const index_t pos, _Args&... args
) noexcept {
  return makeCooRefTuple(data.getValue()[pos], data.template getIdx<0>()[pos], args...);
}

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <index_t _ndim, typename _Scalar>
CooData<_ndim, _Scalar>::CooData() noexcept
  : value_(kNullValue),
    idx_({kNullIdx}) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <index_t _ndim, typename _Scalar>
CooData<_ndim, _Scalar>::CooData(
    const index_t capability
) noexcept
  : value_(new std::valarray<_Scalar>(capability)) {
  assert(capability > 0);
  for ( index_t i = 0; i < _ndim; ++i ) {
    idx_[i] = std::make_shared<std::valarray<index_t>>(capability);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
/// @attention  The size of @p value and each element in @p idx should be the same.
///
template <index_t _ndim, typename _Scalar>
CooData<_ndim, _Scalar>::CooData(
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
template <index_t _ndim, typename _Scalar>
CooData<_ndim, _Scalar>::CooData( const CooData &other ) noexcept
  : value_(other.value_),
    idx_(other.idx_) {
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <index_t _ndim, typename _Scalar>
CooData<_ndim, _Scalar>::CooData( CooData &&other ) noexcept
  : value_(std::move(other.value_)),
    idx_(std::move(other.idx_)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses isvd::blas::copy.
///
template <index_t _ndim, typename _Scalar>
CooData<_ndim, _Scalar>& CooData<_ndim, _Scalar>::operator=( const CooData &other ) noexcept {
  value_ = other.value_; idx_ = other.idx_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <index_t _ndim, typename _Scalar>
CooData<_ndim, _Scalar>& CooData<_ndim, _Scalar>::operator=( CooData &&other ) noexcept {
  value_ = std::move(other.value_); idx_ = std::move(other.idx_);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <index_t _ndim, typename _Scalar>
_Scalar* CooData<_ndim, _Scalar>::operator*() noexcept { return getValue(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <index_t _ndim, typename _Scalar>
const _Scalar* CooData<_ndim, _Scalar>::operator*() const noexcept { return getValue(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Equal-to operator.
///
template <index_t _ndim, typename _Scalar>
bool CooData<_ndim, _Scalar>::operator==( const CooData& other ) const noexcept { return this->value_ == other.value_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Not-equal-to operator.
///
template <index_t _ndim, typename _Scalar>
bool CooData<_ndim, _Scalar>::operator!=( const CooData& other ) const noexcept { return this->value_ != other.value_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the length of value array.
///
template <index_t _ndim, typename _Scalar>
index_t CooData<_ndim, _Scalar>::getCapability() const noexcept { return value_->size(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw value array.
///
template <index_t _ndim, typename _Scalar>
_Scalar* CooData<_ndim, _Scalar>::getValue() noexcept { return &((*value_)[0]); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <index_t _ndim, typename _Scalar>
const _Scalar* CooData<_ndim, _Scalar>::getValue() const noexcept { return &((*value_)[0]); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw value array.
///
template <index_t _ndim, typename _Scalar>
index_t* CooData<_ndim, _Scalar>::getIdx( const index_t dim ) noexcept {
  assert(dim >= 0 && dim < _ndim);
  return (idx_[dim] != nullptr) ? &((*idx_[dim])[0]) : nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIdx
///
template <index_t _ndim, typename _Scalar>
const index_t* CooData<_ndim, _Scalar>::getIdx( const index_t dim ) const noexcept {
  assert(dim >= 0 && dim < _ndim);
  return (idx_[dim] != nullptr) ? &((*idx_[dim])[0]) : nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIdx
///
template <index_t _ndim, typename _Scalar> template <index_t _dim>
index_t* CooData<_ndim, _Scalar>::getIdx() noexcept {
  static_assert(_dim >= 0 && _dim < _ndim, "Invalid dimension!");
  return (idx_[_dim] != nullptr) ? &((*idx_[_dim])[0]) : nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIdx
///
template <index_t _ndim, typename _Scalar> template <index_t _dim>
const index_t* CooData<_ndim, _Scalar>::getIdx() const noexcept {
  static_assert(_dim >= 0 && _dim < _ndim, "Invalid dimension!");
  return (idx_[_dim] != nullptr) ? &((*idx_[_dim])[0]) : nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the tuple of given position.
///
template <index_t _ndim, typename _Scalar>
typename CooData<_ndim, _Scalar>::TupleType CooData<_ndim, _Scalar>::getTuple( const index_t pos ) noexcept {
  return internal::CooDataHelper<_ndim, _Scalar>::getTuple(*this, pos);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getTuple
///
template <index_t _ndim, typename _Scalar>
typename CooData<_ndim, _Scalar>::ConstTupleType CooData<_ndim, _Scalar>::getTuple( const index_t pos ) const noexcept {
  return internal::CooDataHelper<_ndim, _Scalar>::getConstTuple(*this, pos);
}

}  // namespace isvd

#endif  // ISVD_MATRIX_COO_COO_DATA_IPP_
