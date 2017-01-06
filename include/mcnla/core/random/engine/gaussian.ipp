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
#include <random>
#include <mcnla/core/lapack.hpp>
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
) noexcept
#ifdef MCNLA_USE_OMP
  : omp_size_(omp_get_max_threads()),
#else  // MCNLA_USE_OMP
  : omp_size_(1),
#endif  // MCNLA_USE_OMP
    streams_(omp_size_) {
  setSeed(seed);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default destructor.
///
template <typename _Scalar>
GaussianEngine<_Scalar>::~GaussianEngine() noexcept {
  #ifdef MCNLA_USE_MKL
    #pragma omp parallel for
    for ( index_t i = 0; i < omp_size_; ++i ) {
      vslDeleteStream(&(streams_[i]));
    }
  #endif  // MCNLA_USE_MKL
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of OpenMP threads.
///
template <typename _Scalar>
index_t GaussianEngine<_Scalar>::ompSize() const noexcept {
  return omp_size_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  compute
///
template <typename _Scalar>
void GaussianEngine<_Scalar>::operator()(
    VectorType &vector
) noexcept {
  compute(vector);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  compute
///
template <typename _Scalar>
void GaussianEngine<_Scalar>::operator()(
    VectorType &&vector
) noexcept {
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

    std::seed_seq seq{seed};
    std::vector<index_t> seeds(omp_size_);
    seq.generate(seeds.begin(), seeds.end());
    #pragma omp parallel for
    for ( index_t i = 0; i < omp_size_; ++i ) {
      vslNewStream(&(streams_[i]), VSL_BRNG_MCG31, seeds[i]);
    }

  #else  // MCNLA_USE_MKL

    std::seed_seq seq{seed};
    seq.generate(streams_[0], streams_[omp_size_]);
    #pragma omp parallel for
    for ( index_t i = 0; i < omp_size_; ++i ) {
      streams_[i][0] = size_t(streams_[i][0]) % 4096;
      streams_[i][1] = size_t(streams_[i][1]) % 4096;
      streams_[i][2] = size_t(streams_[i][2]) % 4096;
      streams_[i][3] = size_t(streams_[i][3]) % 2048 + 1;
    }

  #endif  // MCNLA_USE_MKL
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns a vector of random numbers from a normal (Gaussian) distribution.
///
template <typename _Scalar>
void GaussianEngine<_Scalar>::compute(
    VectorType &vector
) noexcept {
  #pragma omp parallel for
  for ( index_t i = 0; i < omp_size_; ++i ) {
    index_t length = vector.length() / omp_size_;
    index_t start = length * i;
    if ( i == omp_size_-1 ) {
      length = vector.length() - start;
    }

    #ifdef MCNLA_USE_MKL
      detail::vRngGaussian(VSL_RNG_METHOD_GAUSSIAN_BOXMULLER, streams_[i], length, vector.valuePtr()+start, 0.0, 1.0);
    #else  // MCNLA_USE_MKL
      lapack::detail::larnv(3, streams_[i], length, vector.valuePtr()+start);
    #endif  // MCNLA_USE_MKL

  }
}

}  // namespace random

}  // namespace mcnla

#endif  // MCNLA_CORE_RANDOM_ENGINE_GAUSSIAN_IPP_
