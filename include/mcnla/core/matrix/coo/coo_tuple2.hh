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
/// @tparam  _Val    The value type.
/// @tparam  _Idx    The index type.
/// @tparam  _trans  The transpose storage layout.
///
/// @note  The comparison operators only compare the indices.
///
template <typename _Val, typename _Idx, Trans _trans>
class CooTuple2 : public std::tuple<_Idx&, _Idx&> {

  static_assert(std::is_integral<_Idx>::value, "'_Idx' is not a integer!");

 private:

  using ValType  = _Val;
  using IdxType  = _Idx;
  using IdxsType = std::tuple<_Idx&, _Idx&>;

 protected:

  /// The value.
  ValType &val_;

 public:

  // Constructors
  CooTuple2() = delete;
  CooTuple2( ValType &val, IdxType &rowidx, IdxType &colidx ) noexcept;
  CooTuple2( ValType &val, IdxsType &idxs ) noexcept;
  CooTuple2( const CooTuple2 &other ) noexcept;

  // Assignment operators
  inline CooTuple2& operator=( const CooTuple2 &other ) noexcept;
  inline CooTuple2& operator=( const ValType val ) noexcept;
  inline CooTuple2& operator=( const IdxsType idxs ) noexcept;

  // Assigns value
  inline CooTuple2& operator()( const ValType val, const IdxType rowidx, const IdxType colidx ) noexcept;
  inline CooTuple2& operator()( const ValType val, const IdxsType idxs ) noexcept;

  // Operators
  template <typename __Val, typename __Idx, Trans __Trans>
  friend inline std::ostream& operator<<( std::ostream &os, const CooTuple2<__Val, __Idx, __Trans> &tuple );

  // Gets data
  inline       ValType& val() noexcept;
  inline const ValType& val() const noexcept;
  inline       IdxType& rowidx() noexcept;
  inline const IdxType& rowidx() const noexcept;
  inline       IdxType& colidx() noexcept;
  inline const IdxType& colidx() const noexcept;
  inline       IdxType& idx0() noexcept;
  inline const IdxType& idx0() const noexcept;
  inline       IdxType& idx1() noexcept;
  inline const IdxType& idx1() const noexcept;
  inline       IdxsType& idxs() noexcept;
  inline const IdxsType& idxs() const noexcept;

 protected:

  // Convert to storage order
  inline IdxsType toIdxs( IdxType &rowidx, IdxType &colidx ) const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_TUPLE2_HH_
