////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/random/driver/driver.hh
/// @brief   The definition of random generator driver header.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_RANDOM_DRIVER_DRIVER_HH_
#define MCNLA_CORE_RANDOM_DRIVER_DRIVER_HH_

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
/// @brief  The random generator driver.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class Driver {

 private:

  using ValType    = _Val;
  using VectorType = DenseVector<ValType>;

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
  inline Driver( const index_t seed ) noexcept;

  // Destructor
  inline ~Driver() noexcept;

  // Gets information
  inline index_t ompSize() const noexcept;

  // Computes
  inline void uniform( VectorType &vector, const ValType a = 0, const ValType b = 1 ) noexcept;
  inline void uniform( VectorType &&vector, const ValType a = 0, const ValType b = 1 ) noexcept;
  inline void gaussian( VectorType &vector, const ValType a = 0, const ValType b = 1 ) noexcept;
  inline void gaussian( VectorType &&vector, const ValType a = 0, const ValType b = 1 ) noexcept;

  // Sets seed
  inline void setSeed( const index_t seed ) noexcept;

};

}  // namespace random

}  // namespace mcnla

#endif  // MCNLA_CORE_RANDOM_DRIVER_DRIVER_HH_
