////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/random/vsl/vrnguniformbits.hpp
/// @brief   The VSL vRngUniformBits.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_RANDOM_VSL_VIRNGUNIFORMBITS_HPP_
#define MCNLA_CORE_RANDOM_VSL_VIRNGUNIFORMBITS_HPP_

#include <mcnla/core/random/def.hpp>
#include <mkl.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The RANDOM namespace
//
namespace random {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace
//
namespace detail {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Generates uniformly distributed bits.
///
//@{
static inline index_t vRngUniformBits(
    const index_t method, VSLStreamStatePtr stream, const index_t n, int32_t *r
) noexcept { return virnguniformbits32_(&method, &stream, &n, static_cast<unsigned int*>(static_cast<void*>(r))); }
static inline index_t vRngUniformBits(
    const index_t method, VSLStreamStatePtr stream, const index_t n, int64_t *r
) noexcept { return virnguniformbits64_(&method, &stream, &n, static_cast<unsigned MKL_INT64*>(static_cast<void*>(r))); }
//@}

}  // namespace detail

}  // namespace random

}  // namespace mcnla

#endif  // MCNLA_CORE_RANDOM_VSL_VIRNGUNIFORMBITS_HPP_
