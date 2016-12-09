////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/reduce.hpp
/// @brief   The MPI REDUCE routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_REDUCE_HPP_
#define MCNLA_CORE_MPI_REDUCE_HPP_

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
/// @brief  Reduces values on all processes within a group.
///
/// @attention  The size of @a send should be the same for all MPI nodes.
/// @attention  @a send and @a recv should be shrunk.
///
template <class _Derived>
inline void reduce(
    const DenseBase<_Derived> &send,
          DenseBase<_Derived> &recv,
    const MPI_Op op,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  constexpr const MPI_Datatype &datatype = traits::MpiScalarTraits<typename traits::Traits<_Derived>::ScalarType>::datatype;
  mcnla_assert_true(send.derived().isShrunk());
  mcnla_assert_true(recv.derived().isShrunk());
  mcnla_assert_eq(send.derived().getSizes(), recv.derived().getSizes());
  mpi_int_t size = send.derived().getNelem();
  MPI_Reduce(send.getValue(), recv.getValue(), size, datatype, op, root, comm);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Derived>
inline void reduce(
    const DenseBase<_Derived> &send,
          DenseBase<_Derived> &&recv,
    const MPI_Op op,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  reduce(send, recv, op, root, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_module
/// @brief  Reduces values on all processes within a group (in-place version).
///
/// @attention  The size of @a buffer should be the same for all MPI nodes.
/// @attention  @a buffer should be shrunk.
///
template <class _Derived>
inline void reduce(
          DenseBase<_Derived> &buffer,
    const MPI_Op op,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  constexpr const MPI_Datatype &datatype = traits::MpiScalarTraits<typename traits::Traits<_Derived>::ScalarType>::datatype;
  mcnla_assert_true(buffer.derived().isShrunk());
  mpi_int_t count = buffer.derived().getNelem();
  if ( isCommRoot(root, comm) ) {
    MPI_Reduce(MPI_IN_PLACE, buffer.getValue(), count, datatype, op, root, comm);
  } else {
    MPI_Reduce(buffer.getValue(), buffer.getValue(), count, datatype, op, root, comm);
  }
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Derived>
inline void reduce(
          DenseBase<_Derived> &&buffer,
    const MPI_Op op,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  reduce(buffer, op, root, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_REDUCE_HPP_
