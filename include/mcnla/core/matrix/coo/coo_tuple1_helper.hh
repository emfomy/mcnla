////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_tuple1_helper.hh
/// @brief   The helpers of 1-dimensional COO tuple.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_TUPLE1_HELPER_HH_
#define MCNLA_CORE_MATRIX_COO_COO_TUPLE1_HELPER_HH_

#include <mcnla/core/matrix/def.hpp>
#include <mcnla/core/matrix/coo/coo_tuple1.hh>

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
class CooTuple1Ptr {

 private:

  using TupleType = CooTuple1<_Val, _Idx>;

 protected:

  TupleType tuple_;

 public:

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief  Construct with given tuple.
  ///
  CooTuple1Ptr(
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
///
template <typename _Val, typename _Idx>
inline CooTuple1<_Val, _Idx> makeCooTuple(
    _Val &val,
    _Idx &idx0
) noexcept {
  return CooTuple1<_Val, _Idx>(val, idx0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_coo_module_detail
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
/// @ingroup  matrix_coo_module_detail
/// @brief  Swap two COO tuples
///
template <typename _Val, typename _Idx>
void swap(
    mcnla::matrix::CooTuple1<_Val, _Idx> &a,
    mcnla::matrix::CooTuple1<_Val, _Idx> &b
) noexcept {
  std::swap(a.val(), b.val());
  std::swap(a.idxs(), b.idxs());
}

}  // namespace std

#endif  // MCNLA_CORE_MATRIX_COO_COO_TUPLE1_HELPER_HH_
