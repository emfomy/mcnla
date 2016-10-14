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
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace.
//
namespace detail {

template <index_t _ndim, typename _Scalar, index_t __ndim, index_t __dim, index_t... __dims> template <typename... _Args>
CooData<__ndim, _Scalar> CooDataHelper<_ndim, _Scalar, __ndim, __dim, __dims...>::getData(
    DataType &data, _Args&... args
) noexcept {
  return CooDataHelper<_ndim, _Scalar, __ndim, __dims...>::getData(data, args..., data.template getIdxArray<__dim>());
}

template <index_t _ndim, typename _Scalar, index_t __ndim, index_t __dim> template <typename... _Args>
CooData<__ndim, _Scalar> CooDataHelper<_ndim, _Scalar, __ndim, __dim>::getData(
    DataType &data, _Args&... args
) noexcept {
  return ReducedType(data.getValueArray(), {args..., data.template getIdxArray<__dim>()});
}

template <index_t _ndim, typename _Scalar, index_t __ndim, index_t __dim, index_t... __dims> template <typename... _Args>
const CooData<__ndim, _Scalar> CooDataHelper<_ndim, _Scalar, __ndim, __dim, __dims...>::getConstData(
    const DataType &data, _Args&... args
) noexcept {
  return CooDataHelper<_ndim, _Scalar, __ndim, __dims...>::getConstData(data, args..., data.template getIdxArray<__dim>());
}

template <index_t _ndim, typename _Scalar, index_t __ndim, index_t __dim> template <typename... _Args>
const CooData<__ndim, _Scalar> CooDataHelper<_ndim, _Scalar, __ndim, __dim>::getConstData(
    const DataType &data, _Args&... args
) noexcept {
  return ReducedType(data.getValueArray(), {args..., data.template getIdxArray<__dim>()});
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
  : value_(),
    idxs_() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <index_t _ndim, typename _Scalar>
CooData<_ndim, _Scalar>::CooData(
    const index_t capacity
) noexcept
  : value_(capacity) {
  for ( auto &idx : idxs_ ) {
    idx = IdxArrayType(capacity);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <index_t _ndim, typename _Scalar>
CooData<_ndim, _Scalar>::CooData(
    const ValueArrayType &value,
    const std::array<IdxArrayType, _ndim> &idxs
) noexcept
  : value_(value),
    idxs_(idxs) {}

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
/// @brief  Right-shift the offset.
///
template <index_t _ndim, typename _Scalar>
void CooData<_ndim, _Scalar>::operator>>=( const index_t offset ) noexcept {
  value_ >>= offset;
  for ( auto &idx : idxs_ ) {
    idx >>= offset;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Left-shift the offset.
///
template <index_t _ndim, typename _Scalar>
void CooData<_ndim, _Scalar>::operator<<=( const index_t offset ) noexcept {
  value_ <<= offset;
  for ( auto &idx : idxs_ ) {
    idx <<= offset;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Right-shift the offset.
///
template <index_t _ndim, typename _Scalar>
CooData<_ndim, _Scalar> CooData<_ndim, _Scalar>::operator>>( const index_t offset ) noexcept {
  auto retval = *this; retval >>= offset; return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Right-shift the offset.
///
template <index_t _ndim, typename _Scalar>
const CooData<_ndim, _Scalar> CooData<_ndim, _Scalar>::operator>>( const index_t offset ) const noexcept {
  auto retval = *this; retval >>= offset; return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Left-shift the offset.
///
template <index_t _ndim, typename _Scalar>
CooData<_ndim, _Scalar> CooData<_ndim, _Scalar>::operator<<( const index_t offset ) noexcept {
  auto retval = *this; retval <<= offset; return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Left-shift the offset.
///
template <index_t _ndim, typename _Scalar>
const CooData<_ndim, _Scalar> CooData<_ndim, _Scalar>::operator<<( const index_t offset ) const noexcept {
  auto retval = *this; retval <<= offset; return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw value array array.
///
template <index_t _ndim, typename _Scalar>
Array<_Scalar>& CooData<_ndim, _Scalar>::getValueArray() noexcept { return value_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValueArray
///
template <index_t _ndim, typename _Scalar>
const Array<_Scalar>& CooData<_ndim, _Scalar>::getValueArray() const noexcept { return value_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw index array pointer.
///
template <index_t _ndim, typename _Scalar>
Array<index_t>& CooData<_ndim, _Scalar>::getIdxArray( const index_t dim ) noexcept {
  mcnla_assert_ge(dim, 0);
  mcnla_assert_lt(dim, _ndim);
  return idxs_[dim];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIdxArray
///
template <index_t _ndim, typename _Scalar>
const Array<index_t>& CooData<_ndim, _Scalar>::getIdxArray( const index_t dim ) const noexcept {
  mcnla_assert_ge(dim, 0);
  mcnla_assert_lt(dim, _ndim);
  return idxs_[dim];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIdxArray
///
template <index_t _ndim, typename _Scalar> template <index_t _dim>
Array<index_t>& CooData<_ndim, _Scalar>::getIdxArray() noexcept {
  static_assert(_dim >= 0 && _dim < _ndim, "Invalid dimension!");
  return idxs_[_dim];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIdxArray
///
template <index_t _ndim, typename _Scalar> template <index_t _dim>
const Array<index_t>& CooData<_ndim, _Scalar>::getIdxArray() const noexcept {
  static_assert(_dim >= 0 && _dim < _ndim, "Invalid dimension!");
  return idxs_[_dim];
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

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_DATA_IPP_
