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
  constexpr const MPI_Datatype &datatype = traits::MpiScalarTraits<typename traits::Traits<_Derived>::ScalarType>::datatype;
  mcnla_assert_true(send.derived().isShrunk());
  mcnla_assert_true(recv.derived().isShrunk());
  mcnla_assert_eq(send.derived().sizes(), recv.derived().sizes());
  mpi_int_t count = recv.derived().nelem();
  MPI_Allreduce(send.valuePtr(), recv.valuePtr(), count, datatype, op, comm);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Derived>
inline void allreduce(
    const DenseBase<_Derived> &send,
          DenseBase<_Derived> &&recv,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  allreduce(send, recv, op, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

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
  constexpr const MPI_Datatype &datatype = traits::MpiScalarTraits<typename traits::Traits<_Derived>::ScalarType>::datatype;
  mcnla_assert_true(buffer.derived().isShrunk());
  mpi_int_t count = buffer.derived().nelem();
  MPI_Allreduce(MPI_IN_PLACE, buffer.valuePtr(), count, datatype, op, comm);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Derived>
inline void allreduce(
          DenseBase<_Derived> &&buffer,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  allreduce(buffer, op, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_ALLREDUCE_HPP_
