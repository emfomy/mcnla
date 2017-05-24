////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_tuple1.hh
/// @brief   The definition of 1-dimensional COO tuple.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_TUPLE1_HH_
#define MCNLA_CORE_MATRIX_COO_COO_TUPLE1_HH_

#include <mcnla/core/matrix/coo/def.hpp>
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
/// The 1-dimensional COO tuple.
///
/// @tparam  _Val  The value type.
/// @tparam  _Idx  The index type.
///
/// @note  The comparison operators only compare the indices.
///
template <typename _Val, typename _Idx>
class CooTuple1 : public std::tuple<_Idx&> {

  static_assert(std::is_integral<_Idx>::value, "'_Idx' is not a integer!");

 private:

  using ValType  = _Val;
  using IdxType  = _Idx;
  using IdxsType = std::tuple<_Idx>;
  using BaseType = std::tuple<_Idx&>;

 protected:

  /// The value.
  ValType &val_;

 public:

  // Constructors
  CooTuple1() = delete;
  CooTuple1( ValType &val, IdxType &idx ) noexcept;
  CooTuple1( ValType &val, BaseType &idxs ) noexcept;
  CooTuple1( const CooTuple1 &other ) noexcept;

  // Assignment operators
  inline CooTuple1& operator=( const CooTuple1 &other ) noexcept;
  inline CooTuple1& operator=( const ValType &val ) noexcept;
  inline CooTuple1& operator=( const IdxsType &idxs ) noexcept;
  inline CooTuple1& operator=( const BaseType &idxs ) noexcept;

  // Assigns value
  inline CooTuple1& operator()( const ValType &val, const IdxType &idx ) noexcept;
  inline CooTuple1& operator()( const ValType &val, const IdxsType &idxs ) noexcept;
  inline CooTuple1& operator()( const ValType &val, const BaseType &idxs ) noexcept;

  // Operators
  template <typename ..._Args>
  friend inline std::ostream& operator<<( std::ostream &os, const CooTuple1<_Args...> &tuple ) noexcept;

  // Gets data
  inline       ValType& val() noexcept;
  inline const ValType& val() const noexcept;
  inline       IdxType& idx() noexcept;
  inline const IdxType& idx() const noexcept;
  inline       IdxType& idx0() noexcept;
  inline const IdxType& idx0() const noexcept;
  inline       BaseType& idxs() noexcept;
  inline const BaseType& idxs() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_TUPLE1_HH_
