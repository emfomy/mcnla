////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/dense/send.hpp
/// @brief   The MPI SEND routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_DENSE_SEND_HPP_
#define MCNLA_CORE_MPI_DENSE_SEND_HPP_

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
inline void sendImpl(
    const DenseStorage<CpuTag, _Val> &buffer,
    const mpi_int_t count,
    const mpi_int_t dest,
    const mpi_int_t tag,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_mpi_count(count * sizeof(_Val));
  constexpr const MPI_Datatype datatype = traits::MpiValTraits<_Val>::datatype;
  MPI_Send(buffer.valPtr(), count, datatype, dest, tag, comm);
}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_dense_module
/// @brief  Performs a blocking send
///
/// @attention  @a buffer should be shrunk.
///
//@{
template <typename _Val>
inline void send(
    const DenseVector<_Val> &buffer,
    const mpi_int_t dest,
    const mpi_int_t tag,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(buffer.isShrunk());
  detail::sendImpl(buffer, buffer.nelem(), dest, tag, comm);
}

template <typename _Val, Trans _trans>
inline void send(
    const DenseMatrix<_Val, _trans> &buffer,
    const mpi_int_t dest,
    const mpi_int_t tag,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(buffer.isShrunk());
  detail::sendImpl(buffer, buffer.nelem(), dest, tag, comm);
}
//@}

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_DENSE_SEND_HPP_
