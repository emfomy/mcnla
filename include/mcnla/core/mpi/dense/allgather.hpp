////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/dense/all_gather.hpp
/// @brief   The MPI ALLGATHER routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_DENSE_ALLGATHER_HPP_
#define MCNLA_CORE_MPI_DENSE_ALLGATHER_HPP_

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
inline void allgatherImpl(
    const DenseStorage<CpuTag, _Val> &send,
          DenseStorage<CpuTag, _Val> &recv,
    const mpi_int_t count,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_mpi_count(count * commSize(comm) * sizeof(_Val));
  constexpr const MPI_Datatype datatype = traits::MpiValTraits<_Val>::datatype;
  MPI_Allgather(send.valPtr(), count, datatype, recv.valPtr(), count, datatype, comm);
}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_dense_module
/// @brief  Gathers values from a group of processes.
///
/// @attention  The dimensions of @a send should be the same for all MPI nodes.
/// @attention  @a send and @a recv should be shrunk.
///
//@{
template <typename _Val>
inline void allgather(
    const DenseVector<_Val> &send,
          DenseVector<_Val> &recv,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  mcnla_assert_eq(send.dim0() * commSize(comm), recv.dim0());
  detail::allgatherImpl(send, recv, send.nelem(), comm);
}

template <typename _Val, Trans _trans>
inline void allgather(
    const DenseMatrix<_Val, _trans> &send,
          DenseMatrix<_Val, _trans> &recv,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  mcnla_assert_eq(send.dim0(),                  recv.dim0());
  mcnla_assert_eq(send.dim1() * commSize(comm), recv.dim1());
  detail::allgatherImpl(send, recv, send.nelem(), comm);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void allgather(
    const DenseVector<_Val> &send,
          DenseVector<_Val> &&recv,
    const MPI_Comm comm
) noexcept {
  allgather(send, recv, comm);
}

template <typename _Val, Trans _trans>
inline void allgather(
    const DenseMatrix<_Val, _trans> &send,
          DenseMatrix<_Val, _trans> &&recv,
    const MPI_Comm comm
) noexcept {
  allgather(send, recv, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_DENSE_ALLGATHER_HPP_
