////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/random/routine/uniform.hpp
/// @brief   The uniform distribution generator routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_RANDOM_ROUTINE_UNIFORM_HPP_
#define MCNLA_CORE_RANDOM_ROUTINE_UNIFORM_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/random/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/random.hpp>

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

template <typename _Scalar>
inline void uniformImpl(
    DenseVector<_Scalar> &vector,
    const index_t seed
) noexcept {
  Engine<_Scalar> engine(seed);
  engine.uniform(vector);
}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  random_module
/// @copydoc  mcnla::random::Engine::uniform
///
/// @see  mcnla::random::Engine
///
template <typename _Scalar>
inline void uniform(
    DenseVector<_Scalar> &vector,
    const index_t seed
) noexcept {
  detail::uniformImpl(vector, seed);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar>
inline void uniform(
    DenseVector<_Scalar> &&vector,
    const index_t seed
) noexcept {
  detail::uniformImpl(vector, seed);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace random

}  // namespace mcnla

#endif  // MCNLA_CORE_RANDOM_ROUTINE_UNIFORM_HPP_
