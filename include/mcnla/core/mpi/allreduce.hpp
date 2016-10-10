////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/allreduce.hpp
/// @brief   The MPI ALLREDUCE routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_ALLREDUCE_HPP_
#define MCNLA_CORE_MPI_ALLREDUCE_HPP_

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
/// @brief  Combines values from all processes and distributes the result back to all processes.
///
/// @attention  The size of @a send and @a recv should be the same for all MPI nodes.
/// @attention  @a send and @a recv should be shrunk.
///
template <class _Derived>
inline void allreduce(
    const DenseBase<_Derived> &send,
          DenseBase<_Derived> &recv,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  constexpr const MPI_Datatype &data_type = traits::MpiScalarTraits<typename traits::Traits<_Derived>::ScalarType>::data_type;
  assert(send.derived().isShrunk());
  assert(recv.derived().isShrunk());
  assert(send.derived().getSizes() == recv.derived().getSizes());
  mpi_int_t size = send.derived().getNelem();
  MPI_Allreduce(send.getValue(), recv.getValue(), size, data_type, op, comm);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_module
/// @brief  Combines values from all processes and distributes the result back to all processes (in-place version).
///
/// @attention  The size of @a buffer should be the same for all MPI nodes.
/// @attention  @a buffer should be shrunk.
///
template <class _Derived>
inline void allreduce(
          DenseBase<_Derived> &buffer,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  constexpr const MPI_Datatype &data_type = traits::MpiScalarTraits<typename traits::Traits<_Derived>::ScalarType>::data_type;
  assert(buffer.derived().isShrunk());
  mpi_int_t size = buffer.derived().getNelem();
  MPI_Allreduce(MPI_IN_PLACE, buffer.derived().getValue(), size, data_type, op, comm);
}

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_ALLREDUCE_HPP_
