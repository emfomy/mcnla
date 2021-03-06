////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/larnv.hpp
/// @brief   The LAPACK LARNV routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_LARNV_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_LARNV_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/raw/lapack/larnv.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The linear algebra namespace
//
namespace la {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_lapack_aux_module
/// @brief  Returns a vector of random numbers from a uniform or normal distribution.
///
/// @attention  The out-of-range spaces are also changed.
///
template <index_t idist, typename _Val>
inline void larnv(
    DenseVector<_Val> &x,
    index_t iseed[4]
) noexcept {
  static_assert(traits::ValTraits<_Val>::is_real ? (1 <= idist && idist <= 3) : (1 <= idist && idist <= 5),
                "Invalid idist!");
  detail::larnv(idist, iseed, (x.len()-1) * x.stride() + 1, x.valPtr());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <index_t idist, typename _Val>
inline void larnv(
    DenseVector<_Val> &&x,
    index_t iseed[4]
) noexcept {
  larnv<idist>(x, iseed);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_LARNV_HPP_
