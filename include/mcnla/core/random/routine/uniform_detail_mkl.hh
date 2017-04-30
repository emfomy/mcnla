////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/random/routine/uniform_detail_mkl.hh
/// @brief   The detail of uniform distribution generator with MKL.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_RANDOM_ROUTINE_UNIFORM_DETAIL_HH_
#define MCNLA_CORE_RANDOM_ROUTINE_UNIFORM_DETAIL_HH_

#ifndef MCNLA_USE_MKL
  #error 'MCNLA_USE_MKL' should be set!
#endif

#include <mcnla/core/random/vsl/vrnguniform.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The random namespace
//
namespace random {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace
//
namespace detail {

template <typename _Val>
static inline void uniformImpl(
          VSLStreamStatePtr stream,
          DenseVector<_Val> &&vector,
    const _Val a,
    const _Val b
) noexcept {
  detail::vRngUniform(VSL_RNG_METHOD_UNIFORM_STD, stream, vector.length(), vector.valPtr(), a, b);
}

}  // namespace detail

}  // namespace random

}  // namespace mcnla

#endif  // MCNLA_CORE_RANDOM_ROUTINE_UNIFORM_DETAIL_HH_
