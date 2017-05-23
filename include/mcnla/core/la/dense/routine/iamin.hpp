////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/iamin.hpp
/// @brief   The BLAS IAMIN routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_IAMIN_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_IAMIN_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/raw/blas/iamin.hpp>

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
/// @brief  Finds the index of the element with minimum absolute value.
///
//@{
template <typename _Val>
inline index_t iamin(
    const DenseVector<_Val> &x
) noexcept {
  return detail::iamin(x.length(), x.valPtr(), x.stride());
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas1_module
/// @brief  Finds the element with minimum absolute value.
///
//@{
template <typename _Val>
inline RealValT<_Val> amin(
    const DenseVector<_Val> &x
) noexcept {
  index_t idx = detail::iamin(x.length(), x.valPtr(), x.stride());
  return std::abs(x(idx));
}
//@}

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_IAMIN_HPP_
