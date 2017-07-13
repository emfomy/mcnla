////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/dense/gather.hpp
/// @brief   The MPI GATHER routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_DENSE_GATHER_HPP_
#define MCNLA_CORE_MPI_DENSE_GATHER_HPP_

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
inline void gatherImpl(
    const DenseStorage<CpuTag, _Val> &send,
          DenseStorage<CpuTag, _Val> &recv,
    const mpi_int_t count,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_mpi_count(count * commSize(comm));
  constexpr const MPI_Datatype datatype = traits::MpiValTraits<_Val>::datatype;
  MPI_Gather(send.valPtr(), count, datatype, recv.valPtr(), count, datatype, root, comm);
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
inline void gather(
    const DenseVector<_Val> &send,
          DenseVector<_Val> &recv,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  if ( isCommRoot(root, comm) ) {
    mcnla_assert_eq(send.dim0() * commSize(comm), recv.dim0());
  }
  detail::gatherImpl(send, recv, send.nelem(), root, comm);
}

template <typename _Val, Trans _trans>
inline void gather(
    const DenseMatrix<_Val, _trans> &send,
          DenseMatrix<_Val, _trans> &recv,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  if ( isCommRoot(root, comm) ) {
    mcnla_assert_eq(send.dim0(),                  recv.dim0());
    mcnla_assert_eq(send.dim1() * commSize(comm), recv.dim1());
  }
  detail::gatherImpl(send, recv, send.nelem(), root, comm);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void gather(
    const DenseVector<_Val> &send,
          DenseVector<_Val> &&recv,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  gather(send, recv, root, comm);
}

template <typename _Val, Trans _trans>
inline void gather(
    const DenseMatrix<_Val, _trans> &send,
          DenseMatrix<_Val, _trans> &&recv,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  gather(send, recv, root, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_DENSE_GATHER_HPP_
