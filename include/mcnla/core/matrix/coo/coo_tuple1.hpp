////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_tuple1.hpp
/// @brief   The 1-dimensional COO tuple.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_TUPLE1_HPP_
#define MCNLA_CORE_MATRIX_COO_COO_TUPLE1_HPP_

#include <mcnla/core/matrix/coo/coo_tuple1.hh>
#include <iomanip>
#include <mcnla/core/matrix/coo/coo_tuple1_helper.hh>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given data.
///
template <typename _Val, typename _Idx>
CooTuple1<_Val, _Idx>::CooTuple1(
    ValType& val,
    IdxType& idx
) noexcept
  : BaseType(idx),
    val_(val) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given data.
///
template <typename _Val, typename _Idx>
CooTuple1<_Val, _Idx>::CooTuple1(
    ValType& val,
    BaseType& idxs
) noexcept
  : BaseType(idxs),
    val_(val) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
template <typename _Val, typename _Idx>
CooTuple1<_Val, _Idx>::CooTuple1( const CooTuple1 &other ) noexcept
  : BaseType(other),
    val_(other.val_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
template <typename _Val, typename _Idx>
CooTuple1<_Val, _Idx>& CooTuple1<_Val, _Idx>::operator=(
    const CooTuple1 &other
) noexcept {
  BaseType::operator=(other);
  val_ = (other.val_);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Assignment operator.
///
template <typename _Val, typename _Idx>
CooTuple1<_Val, _Idx>& CooTuple1<_Val, _Idx>::operator=(
    const ValType &val
) noexcept {
  val_ = val;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Assignment operator.
///
template <typename _Val, typename _Idx>
CooTuple1<_Val, _Idx>& CooTuple1<_Val, _Idx>::operator=(
    const IdxsType &idxs
) noexcept {
  BaseType::operator=(idxs);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Assignment operator.
///
template <typename _Val, typename _Idx>
CooTuple1<_Val, _Idx>& CooTuple1<_Val, _Idx>::operator=(
    const BaseType &idxs
) noexcept {
  BaseType::operator=(idxs);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Assign value.
///
template <typename _Val, typename _Idx>
CooTuple1<_Val, _Idx>& CooTuple1<_Val, _Idx>::operator()(
    const ValType &val,
    const IdxType &idx
) noexcept {
  std::get<0>(*this) = idx;
  val_ = val;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Assign value.
///
template <typename _Val, typename _Idx>
CooTuple1<_Val, _Idx>& CooTuple1<_Val, _Idx>::operator()(
    const ValType  &val,
    const IdxsType &idxs
) noexcept {
  BaseType::operator=(idxs);
  val_ = val;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Assign value.
///
template <typename _Val, typename _Idx>
CooTuple1<_Val, _Idx>& CooTuple1<_Val, _Idx>::operator()(
    const ValType  &val,
    const BaseType &idxs
) noexcept {
  BaseType::operator=(idxs);
  val_ = val;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Output to stream.
///
template <typename __Val, typename __Idx>
std::ostream& operator<<(
    std::ostream &os,
    const CooTuple1<__Val, __Idx> &tuple
) noexcept {
  return os << "(" << std::setw(kOsIdxWidth) << tuple.idx() << ")  "
                   << std::setw(kOsValWidth) << tuple.val();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value.
///
template <typename _Val, typename _Idx>
_Val& CooTuple1<_Val, _Idx>::val() noexcept {
  return val_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  val
///
template <typename _Val, typename _Idx>
const _Val& CooTuple1<_Val, _Idx>::val() const noexcept {
  return val_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index.
///
template <typename _Val, typename _Idx>
_Idx& CooTuple1<_Val, _Idx>::idx() noexcept {
  return this->idx0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  idx
///
template <typename _Val, typename _Idx>
const _Idx& CooTuple1<_Val, _Idx>::idx() const noexcept {
  return this->idx0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the first index.
///
template <typename _Val, typename _Idx>
_Idx& CooTuple1<_Val, _Idx>::idx0() noexcept {
  return std::get<0>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  idx0
///
template <typename _Val, typename _Idx>
const _Idx& CooTuple1<_Val, _Idx>::idx0() const noexcept {
  return std::get<0>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the indices.
///
template <typename _Val, typename _Idx>
std::tuple<_Idx&>& CooTuple1<_Val, _Idx>::idxs() noexcept {
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  idxs
///
template <typename _Val, typename _Idx>
const std::tuple<_Idx&>& CooTuple1<_Val, _Idx>::idxs() const noexcept {
  return *this;
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_TUPLE1_HPP_
