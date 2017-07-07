////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/random/vsl/vrnguniform.hpp
/// @brief   The VSL vRngUniform.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_RANDOM_VSL_VIRNGUNIFORM_HPP_
#define MCNLA_CORE_RANDOM_VSL_VIRNGUNIFORM_HPP_

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
/// @brief  Generates random numbers with uniform distribution.
///
//@{
static inline index_t vRngUniform(
    const index_t method, VSLStreamStatePtr stream, const index_t n, float *r, const float a, const float b
) noexcept { return vsrnguniform_(&method, &stream, &n, r, &a, &b); }
static inline index_t vRngUniform(
    const index_t method, VSLStreamStatePtr stream, const index_t n, double *r, const double a, const double b
) noexcept { return vdrnguniform_(&method, &stream, &n, r, &a, &b); }
static inline index_t vRngUniform(
    const index_t method, VSLStreamStatePtr stream, const index_t n, int32_t *r, const int32_t a, const int32_t b
) noexcept { return virnguniform_(&method, &stream, &n, r, &a, &b); }
static inline index_t vRngUniform(
    const index_t method, VSLStreamStatePtr stream, const index_t n, int64_t *r, const int64_t a, const int64_t b
) noexcept = delete;
//@}

}  // namespace detail

}  // namespace random

}  // namespace mcnla

#endif  // MCNLA_CORE_RANDOM_VSL_VIRNGUNIFORM_HPP_
