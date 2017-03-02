////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_tuple2.hpp
/// @brief   The 2-dimensional COO tuple.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_TUPLE2_HPP_
#define MCNLA_CORE_MATRIX_COO_COO_TUPLE2_HPP_

#include <mcnla/core/matrix/coo/coo_tuple2.hh>
#include <iomanip>
#include <mcnla/core/matrix/coo/coo_tuple2_helper.hh>

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
template <typename _Val, typename _Idx, Trans _trans>
CooTuple2<_Val, _Idx, _trans>::CooTuple2(
    ValType &val,
    IdxType &rowidx,
    IdxType &colidx
) noexcept
  : IdxsType(toIdxs(rowidx, colidx)),
    val_(val) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given data.
///
template <typename _Val, typename _Idx, Trans _trans>
CooTuple2<_Val, _Idx, _trans>::CooTuple2(
    ValType  &val,
    IdxsType &idxs
) noexcept
  : IdxsType(idxs),
    val_(val) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
template <typename _Val, typename _Idx, Trans _trans>
CooTuple2<_Val, _Idx, _trans>::CooTuple2( const CooTuple2 &other ) noexcept
  : IdxsType(other),
    val_(other.val_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
template <typename _Val, typename _Idx, Trans _trans>
CooTuple2<_Val, _Idx, _trans>& CooTuple2<_Val, _Idx, _trans>::operator=(
    const CooTuple2 &other
) noexcept {
  IdxsType::operator=(other);
  val_ = (other.val_);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Assignment operator.
///
template <typename _Val, typename _Idx, Trans _trans>
CooTuple2<_Val, _Idx, _trans>& CooTuple2<_Val, _Idx, _trans>::operator=(
    const ValType val
) noexcept {
  val_ = val;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Assignment operator.
///
template <typename _Val, typename _Idx, Trans _trans>
CooTuple2<_Val, _Idx, _trans>& CooTuple2<_Val, _Idx, _trans>::operator=(
    const IdxsType idxs
) noexcept {
  IdxsType::operator=(idxs);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Assign value.
///
template <typename _Val, typename _Idx, Trans _trans>
CooTuple2<_Val, _Idx, _trans>& CooTuple2<_Val, _Idx, _trans>::operator()(
    const ValType val,
    const IdxType rowidx,
    const IdxType colidx
) noexcept {
  this->rowidx() = rowidx;
  this->colidx() = rowidx;
  val_ = val;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Assign value.
///
template <typename _Val, typename _Idx, Trans _trans>
CooTuple2<_Val, _Idx, _trans>& CooTuple2<_Val, _Idx, _trans>::operator()(
    const ValType val,
    const IdxsType idxs
) noexcept {
  IdxsType::operator=(idxs);
  val_ = val;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Output to stream.
///
template <typename __Val, typename __Idx, Trans __trans>
std::ostream& operator<<(
    std::ostream &os,
    const CooTuple2<__Val, __Idx, __trans> &tuple
) {
  return os << "(" << std::setw(kOsIdxWidth) << tuple.rowidx() << ", "
                   << std::setw(kOsIdxWidth) << tuple.colidx() << ")  "
                   << std::setw(kOsValWidth) << tuple.val();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value.
///
template <typename _Val, typename _Idx, Trans _trans>
_Val& CooTuple2<_Val, _Idx, _trans>::val() noexcept {
  return val_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  val
///
template <typename _Val, typename _Idx, Trans _trans>
const _Val& CooTuple2<_Val, _Idx, _trans>::val() const noexcept {
  return val_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the row index.
///
template <typename _Val, typename _Idx, Trans _trans>
_Idx& CooTuple2<_Val, _Idx, _trans>::rowidx() noexcept {
  return !isTrans(_trans) ? this->idx0() : this->idx1();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  rowidx
///
template <typename _Val, typename _Idx, Trans _trans>
const _Idx& CooTuple2<_Val, _Idx, _trans>::rowidx() const noexcept {
  return !isTrans(_trans) ? this->idx0() : this->idx1();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the column index.
///
template <typename _Val, typename _Idx, Trans _trans>
_Idx& CooTuple2<_Val, _Idx, _trans>::colidx() noexcept {
  return !isTrans(_trans) ? this->idx1() : this->idx0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  colidx
///
template <typename _Val, typename _Idx, Trans _trans>
const _Idx& CooTuple2<_Val, _Idx, _trans>::colidx() const noexcept {
  return !isTrans(_trans) ? this->idx1() : this->idx0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the first index.
///
template <typename _Val, typename _Idx, Trans _trans>
_Idx& CooTuple2<_Val, _Idx, _trans>::idx0() noexcept {
  return std::get<0>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  idx0
///
template <typename _Val, typename _Idx, Trans _trans>
const _Idx& CooTuple2<_Val, _Idx, _trans>::idx0() const noexcept {
  return std::get<0>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the second index.
///
template <typename _Val, typename _Idx, Trans _trans>
_Idx& CooTuple2<_Val, _Idx, _trans>::idx1() noexcept {
  return std::get<1>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  idx1
///
template <typename _Val, typename _Idx, Trans _trans>
const _Idx& CooTuple2<_Val, _Idx, _trans>::idx1() const noexcept {
  return std::get<1>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the indices (storage order).
///
template <typename _Val, typename _Idx, Trans _trans>
std::tuple<_Idx&, _Idx&>& CooTuple2<_Val, _Idx, _trans>::idxs() noexcept {
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  idxs
///
template <typename _Val, typename _Idx, Trans _trans>
const std::tuple<_Idx&, _Idx&>& CooTuple2<_Val, _Idx, _trans>::idxs() const noexcept {
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert to the indices (storage order).
///
template <typename _Val, typename _Idx, Trans _trans>
std::tuple<_Idx&, _Idx&> CooTuple2<_Val, _Idx, _trans>::toIdxs(
    IdxType &rowidx,
    IdxType &colidx
) const noexcept {
  return !isTrans(_trans) ? IdxsType(rowidx, colidx) : IdxsType(colidx, rowidx);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_TUPLE2_HPP_
