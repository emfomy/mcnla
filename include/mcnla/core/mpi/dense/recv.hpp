////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/dense/recv.hpp
/// @brief   The MPI RECV routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_DENSE_RECV_HPP_
#define MCNLA_CORE_MPI_DENSE_RECV_HPP_

#include <mcnla/core/mpi/def.hpp>
#include <mcnla/core/matrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MPI namespace.
//
namespace mpi {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace
//
namespace detail {

template <typename _Val>
inline void recvImpl(
          DenseStorage<CpuTag, _Val> &buffer,
    const mpi_int_t count,
    const mpi_int_t source,
    const mpi_int_t tag,
    const MPI_Comm comm,
          MPI_Status &status
) noexcept {
  constexpr const MPI_Datatype &datatype = traits::MpiValTraits<_Val>::datatype;
  MPI_Recv(buffer.valPtr(), count, datatype, source, tag, comm, &status);
}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_dense_module
/// @brief  Blocking receive for a message.
///
/// @attention  @a buffer should be shrunk.
///
//@{
template <typename _Val>
inline MPI_Status recv(
          DenseVector<_Val> &buffer,
    const mpi_int_t source,
    const mpi_int_t tag,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(buffer.isShrunk());
  MPI_Status status;
  detail::recvImpl(buffer, buffer.nelem(), source, tag, comm, status);
  return status;
}

template <typename _Val, Trans _trans>
inline MPI_Status recv(
          DenseMatrix<_Val, _trans> &buffer,
    const mpi_int_t source,
    const mpi_int_t tag,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(buffer.isShrunk());
  MPI_Status status;
  detail::recvImpl(buffer, buffer.nelem(), source, tag, comm, status);
  return status;
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline MPI_Status recv(
          DenseVector<_Val> &&buffer,
    const mpi_int_t source,
    const mpi_int_t tag,
    const MPI_Comm comm
) noexcept {
  MPI_Status status;
  recv(buffer, source, tag, comm, status);
  return status;
}

template <typename _Val, Trans _trans>
inline MPI_Status recv(
          DenseMatrix<_Val, _trans> &&buffer,
    const mpi_int_t source,
    const mpi_int_t tag,
    const MPI_Comm comm
) noexcept {
  MPI_Status status;
  recv(buffer, source, tag, comm, status);
  return status;
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_DENSE_RECV_HPP_
