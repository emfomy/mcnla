////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/random/routine/uniform.hpp
/// @brief   The uniform distribution generator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_RANDOM_ROUTINE_UNIFORM_HPP_
#define MCNLA_CORE_RANDOM_ROUTINE_UNIFORM_HPP_

#include <mcnla/core/random/def.hpp>
#include <mcnla/core/random/streams.hpp>

#ifdef MCNLA_USE_OMP
  #include <omp.h>
#endif  // MCNLA_USE_MKL

#ifdef MCNLA_USE_MKL
  #include <mcnla/core/random/routine/uniform_detail_mkl.hh>
#else  // MCNLA_USE_MKL
  #include <mcnla/core/random/routine/uniform_detail_nomkl.hh>
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
/// @brief  Returns a vector of random numbers from a uniform distribution.
///
template <typename _Val>
inline void uniform(
    const Streams &streams,
          DenseVector<_Val> &vector,
    const _Val a = 0,
    const _Val b = 1
) noexcept {
#ifdef MCNLA_USE_OMP
  #pragma omp parallel for
#endif  // MCNLA_USE_OMP
  for ( index_t i = 0; i < streams.ompSize(); ++i ) {
    index_t length = vector.length() / streams.ompSize();
    index_t start = length * i;
    if ( i == streams.ompSize()-1 ) {
      length = vector.length() - start;
    }
    detail::uniformImpl(streams[i], vector({start, start+length}), a, b);
  }
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void uniform(
    const Streams &streams,
          DenseVector<_Val> &&vector,
    const _Val a = 0,
    const _Val b = 1
) noexcept {
  uniform(streams, vector, a, b);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace random

}  // namespace mcnla

#endif  // MCNLA_CORE_RANDOM_ROUTINE_UNIFORM_HPP_
