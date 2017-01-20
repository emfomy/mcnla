////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/def.hpp
/// @brief   The MPI definitions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_DEF_HPP_
#define MCNLA_CORE_MPI_DEF_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/matrix/def.hpp>
#include <mpi.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  mpi_module  MPI Module
/// @ingroup   core_module
/// @brief     The MPI Module
///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

/// The type of MPI integer.
using mpi_int_t = int32_t;

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
  mpi_int_t size; mcnla_assert_eq(MPI_Comm_size(comm, &size), 0); return size;
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
  mpi_int_t rank; mcnla_assert_eq(MPI_Comm_rank(comm, &rank), 0); return rank;
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
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
struct MpiScalarTraits {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The 8-bit character MPI data type traits.
///
template <>
struct MpiScalarTraits<char> {
  static constexpr const MPI_Datatype &datatype = MPI_CHARACTER;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The 8-bit integer MPI data type traits.
///
template <>
struct MpiScalarTraits<int8_t> {
  static constexpr const MPI_Datatype &datatype = MPI_INTEGER1;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The 16-bit integer MPI data type traits.
///
template <>
struct MpiScalarTraits<int16_t> {
  static constexpr const MPI_Datatype &datatype = MPI_INTEGER2;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The 32-bit integer MPI data type traits.
///
template <>
struct MpiScalarTraits<int32_t> {
  static constexpr const MPI_Datatype &datatype = MPI_INTEGER4;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The 64-bit integer MPI data type traits.
///
template <>
struct MpiScalarTraits<int64_t> {
  static constexpr const MPI_Datatype &datatype = MPI_INTEGER8;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The 32-bit floating point MPI data type traits.
///
template <>
struct MpiScalarTraits<float> {
  static constexpr const MPI_Datatype &datatype = MPI_REAL4;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The 64-bit floating point MPI data type traits.
///
template <>
struct MpiScalarTraits<double> {
  static constexpr const MPI_Datatype &datatype = MPI_REAL8;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The complex float MPI data type traits.
///
template <>
struct MpiScalarTraits<std::complex<float>> {
  static constexpr const MPI_Datatype &datatype = MPI_COMPLEX8;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The complex double MPI data type traits.
///
template <>
struct MpiScalarTraits<std::complex<double>> {
  static constexpr const MPI_Datatype &datatype = MPI_COMPLEX16;
};

}  // namespace traits

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_DEF_HPP_
