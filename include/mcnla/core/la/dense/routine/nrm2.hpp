////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/nrm2.hpp
/// @brief   The BLAS NRM2 routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_NRM2_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_NRM2_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/raw/blas/nrm2.hpp>

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
/// @brief  Computes the Euclidean norm of a vector.
///
template <typename _Val>
inline RealValT<_Val> nrm2(
    const DenseVector<_Val> &x
) noexcept {
  return detail::nrm2(x.len(), x.valPtr(), x.stride());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas1_module
/// @brief  Computes the Frobenius norm of a vector.
///
template <typename _Val>
inline RealValT<_Val> nrmf(
    const DenseVector<_Val> &x
) noexcept {
  return nrm2(x);
}

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_NRM2_HPP_
