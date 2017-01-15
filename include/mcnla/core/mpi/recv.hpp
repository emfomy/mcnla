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
#include <mcnla/core/container.hpp>

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

template <typename _Scalar>
inline void recvImpl(
          DenseStorage<_Scalar> &buffer,
    const mpi_int_t source,
    const mpi_int_t tag,
    const MPI_Comm comm,
          MPI_Status &status,
    const index_t count
) noexcept {
  constexpr const MPI_Datatype &datatype = traits::MpiScalarTraits<_Scalar>::datatype;
  MPI_Recv(buffer.valuePtr(), count, datatype, source, tag, comm, &status);
}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_module
/// @brief  Blocking receive for a message.
///
/// @attention  @a buffer should be shrunk.
///
//@{
template <typename _Scalar>
inline void recv(
          DenseVector<_Scalar> &buffer,
    const mpi_int_t source,
    const mpi_int_t tag,
    const MPI_Comm comm,
          MPI_Status &status
) noexcept {
  mcnla_assert_true(buffer.isShrunk());
  detail::recvImpl(buffer, source, tag, comm, status, buffer.nelem());
}

template <typename _Scalar, Trans _trans>
inline void recv(
          DenseMatrix<_Scalar, _trans> &buffer,
    const mpi_int_t source,
    const mpi_int_t tag,
    const MPI_Comm comm,
          MPI_Status &status
) noexcept {
  mcnla_assert_true(buffer.isShrunk());
  detail::recvImpl(buffer, source, tag, comm, status, buffer.nelem());
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar>
inline void recv(
          DenseVector<_Scalar> &&buffer,
    const mpi_int_t source,
    const mpi_int_t tag,
    const MPI_Comm comm,
          MPI_Status &status
) noexcept {
  recv(buffer, source, tag, comm, status);
}

template <typename _Scalar, Trans _trans>
inline void recv(
          DenseMatrix<_Scalar, _trans> &&buffer,
    const mpi_int_t source,
    const mpi_int_t tag,
    const MPI_Comm comm,
          MPI_Status &status
) noexcept {
  recv(buffer, source, tag, comm, status);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_RECV_HPP_
