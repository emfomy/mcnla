////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/def.hpp
/// @brief   The MPI definitions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_DEF_HPP_
#define MCNLA_CORE_MPI_DEF_HPP_

#include <mcnla/core/def.hpp>
#include <mpi.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

/// The type of MPI integer.
using mpi_int_t = int;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_module
/// The MPI namespace.
///
namespace mpi {

#pragma warning
// using namespace matrix;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_module
/// @brief  Returns the size of the group associated with a communicator.
///
/// @param  comm  The communicator.
///
/// @return       The number of processes in the group of @a comm.
///
static inline mpi_int_t commSize( const MPI_Comm comm ) noexcept {
  mpi_int_t size;
  mcnla_assert_eq(MPI_Comm_size(comm, &size), 0);
  return size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_module
/// @brief  Determines the rank of the calling process in the communicator.
///
/// @param  comm  The communicator.
///
/// @return       The rank of the calling process in group of @a comm.
///
static inline mpi_int_t commRank( const MPI_Comm comm ) noexcept {
  mpi_int_t rank;
  mcnla_assert_eq(MPI_Comm_rank(comm, &rank), 0);
  return rank;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_module
/// @brief  Determines if rank is the root rank.
///
/// @param  root  The root rank.
/// @param  comm  The communicator.
///
static inline bool isCommRoot( const mpi_int_t root, const MPI_Comm comm ) noexcept {
  return (commRank(comm) == root);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The MPI detail namespace.
///
namespace detail {}

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_DEF_HPP_
