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
template <typename _Scalar>
inline _Scalar dot(
    const DenseVector<_Scalar> &x,
    const DenseVector<_Scalar> &y
) noexcept {
  mcnla_assert_eq(x.sizes(), y.sizes());
  return detail::dot(x.length(), x.valuePtr(), x.stride(), y.valuePtr(), y.stride());
}

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_DOT_HPP_
