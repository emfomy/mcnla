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
template <index_t _ndim>
IdxTuple<_ndim>::IdxTuple() noexcept
  : BaseType(),
    idx_() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given index pointers.
///
template <index_t _ndim>
IdxTuple<_ndim>::IdxTuple( const std::array<index_t*, _ndim> &idxptr ) noexcept
  : BaseType(idxptr),
    idx_() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given index pointers.
///
template <index_t _ndim>
IdxTuple<_ndim>::IdxTuple( std::array<index_t*, _ndim> &&idxptr ) noexcept
  : BaseType(idxptr),
    idx_() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given indices.
///
template <index_t _ndim>
IdxTuple<_ndim>::IdxTuple( const std::array<index_t, _ndim> &idx ) noexcept
  : BaseType(),
    idx_(idx) {
  for ( index_t i = 0; i < _ndim; ++i ) {
    BaseType::operator[](i) = &(idx_[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given indices.
///
template <index_t _ndim>
IdxTuple<_ndim>::IdxTuple( std::array<index_t, _ndim> &&idx ) noexcept
  : BaseType(),
    idx_(idx) {
  for ( index_t i = 0; i < _ndim; ++i ) {
    BaseType::operator[](i) = &(idx_[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
template <index_t _ndim>
IdxTuple<_ndim>::IdxTuple( const IdxTuple &other ) noexcept
  : BaseType(other),
    idx_(other.idx_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
template <index_t _ndim>
IdxTuple<_ndim>& IdxTuple<_ndim>::operator=( const IdxTuple &other ) noexcept {
  BaseType::operator=(other); idx_ = other.idx_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Less-than operator.
///
template <index_t _ndim>
bool IdxTuple<_ndim>::operator<( const IdxTuple& other ) const noexcept {
  for ( index_t dim = _ndim-1; dim >= 0; --dim ) {
    if ( (*this)[dim] != other[dim] ) {
      return ((*this)[dim] < other[dim]);
    }
  }
  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Greater-than operator.
///
template <index_t _ndim>
bool IdxTuple<_ndim>::operator>( const IdxTuple& other ) const noexcept {
  for ( index_t dim = _ndim-1; dim >= 0; --dim ) {
    if ( (*this)[dim] != other[dim] ) {
      return ((*this)[dim] > other[dim]);
    }
  }
  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Less-than or equal-to operator.
///
template <index_t _ndim>
bool IdxTuple<_ndim>::operator<=( const IdxTuple& other ) const noexcept {
  return !(*this > other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Greater-than or equal-to operator.
///
template <index_t _ndim>
bool IdxTuple<_ndim>::operator>=( const IdxTuple& other ) const noexcept {
  return !(*this < other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Subscript operator operator.
///
template <index_t _ndim>
index_t& IdxTuple<_ndim>::operator[]( const index_t dim ) noexcept {
  return *(BaseType::operator[](dim));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Subscript operator operator.
///
template <index_t _ndim>
const index_t& IdxTuple<_ndim>::operator[]( const index_t dim ) const noexcept {
  return *(BaseType::operator[](dim));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Makes a index tuple
///
/// @param  args  The indices in storage order (idx1, idx2, ...).
///
template <typename... Args>
inline IdxTuple<sizeof...(Args)> makeIdxTuple( const Args... args ) {
  return IdxTuple<sizeof...(Args)>({args...});
}

}  // namespace isvd

#endif  // ISVD_MATRIX_KIT_IDX_TUPLE_IPP_
