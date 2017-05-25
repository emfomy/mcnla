////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/random/routine/uniform_bits_detail_mkl.hh
/// @brief   The detail of uniformly distributed bits generator with MKL.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_RANDOM_ROUTINE_UNIFORM_BITS_DETAIL_HH_
#define MCNLA_CORE_RANDOM_ROUTINE_UNIFORM_BITS_DETAIL_HH_

#ifndef MCNLA_USE_MKL
  #error 'MCNLA_USE_MKL' should be set!
#endif

#include <mcnla/core/random/vsl/vrnguniformbits.hpp>

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

static inline void uniformBitsImpl(
    VSLStreamStatePtr stream,
    DenseVector<int32_t> &&vector
) noexcept {
  detail::vRngUniformBits(VSL_RNG_METHOD_UNIFORMBITS32_STD, stream, vector.len(), vector.valPtr());
}

static inline void uniformBitsImpl(
    VSLStreamStatePtr stream,
    DenseVector<int64_t> &&vector
) noexcept {
  detail::vRngUniformBits(VSL_RNG_METHOD_UNIFORMBITS64_STD, stream, vector.len(), vector.valPtr());
}

}  // namespace detail

}  // namespace random

}  // namespace mcnla

#endif  // MCNLA_CORE_RANDOM_ROUTINE_UNIFORM_BITS_DETAIL_HH_
