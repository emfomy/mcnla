////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/random/engine/engine.hpp
/// @brief   The random generator engine header.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_RANDOM_ENGINE_ENGINE_HPP_
#define MCNLA_CORE_RANDOM_ENGINE_ENGINE_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/random/def.hpp>
#include <vector>
#include <omp.h>
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
/// @brief  The random generator engine.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
class Engine {

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
  inline Engine( const index_t seed ) noexcept;

  // Destructor
  inline ~Engine() noexcept;

  // Gets information
  inline index_t ompSize() const noexcept;

  // Computes
  inline void uniform( VectorType &vector, const ScalarType a = 0, const ScalarType b = 1 ) noexcept;
  inline void uniform( VectorType &&vector, const ScalarType a = 0, const ScalarType b = 1 ) noexcept;
  inline void gaussian( VectorType &vector, const ScalarType a = 0, const ScalarType b = 1 ) noexcept;
  inline void gaussian( VectorType &&vector, const ScalarType a = 0, const ScalarType b = 1 ) noexcept;

  // Sets seed
  inline void setSeed( const index_t seed ) noexcept;

};

}  // namespace random

}  // namespace mcnla

#endif  // MCNLA_CORE_RANDOM_ENGINE_ENGINE_HPP_
