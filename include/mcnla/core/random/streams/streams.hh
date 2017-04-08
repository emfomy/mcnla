////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/random/streams/streams.hh
/// @brief   The definition of random streams.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_RANDOM_STREAMS_STREAMS_HH_
#define MCNLA_CORE_RANDOM_STREAMS_STREAMS_HH_

#include <mcnla/core/random/def.hpp>
#include <vector>
#include <mcnla/core/mpi.hpp>

#ifdef MCNLA_USE_OMP
  #include <omp.h>
#endif  // MCNLA_USE_OMP

#ifdef MCNLA_USE_MKL
  #include <mkl.h>
#else
  #include <random>
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
/// @brief  The random streams.
///
class Streams {

 public:

#ifdef MCNLA_USE_MKL
  using StreamType = VSLStreamStatePtr;
#else  // MCNLA_USE_MKL
  using StreamType = std::mt19937;
#endif  // MCNLA_USE_MKL

 protected:

  /// The number of threads
  const index_t omp_size_;

  /// The random streams
  std::vector<StreamType> streams_;

 public:

  // Constructors
  inline Streams( const index_t seed ) noexcept;
  inline Streams( const Streams &other ) noexcept = delete;

  // Operators
  Streams& operator=( const Streams &other ) const noexcept = delete;

  // Destructor
  inline ~Streams() noexcept;

  // Gets information
  inline index_t ompSize() const noexcept;
  inline StreamType& operator[]( const index_t i ) const noexcept;

  // Sets seed
  inline void setSeed( const index_t seed ) noexcept;
  inline void setSeeds( const index_t seed, const mpi_int_t mpi_root, const MPI_Comm mpi_comm ) noexcept;

};

}  // namespace random

}  // namespace mcnla

#endif  // MCNLA_CORE_RANDOM_STREAMS_STREAMS_HH_
