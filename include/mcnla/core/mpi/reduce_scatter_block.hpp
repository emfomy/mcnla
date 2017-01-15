////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/reduce_scatter_block.hpp
/// @brief   The MPI RECUDE_SCATTER_BLOCK routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_RECUDESCATTER_HPP_
#define MCNLA_CORE_MPI_RECUDESCATTER_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/mpi/def.hpp>
#include <mcnla/core/container.hpp>
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

template <typename _Scalar>
inline void reduceScatterBlockImpl(
    const DenseStorage<_Scalar> &send,
          DenseStorage<_Scalar> &recv,
    const MPI_Op op,
    const MPI_Comm comm,
    const index_t count
) noexcept {
  constexpr const MPI_Datatype &datatype = traits::MpiScalarTraits<_Scalar>::datatype;
  MPI_Reduce_scatter_block(send.valuePtr(), recv.valuePtr(), count, datatype, op, comm);
}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_module
/// @brief  Combines values and scatters the results (same-size version).
///
/// @attention  The size of @a send should be equal to the size of @a recv &times the number of MPI rank.
/// @attention  @a send and @a recv should be shrunk.
///
//@{
template <typename _Scalar>
inline void reduceScatterBlock(
    const DenseVector<_Scalar> &send,
          DenseVector<_Scalar> &recv,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  mcnla_assert_eq(send.nelem(), recv.nelem() * commSize(comm));
  detail::reduceScatterBlockImpl(send, recv, op, comm, recv.nelem());
}

template <typename _Scalar, Trans _transs, Trans _transr>
inline void reduceScatterBlock(
    const DenseMatrix<_Scalar, _transs> &send,
          DenseMatrix<_Scalar, _transr> &recv,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  mcnla_assert_eq(send.nelem(), recv.nelem() * commSize(comm));
  detail::reduceScatterBlockImpl(send, recv, op, comm, recv.nelem());
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar>
inline void reduceScatterBlock(
    const DenseVector<_Scalar> &send,
          DenseVector<_Scalar> &&recv,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  reduceScatterBlock(send, recv, op, comm);
}

template <typename _Scalar, Trans _transs, Trans _transr>
inline void reduceScatterBlock(
    const DenseMatrix<_Scalar, _transs> &send,
          DenseMatrix<_Scalar, _transr> &&recv,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  reduceScatterBlock(send, recv, op, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_RECUDESCATTER_HPP_
