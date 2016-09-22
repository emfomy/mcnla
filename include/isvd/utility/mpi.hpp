////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/utility/mpi.hpp
/// @brief   The MPI utilities.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_UTILITY_MPI_HPP_
#define ISVD_UTILITY_MPI_HPP_

#include <isvd/isvd.hpp>
#include <isvd/matrix.hpp>
#include <mpi.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The MPI namespace.
///
namespace mpi {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The MPI detail namespace.
///
namespace detail {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The MPI data type traits
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
struct MpiScalarTraits {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The float MPI data type traits
///
/// @tparam  _Scalar  The scalar type.
///
template <>
struct MpiScalarTraits<float> {
  static constexpr const MPI_Datatype &data_type = MPI_FLOAT;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The double MPI data type traits
///
/// @tparam  _Scalar  The scalar type.
///
template <>
struct MpiScalarTraits<double> {
  static constexpr const MPI_Datatype &data_type = MPI_DOUBLE;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The complex float MPI data type traits
///
/// @tparam  _Scalar  The scalar type.
///
template <>
struct MpiScalarTraits<std::complex<float>> {
  static constexpr const MPI_Datatype &data_type = MPI_COMPLEX;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The complex double MPI data type traits
///
/// @tparam  _Scalar  The scalar type.
///
template <>
struct MpiScalarTraits<std::complex<double>> {
  static constexpr const MPI_Datatype &data_type = MPI_DOUBLE_COMPLEX;
};

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns the size of the group associated with a communicator.
///
/// @param  comm  The communicator.
///
/// @return       The number of processes in the group of @a comm.
///
static inline mpi_int_t getCommSize( const MPI_Comm comm ) noexcept {
  mpi_int_t size; assert(MPI_Comm_size(comm, &size) == 0); return size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines the rank of the calling process in the communicator.
///
/// @param  comm  The communicator.
///
/// @return       The rank of the calling process in group of @a comm.
///
static inline mpi_int_t getCommRank( const MPI_Comm comm ) noexcept {
  mpi_int_t rank; assert(MPI_Comm_rank(comm, &rank) == 0); return rank;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if rank is the root rank.
///
/// @param  root  The root rank.
/// @param  comm  The communicator.
///
static inline bool isCommRoot( const mpi_int_t root, const MPI_Comm comm ) noexcept {
  return (getCommRank(comm) == root);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Broadcasts a message from the process with rank root to all other processes of the group.
///
/// @attention  The size of @a buffer should be the same for all MPI nodes.
///
template <typename _Scalar, Layout _layout>
inline void bcast(
          DenseMatrix<_Scalar, _layout> buffer,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  assert(buffer.isShrunk());
  MPI_Bcast(buffer.getValue(), buffer.getNelem(), detail::MpiScalarTraits<_Scalar>::data_type, root, comm);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gathers values from a group of processes.
///
/// @attention  The size of @a send should be the same for all MPI nodes.
///
template <typename _Scalar, Layout _layout>
inline void gather(
    const DenseMatrix<_Scalar, _layout> send,
          DenseMatrix<_Scalar, _layout> recv,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  assert(send.isShrunk());
  assert(recv.isShrunk());
  assert(isCommRoot(root, comm) ? send.getSize0()                     == recv.getSize0() : true);
  assert(isCommRoot(root, comm) ? send.getSize1() * getCommSize(comm) == recv.getSize1() : true);
  mpi_int_t size = send.getNelem();
  MPI_Gather(send.getValue(), size, detail::MpiScalarTraits<_Scalar>::data_type,
             recv.getValue(), size, detail::MpiScalarTraits<_Scalar>::data_type, root, comm);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Combines values from all processes and distributes the result back to all processes.
///
/// @attention  The size of @a send and @a recv should be the same for all MPI nodes.
///
//@{
template <typename _Scalar>
inline void allreduce(
    const DenseVector<_Scalar> send,
          DenseVector<_Scalar> recv,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  assert(send.isShrunk());
  assert(recv.isShrunk());
  assert(send.getSizes() == recv.getSizes());
  mpi_int_t size = send.getNelem();
  MPI_Allreduce(send.getValue(), recv.getValue(), size, detail::MpiScalarTraits<_Scalar>::data_type, op, comm);
}

template <typename _Scalar, Layout _layout>
inline void allreduce(
    const DenseMatrix<_Scalar, _layout> send,
          DenseMatrix<_Scalar, _layout> recv,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  assert(send.isShrunk());
  assert(recv.isShrunk());
  assert(send.getSizes() == recv.getSizes());
  mpi_int_t size = send.getNelem();
  MPI_Allreduce(send.getValue(), recv.getValue(), size, detail::MpiScalarTraits<_Scalar>::data_type, op, comm);
}

template <typename _Scalar, Layout _layout>
inline void allreduce(
    const DenseCube<_Scalar, _layout> send,
          DenseCube<_Scalar, _layout> recv,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  assert(send.isShrunk());
  assert(recv.isShrunk());
  assert(send.getSizes() == recv.getSizes());
  mpi_int_t size = send.getNelem();
  MPI_Allreduce(send.getValue(), recv.getValue(), size, detail::MpiScalarTraits<_Scalar>::data_type, op, comm);
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Combines values from all processes and distributes the result back to all processes. (in-place version)
///
/// @attention  The size of @a buffer should be the same for all MPI nodes.
///
//@{
template <typename _Scalar>
inline void allreduce(
          DenseVector<_Scalar> buffer,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  assert(buffer.isShrunk());
  mpi_int_t size = buffer.getNelem();
  MPI_Allreduce(MPI_IN_PLACE, buffer.getValue(), size, detail::MpiScalarTraits<_Scalar>::data_type, op, comm);
}

template <typename _Scalar, Layout _layout>
inline void allreduce(
          DenseMatrix<_Scalar, _layout> buffer,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  assert(buffer.isShrunk());
  mpi_int_t size = buffer.getNelem();
  MPI_Allreduce(MPI_IN_PLACE, buffer.getValue(), size, detail::MpiScalarTraits<_Scalar>::data_type, op, comm);
}

template <typename _Scalar, Layout _layout>
inline void allreduce(
          DenseCube<_Scalar, _layout> buffer,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  assert(buffer.isShrunk());
  mpi_int_t size = buffer.getNelem();
  MPI_Allreduce(MPI_IN_PLACE, buffer.getValue(), size, detail::MpiScalarTraits<_Scalar>::data_type, op, comm);
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  All processes send data to all.
///
/// @attention  The size of @a send should be the same for all MPI nodes.
/// @attention  The size of @a recv should be the same for all MPI nodes.
///
template <typename _Scalar, Layout _layout>
inline void alltoall(
    const DenseMatrix<_Scalar, _layout> send,
          DenseCube<_Scalar, _layout> recv,
    const MPI_Comm comm
) noexcept {
  assert(send.isShrunk());
  assert(recv.isShrunk());
  assert(send.getSize0()  == recv.getSize0());
  assert(send.getSize1()  == recv.getSize1() * recv.getNpage());
  assert(recv.getNpage() == getCommSize(comm));
  mpi_int_t size = recv.getSize0() * recv.getSize1();
  MPI_Alltoall(send.getValue(), size, detail::MpiScalarTraits<_Scalar>::data_type,
               recv.getValue(), size, detail::MpiScalarTraits<_Scalar>::data_type, comm);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  All processes send data to all. (in-place version)
///
/// @attention  The size of @a buffer should be the same for all MPI nodes.
///
template <typename _Scalar, Layout _layout>
inline void alltoall(
          DenseCube<_Scalar, _layout> buffer,
    const MPI_Comm comm
) noexcept {
  assert(buffer.isShrunk());
  assert(buffer.getNpage() == getCommSize(comm));
  mpi_int_t size = buffer.getSize0() * buffer.getSize1();
  MPI_Alltoall(MPI_IN_PLACE, size, detail::MpiScalarTraits<_Scalar>::data_type,
               buffer.getValue(), size, detail::MpiScalarTraits<_Scalar>::data_type, comm);
}

}  // namespace mpi

}  // namespace isvd

#endif  // ISVD_UTILITY_MPI_HPP_
