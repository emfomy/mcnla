////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/random/vsl/vrnggaussian.hpp
/// @brief   The VSL vRngGaussian.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_RANDOM_VSL_VRNGGAUSSIAN_HPP_
#define MCNLA_CORE_RANDOM_VSL_VRNGGAUSSIAN_HPP_

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
/// @brief  Generates normally distributed random numbers.
///
//@{
static inline index_t vRngGaussian(
    const index_t method, VSLStreamStatePtr stream, const index_t n, float *r, const float a, const float sigma
) noexcept { return vsRngGaussian(method, stream, n, r, a, sigma); }
static inline index_t vRngGaussian(
    const index_t method, VSLStreamStatePtr stream, const index_t n, double *r, const double a, const double sigma
) noexcept { return vdRngGaussian(method, stream, n, r, a, sigma); }
//@}

}  // namespace detail

}  // namespace random

}  // namespace mcnla

#endif  // MCNLA_CORE_RANDOM_VSL_VRNGGAUSSIAN_HPP_
