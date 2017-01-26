////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/random/driver/driver_detail_mkl.hpp
/// @brief   The detail of random generator driver with MKL.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_RANDOM_DRIVER_DRIVER_DETAIL_HPP_
#define MCNLA_CORE_RANDOM_DRIVER_DRIVER_DETAIL_HPP_

#ifndef MCNLA_USE_MKL
  #error 'MCNLA_USE_MKL' should be set!
#endif

#include <mcnla/core/matrix.hpp>
#include <mcnla/core/random/vsl/vrnguniform.hpp>
#include <mcnla/core/random/vsl/vrnggaussian.hpp>

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


template <typename _Scalar>
static inline void uniformImpl(
          VSLStreamStatePtr stream,
          DenseVector<_Scalar> &&vector,
    const _Scalar a,
    const _Scalar b
) noexcept {
  detail::vRngUniform(VSL_RNG_METHOD_UNIFORM_STD, stream, vector.length(), vector.valPtr(), a, b);
}

template <typename _Scalar>
static inline void gaussianImpl(
          VSLStreamStatePtr stream,
          DenseVector<_Scalar> &&vector,
    const _Scalar a,
    const _Scalar b
) noexcept {
  detail::vRngGaussian(VSL_RNG_METHOD_GAUSSIAN_BOXMULLER, stream, vector.length(), vector.valPtr(), a, b);
}

}  // namespace detail

}  // namespace random

}  // namespace mcnla

#endif  // MCNLA_CORE_RANDOM_DRIVER_DRIVER_DETAIL_HPP_
