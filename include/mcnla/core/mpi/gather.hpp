////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/gather.hpp
/// @brief   The MPI GATHER routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_GATHER_HPP_
#define MCNLA_CORE_MPI_GATHER_HPP_

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
inline void gatherImpl(
    const DenseStorage<_Scalar> &send,
          DenseStorage<_Scalar> &recv,
    const mpi_int_t root,
    const MPI_Comm comm,
    const index_t count
) noexcept {
  constexpr const MPI_Datatype &datatype = traits::MpiScalarTraits<_Scalar>::datatype;
  MPI_Gather(send.valPtr(), count, datatype, recv.valPtr(), count, datatype, root, comm);
}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_module
/// @brief  Gathers values from a group of processes.
///
/// @attention  The dimensions of @a send should be the same for all MPI nodes.
/// @attention  @a send and @a recv should be shrunk.
///
//@{
template <typename _Scalar>
inline void gather(
    const DenseVector<_Scalar> &send,
          DenseVector<_Scalar> &recv,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  if ( isCommRoot(root, comm) ) {
    mcnla_assert_eq(send.dim0() * commSize(comm), recv.dim0());
  }
  detail::gatherImpl(send, recv, root, comm, send.nelem());
}

template <typename _Scalar, Trans _transs, Trans _transr>
inline void gather(
    const DenseMatrix<_Scalar, _transs> &send,
          DenseMatrix<_Scalar, _transr> &recv,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(send.isShrunk());
  mcnla_assert_true(recv.isShrunk());
  if ( isCommRoot(root, comm) ) {
    mcnla_assert_eq(send.dim0(),                     recv.dim0());
    mcnla_assert_eq(send.dim1() * commSize(comm), recv.dim1());
  }
  detail::gatherImpl(send, recv, root, comm, send.nelem());
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar>
inline void gather(
    const DenseVector<_Scalar> &send,
          DenseVector<_Scalar> &&recv,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  gather(send, recv, root, comm);
}

template <typename _Scalar, Trans _transs, Trans _transr>
inline void gather(
    const DenseMatrix<_Scalar, _transs> &send,
          DenseMatrix<_Scalar, _transr> &&recv,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  gather(send, recv, root, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_GATHER_HPP_
