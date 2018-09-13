////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_tuple1_helper.hh
/// @brief   The helpers of 1-dimensional COO tuple.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_TUPLE1_HELPER_HH_
#define MCNLA_CORE_MATRIX_COO_COO_TUPLE1_HELPER_HH_

#include <mcnla/core/matrix/coo/def.hpp>
#include <mcnla/core/matrix/coo/coo_tuple1.hh>
#include <mcnla/core/matrix/kit/ptr.hh>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

template <typename _Val, typename _Idx>
using CooTuple1Ptr = Ptr<CooTuple1<_Val, _Idx>>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Makes a COO tuple
///
/// @param  val  The value.
/// @param  idx  The index.
///
template <typename _Val, typename _Idx>
inline CooTuple1<_Val, _Idx> makeCooTuple(
    _Val &val,
    _Idx &idx
) noexcept {
  return CooTuple1<_Val, _Idx>(val, idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Makes a COO tuple
///
/// @param  val   The value.
/// @param  idxs  The indices.
///
template <typename _Val, typename _Idx>
inline CooTuple1<_Val, _Idx> makeCooTuple(
    _Val &val,
    std::tuple<_Idx&> &idxs
) noexcept {
  return CooTuple1<_Val, _Idx>(val, idxs);
}

}  // namespace matrix

}  // namespace mcnla

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The STL namespace.
//
namespace std {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Swap two COO tuples
///
template <typename _Val, typename _Idx>
inline void swap(
    mcnla::matrix::CooTuple1<_Val, _Idx> a,
    mcnla::matrix::CooTuple1<_Val, _Idx> b
) noexcept {
  std::swap(a.val(), b.val());
  std::swap(a.idxs(), b.idxs());
}

}  // namespace std

#endif  // MCNLA_CORE_MATRIX_COO_COO_TUPLE1_HELPER_HH_
