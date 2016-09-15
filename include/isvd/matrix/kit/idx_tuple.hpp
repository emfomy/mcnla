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
/// @tparam  _Scalar  The scalar type.
/// @tparam  _ndim    The dimension.
///
template <typename _Scalar, index_t _ndim>
class IdxTuple : protected std::array<index_t, _ndim> {

 private:

  using BaseType = std::array<index_t, _ndim>;

 public:

  // Constructors
  IdxTuple() noexcept;
  IdxTuple( const IdxTuple &other ) noexcept;
  IdxTuple( const BaseType &other ) noexcept;
  IdxTuple( IdxTuple &&other ) noexcept;
  IdxTuple( BaseType &&other ) noexcept;

  // Operators
  inline IdxTuple& operator=( const IdxTuple &other ) noexcept;
  inline IdxTuple& operator=( IdxTuple &&other ) noexcept;
  inline bool operator<( const IdxTuple &other ) const noexcept;
  inline bool operator>( const IdxTuple &other ) const noexcept;
  inline bool operator<=( const IdxTuple &other ) const noexcept;
  inline bool operator>=( const IdxTuple &other ) const noexcept;

};

}  // namespace isvd

#endif  // ISVD_MATRIX_KIT_IDX_TUPLE_HPP_
