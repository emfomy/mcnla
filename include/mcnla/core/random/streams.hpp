////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/random/streams.hpp
/// @brief   The random generator driver.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_RANDOM_STREAMS_HPP_
#define MCNLA_CORE_RANDOM_STREAMS_HPP_

#include <mcnla/core/random/streams.hh>
#include <random>

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
Streams::Streams(
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
Streams::~Streams() noexcept {
#ifdef MCNLA_USE_MKL
  for ( index_t i = 0; i < omp_size_; ++i ) {
    vslDeleteStream(&(streams_[i]));
  }
#endif  // MCNLA_USE_MKL
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of OpenMP threads.
///
index_t Streams::ompSize() const noexcept {
  return omp_size_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw random stream.
///
Streams::StreamType Streams::operator[](
    const index_t i
) const noexcept {
  return streams_[i];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the random seed.
///
void Streams::setSeed(
    const index_t seed
) noexcept {
#ifdef MCNLA_USE_MKL
  std::seed_seq seq{seed};
  std::vector<index_t> seeds(omp_size_);
  seq.generate(seeds.begin(), seeds.end());
  for ( index_t i = 0; i < omp_size_; ++i ) {
    vslNewStream(&(streams_[i]), VSL_BRNG_MCG31, seeds[i]);
  }
#else  // MCNLA_USE_MKL
  std::seed_seq seq{seed};
  seq.generate(streams_, streams_ + omp_size_);
#endif  // MCNLA_USE_MKL
}

}  // namespace random

}  // namespace mcnla

#endif  // MCNLA_CORE_RANDOM_STREAMS_HPP_
