////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/alltoall.hpp
/// @brief   The MPI ALLTOALL routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_ALLTOALL_HPP_
#define MCNLA_CORE_MPI_ALLTOALL_HPP_

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
/// @brief  All processes send data to all.
///
/// @attention  The size of @a send should be the same for all MPI nodes.
/// @attention  The size of @a recv should be the same for all MPI nodes.
/// @attention  @a send and @a recv should be shrunk.
///
//@{
template <typename _Scalar, Layout _layout>
inline void alltoall(
    const DenseMatrix<_Scalar, _layout> &send,
          DenseCube<_Scalar, _layout>   &recv,
    const MPI_Comm comm
) noexcept {
  constexpr const MPI_Datatype &data_type = traits::MpiScalarTraits<_Scalar>::data_type;
  assert(send.isShrunk());
  assert(recv.isShrunk());
  assert(send.template getSize<0>() == recv.template getSize<0>());
  assert(send.template getSize<1>() == recv.template getSize<1>() * recv.getNpage());
  assert(recv.getNpage()            == getCommSize(comm));
  mpi_int_t size = recv.template getSize<0>() * recv.template getSize<1>();
  MPI_Alltoall(send.getValue(), size, data_type, recv.getValue(), size, data_type, comm);
}

template <typename _Scalar, Layout _layout>
inline void alltoall(
    const DenseMatrix<_Scalar, _layout> &send,
          DenseCube<_Scalar, _layout>   &&recv,
    const MPI_Comm comm
) noexcept {
  alltoall(send, recv, comm);
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_module
/// @brief  All processes send data to all (in-place version).
///
/// @attention  The size of @a buffer should be the same for all MPI nodes.
/// @attention  @a buffer should be shrunk.
///
//@{
template <typename _Scalar, Layout _layout>
inline void alltoall(
          DenseCube<_Scalar, _layout> &buffer,
    const MPI_Comm comm
) noexcept {
  constexpr const MPI_Datatype &data_type = traits::MpiScalarTraits<_Scalar>::data_type;
  assert(buffer.isShrunk());
  assert(buffer.getNpage() == getCommSize(comm));
  mpi_int_t size = buffer.template getSize<0>() * buffer.template getSize<1>();
  MPI_Alltoall(MPI_IN_PLACE, size, data_type, buffer.getValue(), size, data_type, comm);
}

template <typename _Scalar, Layout _layout>
inline void alltoall(
          DenseCube<_Scalar, _layout> &&buffer,
    const MPI_Comm comm
) noexcept {
  alltoall(buffer, comm);
}
//@}

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_ALLTOALL_HPP_
