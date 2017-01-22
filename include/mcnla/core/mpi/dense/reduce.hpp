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

template <typename _Scalar>
inline void reduceImpl(
    const DenseStorage<_Scalar> &send,
          DenseStorage<_Scalar> &recv,
    const MPI_Op op,
    const mpi_int_t root,
    const MPI_Comm comm,
    const index_t count
) noexcept {
  constexpr const MPI_Datatype &datatype = traits::MpiScalarTraits<_Scalar>::datatype;
  MPI_Reduce(send.valPtr(), recv.valPtr(), count, datatype, op, root, comm);
}

template <typename _Scalar>
inline void reduceImpl(
          DenseStorage<_Scalar> &buffer,
    const MPI_Op op,
    const mpi_int_t root,
    const MPI_Comm comm,
    const index_t count
) noexcept {
  constexpr const MPI_Datatype &datatype = traits::MpiScalarTraits<_Scalar>::datatype;
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
template <typename _Scalar>
inline void reduce(
    const DenseVector<_Scalar> &send,
          DenseVector<_Scalar> &recv,
    const MPI_Op op,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  mcnla_assert_eq(send.dims(), recv.dims());
  detail::reduceImpl(send, recv, op, root, comm, send.nelem());
}

template <typename _Scalar, Trans _transs, Trans _transr>
inline void reduce(
    const DenseMatrix<_Scalar, _transs> &send,
          DenseMatrix<_Scalar, _transr> &recv,
    const MPI_Op op,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  mcnla_assert_eq(send.dims(), recv.dims());
  detail::reduceImpl(send, recv, op, root, comm, send.nelem());
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar>
inline void reduce(
    const DenseVector<_Scalar> &send,
          DenseVector<_Scalar> &&recv,
    const MPI_Op op,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  reduce(send, recv, op, root, comm);
}

template <typename _Scalar, Trans _transs, Trans _transr>
inline void reduce(
    const DenseMatrix<_Scalar, _transs> &send,
          DenseMatrix<_Scalar, _transr> &&recv,
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
template <typename _Scalar>
inline void reduce(
          DenseVector<_Scalar> &buffer,
    const MPI_Op op,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(buffer.isShrunk());
  detail::reduceImpl(buffer, op, root, comm, buffer.nelem());
}

template <typename _Scalar, Trans _trans>
inline void reduce(
          DenseMatrix<_Scalar, _trans> &buffer,
    const MPI_Op op,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(buffer.isShrunk());
  detail::reduceImpl(buffer, op, root, comm, buffer.nelem());
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar>
inline void reduce(
          DenseVector<_Scalar> &&buffer,
    const MPI_Op op,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  reduce(buffer, op, root, comm);
}

template <typename _Scalar, Trans _trans>
inline void reduce(
          DenseMatrix<_Scalar, _trans> &&buffer,
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
