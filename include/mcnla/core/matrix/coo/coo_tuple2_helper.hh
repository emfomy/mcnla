////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_tuple2_helper.hh
/// @brief   The helpers of 2-dimensional COO tuple.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_TUPLE2_HELPER_HH_
#define MCNLA_CORE_MATRIX_COO_COO_TUPLE2_HELPER_HH_

#include <mcnla/core/matrix/def.hpp>
#include <mcnla/core/matrix/coo/coo_tuple2.hh>

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
/// The pointer type of CooTuple1
///
/// @tparam  _Val  The value type.
/// @tparam  _Idx  The index type.
///
template <typename _Val, typename _Idx>
class CooTuple2Ptr {

 private:

  using TupleType = CooTuple2<_Val, _Idx>;

 protected:

  /// The tuple.
  TupleType tuple_;

 public:

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief  Construct with given tuple.
  ///
  CooTuple2Ptr(
    const TupleType &tuple
  ) noexcept
    : tuple_(tuple) {}


  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief  Indirection operator.
  ///
  inline TupleType* operator->() noexcept {
    return &tuple_;
  }


  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @copydoc  operator->()
  ///
  inline const TupleType* operator->() const noexcept {
    return &tuple_;
  }

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
/// @param  val   The value.
/// @param  idxs  The indices.
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
inline void swap(
    mcnla::matrix::CooTuple2<_Val, _Idx> &a,
    mcnla::matrix::CooTuple2<_Val, _Idx> &b
) noexcept {
  std::swap(a.val(), b.val());
  std::swap(a.idxs(), b.idxs());
}

}  // namespace std

#endif  // MCNLA_CORE_MATRIX_COO_COO_TUPLE2_HELPER_HH_
