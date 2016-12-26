////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/allreduce.hpp
/// @brief   The MPI ALLREDUCE routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_ALLREDUCE_HPP_
#define MCNLA_CORE_MPI_ALLREDUCE_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/mpi/def.hpp>
#include <mcnla/core/matrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The MPI namespace.
///
namespace mpi {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace
//
namespace detail {

template <typename _Scalar>
inline void allreduceImpl(
    const DenseStorage<_Scalar> &send,
          DenseStorage<_Scalar> &recv,
    const MPI_Op op,
    const MPI_Comm comm,
    const index_t count
) noexcept {
  constexpr const MPI_Datatype &datatype = traits::MpiScalarTraits<_Scalar>::datatype;
  MPI_Allreduce(send.valuePtr(), recv.valuePtr(), count, datatype, op, comm);
}

template <typename _Scalar>
inline void allreduceImpl(
          DenseStorage<_Scalar> &buffer,
    const MPI_Op op,
    const MPI_Comm comm,
    const index_t count
) noexcept {
  constexpr const MPI_Datatype &datatype = traits::MpiScalarTraits<_Scalar>::datatype;
  MPI_Allreduce(MPI_IN_PLACE, buffer.valuePtr(), count, datatype, op, comm);
}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_module
/// @brief  Combines values from all processes and distributes the result back to all processes.
///
/// @attention  The size of @a send and @a recv should be the same for all MPI nodes.
/// @attention  @a send and @a recv should be shrunk.
///
//@{
template <typename _Scalar>
inline void allreduce(
    const DenseVector<_Scalar> &send,
          DenseVector<_Scalar> &recv,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  mcnla_assert_eq(send.dims(), recv.dims());
  detail::allreduceImpl(send, recv, op, comm, recv.nelem());
}

template <typename _Scalar, Trans _transa, Trans _transb>
inline void allreduce(
    const DenseMatrix<_Scalar, _transa> &send,
          DenseMatrix<_Scalar, _transb> &recv,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  mcnla_assert_eq(send.dims(), recv.dims());
  detail::allreduceImpl(send, recv, op, comm, recv.nelem());
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar>
inline void allreduce(
    const DenseVector<_Scalar> &send,
          DenseVector<_Scalar> &&recv,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  allreduce(send, recv, op, comm);
}

template <typename _Scalar, Trans _transa, Trans _transb>
inline void allreduce(
    const DenseMatrix<_Scalar, _transa> &send,
          DenseMatrix<_Scalar, _transb> &&recv,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  allreduce(send, recv, op, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_module
/// @brief  Combines values from all processes and distributes the result back to all processes (in-place version).
///
/// @attention  The size of @a buffer should be the same for all MPI nodes.
/// @attention  @a buffer should be shrunk.
///
//@{
template <typename _Scalar>
inline void allreduce(
          DenseVector<_Scalar> &buffer,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(buffer.isShrunk());
  detail::allreduceImpl(buffer, op, comm, buffer.nelem());
}

template <typename _Scalar, Trans _trans>
inline void allreduce(
          DenseMatrix<_Scalar, _trans> &buffer,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(buffer.isShrunk());
  detail::allreduceImpl(buffer, op, comm, buffer.nelem());
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar>
inline void allreduce(
          DenseVector<_Scalar> &&buffer,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  allreduce(buffer, op, comm);
}

template <typename _Scalar, Trans _trans>
inline void allreduce(
          DenseMatrix<_Scalar, _trans> &&buffer,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  allreduce(buffer, op, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_ALLREDUCE_HPP_
