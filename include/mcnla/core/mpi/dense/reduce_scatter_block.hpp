////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/dense/reduce_scatter_block.hpp
/// @brief   The MPI RECUDE_SCATTER_BLOCK routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_DENSE_RECUDESCATTER_HPP_
#define MCNLA_CORE_MPI_DENSE_RECUDESCATTER_HPP_

#include <mcnla/core/mpi/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <algorithm>
#include <numeric>

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
inline void reduceScatterBlockImpl(
    const DenseStorage<CpuTag, _Val> &send,
          DenseStorage<CpuTag, _Val> &recv,
    const mpi_int_t count,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_mpi_count(count * commSize(comm) * sizeof(_Val));
  constexpr const MPI_Datatype datatype = traits::MpiValTraits<_Val>::datatype;
  MPI_Reduce_scatter_block(send.valPtr(), recv.valPtr(), count, datatype, op, comm);
}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_dense_module
/// @brief  Combines values and scatters the results (same-size version).
///
/// @attention  The size of @a send should be equal to the size of @a recv &times the number of MPI rank.
/// @attention  @a send and @a recv should be shrunk.
///
//@{
template <typename _Val>
inline void reduceScatterBlock(
    const DenseVector<_Val> &send,
          DenseVector<_Val> &recv,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  mcnla_assert_eq(send.nelem(), recv.nelem() * commSize(comm));
  detail::reduceScatterBlockImpl(send, recv, recv.nelem(), op, comm);
}

template <typename _Val, Trans _trans>
inline void reduceScatterBlock(
    const DenseMatrix<_Val, _trans> &send,
          DenseMatrix<_Val, _trans> &recv,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  mcnla_assert_eq(send.nelem(), recv.nelem() * commSize(comm));
  detail::reduceScatterBlockImpl(send, recv, recv.nelem(), op, comm);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void reduceScatterBlock(
    const DenseVector<_Val> &send,
          DenseVector<_Val> &&recv,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  reduceScatterBlock(send, recv, op, comm);
}

template <typename _Val, Trans _trans>
inline void reduceScatterBlock(
    const DenseMatrix<_Val, _trans> &send,
          DenseMatrix<_Val, _trans> &&recv,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  reduceScatterBlock(send, recv, op, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_DENSE_RECUDESCATTER_HPP_
