////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/random/engine/gaussian.ipp
/// @brief   The implementation of normal (Gaussian) distribution generator engine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_RANDOM_ENGINE_GAUSSIAN_IPP_
#define MCNLA_CORE_RANDOM_ENGINE_GAUSSIAN_IPP_

#include <mcnla/core/random/engine/gaussian.hpp>

#ifndef MCNLA_USE_MKL
#include <<mcnla/core/lapack.hpp>
#endif  // MCNLA_USE_MKL

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The random namespace
//
namespace random {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given seed.
///
template <typename _Scalar>
GaussianEngine<_Scalar>::GaussianEngine(
    const index_t seed
) noexcept {
  setSeed(seed);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default destructor.
///
template <typename _Scalar>
GaussianEngine<_Scalar>::~GaussianEngine() noexcept {
#ifdef MCNLA_USE_MKL
  vslDeleteStream(&stream_);
#endif  // MCNLA_USE_MKL
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  compute
///
template <typename _Scalar>
void GaussianEngine<_Scalar>::operator()(
    VectorType &vector
) const noexcept {
  compute(vector);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  compute
///
template <typename _Scalar>
void GaussianEngine<_Scalar>::operator()(
    VectorType &&vector
) const noexcept {
  compute(vector);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the random seed.
///
template <typename _Scalar>
void GaussianEngine<_Scalar>::setSeed(
    const index_t seed
) noexcept {
#ifdef MCNLA_USE_MKL
  vslNewStream(&stream_, VSL_BRNG_MCG31, seed);
#else  // MCNLA_USE_MKL
  seed_[0] = (seed & 0x000000FF);
  seed_[1] = (seed & 0x0000FF00) >> 8;
  seed_[2] = (seed & 0x00FF0000) >> 16;
  seed_[3] = (seed & 0xFF000000) >> 23 + 1;
#endif  // MCNLA_USE_MKL
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns a vector of random numbers from a normal (Gaussian) distribution.
///
template <typename _Scalar>
void GaussianEngine<_Scalar>::compute(
    VectorType &vector
) const noexcept {
#ifdef MCNLA_USE_MKL
  vdRngGaussian(VSL_RNG_METHOD_GAUSSIAN_BOXMULLER, stream_, vector.length(), vector.valuePtr(), 0.0, 1.0);
#else  // MCNLA_USE_MKL
  lapack::larnv<3>(vector, seed_);
#endif  // MCNLA_USE_MKL
}

}  // namespace random

}  // namespace mcnla

#endif  // MCNLA_CORE_RANDOM_ENGINE_GAUSSIAN_IPP_
