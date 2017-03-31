////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/random/streams/mpi_streams.hh
/// @brief   The definition of MPI random streams.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_RANDOM_STREAMS_MPI_STREAMS_HH_
#define MCNLA_CORE_RANDOM_STREAMS_MPI_STREAMS_HH_

#include <mcnla/core/random/def.hpp>
#include <mcnla/core/random/streams/streams.hpp>
#include <mcnla/core/mpi.hpp>

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
/// @brief  The MPI random streams.
///
class MpiStreams {

 protected:

  /// The MPI communicator
  const MPI_Comm mpi_comm_;

  /// The MPI root
  const index_t mpi_root_;

  /// The random streams.
  Streams streams_;

 public:

  // Constructors
  inline MpiStreams( const MPI_Comm mpi_comm, const mpi_int_t mpi_root, const index_t seed ) noexcept;

  // Type conversion
  inline operator Streams&() noexcept;
  inline operator const Streams&() const noexcept;

  // Gets information
  inline Streams& streams() noexcept;
  inline const Streams& streams() const noexcept;
  inline Streams::StreamType operator[]( const index_t i ) const noexcept;

  // Sets seed
  inline void setSeed( const index_t seed ) noexcept;

 protected:

  // Boardcast seeds
  inline index_t bcastSeed( const index_t seed ) const noexcept;

};

}  // namespace random

}  // namespace mcnla

#endif  // MCNLA_CORE_RANDOM_STREAMS_MPI_STREAMS_HH_
