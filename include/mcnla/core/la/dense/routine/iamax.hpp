////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/iamax.hpp
/// @brief   The BLAS IAMAX routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_IAMAX_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_IAMAX_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/raw/blas/iamax.hpp>

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
/// @brief  Finds the index of the element with maximum absolute value.
///
//@{
template <typename _Val>
inline index_t iamax(
    const DenseVector<_Val> &x
) noexcept {
  return detail::iamax(x.length(), x.valPtr(), x.stride());
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas1_module
/// @brief  Finds the element with maximum absolute value.
///
//@{
template <typename _Val>
inline RealValT<_Val> amax(
    const DenseVector<_Val> &x
) noexcept {
  index_t idx = detail::iamax(x.length(), x.valPtr(), x.stride());
  return std::abs(x(idx));
}
//@}

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_IAMAX_HPP_
