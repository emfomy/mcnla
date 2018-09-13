////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_tuple2_helper.hh
/// @brief   The helpers of 2-dimensional COO tuple.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_TUPLE2_HELPER_HH_
#define MCNLA_CORE_MATRIX_COO_COO_TUPLE2_HELPER_HH_

#include <mcnla/core/matrix/coo/def.hpp>
#include <mcnla/core/matrix/coo/coo_tuple2.hh>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

template <typename _Val, typename _Idx, Trans _trans>
using CooTuple2Ptr = Ptr<CooTuple2<_Val, _Idx, _trans>>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Makes a COO tuple
///
/// @param  val     The value.
/// @param  rowidx  The row index.
/// @param  colidx  The column index.
///
template <typename _Val, typename _Idx, Trans _trans>
inline CooTuple2<_Val, _Idx, _trans> makeCooTuple(
    _Val &val,
    _Idx &rowidx,
    _Idx &colidx
) noexcept {
  return CooTuple2<_Val, _Idx, _trans>(val, rowidx, colidx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Makes a COO tuple
///
/// @param  val   The value.
/// @param  idxs  The indices.
///
template <typename _Val, typename _Idx, Trans _trans>
inline CooTuple2<_Val, _Idx, _trans> makeCooTuple(
    _Val &val,
    std::tuple<_Idx&, _Idx&> &idxs
) noexcept {
  return CooTuple2<_Val, _Idx, _trans>(val, idxs);
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
template <typename _Val, typename _Idx, mcnla::Trans _trans>
inline void swap(
    mcnla::matrix::CooTuple2<_Val, _Idx, _trans> a,
    mcnla::matrix::CooTuple2<_Val, _Idx, _trans> b
) noexcept {
  std::swap(a.val(), b.val());
  std::swap(a.idxs(), b.idxs());
}

}  // namespace std

#endif  // MCNLA_CORE_MATRIX_COO_COO_TUPLE2_HELPER_HH_
