////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/random/driver/driver.hpp
/// @brief   The random generator driver.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_RANDOM_DRIVER_DRIVER_HPP_
#define MCNLA_CORE_RANDOM_DRIVER_DRIVER_HPP_

#include <mcnla/core/random/driver/driver.hh>
#include <random>

#ifdef MCNLA_USE_MKL
  #include <mcnla/core/random/driver/driver_detail_mkl.hh>
#else  // MCNLA_USE_MKL
  #include <mcnla/core/random/driver/driver_detail_nomkl.hh>
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
template <typename _Val>
Driver<_Val>::Driver(
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
template <typename _Val>
Driver<_Val>::~Driver() noexcept {
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
template <typename _Val>
index_t Driver<_Val>::ompSize() const noexcept {
  return omp_size_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns a vector of random numbers from a uniform distribution.
///
template <typename _Val>
void Driver<_Val>::uniform(
          VectorType &vector,
    const ValType a,
    const ValType b
) noexcept {
  #pragma omp parallel for
  for ( index_t i = 0; i < omp_size_; ++i ) {
    index_t length = vector.length() / omp_size_;
    index_t start = length * i;
    if ( i == omp_size_-1 ) {
      length = vector.length() - start;
    }
    detail::uniformImpl(streams_[i], vector({start, start+length}), a, b);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  uniform
///
template <typename _Val>
void Driver<_Val>::uniform(
          VectorType &&vector,
    const ValType a,
    const ValType b
) noexcept {
  uniform(vector, a, b);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns a vector of random numbers from a normal (Gaussian) distribution.
///
template <typename _Val>
void Driver<_Val>::gaussian(
          VectorType &vector,
    const ValType a,
    const ValType b
) noexcept {
  #pragma omp parallel for
  for ( index_t i = 0; i < omp_size_; ++i ) {
    index_t length = vector.length() / omp_size_;
    index_t start = length * i;
    if ( i == omp_size_-1 ) {
      length = vector.length() - start;
    }
    detail::gaussianImpl(streams_[i], vector({start, start+length}), a, b);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  gaussian
///
template <typename _Val>
void Driver<_Val>::gaussian(
          VectorType &&vector,
    const ValType a,
    const ValType b
) noexcept {
  gaussian(vector, a, b);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the random seed.
///
template <typename _Val>
void Driver<_Val>::setSeed(
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

}  // namespace random

}  // namespace mcnla

#endif  // MCNLA_CORE_RANDOM_DRIVER_DRIVER_HPP_
