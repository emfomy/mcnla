////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/random/routine/gaussian.hpp
/// @brief   The Gaussian distribution generator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_RANDOM_ROUTINE_GAUSSIAN_HPP_
#define MCNLA_CORE_RANDOM_ROUTINE_GAUSSIAN_HPP_

#include <mcnla/core/random/def.hpp>
#include <mcnla/core/random/streams.hpp>

#ifdef MCNLA_USE_OMP
  #include <omp.h>
#endif  // MCNLA_USE_MKL

#ifdef MCNLA_USE_MKL
  #include <mcnla/core/random/routine/gaussian_detail_mkl.hh>
#else  // MCNLA_USE_MKL
  #include <mcnla/core/random/routine/gaussian_detail_nomkl.hh>
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
/// @ingroup  random_module
/// @brief  Returns a vector of random numbers from a normal (Gaussian) distribution.
///
template <typename _Val>
inline void gaussian(
    const Streams &streams,
          DenseVector<_Val> &vector,
    const _Val a = 0,
    const _Val sigma = 1
) noexcept {
#ifdef MCNLA_USE_OMP
  #pragma omp parallel for
#endif  // MCNLA_USE_OMP
  for ( index_t i = 0; i < streams.ompSize(); ++i ) {
    index_t len = vector.len() / streams.ompSize();
    index_t start = len * i;
    if ( i == streams.ompSize()-1 ) {
      len = vector.len() - start;
    }
    detail::gaussianImpl(streams[i], vector({start, start+len}), a, sigma);
  }
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void gaussian(
    const Streams &streams,
          DenseVector<_Val> &&vector,
    const _Val a = 0,
    const _Val sigma = 1
) noexcept {
  gaussian(streams, vector, a, sigma);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace random

}  // namespace mcnla

#endif  // MCNLA_CORE_RANDOM_ROUTINE_GAUSSIAN_HPP_
