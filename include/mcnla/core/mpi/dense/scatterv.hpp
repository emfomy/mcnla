////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/dense/scatterv.hpp
/// @brief   The MPI SCATTERV routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_DENSE_SCATTERV_HPP_
#define MCNLA_CORE_MPI_DENSE_SCATTERV_HPP_

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
inline void scattervImpl(
    const DenseStorage<CpuTag, _Val> &send,
          DenseStorage<CpuTag, _Val> &recv,
    const mpi_int_t *sendcounts,
    const mpi_int_t *displs,
    const mpi_int_t recvcount,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  constexpr const MPI_Datatype &datatype = traits::MpiValTraits<_Val>::datatype;
  MPI_Scatterv(send.valPtr(), sendcounts, displs, datatype, recv.valPtr(), recvcount, datatype, root, comm);
}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_dense_module
/// @brief  Scatters a buffer in parts to all processes in a communicator.
///
/// @attention  @a send and @a recv should be shrunk.
///
//@{
template <typename _Val>
inline void scatterv(
    const DenseVector<_Val> &send,
          DenseVector<_Val> &recv,
    const mpi_int_t *sendcounts,
    const mpi_int_t *displs,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  detail::scattervImpl(send, recv, sendcounts, displs, recv.nelem(), root, comm);
}

template <typename _Val, Trans _trans>
inline void scatterv(
    const DenseMatrix<_Val, _trans> &send,
          DenseMatrix<_Val, _trans> &recv,
    const mpi_int_t *sendcounts,
    const mpi_int_t *displs,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  detail::scattervImpl(send, recv, sendcounts, displs, recv.nelem(), root, comm);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void scatterv(
    const DenseVector<_Val> &send,
          DenseVector<_Val> &&recv,
    const mpi_int_t *sendcounts,
    const mpi_int_t *displs,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  scatterv(send, recv, sendcounts, displs, root, comm);
}

template <typename _Val, Trans _trans>
inline void scatterv(
    const DenseMatrix<_Val, _trans> &send,
          DenseMatrix<_Val, _trans> &&recv,
    const mpi_int_t *sendcounts,
    const mpi_int_t *displs,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  scatterv(send, recv, sendcounts, displs, root, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_DENSE_SCATTERV_HPP_
