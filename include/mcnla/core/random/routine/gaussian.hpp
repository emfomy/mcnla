////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/random/routine/gaussian.hpp
/// @brief   The normal (Gaussian) distribution generator routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_RANDOM_ROUTINE_GAUSSIAN_HPP_
#define MCNLA_CORE_RANDOM_ROUTINE_GAUSSIAN_HPP_

#include <mcnla/core/random/def.hpp>
#include <mcnla/core/random/driver.hpp>

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

template <typename _Val>
inline void gaussianImpl(
    DenseVector<_Val> &vector,
    const index_t seed
) noexcept {
  Driver<_Val> driver(seed);
  driver.gaussian(vector);
}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  random_module
/// @copydoc  mcnla::random::Driver::gaussian
///
/// @see  mcnla::random::Driver
///
template <typename _Val>
inline void gaussian(
    DenseVector<_Val> &vector,
    const index_t seed
) noexcept {
  detail::gaussianImpl(vector, seed);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void gaussian(
    DenseVector<_Val> &&vector,
    const index_t seed
) noexcept {
  detail::gaussianImpl(vector, seed);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace random

}  // namespace mcnla

#endif  // MCNLA_CORE_RANDOM_ROUTINE_GAUSSIAN_HPP_
