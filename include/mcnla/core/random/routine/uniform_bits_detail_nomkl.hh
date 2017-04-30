////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/random/routine/uniform_bits_detail_nomkl.hh
/// @brief   The detail of uniformly distributed bits generator without MKL.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_RANDOM_ROUTINE_UNIFORM_BITS_DETAIL_HH_
#define MCNLA_CORE_RANDOM_ROUTINE_UNIFORM_BITS_DETAIL_HH_

#ifdef MCNLA_USE_MKL
  #error 'MCNLA_USE_MKL' should not be set!
#endif

#include <mcnla/core/random/streams/streams.hh>

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
static inline void uniformBitsImpl(
    _Gen &gen,
    DenseVector<index_t> &&vector
) noexcept {
  for ( auto &v : vector ) {
    v = gen();
  }
}

}  // namespace detail

}  // namespace random

}  // namespace mcnla

#endif  // MCNLA_CORE_RANDOM_ROUTINE_UNIFORM_BITS_DETAIL_HH_
