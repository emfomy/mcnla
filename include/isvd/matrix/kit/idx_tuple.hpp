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
template <index_t _ndim>
class IdxTuple : protected std::array<index_t*, _ndim> {

 private:

  using BaseType = std::array<index_t*, _ndim>;

 protected:

  std::array<index_t, _ndim> idx_;

 public:

  // Constructors
  IdxTuple() noexcept;
  IdxTuple( const std::array<index_t*, _ndim> &idxptr ) noexcept;
  IdxTuple( std::array<index_t*, _ndim> &&idxptr ) noexcept;
  IdxTuple( const std::array<index_t, _ndim> &idx ) noexcept;
  IdxTuple( std::array<index_t, _ndim> &&idx ) noexcept;
  IdxTuple( const IdxTuple &other ) noexcept;

 public:

  // Operators
  inline IdxTuple& operator=( const IdxTuple &other ) noexcept;
  inline bool operator<( const IdxTuple &other ) const noexcept;
  inline bool operator>( const IdxTuple &other ) const noexcept;
  inline bool operator<=( const IdxTuple &other ) const noexcept;
  inline bool operator>=( const IdxTuple &other ) const noexcept;
  inline       index_t& operator[]( const index_t dim ) noexcept;
  inline const index_t& operator[]( const index_t dim ) const noexcept;

};

// Makes a index tuple
template <typename... Args>
inline IdxTuple<sizeof...(Args)> makeIdxTuple( const Args... args );

}  // namespace isvd

#endif  // ISVD_MATRIX_KIT_IDX_TUPLE_HPP_
