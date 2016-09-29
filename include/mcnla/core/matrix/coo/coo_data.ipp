////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_data.ipp
/// @brief   The implementation of COO data storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_DATA_IPP_
#define MCNLA_CORE_MATRIX_COO_COO_DATA_IPP_

#include <mcnla/core/matrix/coo/coo_data.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace.
//
namespace detail {

template <index_t _ndim, typename _Scalar, index_t __ndim, index_t __dim, index_t... __dims> template <typename... _Args>
CooData<__ndim, _Scalar> CooDataHelper<_ndim, _Scalar, __ndim, __dim, __dims...>::getData(
    DataType &data, _Args&... args
) noexcept {
  return CooDataHelper<_ndim, _Scalar, __ndim, __dims...>::getData(data, args..., data.template getIdxPtr<__dim>());
}

template <index_t _ndim, typename _Scalar, index_t __ndim, index_t __dim> template <typename... _Args>
CooData<__ndim, _Scalar> CooDataHelper<_ndim, _Scalar, __ndim, __dim>::getData(
    DataType &data, _Args&... args
) noexcept {
  return ReducedType(data.getValuePtr(), {args..., data.template getIdxPtr<__dim>()});
}

template <index_t _ndim, typename _Scalar, index_t __ndim, index_t __dim, index_t... __dims> template <typename... _Args>
const CooData<__ndim, _Scalar> CooDataHelper<_ndim, _Scalar, __ndim, __dim, __dims...>::getConstData(
    const DataType &data, _Args&... args
) noexcept {
  return CooDataHelper<_ndim, _Scalar, __ndim, __dims...>::getConstData(data, args..., data.template getIdxPtr<__dim>());
}

template <index_t _ndim, typename _Scalar, index_t __ndim, index_t __dim> template <typename... _Args>
const CooData<__ndim, _Scalar> CooDataHelper<_ndim, _Scalar, __ndim, __dim>::getConstData(
    const DataType &data, _Args&... args
) noexcept {
  return ReducedType(data.getValuePtr(), {args..., data.template getIdxPtr<__dim>()});
}

template <index_t _ndim, typename _Scalar, index_t _dim> template <typename... _Args>
CooTuple<_ndim, _Scalar, index_t> CooDataTupleHelper<_ndim, _Scalar, _dim>::getTuple(
    DataType &data, const index_t itidx, _Args&... args
) noexcept {
  return CooDataTupleHelper<_ndim, _Scalar, _dim-1>::getTuple(data, itidx, data.template getIdx<_dim>()[itidx], args...);
}

template <index_t _ndim, typename _Scalar> template <typename... _Args>
CooTuple<_ndim, _Scalar, index_t> CooDataTupleHelper<_ndim, _Scalar, 0>::getTuple(
    DataType &data, const index_t itidx, _Args&... args
) noexcept {
  return makeCooRefTuple(data.getValue()[itidx], data.template getIdx<0>()[itidx], args...);
}

template <index_t _ndim, typename _Scalar, index_t _dim> template <typename... _Args>
CooTuple<_ndim, const _Scalar, const index_t> CooDataTupleHelper<_ndim, _Scalar, _dim>::getConstTuple(
    const DataType &data, const index_t itidx, _Args&... args
) noexcept {
  return CooDataTupleHelper<_ndim, _Scalar, _dim-1>::getConstTuple(data, itidx, data.template getIdx<_dim>()[itidx], args...);
}

template <index_t _ndim, typename _Scalar> template <typename... _Args>
CooTuple<_ndim, const _Scalar, const index_t> CooDataTupleHelper<_ndim, _Scalar, 0>::getConstTuple(
    const DataType &data, const index_t itidx, _Args&... args
) noexcept {
  return makeCooRefTuple(data.getValue()[itidx], data.template getIdx<0>()[itidx], args...);
}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <index_t _ndim, typename _Scalar>
CooData<_ndim, _Scalar>::CooData() noexcept
  : value_(kNullValue),
    idxs_() {
  for ( index_t i = 0; i < _ndim; ++i ) {
    idxs_[i] = kNullIdx;
  }
}

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
    idxs_[i] = std::make_shared<std::valarray<index_t>>(capability);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
/// @attention  The size of @a value and each element in @a idxs should be the same.
///
template <index_t _ndim, typename _Scalar>
CooData<_ndim, _Scalar>::CooData(
    const ValuePtrType &value,
    const std::array<IdxPtrType, _ndim> &idxs
) noexcept
  : value_(value),
    idxs_(idxs) {
  for ( index_t i = 0; i < _ndim; ++i ) {
    assert(value->size() == idxs_[i]->size());
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <index_t _ndim, typename _Scalar>
CooData<_ndim, _Scalar>::CooData( const CooData &other ) noexcept
  : value_(other.value_),
    idxs_(other.idxs_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <index_t _ndim, typename _Scalar>
CooData<_ndim, _Scalar>::CooData( CooData &&other ) noexcept
  : value_(std::move(other.value_)),
    idxs_(std::move(other.idxs_)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <index_t _ndim, typename _Scalar>
CooData<_ndim, _Scalar>& CooData<_ndim, _Scalar>::operator=( const CooData &other ) noexcept {
  value_ = other.value_; idxs_ = other.idxs_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <index_t _ndim, typename _Scalar>
CooData<_ndim, _Scalar>& CooData<_ndim, _Scalar>::operator=( CooData &&other ) noexcept {
  value_ = std::move(other.value_); idxs_ = std::move(other.idxs_);
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
bool CooData<_ndim, _Scalar>::operator==( const CooData& other ) const noexcept {
  return this->value_ == other.value_ && this->idxs_ == other.idxs_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Not-equal-to operator.
///
template <index_t _ndim, typename _Scalar>
bool CooData<_ndim, _Scalar>::operator!=( const CooData& other ) const noexcept {
  return !(*this == other);
}

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
/// @brief  Gets the raw index array.
///
template <index_t _ndim, typename _Scalar>
index_t* CooData<_ndim, _Scalar>::getIdx( const index_t dim ) noexcept {
  assert(dim >= 0 && dim < _ndim);
  return &((*idxs_[dim])[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIdx
///
template <index_t _ndim, typename _Scalar>
const index_t* CooData<_ndim, _Scalar>::getIdx( const index_t dim ) const noexcept {
  assert(dim >= 0 && dim < _ndim);
  return &((*idxs_[dim])[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIdx
///
template <index_t _ndim, typename _Scalar> template <index_t _dim>
index_t* CooData<_ndim, _Scalar>::getIdx() noexcept {
  static_assert(_dim >= 0 && _dim < _ndim, "Invalid dimension!");
  return &((*idxs_[_dim])[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIdx
///
template <index_t _ndim, typename _Scalar> template <index_t _dim>
const index_t* CooData<_ndim, _Scalar>::getIdx() const noexcept {
  static_assert(_dim >= 0 && _dim < _ndim, "Invalid dimension!");
  return &((*idxs_[_dim])[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the tuple of given iterator index.
///
template <index_t _ndim, typename _Scalar>
CooTuple<_ndim, _Scalar, index_t> CooData<_ndim, _Scalar>::getTuple( const index_t itidx ) noexcept {
  return detail::CooDataTupleHelper<_ndim, _Scalar>::getTuple(*this, itidx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getTuple
///
template <index_t _ndim, typename _Scalar>
CooTuple<_ndim, const _Scalar, const index_t> CooData<_ndim, _Scalar>::getTuple( const index_t itidx ) const noexcept {
  return detail::CooDataTupleHelper<_ndim, _Scalar>::getConstTuple(*this, itidx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value array pointer.
///
template <index_t _ndim, typename _Scalar>
std::shared_ptr<std::valarray<_Scalar>>& CooData<_ndim, _Scalar>::getValuePtr() noexcept { return value_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValuePtr
///
template <index_t _ndim, typename _Scalar>
const std::shared_ptr<std::valarray<_Scalar>>& CooData<_ndim, _Scalar>::getValuePtr() const noexcept { return value_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index array pointer.
///
template <index_t _ndim, typename _Scalar>
std::shared_ptr<std::valarray<index_t>>& CooData<_ndim, _Scalar>::getIdxPtr( const index_t dim ) noexcept {
  assert(dim >= 0 && dim < _ndim);
  return idxs_[dim];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIdxPtr
///
template <index_t _ndim, typename _Scalar>
const std::shared_ptr<std::valarray<index_t>>& CooData<_ndim, _Scalar>::getIdxPtr( const index_t dim ) const noexcept {
  assert(dim >= 0 && dim < _ndim);
  return idxs_[dim];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIdxPtr
///
template <index_t _ndim, typename _Scalar> template <index_t _dim>
std::shared_ptr<std::valarray<index_t>>& CooData<_ndim, _Scalar>::getIdxPtr() noexcept {
  static_assert(_dim >= 0 && _dim < _ndim, "Invalid dimension!");
  return idxs_[_dim];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIdxPtr
///
template <index_t _ndim, typename _Scalar> template <index_t _dim>
const std::shared_ptr<std::valarray<index_t>>& CooData<_ndim, _Scalar>::getIdxPtr() const noexcept {
  static_assert(_dim >= 0 && _dim < _ndim, "Invalid dimension!");
  return idxs_[_dim];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reduces dimension.
///
template <index_t _ndim, typename _Scalar> template <index_t... _dims>
CooData<sizeof...(_dims), _Scalar> CooData<_ndim, _Scalar>::getReduced() noexcept {
  return detail::CooDataHelper<_ndim, _Scalar, sizeof...(_dims), _dims...>::getData(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getReduced
///
template <index_t _ndim, typename _Scalar> template <index_t... _dims>
const CooData<sizeof...(_dims), _Scalar> CooData<_ndim, _Scalar>::getReduced() const noexcept {
  return detail::CooDataHelper<_ndim, _Scalar, sizeof...(_dims), _dims...>::getConstData(*this);
}

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_DATA_IPP_
