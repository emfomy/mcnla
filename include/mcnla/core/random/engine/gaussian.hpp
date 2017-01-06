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
#include <vector>
#include <omp.h>

#ifdef MCNLA_USE_MKL
  #include <mcnla/core/random/vsl/vrnggaussian.hpp>
#else  // MCNLA_USE_MKL
  #include <mcnla/core/lapack.hpp>
#endif  // MCNLA_USE_MKL

#include <mcnla/core/matrix.hpp>
#include <mcnla/core/utility/traits.hpp>

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

  /// The number of threads
  const index_t omp_size_;

#ifdef MCNLA_USE_MKL

  /// The random streams
  std::vector<VSLStreamStatePtr> streams_;

#else  // MCNLA_USE_MKL

  /// The random streams
  std::vector<index_t[4]> streams_;

#endif  // MCNLA_USE_MKL

 public:

  // Constructors
  inline GaussianEngine( const index_t seed ) noexcept;

  // Destructor
  inline ~GaussianEngine() noexcept;

  // Gets information
  inline index_t ompSize() const noexcept;

  // Operators
  inline void operator()( VectorType &vector ) noexcept;
  inline void operator()( VectorType &&vector ) noexcept;

  // Sets seed
  inline void setSeed( const index_t seed ) noexcept;

 protected:

  // Computes
  inline void compute( VectorType &vector ) noexcept;

};

}  // namespace random

}  // namespace mcnla

#endif  // MCNLA_CORE_RANDOM_ENGINE_GAUSSIAN_ENGINE_HPP_
