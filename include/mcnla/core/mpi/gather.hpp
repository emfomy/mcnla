////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/gather.hpp
/// @brief   The MPI GATHER routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_GATHER_HPP_
#define MCNLA_CORE_MPI_GATHER_HPP_

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
/// @brief  Gathers values from a group of processes.
///
/// @attention  The size of @a send should be the same for all MPI nodes.
/// @attention  @a send and @a recv should be shrunk.
///
template <typename _Scalar, Layout _layout>
inline void gather(
    const DenseMatrix<_Scalar, _layout> &send,
          DenseMatrix<_Scalar, _layout> &recv,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  constexpr const MPI_Datatype &datatype = traits::MpiScalarTraits<_Scalar>::datatype;
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  if ( isCommRoot(root, comm) ) {
    mcnla_assert_eq(send.template getSize<0>(),                     recv.template getSize<0>());
    mcnla_assert_eq(send.template getSize<1>() * getCommSize(comm), recv.template getSize<1>());
  }
  mpi_int_t count = send.getNelem();
  MPI_Gather(send.getValuePtr(), count, datatype, recv.getValuePtr(), count, datatype, root, comm);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Layout _layout>
inline void gather(
    const DenseMatrix<_Scalar, _layout> &send,
          DenseMatrix<_Scalar, _layout> &&recv,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  gather(send, recv, root, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_GATHER_HPP_
