////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/kit/idx_tuple.hpp
/// @brief   The index tuple.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_KIT_IDX_TUPLE_HPP_
#define ISVD_MATRIX_KIT_IDX_TUPLE_HPP_

#include <isvd/isvd.hpp>
#include <array>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The index tuple.
///
/// @tparam  _ndim  The dimension.
///
template <index_t _ndim, typename _Index = index_t>
class IdxTuple : protected std::array<_Index*, _ndim> {

 private:

  using BaseType = std::array<_Index*, _ndim>;

 protected:

  std::array<index_t, _ndim> idx_;

 public:

  // Constructors
  IdxTuple() noexcept;
  IdxTuple( const std::array<index_t, _ndim> &idx ) noexcept;
  IdxTuple( std::array<index_t, _ndim> &&idx ) noexcept;
  IdxTuple( const std::array<_Index*, _ndim> &idxptr ) noexcept;
  IdxTuple( std::array<_Index*, _ndim> &&idxptr ) noexcept;
  IdxTuple( const IdxTuple &other ) noexcept;

 public:

  // Operators
  inline IdxTuple& operator=( const IdxTuple &other ) noexcept;
  template <typename __Index> inline bool operator==( const IdxTuple<_ndim, __Index> &other ) const noexcept;
  template <typename __Index> inline bool operator!=( const IdxTuple<_ndim, __Index> &other ) const noexcept;
  template <typename __Index> inline bool operator<( const IdxTuple<_ndim, __Index> &other ) const noexcept;
  template <typename __Index> inline bool operator>( const IdxTuple<_ndim, __Index> &other ) const noexcept;
  template <typename __Index> inline bool operator<=( const IdxTuple<_ndim, __Index> &other ) const noexcept;
  template <typename __Index> inline bool operator>=( const IdxTuple<_ndim, __Index> &other ) const noexcept;
  inline       _Index& operator[]( const index_t dim ) noexcept;
  inline const _Index& operator[]( const index_t dim ) const noexcept;

  // Swaps
  static inline void swap( IdxTuple a, IdxTuple b ) noexcept;

};

// Makes a index tuple
template <typename _Index, typename... _Args>
inline IdxTuple<sizeof...(_Args)+1, _Index> makeIdxTuple( _Index idx,  _Args... args );
template <typename _Index, typename... _Args>
inline IdxTuple<sizeof...(_Args)+1, _Index> makeIdxTuple( _Index *idx, _Args... args );

}  // namespace isvd

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The STL namespace.
//
namespace std {

// Swaps
template <isvd::index_t _ndim, typename _Index>
inline void swap( isvd::IdxTuple<_ndim, _Index> a, isvd::IdxTuple<_ndim, _Index> b ) noexcept;

}  // namespace std

#endif  // ISVD_MATRIX_KIT_IDX_TUPLE_HPP_
