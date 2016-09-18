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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <index_t _ndim, typename _Index, typename _Scalar> class CooTuple;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The COO tuple generator.
///
//@{
template <index_t _ndim, typename _Scalar, typename _Index, typename... _Args>
struct CooTupleGenerator {
  using type = typename CooTupleGenerator<_ndim-1, _Scalar, _Index, _Index, _Args...>::type;
};

template <typename _Scalar, typename _Index, typename... _Args>
struct CooTupleGenerator<0, _Scalar, _Index, _Args...> {
  using type = std::tuple<_Args&..., _Scalar&>;
};

template <typename _Index, typename... _Args>
struct CooTupleGenerator<0, void, _Index, _Args...> {
  using type = std::tuple<_Args...>;
};
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The COO tuple base.
///
template <index_t _ndim, typename _Scalar, typename _Index>
using CooTupleBase = typename CooTupleGenerator<_ndim, _Scalar, _Index>::type;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The COO tuple proxy.
///
//@{
template <index_t _ndim, index_t _dim = _ndim-1>
struct CooTupleProxy {
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
  template <typename _Index, typename _Scalar>
  static inline void swap( CooTuple<_ndim, _Index, _Scalar> a, CooTuple<_ndim, _Index, _Scalar> b ) noexcept;
};

template <index_t _ndim>
struct CooTupleProxy<_ndim, 0> {

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
  template <typename _Index, typename _Scalar>
  static inline void swap( CooTuple<_ndim, _Index, _Scalar> a, CooTuple<_ndim, _Index, _Scalar> b ) noexcept;
};

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) tuple.
///
/// @tparam  _ndim    The dimension.
/// @tparam  _Index   The index type.
/// @tparam  _Scalar  The scalar type.
///
template <index_t _ndim, typename _Index = index_t, typename _Scalar = void>
class CooTuple : public internal::CooTupleBase<_ndim, _Scalar, _Index> {

  static_assert(_ndim >= 0, "Invalid dimension!");

 public:

  using BaseType = internal::CooTupleBase<_ndim, _Scalar, _Index>;

 public:

  // Constructors
  CooTuple() noexcept = delete;
  CooTuple( const BaseType base ) noexcept;
  CooTuple( const CooTuple &other ) noexcept;

  // Operators
  inline CooTuple& operator=( const CooTuple &other ) noexcept;
  template <typename __Index, typename __Scalar>
  inline bool operator==( const CooTuple<_ndim, __Index, __Scalar> &other ) const noexcept;
  template <typename __Index, typename __Scalar>
  inline bool operator!=( const CooTuple<_ndim, __Index, __Scalar> &other ) const noexcept;
  template <typename __Index, typename __Scalar>
  inline bool operator<(  const CooTuple<_ndim, __Index, __Scalar> &other ) const noexcept;
  template <typename __Index, typename __Scalar>
  inline bool operator>(  const CooTuple<_ndim, __Index, __Scalar> &other ) const noexcept;
  template <typename __Index, typename __Scalar>
  inline bool operator<=( const CooTuple<_ndim, __Index, __Scalar> &other ) const noexcept;
  template <typename __Index, typename __Scalar>
  inline bool operator>=( const CooTuple<_ndim, __Index, __Scalar> &other ) const noexcept;

  // Swaps
  static inline void swap( CooTuple a, CooTuple b ) noexcept;

};

// Makes a index tuple
template <typename _Index, typename... _Args>
inline CooTuple<sizeof...(_Args)+1, _Index> makeCooTuple( _Index idx, _Args... args );
template <typename _Scalar, typename _Index, typename... _Args>
inline CooTuple<sizeof...(_Args)+1, _Index, _Scalar> makeRefCooTuple( _Scalar &value, _Index &idx, _Args&... args );

}  // namespace isvd

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The STL namespace.
//
namespace std {

template <isvd::index_t _ndim, typename _Index, typename _Scalar>
inline void swap( isvd::CooTuple<_ndim, _Index, _Scalar> a, isvd::CooTuple<_ndim, _Index, _Scalar> b ) noexcept;

}  // namespace std

#endif  // ISVD_MATRIX_COO_COO_TUPLE_HPP_
