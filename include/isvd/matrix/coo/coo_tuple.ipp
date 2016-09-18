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
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Equal-to operator.
///
template <index_t _ndim, index_t _dim> template <typename _Indexa, typename _Scalara, typename _Indexb, typename _Scalarb>
bool CooTupleProxy<_ndim, _dim>::equalTo(
    const CooTuple<_ndim, _Indexa, _Scalara> &a,
    const CooTuple<_ndim, _Indexb, _Scalarb> &b
) noexcept {
  return (std::get<_dim>(a) == std::get<_dim>(b)) ? CooTupleProxy<_ndim, _dim-1>::equalTo(a, b) : false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Equal-to operator.
///
template <index_t _ndim> template <typename _Indexa, typename _Scalara, typename _Indexb, typename _Scalarb>
bool CooTupleProxy<_ndim, 0>::equalTo(
    const CooTuple<_ndim, _Indexa, _Scalara> &a,
    const CooTuple<_ndim, _Indexb, _Scalarb> &b
) noexcept {
  return (std::get<0>(a) == std::get<0>(b));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Less-than operator.
///
template <index_t _ndim, index_t _dim> template <typename _Indexa, typename _Scalara, typename _Indexb, typename _Scalarb>
bool CooTupleProxy<_ndim, _dim>::lessThan(
    const CooTuple<_ndim, _Indexa, _Scalara> &a,
    const CooTuple<_ndim, _Indexb, _Scalarb> &b
) noexcept {
  return (std::get<_dim>(a) == std::get<_dim>(b)) ? CooTupleProxy<_ndim, _dim-1>::lessThan(a, b)
                                                  : (std::get<_dim>(a) < std::get<_dim>(b));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Less-than operator.
///
template <index_t _ndim> template <typename _Indexa, typename _Scalara, typename _Indexb, typename _Scalarb>
bool CooTupleProxy<_ndim, 0>::lessThan(
    const CooTuple<_ndim, _Indexa, _Scalara> &a,
    const CooTuple<_ndim, _Indexb, _Scalarb> &b
) noexcept {
  return (std::get<0>(a) < std::get<0>(b));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Greater-than operator.
///
template <index_t _ndim, index_t _dim> template <typename _Indexa, typename _Scalara, typename _Indexb, typename _Scalarb>
bool CooTupleProxy<_ndim, _dim>::greaterThan(
    const CooTuple<_ndim, _Indexa, _Scalara> &a,
    const CooTuple<_ndim, _Indexb, _Scalarb> &b
) noexcept {
  return (std::get<_dim>(a) == std::get<_dim>(b)) ? CooTupleProxy<_ndim, _dim-1>::greaterThan(a, b)
                                                  : (std::get<_dim>(a) > std::get<_dim>(b));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Greater-than operator.
///
template <index_t _ndim> template <typename _Indexa, typename _Scalara, typename _Indexb, typename _Scalarb>
bool CooTupleProxy<_ndim, 0>::greaterThan(
    const CooTuple<_ndim, _Indexa, _Scalara> &a,
    const CooTuple<_ndim, _Indexb, _Scalarb> &b
) noexcept {
  return (std::get<0>(a) > std::get<0>(b));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc isvd::CooTuple::swap
///
template <index_t _ndim, index_t _dim> template <typename _Index, typename _Scalar>
void CooTupleProxy<_ndim, _dim>::swap( CooTuple<_ndim, _Index, _Scalar> a, CooTuple<_ndim, _Index, _Scalar> b ) noexcept {
  static_assert(!std::is_void<_Scalar>::value, "'CooTuple<n, void>' could not swap!");
  std::swap(std::get<_dim>(a), std::get<_dim>(b));
  CooTupleProxy<_ndim, _dim-1>::swap(a, b);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc isvd::CooTuple::swap
///
template <index_t _ndim> template <typename _Index, typename _Scalar>
void CooTupleProxy<_ndim, 0>::swap( CooTuple<_ndim, _Index, _Scalar> a, CooTuple<_ndim, _Index, _Scalar> b ) noexcept {
  static_assert(!std::is_void<_Scalar>::value, "'CooTuple<n, void>' could not swap!");
  std::swap(std::get<0>(a), std::get<0>(b));
  std::swap(std::get<_ndim>(a), std::get<_ndim>(b));
}

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given indices.
///
template <index_t _ndim, typename _Index, typename _Scalar>
CooTuple<_ndim, _Index, _Scalar>::CooTuple( const BaseType base ) noexcept
  : BaseType(base) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
template <index_t _ndim, typename _Index, typename _Scalar>
CooTuple<_ndim, _Index, _Scalar>::CooTuple( const CooTuple &other ) noexcept
  : BaseType(other) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
template <index_t _ndim, typename _Index, typename _Scalar>
CooTuple<_ndim, _Index, _Scalar>& CooTuple<_ndim, _Index, _Scalar>::operator=( const CooTuple &other ) noexcept {
  BaseType::operator=(other); return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Equal-to operator.
///
template <index_t _ndim, typename _Index, typename _Scalar> template <typename __Index, typename __Scalar>
bool CooTuple<_ndim, _Index, _Scalar>::operator==( const CooTuple<_ndim, __Index, __Scalar>& other ) const noexcept {
  return internal::CooTupleProxy<_ndim>::equalTo(*this, other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Not-qual-to operator.
///
template <index_t _ndim, typename _Index, typename _Scalar> template <typename __Index, typename __Scalar>
bool CooTuple<_ndim, _Index, _Scalar>::operator!=( const CooTuple<_ndim, __Index, __Scalar>& other ) const noexcept {
  return !(*this == other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Less-than operator.
///
template <index_t _ndim, typename _Index, typename _Scalar> template <typename __Index, typename __Scalar>
bool CooTuple<_ndim, _Index, _Scalar>::operator<( const CooTuple<_ndim, __Index, __Scalar>& other ) const noexcept {
  return internal::CooTupleProxy<_ndim>::lessThan(*this, other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Greater-than operator.
///
template <index_t _ndim, typename _Index, typename _Scalar> template <typename __Index, typename __Scalar>
bool CooTuple<_ndim, _Index, _Scalar>::operator>( const CooTuple<_ndim, __Index, __Scalar>& other ) const noexcept {
  return internal::CooTupleProxy<_ndim>::greaterThan(*this, other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Less-than or equal-to operator.
///
template <index_t _ndim, typename _Index, typename _Scalar> template <typename __Index, typename __Scalar>
bool CooTuple<_ndim, _Index, _Scalar>::operator<=( const CooTuple<_ndim, __Index, __Scalar>& other ) const noexcept {
  return !(*this > other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Greater-than or equal-to operator.
///
template <index_t _ndim, typename _Index, typename _Scalar> template <typename __Index, typename __Scalar>
bool CooTuple<_ndim, _Index, _Scalar>::operator>=( const CooTuple<_ndim, __Index, __Scalar>& other ) const noexcept {
  return !(*this < other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Swaps COO tuples.
///
template <index_t _ndim, typename _Index, typename _Scalar>
void CooTuple<_ndim, _Index, _Scalar>::swap( CooTuple a, CooTuple b ) noexcept {
  internal::CooTupleProxy<_ndim>::swap(a, b);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Makes a COO tuple
///
/// @param  args  The indices in storage order (idx1, idx2, ...).
/// @param  idx
///
template <typename _Index, typename... _Args>
CooTuple<sizeof...(_Args)+1, _Index> makeCooTuple( _Index idx, _Args... args ) {
  return CooTuple<sizeof...(_Args)+1, _Index>(std::make_tuple(idx, args...));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Makes a reference COO tuple
///
/// @param  value  The value.
/// @param  args   The indices in storage order (idx1, idx2, ...).
/// @param  idx
///
template <typename _Scalar, typename _Index, typename... _Args>
CooTuple<sizeof...(_Args)+1, _Index, _Scalar> makeRefCooTuple( _Scalar &value, _Index &idx, _Args&... args ) {
  return CooTuple<sizeof...(_Args)+1, _Index, _Scalar>(std::tie(idx, args..., value));
}

}  // namespace isvd

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc isvd::CooTuple::swap
///
template <isvd::index_t _ndim, typename _Index, typename _Scalar>
void std::swap( isvd::CooTuple<_ndim, _Index, _Scalar> a, isvd::CooTuple<_ndim, _Index, _Scalar> b ) noexcept {
  isvd::CooTuple<_ndim, _Index, _Scalar>::swap(a, b);
}

#endif  // ISVD_MATRIX_COO_COO_TUPLE_IPP_
