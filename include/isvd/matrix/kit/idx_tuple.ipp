////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/kit/idx_tuple.ipp
/// @brief   The implementation of the index tuple.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_KIT_IDX_TUPLE_IPP_
#define ISVD_MATRIX_KIT_IDX_TUPLE_IPP_

#include <isvd/isvd.hpp>
#include <isvd/matrix/kit/idx_tuple.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <typename _Scalar, index_t _ndim>
IdxTuple<_Scalar, _ndim>::IdxTuple() noexcept
  : BaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
template <typename _Scalar, index_t _ndim>
IdxTuple<_Scalar, _ndim>::IdxTuple( const IdxTuple &other ) noexcept
  : BaseType(other) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
template <typename _Scalar, index_t _ndim>
IdxTuple<_Scalar, _ndim>::IdxTuple( const BaseType &other ) noexcept
  : BaseType(other) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar, index_t _ndim>
IdxTuple<_Scalar, _ndim>::IdxTuple( IdxTuple &&other ) noexcept
  : BaseType(std::move(other)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar, index_t _ndim>
IdxTuple<_Scalar, _ndim>::IdxTuple( BaseType &&other ) noexcept
  : BaseType(std::move(other)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
template <typename _Scalar, index_t _ndim>
IdxTuple<_Scalar, _ndim>& IdxTuple<_Scalar, _ndim>::operator=( const IdxTuple &other ) noexcept {
  BaseType::operator=(other);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Scalar, index_t _ndim>
IdxTuple<_Scalar, _ndim>& IdxTuple<_Scalar, _ndim>::operator=( IdxTuple &&other ) noexcept {
  BaseType::operator=(std::move(other));
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Less-than operator.
///
template <typename _Scalar, index_t _ndim>
bool IdxTuple<_Scalar, _ndim>::operator<( const IdxTuple& other ) const noexcept {
  for ( index_t dim = 0; dim < _ndim; ++dim ) {
    if ( (*this)[dim] != other[dim] ) {
      return ((*this)[dim] < other[dim]);
    }
  }
  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Greater-than operator.
///
template <typename _Scalar, index_t _ndim>
bool IdxTuple<_Scalar, _ndim>::operator>( const IdxTuple& other ) const noexcept {
  for ( index_t dim = 0; dim < _ndim; ++dim ) {
    if ( (*this)[dim] != other[dim] ) {
      return ((*this)[dim] > other[dim]);
    }
  }
  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Less-than or equal-to operator.
///
template <typename _Scalar, index_t _ndim>
bool IdxTuple<_Scalar, _ndim>::operator<=( const IdxTuple& other ) const noexcept {
  return !(*this > other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Greater-than or equal-to operator.
///
template <typename _Scalar, index_t _ndim>
bool IdxTuple<_Scalar, _ndim>::operator>=( const IdxTuple& other ) const noexcept {
  return !(*this < other);
}

}  // namespace isvd

#endif  // ISVD_MATRIX_KIT_IDX_TUPLE_IPP_
