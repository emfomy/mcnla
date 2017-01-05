////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/random/engine/gaussian.hpp
/// @brief   The normal (Gaussian) distribution generator engine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_RANDOM_ENGINE_GAUSSIAN_ENGINE_HPP_
#define MCNLA_CORE_RANDOM_ENGINE_GAUSSIAN_ENGINE_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/random/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/utility/traits.hpp>

#ifdef MCNLA_USE_MKL
#include <mkl.h>
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
/// @brief  The normal (Gaussian) distribution generator engine.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
class GaussianEngine {

 private:

  using ScalarType = _Scalar;
  using VectorType = DenseVector<ScalarType>;

 protected:

#ifdef MCNLA_USE_MKL

  /// The random stream
  VSLStreamStatePtr stream_;

#else  // MCNLA_USE_MKL

  index_t seed_[4];

#endif  // MCNLA_USE_MKL

 public:

  // Constructors
  inline GaussianEngine( const index_t seed ) noexcept;

  // Destructor
  inline ~GaussianEngine() noexcept;

  // Operators
  inline void operator()( VectorType &vector ) const noexcept;
  inline void operator()( VectorType &&vector ) const noexcept;

  // Sets seed
  inline void setSeed( const index_t seed ) noexcept;

 protected:

  // Computes
  inline void compute( VectorType &vector ) const noexcept;

};

}  // namespace random

}  // namespace mcnla

#endif  // MCNLA_CORE_RANDOM_ENGINE_GAUSSIAN_ENGINE_HPP_
