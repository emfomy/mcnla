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
#include <mcnla/core/lapack/def.hpp>
#include <mcnla/core/matrix.hpp>
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
/// @ingroup  lapack_auxiliary_module
/// @brief  Returns a vector of random numbers from a uniform or normal distribution.
///
/// @attention  The out-of-range spaces are also changed.
///
template <index_t idist, typename _Scalar>
inline void larnv(
    DenseVector<_Scalar> &x,
    index_t iseed[4]
) noexcept {
  static_assert(traits::ScalarTraits<_Scalar>::is_real ? (1 <= idist && idist <= 3) : (1 <= idist && idist <= 5),
                "Invalid idist!");
  detail::larnv(idist, iseed, (x.getLength()-1) * x.getStride() + 1, x.getValuePtr());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <index_t idist, typename _Scalar>
inline void larnv(
    DenseVector<_Scalar> &&x,
    index_t iseed[4]
) noexcept {
  larnv<idist>(x, iseed);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace lapack

}  // namespace mcnla

#endif  // MCNLA_CORE_LAPACK_ROUTINE_LARNV_HPP_
