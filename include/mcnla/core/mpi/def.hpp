////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/def.hpp
/// @brief   The MPI definitions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_DEF_HPP_
#define MCNLA_CORE_MPI_DEF_HPP_

#include <mcnla/core/def.hpp>
#include <mcnla/core/matrix/def.hpp>
#include <mcnla/core/utility/traits.hpp>
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

using namespace matrix;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_module
/// @brief  Returns the size of the group associated with a communicator.
///
/// @param  comm  The communicator.
///
/// @return       The number of processes in the group of @a comm.
///
static inline mpi_int_t commSize( const MPI_Comm comm ) noexcept {
  mpi_int_t size; mcnla_assert_pass(MPI_Comm_size(comm, &size)); return size;
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
  mpi_int_t rank; mcnla_assert_pass(MPI_Comm_rank(comm, &rank)); return rank;
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The MPI data type traits.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
struct MpiValTraits;

#define MCNLA_MPI_VAL_TRAITS_DEF( _Type, _value ) \
  template <> struct MpiValTraits<_Type> { static constexpr const MPI_Datatype &datatype = _value; };

MCNLA_MPI_VAL_TRAITS_DEF(char,                 MPI_CHARACTER)
MCNLA_MPI_VAL_TRAITS_DEF(int8_t,               MPI_INTEGER1)
MCNLA_MPI_VAL_TRAITS_DEF(int16_t,              MPI_INTEGER2)
MCNLA_MPI_VAL_TRAITS_DEF(int32_t,              MPI_INTEGER4)
MCNLA_MPI_VAL_TRAITS_DEF(int64_t,              MPI_INTEGER8)
MCNLA_MPI_VAL_TRAITS_DEF(float,                MPI_REAL4)
MCNLA_MPI_VAL_TRAITS_DEF(double,               MPI_REAL8)
MCNLA_MPI_VAL_TRAITS_DEF(std::complex<float>,  MPI_COMPLEX8)
MCNLA_MPI_VAL_TRAITS_DEF(std::complex<double>, MPI_COMPLEX16)

#undef MCNLA_MPI_VAL_TRAITS_DEF

}  // namespace traits

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_DEF_HPP_
