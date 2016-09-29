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
  constexpr const MPI_Datatype &data_type = traits::MpiScalarTraits<_Scalar>::data_type;
  assert(send.isShrunk());
  assert(recv.isShrunk());
  assert(isCommRoot(root, comm) ? send.template getSize<0>()                     == recv.template getSize<0>() : true);
  assert(isCommRoot(root, comm) ? send.template getSize<1>() * getCommSize(comm) == recv.template getSize<1>() : true);
  mpi_int_t size = send.getNelem();
  MPI_Gather(send.getValue(), size, data_type, recv.getValue(), size, data_type, root, comm);
}

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_GATHER_HPP_
