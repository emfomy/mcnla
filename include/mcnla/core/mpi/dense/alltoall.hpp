////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/dense/alltoall.hpp
/// @brief   The MPI ALLTOALL routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_DENSE_ALLTOALL_HPP_
#define MCNLA_CORE_MPI_DENSE_ALLTOALL_HPP_

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
inline void alltoallImpl(
    const DenseStorage<CpuTag, _Val> &send,
          DenseStorage<CpuTag, _Val> &recv,
    const mpi_int_t count,
    const MPI_Comm comm
) noexcept {
  constexpr const MPI_Datatype &datatype = traits::MpiValTraits<_Val>::datatype;
  MPI_Alltoall(send.valPtr(), count, datatype, recv.valPtr(), count, datatype, comm);
}

template <typename _Val>
inline void alltoallImpl(
          DenseStorage<CpuTag, _Val> &buffer,
    const mpi_int_t count,
    const MPI_Comm comm
) noexcept {
  constexpr const MPI_Datatype &datatype = traits::MpiValTraits<_Val>::datatype;
  MPI_Alltoall(MPI_IN_PLACE, count, datatype, buffer.valPtr(), count, datatype, comm);
}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_dense_module
/// @brief  All processes send data to all.
///
/// @attention  The dimensions of @a send should be the same for all MPI nodes.
/// @attention  The dimensions of @a recv should be the same for all MPI nodes.
/// @attention  @a send and @a recv should be shrunk.
///
//@{
template <typename _Val>
inline void alltoall(
    const DenseVector<_Val> &send,
          DenseVector<_Val> &recv,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  mcnla_assert_eq(send.dims(), recv.dims());
  mcnla_assert_eq(send.dim0() % commSize(comm), 0);
  detail::alltoallImpl(send, recv, send.nelem() / commSize(comm), comm);
}

template <typename _Val, Trans _trans>
inline void alltoall(
    const DenseMatrix<_Val, _trans> &send,
          DenseMatrix<_Val, _trans> &recv,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  mcnla_assert_eq(send.dims(), recv.dims());
  mcnla_assert_eq(send.dim1() % commSize(comm), 0);
  detail::alltoallImpl(send, recv, send.nelem() / commSize(comm), comm);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void alltoall(
    const DenseVector<_Val> &send,
          DenseVector<_Val> &&recv,
    const MPI_Comm comm
) noexcept {
  alltoall(send, recv, comm);
}

template <typename _Val, Trans _trans>
inline void alltoall(
    const DenseMatrix<_Val, _trans> &send,
          DenseMatrix<_Val, _trans> &&recv,
    const MPI_Comm comm
) noexcept {
  alltoall(send, recv, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_dense_module
/// @brief  All processes send data to all (in-place version).
///
/// @attention  The size of @a buffer should be the same for all MPI nodes.
/// @attention  @a buffer should be shrunk.
///
//@{
template <typename _Val>
inline void alltoall(
          DenseVector<_Val> &buffer,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(buffer.isShrunk());
  mcnla_assert_eq(buffer.dim0() % commSize(comm), 0);
  detail::alltoallImpl(buffer, buffer.nelem() / commSize(comm), comm);
}

template <typename _Val, Trans _trans>
inline void alltoall(
          DenseMatrix<_Val, _trans> &buffer,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(buffer.isShrunk());
  mcnla_assert_eq(buffer.dim1() % commSize(comm), 0);
  detail::alltoallImpl(buffer, buffer.nelem() / commSize(comm), comm);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void alltoall(
          DenseVector<_Val> &&buffer,
    const MPI_Comm comm
) noexcept {
  alltoall(buffer, comm);
}

template <typename _Val, Trans _trans>
inline void alltoall(
          DenseMatrix<_Val, _trans> &&buffer,
    const MPI_Comm comm
) noexcept {
  alltoall(buffer, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_DENSE_ALLTOALL_HPP_
