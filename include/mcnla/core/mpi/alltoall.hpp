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
template <typename _Scalar, Layout _layout>
inline void alltoall(
    const DenseMatrix<_Scalar, _layout> &send,
          DenseMatrix<_Scalar, _layout> &recv,
    const MPI_Comm comm
) noexcept {
  constexpr const MPI_Datatype &datatype = traits::MpiScalarTraits<_Scalar>::datatype;
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  mcnla_assert_eq(send.getSizes(), recv.getSizes());
  mcnla_assert_eq(send.template getSize<1>() % getCommSize(comm), 0);
  mpi_int_t count = send.getNelem() / getCommSize(comm);
  MPI_Alltoall(send.getValuePtr(), count, datatype, recv.getValuePtr(), count, datatype, comm);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Layout _layout>
inline void alltoall(
    const DenseMatrix<_Scalar, _layout> &send,
          DenseMatrix<_Scalar, _layout> &&recv,
    const MPI_Comm comm
) noexcept {
  alltoall(send, recv, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_module
/// @brief  All processes send data to all (in-place version).
///
/// @attention  The size of @a buffer should be the same for all MPI nodes.
/// @attention  @a buffer should be shrunk.
///
template <typename _Scalar, Layout _layout>
inline void alltoall(
          DenseMatrix<_Scalar, _layout> &buffer,
    const MPI_Comm comm
) noexcept {
  constexpr const MPI_Datatype &datatype = traits::MpiScalarTraits<_Scalar>::datatype;
  mcnla_assert_true(buffer.isShrunk());
  mcnla_assert_eq(buffer.template getSize<1>() % getCommSize(comm), 0);
  mpi_int_t count = buffer.getNelem() / getCommSize(comm);
  MPI_Alltoall(MPI_IN_PLACE, count, datatype, buffer.getValuePtr(), count, datatype, comm);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Layout _layout>
inline void alltoall(
          DenseMatrix<_Scalar, _layout> &&buffer,
    const MPI_Comm comm
) noexcept {
  alltoall(buffer, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_ALLTOALL_HPP_
