////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/recv.hpp
/// @brief   The MPI RECV routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_RECV_HPP_
#define MCNLA_CORE_MPI_RECV_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/mpi/def.hpp>
#include <mcnla/core/matrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The MPI namespace.
///
namespace mpi {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_module
/// @brief  Blocking receive for a message.
///
/// @attention  @a buffer should be shrunk.
///
template <class _Derived>
inline void recv(
          DenseBase<_Derived> &buffer,
    const mpi_int_t source,
    const mpi_int_t tag,
    const MPI_Comm comm,
          MPI_Status &status
) noexcept {
  constexpr const MPI_Datatype &data_type = traits::MpiScalarTraits<typename traits::Traits<_Derived>::ScalarType>::data_type;
  mcnla_assert_true(buffer.derived().isShrunk());
  MPI_Recv(buffer.getValue(), buffer.derived().getNelem(), data_type, source, tag, comm, &status);
}

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_RECV_HPP_