////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/lapack/routine/larnv.hpp
/// @brief   The LAPACK LARNV routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LAPACK_ROUTINE_LARNV_HPP_
#define MCNLA_CORE_LAPACK_ROUTINE_LARNV_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/lapack/lapack.hpp>
#include <mcnla/core/lapack/lapack/larnv.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The LAPACK namespace
//
namespace lapack {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns a vector of random numbers from a uniform or normal distribution.
///
//@{
template <index_t idist, typename _Scalar>
inline void larnv(
    DenseVector<_Scalar> &x,
    index_t iseed[4]
) noexcept {
  static_assert(traits::ScalarTraits<_Scalar>::is_real ? (1 <= idist && idist <= 3) : (1 <= idist && idist <= 5),
                "The value of 'idist' is invalid!");
  detail::larnv(idist, iseed, x.getLength(), x.getValue());
}

template <index_t idist, typename _Scalar>
inline void larnv(
    DenseVector<_Scalar> &&x,
    index_t iseed[4]
) noexcept {
  larnv<idist>(x, iseed);
}
//@}

}  // namespace lapack

}  // namespace mcnla

#endif  // MCNLA_CORE_LAPACK_ROUTINE_LARNV_HPP_
