////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/random/driver/driver_detail_nomkl.hpp
/// @brief   The detail of random generator driver without MKL.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_RANDOM_DRIVER_DRIVER_DETAIL_HPP_
#define MCNLA_CORE_RANDOM_DRIVER_DRIVER_DETAIL_HPP_

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
          index_t iseed[4],
          DenseVector<index_t> &&vector,
    const index_t a,
    const index_t b
) noexcept {
  std::seed_seq seq({iseed[0], iseed[1], iseed[2], iseed[3]});
  std::mt19937 gen(seq);
  std::uniform_int_distribution<> dis(a, b);
  for ( auto &v : vector ) {
    v = dis(gen);
  }
}

template <typename _Scalar>
static inline void uniformImpl(
          index_t iseed[4],
          DenseVector<_Scalar> &&vector,
    const _Scalar a,
    const _Scalar b
) noexcept {
  std::seed_seq seq({iseed[0], iseed[1], iseed[2], iseed[3]});
  std::mt19937 gen(seq);
  std::uniform_real_distribution<> dis(a, b);
  for ( auto &v : vector ) {
    v = dis(gen);
  }
}

template <typename _Scalar>
static inline void gaussianImpl(
          index_t iseed[4],
          DenseVector<_Scalar> &&vector,
    const _Scalar a,
    const _Scalar b
) noexcept {
  std::seed_seq seq({iseed[0], iseed[1], iseed[2], iseed[3]});
  std::mt19937 gen(seq);
  std::normal_distribution<> dis(a, b);
  for ( auto &v : vector ) {
    v = dis(gen);
  }
}

}  // namespace detail

}  // namespace random

}  // namespace mcnla

#endif  // MCNLA_CORE_RANDOM_DRIVER_DRIVER_DETAIL_HPP_
