////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/random/routine/uniform_detail_nomkl.hh
/// @brief   The detail of uniform distribution generator without MKL.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_RANDOM_ROUTINE_UNIFORM_DETAIL_HH_
#define MCNLA_CORE_RANDOM_ROUTINE_UNIFORM_DETAIL_HH_

#ifdef MCNLA_USE_MKL
  #error 'MCNLA_USE_MKL' should not be set!
#endif

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

template <typename _Gen>
static inline void uniformImpl(
          _Gen &gen,
          DenseVector<index_t> &&vector,
    const index_t a,
    const index_t b
) noexcept {
  std::uniform_int_distribution<> dis(a, b);
  for ( auto &v : vector ) {
    v = dis(gen);
  }
}

template <typename _Val, typename _Gen>
static inline void uniformImpl(
          _Gen &gen,
          DenseVector<_Val> &&vector,
    const _Val a,
    const _Val b
) noexcept {
  std::uniform_real_distribution<> dis(a, b);
  for ( auto &v : vector ) {
    v = dis(gen);
  }
}

}  // namespace detail

}  // namespace random

}  // namespace mcnla

#endif  // MCNLA_CORE_RANDOM_ROUTINE_UNIFORM_DETAIL_HH_
