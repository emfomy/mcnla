////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/dense/allreduce.hpp
/// @brief   The MPI ALLREDUCE routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_DENSE_ALLREDUCE_HPP_
#define MCNLA_CORE_MPI_DENSE_ALLREDUCE_HPP_

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
inline void allreduceImpl(
    const DenseStorage<CoreTag, _Val> &send,
          DenseStorage<CoreTag, _Val> &recv,
    const mpi_int_t count,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  constexpr const MPI_Datatype &datatype = traits::MpiValTraits<_Val>::datatype;
  MPI_Allreduce(send.valPtr(), recv.valPtr(), count, datatype, op, comm);
}

template <typename _Val>
inline void allreduceImpl(
          DenseStorage<CoreTag, _Val> &buffer,
    const mpi_int_t count,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  constexpr const MPI_Datatype &datatype = traits::MpiValTraits<_Val>::datatype;
  MPI_Allreduce(MPI_IN_PLACE, buffer.valPtr(), count, datatype, op, comm);
}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_dense_module
/// @brief  Combines values from all processes and distributes the result back to all processes.
///
/// @attention  The dimensions of @a send and @a recv should be the same for all MPI nodes.
/// @attention  @a send and @a recv should be shrunk.
///
//@{
template <typename _Val>
inline void allreduce(
    const DenseVector<_Val> &send,
          DenseVector<_Val> &recv,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  mcnla_assert_eq(send.dims(), recv.dims());
  detail::allreduceImpl(send, recv, send.nelem(), op, comm);
}

template <typename _Val, Trans _trans>
inline void allreduce(
    const DenseMatrix<_Val, _trans> &send,
          DenseMatrix<_Val, _trans> &recv,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  mcnla_assert_eq(send.dims(), recv.dims());
  detail::allreduceImpl(send, recv, send.nelem(), op, comm);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void allreduce(
    const DenseVector<_Val> &send,
          DenseVector<_Val> &&recv,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  allreduce(send, recv, op, comm);
}

template <typename _Val, Trans _trans>
inline void allreduce(
    const DenseMatrix<_Val, _trans> &send,
          DenseMatrix<_Val, _trans> &&recv,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  allreduce(send, recv, op, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_dense_module
/// @brief  Combines values from all processes and distributes the result back to all processes (in-place version).
///
/// @attention  The dimension of @a buffer should be the same for all MPI nodes.
/// @attention  @a buffer should be shrunk.
///
//@{
template <typename _Val>
inline void allreduce(
          DenseVector<_Val> &buffer,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(buffer.isShrunk());
  detail::allreduceImpl(buffer, buffer.nelem(), op, comm);
}

template <typename _Val, Trans _trans>
inline void allreduce(
          DenseMatrix<_Val, _trans> &buffer,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(buffer.isShrunk());
  detail::allreduceImpl(buffer, buffer.nelem(), op, comm);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void allreduce(
          DenseVector<_Val> &&buffer,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  allreduce(buffer, op, comm);
}

template <typename _Val, Trans _trans>
inline void allreduce(
          DenseMatrix<_Val, _trans> &&buffer,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  allreduce(buffer, op, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_DENSE_ALLREDUCE_HPP_
