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
template <index_t _ndim, typename _Index>
IdxTuple<_ndim, _Index>::IdxTuple() noexcept
  : BaseType(),
    idx_() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given indices.
///
template <index_t _ndim, typename _Index>
IdxTuple<_ndim, _Index>::IdxTuple( const std::array<index_t, _ndim> &idx ) noexcept
  : BaseType(),
    idx_(idx) {
  for ( index_t i = 0; i < _ndim; ++i ) {
    BaseType::operator[](i) = &(idx_[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given indices.
///
template <index_t _ndim, typename _Index>
IdxTuple<_ndim, _Index>::IdxTuple( std::array<index_t, _ndim> &&idx ) noexcept
  : BaseType(),
    idx_(idx) {
  for ( index_t i = 0; i < _ndim; ++i ) {
    BaseType::operator[](i) = &(idx_[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given index pointers.
///
template <index_t _ndim, typename _Index>
IdxTuple<_ndim, _Index>::IdxTuple( const std::array<_Index*, _ndim> &idxptr ) noexcept
  : BaseType(idxptr),
    idx_() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given index pointers.
///
template <index_t _ndim, typename _Index>
IdxTuple<_ndim, _Index>::IdxTuple( std::array<_Index*, _ndim> &&idxptr ) noexcept
  : BaseType(idxptr),
    idx_() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
template <index_t _ndim, typename _Index>
IdxTuple<_ndim, _Index>::IdxTuple( const IdxTuple &other ) noexcept
  : BaseType(other),
    idx_(other.idx_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
template <index_t _ndim, typename _Index>
IdxTuple<_ndim, _Index>& IdxTuple<_ndim, _Index>::operator=( const IdxTuple &other ) noexcept {
  BaseType::operator=(other); idx_ = other.idx_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Equal-to operator.
///
template <index_t _ndim, typename _Index> template <typename __Index>
bool IdxTuple<_ndim, _Index>::operator==( const IdxTuple<_ndim, __Index>& other ) const noexcept {
  for ( index_t dim = 0; dim < _ndim; ++dim ) {
    if ( (*this)[dim] != other[dim] ) {
      return false;
    }
  }
  return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Not-qual-to operator.
///
template <index_t _ndim, typename _Index> template <typename __Index>
bool IdxTuple<_ndim, _Index>::operator!=( const IdxTuple<_ndim, __Index>& other ) const noexcept {
  return !(*this == other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Less-than operator.
///
template <index_t _ndim, typename _Index> template <typename __Index>
bool IdxTuple<_ndim, _Index>::operator<( const IdxTuple<_ndim, __Index>& other ) const noexcept {
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
template <index_t _ndim, typename _Index> template <typename __Index>
bool IdxTuple<_ndim, _Index>::operator>( const IdxTuple<_ndim, __Index>& other ) const noexcept {
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
template <index_t _ndim, typename _Index> template <typename __Index>
bool IdxTuple<_ndim, _Index>::operator<=( const IdxTuple<_ndim, __Index>& other ) const noexcept {
  return !(*this > other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Greater-than or equal-to operator.
///
template <index_t _ndim, typename _Index> template <typename __Index>
bool IdxTuple<_ndim, _Index>::operator>=( const IdxTuple<_ndim, __Index>& other ) const noexcept {
  return !(*this < other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Subscript operator operator.
///
template <index_t _ndim, typename _Index>
_Index& IdxTuple<_ndim, _Index>::operator[]( const index_t dim ) noexcept {
  return *(BaseType::operator[](dim));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Subscript operator operator.
///
template <index_t _ndim, typename _Index>
const _Index& IdxTuple<_ndim, _Index>::operator[]( const index_t dim ) const noexcept {
  return *(BaseType::operator[](dim));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Swaps index tuples.
///
template <index_t _ndim, typename _Index>
void IdxTuple<_ndim, _Index>::swap( IdxTuple a, IdxTuple b ) noexcept {
  for ( index_t dim = 0; dim < _ndim; ++dim ) {
    std::swap(a[dim], b[dim]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Makes a index tuple
///
/// @param  args  The indices in storage order (idx1, idx2, ...).
///
template <typename _Index, typename... _Args>
inline IdxTuple<sizeof...(_Args)+1, _Index> makeIdxTuple( _Index idx, _Args... args ) {
  return IdxTuple<sizeof...(_Args)+1, _Index>({idx, args...});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Makes a index tuple
///
/// @param  args  The indices in storage order (idx1, idx2, ...).
///
template <typename _Index, typename... _Args>
inline IdxTuple<sizeof...(_Args)+1, _Index> makeIdxTuple( _Index* idx, _Args... args ) {
  return IdxTuple<sizeof...(_Args)+1, _Index>({idx, args...});
}

}  // namespace isvd

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc isvd::IdxTuple::swap
///
template <isvd::index_t _ndim, typename _Index>
void std::swap( isvd::IdxTuple<_ndim, _Index> a, isvd::IdxTuple<_ndim, _Index> b ) noexcept {
  isvd::IdxTuple<_ndim, _Index>::swap(a, b);
}

#endif  // ISVD_MATRIX_KIT_IDX_TUPLE_IPP_
