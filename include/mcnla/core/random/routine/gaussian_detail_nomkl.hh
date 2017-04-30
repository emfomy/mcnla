////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/random/routine/gaussian_detail_nomkl.hh
/// @brief   The detail of Gaussian distribution generator without MKL.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_RANDOM_ROUTINE_GAUSSIAN_DETAIL_HH_
#define MCNLA_CORE_RANDOM_ROUTINE_GAUSSIAN_DETAIL_HH_

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

template <typename _Val, typename _Gen>
static inline void gaussianImpl(
          _Gen &gen,
          DenseVector<_Val> &&vector,
    const _Val a,
    const _Val sigma
) noexcept {
  std::normal_distribution<> dis(a, sigma);
  for ( auto &v : vector ) {
    v = dis(gen);
  }
}

}  // namespace detail

}  // namespace random

}  // namespace mcnla

#endif  // MCNLA_CORE_RANDOM_ROUTINE_GAUSSIAN_DETAIL_HH_
