////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/dense/scatter.hpp
/// @brief   The MPI SCATTER routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_DENSE_SCATTER_HPP_
#define MCNLA_CORE_MPI_DENSE_SCATTER_HPP_

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
inline void scatterImpl(
    const DenseStorage<_Val, Array> &send,
          DenseStorage<_Val, Array> &recv,
    const mpi_int_t count,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  constexpr const MPI_Datatype &datatype = traits::MpiValTraits<_Val>::datatype;
  MPI_Scatter(send.valPtr(), count, datatype, recv.valPtr(), count, datatype, root, comm);
}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_dense_module
/// @brief  Sends data from one process to all other processes in a communicator.
///
/// @attention  The dimensions of @a recv should be the same for all MPI nodes.
/// @attention  @a send and @a recv should be shrunk.
///
//@{
template <typename _Val>
inline void scatter(
    const DenseVector<_Val> &send,
          DenseVector<_Val> &recv,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  if ( isCommRoot(root, comm) ) {
    mcnla_assert_eq(send.dim0(), recv.dim0() * commSize(comm));
  }
  detail::scatterImpl(send, recv, recv.nelem(), root, comm);
}

template <typename _Val, Trans _trans>
inline void scatter(
    const DenseMatrix<_Val, _trans> &send,
          DenseMatrix<_Val, _trans> &recv,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  if ( isCommRoot(root, comm) ) {
    mcnla_assert_eq(send.dim0(), recv.dim0());
    mcnla_assert_eq(send.dim1(), recv.dim1() * commSize(comm));
  }
  detail::scatterImpl(send, recv, recv.nelem(), root, comm);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void scatter(
    const DenseVector<_Val> &send,
          DenseVector<_Val> &&recv,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  scatter(send, recv, root, comm);
}

template <typename _Val, Trans _trans>
inline void scatter(
    const DenseMatrix<_Val, _trans> &send,
          DenseMatrix<_Val, _trans> &&recv,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  scatter(send, recv, root, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_DENSE_SCATTER_HPP_
