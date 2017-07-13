////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/dense/reduce.hpp
/// @brief   The MPI REDUCE routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_DENSE_REDUCE_HPP_
#define MCNLA_CORE_MPI_DENSE_REDUCE_HPP_

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
inline void reduceImpl(
    const DenseStorage<CpuTag, _Val> &send,
          DenseStorage<CpuTag, _Val> &recv,
    const mpi_int_t count,
    const MPI_Op op,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_mpi_count(count);
  constexpr const MPI_Datatype datatype = traits::MpiValTraits<_Val>::datatype;
  MPI_Reduce(send.valPtr(), recv.valPtr(), count, datatype, op, root, comm);
}

template <typename _Val>
inline void reduceImpl(
          DenseStorage<CpuTag, _Val> &buffer,
    const mpi_int_t count,
    const MPI_Op op,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_mpi_count(count);
  constexpr const MPI_Datatype datatype = traits::MpiValTraits<_Val>::datatype;
  if ( isCommRoot(root, comm) ) {
    MPI_Reduce(MPI_IN_PLACE, buffer.valPtr(), count, datatype, op, root, comm);
  } else {
    MPI_Reduce(buffer.valPtr(), buffer.valPtr(), count, datatype, op, root, comm);
  }
}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_dense_module
/// @brief  Reduces values on all processes within a group.
///
/// @attention  The dimensions of @a send should be the same for all MPI nodes.
/// @attention  @a send and @a recv should be shrunk.
///
//@{
template <typename _Val>
inline void reduce(
    const DenseVector<_Val> &send,
          DenseVector<_Val> &recv,
    const MPI_Op op,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  mcnla_assert_eq(send.dims(), recv.dims());
  detail::reduceImpl(send, recv, send.nelem(), op, root, comm);
}

template <typename _Val, Trans _trans>
inline void reduce(
    const DenseMatrix<_Val, _trans> &send,
          DenseMatrix<_Val, _trans> &recv,
    const MPI_Op op,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  mcnla_assert_eq(send.dims(), recv.dims());
  detail::reduceImpl(send, recv, send.nelem(), op, root, comm);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void reduce(
    const DenseVector<_Val> &send,
          DenseVector<_Val> &&recv,
    const MPI_Op op,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  reduce(send, recv, op, root, comm);
}

template <typename _Val, Trans _trans>
inline void reduce(
    const DenseMatrix<_Val, _trans> &send,
          DenseMatrix<_Val, _trans> &&recv,
    const MPI_Op op,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  reduce(send, recv, op, root, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_dense_module
/// @brief  Reduces values on all processes within a group (in-place version).
///
/// @attention  The dimensions of @a buffer should be the same for all MPI nodes.
/// @attention  @a buffer should be shrunk.
///
//@{
template <typename _Val>
inline void reduce(
          DenseVector<_Val> &buffer,
    const MPI_Op op,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(buffer.isShrunk());
  detail::reduceImpl(buffer, buffer.nelem(), op, root, comm);
}

template <typename _Val, Trans _trans>
inline void reduce(
          DenseMatrix<_Val, _trans> &buffer,
    const MPI_Op op,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(buffer.isShrunk());
  detail::reduceImpl(buffer, buffer.nelem(), op, root, comm);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void reduce(
          DenseVector<_Val> &&buffer,
    const MPI_Op op,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  reduce(buffer, op, root, comm);
}

template <typename _Val, Trans _trans>
inline void reduce(
          DenseMatrix<_Val, _trans> &&buffer,
    const MPI_Op op,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  reduce(buffer, op, root, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_DENSE_REDUCE_HPP_
