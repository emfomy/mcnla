////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/random/vsl/vrnguniform.hpp
/// @brief   The VSL vRngUniform.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_RANDOM_VSL_VIRNGUNIFORM_HPP_
#define MCNLA_CORE_RANDOM_VSL_VIRNGUNIFORM_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
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
    const index_t method, VSLStreamStatePtr stream, const index_t n, index_t *r, const index_t a, const index_t b
) noexcept { return viRngUniform(method, stream, n, r, a, b); }
static inline index_t vRngUniform(
    const index_t method, VSLStreamStatePtr stream, const index_t n, float *r, const float a, const float b
) noexcept { return vsRngUniform(method, stream, n, r, a, b); }
static inline index_t vRngUniform(
    const index_t method, VSLStreamStatePtr stream, const index_t n, double *r, const double a, const double b
) noexcept { return vdRngUniform(method, stream, n, r, a, b); }
//@}

}  // namespace detail

}  // namespace random

}  // namespace mcnla

#endif  // MCNLA_CORE_RANDOM_VSL_VIRNGUNIFORM_HPP_
