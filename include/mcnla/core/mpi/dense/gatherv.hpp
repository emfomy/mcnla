////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/dense/gatherv.hpp
/// @brief   The MPI GATHERV routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_DENSE_GATHERV_HPP_
#define MCNLA_CORE_MPI_DENSE_GATHERV_HPP_

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
inline void gathervImpl(
    const DenseStorage<CpuTag, _Val> &send,
          DenseStorage<CpuTag, _Val> &recv,
    const mpi_int_t sendcount,
    const mpi_int_t *recvcounts,
    const mpi_int_t *displs,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_mpi_count(sendcount);
  constexpr const MPI_Datatype datatype = traits::MpiValTraits<_Val>::datatype;
  MPI_Gatherv(send.valPtr(), sendcount, datatype, recv.valPtr(), recvcounts, displs, datatype, root, comm);
}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_dense_module
/// @brief  Gathers into specified locations from all processes in a group.
///
/// @attention  @a send and @a recv should be shrunk.
///
//@{
template <typename _Val>
inline void gatherv(
    const DenseVector<_Val> &send,
          DenseVector<_Val> &recv,
    const mpi_int_t *recvcounts,
    const mpi_int_t *displs,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  detail::gathervImpl(send, recv, send.nelem(), recvcounts, displs, root, comm);
}

template <typename _Val, Trans _trans>
inline void gatherv(
    const DenseMatrix<_Val, _trans> &send,
          DenseMatrix<_Val, _trans> &recv,
    const mpi_int_t *recvcounts,
    const mpi_int_t *displs,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  detail::gathervImpl(send, recv, send.nelem(), recvcounts, displs, root, comm);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void gatherv(
    const DenseVector<_Val> &send,
          DenseVector<_Val> &&recv,
    const mpi_int_t *recvcounts,
    const mpi_int_t *displs,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  gatherv(send, recv, recvcounts, displs, root, comm);
}

template <typename _Val, Trans _trans>
inline void gatherv(
    const DenseMatrix<_Val, _trans> &send,
          DenseMatrix<_Val, _trans> &&recv,
    const mpi_int_t *recvcounts,
    const mpi_int_t *displs,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  gatherv(send, recv, recvcounts, displs, root, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_DENSE_GATHERV_HPP_
