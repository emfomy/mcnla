////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/random/routine/routine_detail_nomkl.hh
/// @brief   The detail of distribution generators without MKL.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_RANDOM_ROUTINE_ROUTINE_DETAIL_HH_
#define MCNLA_CORE_RANDOM_ROUTINE_ROUTINE_DETAIL_HH_

#ifdef MCNLA_USE_MKL
  #error 'MCNLA_USE_MKL' should not be set!
#endif

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
//  The detail namespace
//
namespace detail {

static inline void uniformImpl(
          index_t seed,
          DenseVector<index_t> &&vector,
    const index_t a,
    const index_t b
) noexcept {
  std::mt19937 gen(seed);
  std::uniform_int_distribution<> dis(a, b);
  for ( auto &v : vector ) {
    v = dis(gen);
  }
}

template <typename _Val>
static inline void uniformImpl(
          index_t seed,
          DenseVector<_Val> &&vector,
    const _Val a,
    const _Val b
) noexcept {
  std::mt19937 gen(seed);
  std::uniform_real_distribution<> dis(a, b);
  for ( auto &v : vector ) {
    v = dis(gen);
  }
}

template <typename _Val>
static inline void gaussianImpl(
          index_t seed,
          DenseVector<_Val> &&vector,
    const _Val a,
    const _Val sigma
) noexcept {
  std::mt19937 gen(seed);
  std::normal_distribution<> dis(a, sigma);
  for ( auto &v : vector ) {
    v = dis(gen);
  }
}

}  // namespace detail

}  // namespace random

}  // namespace mcnla

#endif  // MCNLA_CORE_RANDOM_ROUTINE_ROUTINE_DETAIL_HH_