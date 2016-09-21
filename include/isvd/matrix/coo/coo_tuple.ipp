////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/coo/coo_tuple.ipp
/// @brief   The implementation of COO tuple.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_COO_COO_TUPLE_IPP_
#define ISVD_MATRIX_COO_COO_TUPLE_IPP_

#include <isvd/isvd.hpp>
#include <isvd/matrix/coo/coo_tuple.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace.
//
namespace detail {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Equal-to operator.
///
template <index_t _ndim, index_t _dim> template <typename _Indexa, typename _Scalara, typename _Indexb, typename _Scalarb>
bool CooTupleHelper<_ndim, _dim>::equalTo(
    const CooTuple<_ndim, _Indexa, _Scalara> &a,
    const CooTuple<_ndim, _Indexb, _Scalarb> &b
) noexcept {
  return (std::get<_dim>(a) == std::get<_dim>(b)) ? CooTupleHelper<_ndim, _dim-1>::equalTo(a, b) : false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Equal-to operator.
///
template <index_t _ndim> template <typename _Indexa, typename _Scalara, typename _Indexb, typename _Scalarb>
bool CooTupleHelper<_ndim, 0>::equalTo(
    const CooTuple<_ndim, _Indexa, _Scalara> &a,
    const CooTuple<_ndim, _Indexb, _Scalarb> &b
) noexcept {
  return (std::get<0>(a) == std::get<0>(b));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Less-than operator.
///
template <index_t _ndim, index_t _dim> template <typename _Indexa, typename _Scalara, typename _Indexb, typename _Scalarb>
bool CooTupleHelper<_ndim, _dim>::lessThan(
    const CooTuple<_ndim, _Indexa, _Scalara> &a,
    const CooTuple<_ndim, _Indexb, _Scalarb> &b
) noexcept {
  return (std::get<_dim>(a) == std::get<_dim>(b)) ? CooTupleHelper<_ndim, _dim-1>::lessThan(a, b)
                                                  : (std::get<_dim>(a) < std::get<_dim>(b));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Less-than operator.
///
template <index_t _ndim> template <typename _Indexa, typename _Scalara, typename _Indexb, typename _Scalarb>
bool CooTupleHelper<_ndim, 0>::lessThan(
    const CooTuple<_ndim, _Indexa, _Scalara> &a,
    const CooTuple<_ndim, _Indexb, _Scalarb> &b
) noexcept {
  return (std::get<0>(a) < std::get<0>(b));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Greater-than operator.
///
template <index_t _ndim, index_t _dim> template <typename _Indexa, typename _Scalara, typename _Indexb, typename _Scalarb>
bool CooTupleHelper<_ndim, _dim>::greaterThan(
    const CooTuple<_ndim, _Indexa, _Scalara> &a,
    const CooTuple<_ndim, _Indexb, _Scalarb> &b
) noexcept {
  return (std::get<_dim>(a) == std::get<_dim>(b)) ? CooTupleHelper<_ndim, _dim-1>::greaterThan(a, b)
                                                  : (std::get<_dim>(a) > std::get<_dim>(b));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Greater-than operator.
///
template <index_t _ndim> template <typename _Indexa, typename _Scalara, typename _Indexb, typename _Scalarb>
bool CooTupleHelper<_ndim, 0>::greaterThan(
    const CooTuple<_ndim, _Indexa, _Scalara> &a,
    const CooTuple<_ndim, _Indexb, _Scalarb> &b
) noexcept {
  return (std::get<0>(a) > std::get<0>(b));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Swap two COO tuples
///
template <index_t _ndim, index_t _dim> template <typename _Scalar, typename _Index>
void CooTupleHelper<_ndim, _dim>::swap(
    CooTuple<_ndim, _Scalar, _Index> a,
    CooTuple<_ndim, _Scalar, _Index> b
) noexcept {
  std::swap(std::get<_dim>(a), std::get<_dim>(b));
  CooTupleHelper<_ndim, _dim-1>::swap(a, b);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Swap two COO tuples
///
template <index_t _ndim> template <typename _Scalar, typename _Index>
void CooTupleHelper<_ndim, 0>::swap(
    CooTuple<_ndim, _Scalar, _Index> a,
    CooTuple<_ndim, _Scalar, _Index> b
) noexcept {
  std::swap(std::get<0>(a), std::get<0>(b));
  std::swap(std::get<_ndim>(a), std::get<_ndim>(b));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Makes a reference tuple of given tuple
///
template <index_t _ndim, index_t _dim> template <typename... _Args, typename... __Args>
std::tuple<_Args&...> CooTupleHelper<_ndim, _dim>::makeRefTuple(
    std::tuple<_Args...> &tuple,
    __Args&... args
) noexcept {
  return CooTupleHelper<_ndim, _dim-1>::makeRefTuple(tuple, std::get<_dim>(tuple), args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Makes a reference tuple of given tuple
///
template <index_t _ndim> template <typename... _Args, typename... __Args>
std::tuple<_Args&...> CooTupleHelper<_ndim, 0>::makeRefTuple(
    std::tuple<_Args...> &tuple,
    __Args&... args
) noexcept {
  return std::tie(std::get<0>(tuple), args..., std::get<_ndim>(tuple));
}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given indices.
///
template <index_t _ndim, typename _Scalar, typename _Index>
CooTuple<_ndim, _Scalar, _Index>::CooTuple( const BaseType base ) noexcept
  : BaseType(base),
    tuple_() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given indices.
///
template <index_t _ndim, typename _Scalar, typename _Index>
CooTuple<_ndim, _Scalar, _Index>::CooTuple( const TupleType tuple ) noexcept
  : BaseType(detail::CooTupleHelper<_ndim>::makeRefTuple(tuple_)),
    tuple_(tuple) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
template <index_t _ndim, typename _Scalar, typename _Index>
CooTuple<_ndim, _Scalar, _Index>::CooTuple( const CooTuple &other ) noexcept
  : BaseType(other),
    tuple_() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <index_t _ndim, typename _Scalar, typename _Index>
CooTuple<_ndim, _Scalar, _Index>::CooTuple( CooTuple &&other ) noexcept
  : BaseType(detail::CooTupleHelper<_ndim>::makeRefTuple(tuple_)),
    tuple_(other) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
template <index_t _ndim, typename _Scalar, typename _Index>
CooTuple<_ndim, _Scalar, _Index>& CooTuple<_ndim, _Scalar, _Index>::operator=( const CooTuple &other ) noexcept {
  BaseType::operator=(other); return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Equal-to operator.
///
template <index_t _ndim, typename _Scalar, typename _Index> template <typename __Scalar, typename __Index>
bool CooTuple<_ndim, _Scalar, _Index>::operator==( const CooTuple<_ndim, __Index, __Scalar>& other ) const noexcept {
  return detail::CooTupleHelper<_ndim>::equalTo(*this, other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Not-qual-to operator.
///
template <index_t _ndim, typename _Scalar, typename _Index> template <typename __Scalar, typename __Index>
bool CooTuple<_ndim, _Scalar, _Index>::operator!=( const CooTuple<_ndim, __Index, __Scalar>& other ) const noexcept {
  return !(*this == other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Less-than operator.
///
template <index_t _ndim, typename _Scalar, typename _Index> template <typename __Scalar, typename __Index>
bool CooTuple<_ndim, _Scalar, _Index>::operator<( const CooTuple<_ndim, __Index, __Scalar>& other ) const noexcept {
  return detail::CooTupleHelper<_ndim>::lessThan(*this, other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Greater-than operator.
///
template <index_t _ndim, typename _Scalar, typename _Index> template <typename __Scalar, typename __Index>
bool CooTuple<_ndim, _Scalar, _Index>::operator>( const CooTuple<_ndim, __Index, __Scalar>& other ) const noexcept {
  return detail::CooTupleHelper<_ndim>::greaterThan(*this, other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Less-than or equal-to operator.
///
template <index_t _ndim, typename _Scalar, typename _Index> template <typename __Scalar, typename __Index>
bool CooTuple<_ndim, _Scalar, _Index>::operator<=( const CooTuple<_ndim, __Index, __Scalar>& other ) const noexcept {
  return !(*this > other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Greater-than or equal-to operator.
///
template <index_t _ndim, typename _Scalar, typename _Index> template <typename __Scalar, typename __Index>
bool CooTuple<_ndim, _Scalar, _Index>::operator>=( const CooTuple<_ndim, __Index, __Scalar>& other ) const noexcept {
  return !(*this < other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Assigns values.
///
template <index_t _ndim, typename _Scalar, typename _Index> template <typename __Scalar, typename... _Args>
void CooTuple<_ndim, _Scalar, _Index>::operator()( const __Scalar value, const _Args... args ) noexcept {
  BaseType::operator=(std::make_tuple(args..., value));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Makes a COO tuple
///
/// @param  idx    The first index (idx1).
/// @param  args   The rest of indices in storage order (idx2, idx3, ...).
///
template <typename __Index, typename... __Args>
CooTuple<sizeof...(__Args)+1, void*, __Index> makeCooTuple( const __Index idx, const __Args... args ) {
  return CooTuple<sizeof...(__Args)+1, void*, __Index>(std::make_tuple(idx, args..., nullptr));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Makes a reference COO tuple
///
/// @param  value  The value.
/// @param  idx    The first index (idx1).
/// @param  args   The rest of indices in storage order (idx2, idx3, ...).
///
template <typename __Scalar, typename __Index, typename... __Args>
CooTuple<sizeof...(__Args)+1, __Scalar, __Index> makeCooRefTuple( __Scalar &value, __Index &idx, __Args&... args ) {
  return CooTuple<sizeof...(__Args)+1, __Scalar, __Index>(std::tie(idx, args..., value));
}

}  // namespace isvd

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Swap two COO tuples
///
template <isvd::index_t _ndim, typename _Scalar, typename _Index>
void std::swap( isvd::CooTuple<_ndim, _Scalar, _Index> a, isvd::CooTuple<_ndim, _Scalar, _Index> b ) noexcept {
  isvd::detail::CooTupleHelper<_ndim>::swap(a, b);
}

#endif  // ISVD_MATRIX_COO_COO_TUPLE_IPP_
