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
/// @attention  The dimension of @a send should be the same for all MPI nodes.
/// @attention  The dimension of @a recv should be the same for all MPI nodes.
/// @attention  @a send and @a recv should be shrunk.
///
template <typename _Scalar, Trans _transs, Trans _transr>
inline void alltoall(
    const DenseMatrix<_Scalar, _transs> &send,
          DenseMatrix<_Scalar, _transr> &recv,
    const MPI_Comm comm
) noexcept {
  constexpr const MPI_Datatype &datatype = traits::MpiScalarTraits<_Scalar>::datatype;
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  mcnla_assert_eq(send.dims(), recv.dims());
  mcnla_assert_eq(send.dim1() % getCommSize(comm), 0);
  mpi_int_t count = send.nelem() / getCommSize(comm);
  MPI_Alltoall(send.valuePtr(), count, datatype, recv.valuePtr(), count, datatype, comm);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Trans _transs, Trans _transr>
inline void alltoall(
    const DenseMatrix<_Scalar, _transs> &send,
          DenseMatrix<_Scalar, _transr> &&recv,
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
template <typename _Scalar, Trans _trans>
inline void alltoall(
          DenseMatrix<_Scalar, _trans> &buffer,
    const MPI_Comm comm
) noexcept {
  constexpr const MPI_Datatype &datatype = traits::MpiScalarTraits<_Scalar>::datatype;
  mcnla_assert_true(buffer.isShrunk());
  mcnla_assert_eq(buffer.dim1() % getCommSize(comm), 0);
  mpi_int_t count = buffer.nelem() / getCommSize(comm);
  MPI_Alltoall(MPI_IN_PLACE, count, datatype, buffer.valuePtr(), count, datatype, comm);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Trans _trans>
inline void alltoall(
          DenseMatrix<_Scalar, _trans> &&buffer,
    const MPI_Comm comm
) noexcept {
  alltoall(buffer, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_ALLTOALL_HPP_
