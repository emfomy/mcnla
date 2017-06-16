////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/dot.hpp
/// @brief   The BLAS DOT routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_DOT_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_DOT_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/raw/blas/dot.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The linear algebra namespace
//
namespace la {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas1_module
/// @brief  Computes a vector-vector dot product.
///
//@{
template <typename _Val>
inline _Val dot(
    const DenseVector<_Val> &x,
    const DenseVector<_Val> &y
) noexcept {
  mcnla_assert_eq(x.sizes(), y.sizes());
  return detail::dot(x.len(), x.valPtr(), x.stride(), y.valPtr(), y.stride());
}

template <typename _Val>
inline _Val dot(
    const DenseVector<_Val> &x
) noexcept {
  return dot(x, x);
}
//@}

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_DOT_HPP_
