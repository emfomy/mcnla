////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/send.hpp
/// @brief   The MPI SEND routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_SEND_HPP_
#define MCNLA_CORE_MPI_SEND_HPP_

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
//  The detail namespace
//
namespace detail {

template <typename _Scalar>
inline void sendImpl(
    const DenseStorage<_Scalar> &buffer,
    const mpi_int_t dest,
    const mpi_int_t tag,
    const MPI_Comm comm,
    const index_t count
) noexcept {
  constexpr const MPI_Datatype &datatype = traits::MpiScalarTraits<_Scalar>::datatype;
  MPI_Send(buffer.valuePtr(), count, datatype, dest, tag, comm);
}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_module
/// @brief  Performs a blocking send
///
/// @attention  @a buffer should be shrunk.
///
//@{
template <typename _Scalar>
inline void send(
    const DenseVector<_Scalar> &buffer,
    const mpi_int_t dest,
    const mpi_int_t tag,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(buffer.isShrunk());
  detail::sendImpl(buffer, dest, tag, comm, buffer.nelem());
}

template <typename _Scalar, Trans _trans>
inline void send(
    const DenseMatrix<_Scalar, _trans> &buffer,
    const mpi_int_t dest,
    const mpi_int_t tag,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(buffer.isShrunk());
  detail::sendImpl(buffer, dest, tag, comm, buffer.nelem());
}
//@}

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_SEND_HPP_
