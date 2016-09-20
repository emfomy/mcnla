////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/coo/coo_tuple.hpp
/// @brief   The COO tuple.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_COO_COO_TUPLE_HPP_
#define ISVD_MATRIX_COO_COO_TUPLE_HPP_

#include <isvd/isvd.hpp>
#include <tuple>
#include <isvd/matrix/coo/coo_data.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <index_t _ndim, typename _Scalar, typename _Index> class CooTuple;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace.
//
namespace detail {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The COO tuple generator.
///
template <index_t _ndim, typename _Scalar, typename _Index, typename... _Args>
struct CooTupleGenerator {
  using type = typename CooTupleGenerator<_ndim-1, _Scalar, _Index, _Index, _Args...>::type;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The COO tuple generator.
///
template <typename _Scalar, typename _Index, typename... _Args>
struct CooTupleGenerator<0, _Scalar, _Index, _Args...> {
  using type = std::tuple<_Args..., _Scalar>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The COO tuple base.
///
template <index_t _ndim, typename _Scalar, typename _Index>
using CooTupleBase = typename CooTupleGenerator<_ndim, _Scalar, _Index>::type;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The COO tuple helper.
///
template <index_t _ndim, index_t _dim = _ndim-1>
struct CooTupleHelper {
  static_assert(_dim > 0 && _dim < _ndim, "Invalid dimension!");

  // Operators
  template <typename _Indexa, typename _Scalara, typename _Indexb, typename _Scalarb>
  static inline bool equalTo(     const CooTuple<_ndim, _Indexa, _Scalara> &a,
                                  const CooTuple<_ndim, _Indexb, _Scalarb> &b ) noexcept;
  template <typename _Indexa, typename _Scalara, typename _Indexb, typename _Scalarb>
  static inline bool lessThan(    const CooTuple<_ndim, _Indexa, _Scalara> &a,
                                  const CooTuple<_ndim, _Indexb, _Scalarb> &b ) noexcept;
  template <typename _Indexa, typename _Scalara, typename _Indexb, typename _Scalarb>
  static inline bool greaterThan( const CooTuple<_ndim, _Indexa, _Scalara> &a,
                                  const CooTuple<_ndim, _Indexb, _Scalarb> &b ) noexcept;

  // Swaps
  template <typename _Scalar, typename _Index>
  static inline void swap( CooTuple<_ndim, _Scalar, _Index> a, CooTuple<_ndim, _Scalar, _Index> b ) noexcept;

  // Makes
  template <typename... _Args, typename... __Args>
  static inline std::tuple<_Args&...> makeRefTuple( std::tuple<_Args...> &tuple, __Args&... args ) noexcept;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The COO tuple helper.
///
template <index_t _ndim>
struct CooTupleHelper<_ndim, 0> {

  // Operators
  template <typename _Indexa, typename _Scalara, typename _Indexb, typename _Scalarb>
  static inline bool equalTo(     const CooTuple<_ndim, _Indexa, _Scalara> &a,
                                  const CooTuple<_ndim, _Indexb, _Scalarb> &b ) noexcept;
  template <typename _Indexa, typename _Scalara, typename _Indexb, typename _Scalarb>
  static inline bool lessThan(    const CooTuple<_ndim, _Indexa, _Scalara> &a,
                                  const CooTuple<_ndim, _Indexb, _Scalarb> &b ) noexcept;
  template <typename _Indexa, typename _Scalara, typename _Indexb, typename _Scalarb>
  static inline bool greaterThan( const CooTuple<_ndim, _Indexa, _Scalara> &a,
                                  const CooTuple<_ndim, _Indexb, _Scalarb> &b ) noexcept;

  // Swaps
  template <typename _Scalar, typename _Index>
  static inline void swap( CooTuple<_ndim, _Scalar, _Index> a, CooTuple<_ndim, _Scalar, _Index> b ) noexcept;

  // Makes
  template <typename... _Args, typename... __Args>
  static inline std::tuple<_Args&...> makeRefTuple( std::tuple<_Args...> &tuple, __Args&... args ) noexcept;
};

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) tuple.
///
/// @tparam  _ndim    The dimension.
/// @tparam  _Index   The index type.
/// @tparam  _Scalar  The scalar type.
///
template <index_t _ndim, typename _Scalar, typename _Index>
class CooTuple : public detail::CooTupleBase<_ndim, _Scalar&, _Index&> {

  static_assert(_ndim >= 0, "Invalid dimension!");
  static_assert(std::is_integral<_Index>::value, "'_Index' is not a integer!");

 protected:

  using BaseType  = detail::CooTupleBase<_ndim, _Scalar&, _Index&>;
  using TupleType = detail::CooTupleBase<_ndim, _Scalar, _Index>;

 protected:

  TupleType tuple_;

 protected:

  // Constructors
  CooTuple() = delete;
  CooTuple( const BaseType  base ) noexcept;
  CooTuple( const TupleType base ) noexcept;

 public:

  // Constructors
  CooTuple( const CooTuple &other ) noexcept;
  CooTuple( CooTuple &&other ) noexcept;

  // Assignment operators
  inline CooTuple& operator=( const CooTuple &other ) noexcept;

  // Comparison operators
  template <typename __Scalar, typename __Index>
  inline bool operator==( const CooTuple<_ndim, __Index, __Scalar> &other ) const noexcept;
  template <typename __Scalar, typename __Index>
  inline bool operator!=( const CooTuple<_ndim, __Index, __Scalar> &other ) const noexcept;
  template <typename __Scalar, typename __Index>
  inline bool operator<(  const CooTuple<_ndim, __Index, __Scalar> &other ) const noexcept;
  template <typename __Scalar, typename __Index>
  inline bool operator>(  const CooTuple<_ndim, __Index, __Scalar> &other ) const noexcept;
  template <typename __Scalar, typename __Index>
  inline bool operator<=( const CooTuple<_ndim, __Index, __Scalar> &other ) const noexcept;
  template <typename __Scalar, typename __Index>
  inline bool operator>=( const CooTuple<_ndim, __Index, __Scalar> &other ) const noexcept;

  // Assigns value
  template <typename __Scalar, typename... _Args>
  inline void operator()( const __Scalar value, const _Args... args ) noexcept;

  // Makes
  template <typename __Index, typename... _Args>
  friend inline CooTuple<sizeof...(_Args)+1, void*,    __Index> makeCooTuple( const __Index, const _Args... );
  template <typename __Scalar, typename __Index, typename... _Args>
  friend inline CooTuple<sizeof...(_Args)+1, __Scalar, __Index> makeCooRefTuple( __Scalar&, __Index&, _Args&... );

};

// Makes a tuple
template <typename _Index, typename... _Args>
inline CooTuple<sizeof...(_Args)+1, void*,   _Index> makeCooTuple( const _Index idx, const _Args... args );
template <typename _Scalar, typename _Index, typename... _Args>
inline CooTuple<sizeof...(_Args)+1, _Scalar, _Index> makeCooRefTuple( _Scalar &value, _Index &idx, _Args&... args );

}  // namespace isvd

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The STL namespace.
//
namespace std {

template <isvd::index_t _ndim, typename _Scalar, typename _Index>
inline void swap( isvd::CooTuple<_ndim, _Scalar, _Index> a, isvd::CooTuple<_ndim, _Scalar, _Index> b ) noexcept;

}  // namespace std

#endif  // ISVD_MATRIX_COO_COO_TUPLE_HPP_
