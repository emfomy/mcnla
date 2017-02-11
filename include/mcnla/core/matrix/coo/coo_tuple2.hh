////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_tuple2.hh
/// @brief   The definition of 2-dimensional COO tuple.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_TUPLE2_HH_
#define MCNLA_CORE_MATRIX_COO_COO_TUPLE2_HH_

#include <mcnla/core/matrix/def.hpp>
#include <iostream>
#include <tuple>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_coo_module_detail
/// The 2-dimensional COO tuple.
///
/// @tparam  _Val  The value type.
/// @tparam  _Idx  The index type.
///
/// @note  The comparison operators only compare the indices.
///
template <typename _Val, typename _Idx>
class CooTuple2 : public std::tuple<_Idx&, _Idx&> {

  static_assert(std::is_integral<_Idx>::value, "'_Idx' is not a integer!");

 private:

  using ValType  = _Val;
  using IdxType  = _Idx;
  using IdxsType = std::tuple<_Idx&, _Idx&>;

 protected:

  /// The value.
  ValType val_;

 public:

  // Constructors
  CooTuple2() = delete;
  CooTuple2( ValType& val, IdxType& idx0, IdxType& idx1 ) noexcept;
  CooTuple2( ValType& val, IdxsType& idxs ) noexcept;
  CooTuple2( const CooTuple2 &other ) noexcept;

  // Assignment operators
  inline CooTuple2& operator=( const CooTuple2 &other ) noexcept;
  inline CooTuple2& operator=( const ValType val ) noexcept;
  inline CooTuple2& operator=( const IdxsType idxs ) noexcept;

  // Assigns value
  inline CooTuple2& operator()( const ValType val, const IdxType idx0, const IdxType idx1 ) noexcept;
  inline CooTuple2& operator()( const ValType val, const IdxsType idxs ) noexcept;

  // Operators
  template <typename __Val, typename __Idx>
  friend inline std::ostream& operator<<( std::ostream &os, const CooTuple2<__Val, __Idx> &tuple );

  // Gets data
  inline       ValType& val() noexcept;
  inline const ValType& val() const noexcept;
  inline       IdxType& idx0() noexcept;
  inline const IdxType& idx0() const noexcept;
  inline       IdxType& idx1() noexcept;
  inline const IdxType& idx1() const noexcept;
  inline       IdxsType& idxs() noexcept;
  inline const IdxsType& idxs() const noexcept;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_coo_module_detail
/// @brief  Makes a COO tuple
///
/// @param  val   The value.
/// @param  idx0  The first index.
/// @param  idx1  The second index.
///
template <typename _Val, typename _Idx>
inline CooTuple2<_Val, _Idx> makeCooTuple(
    _Val &val,
    _Idx &idx0,
    _Idx &idx1
) noexcept {
  return CooTuple2<_Val, _Idx>(val, idx0, idx1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_coo_module_detail
/// @brief  Makes a COO tuple
///
/// @param  val  The value.
/// @param  idx  The indices.
///
template <typename _Val, typename _Idx>
inline CooTuple2<_Val, _Idx> makeCooTuple(
    _Val &val,
    std::tuple<_Idx&, _Idx&> &idxs
) noexcept {
  return CooTuple2<_Val, _Idx>(val, idxs);
}

}  // namespace matrix

}  // namespace mcnla

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The STL namespace.
//
namespace std {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_coo_module_detail
/// @brief  Swap two COO tuples
///
template <typename _Val, typename _Idx>
void swap(
    mcnla::matrix::CooTuple2<_Val, _Idx> &a,
    mcnla::matrix::CooTuple2<_Val, _Idx> &b
) noexcept {
  std::swap(a.val(), b.val());
  std::swap(a.idxs(), b.idxs());
}

}  // namespace std

#endif  // MCNLA_CORE_MATRIX_COO_COO_TUPLE2_HH_
