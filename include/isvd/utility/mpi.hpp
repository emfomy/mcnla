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
/// The internal namespace.
///
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The MPI data type
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
struct MpiScalarTraits {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The float MPI data type
///
/// @tparam  _Scalar  The scalar type.
///
template <>
struct MpiScalarTraits<float> {
  constexpr static const MPI_Datatype &data_type = MPI_FLOAT;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The double MPI data type
///
/// @tparam  _Scalar  The scalar type.
///
template <>
struct MpiScalarTraits<double> {
  constexpr static const MPI_Datatype &data_type = MPI_DOUBLE;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The complex float MPI data type
///
/// @tparam  _Scalar  The scalar type.
///
template <>
struct MpiScalarTraits<std::complex<float>> {
  constexpr static const MPI_Datatype &data_type = MPI_COMPLEX;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The complex double MPI data type
///
/// @tparam  _Scalar  The scalar type.
///
template <>
struct MpiScalarTraits<std::complex<double>> {
  constexpr static const MPI_Datatype &data_type = MPI_DOUBLE_COMPLEX;
};

}  // internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns the size of the group associated with a communicator.
///
/// @param  comm  The communicator.
///
/// @return       The number of processes in the group of @p comm.
///
static inline index_t getCommSize( const MPI_Comm comm ) noexcept {
  index_t size; assert(MPI_Comm_size(comm, &size) == 0); return size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines the rank of the calling process in the communicator.
///
/// @param  comm  The communicator.
///
/// @return       The rank of the calling process in group of @p comm.
///
static inline index_t getCommRank( const MPI_Comm comm ) noexcept {
  index_t rank; assert(MPI_Comm_rank(comm, &rank) == 0); return rank;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if rank is the root rank.
///
/// @param  root  The root rank.
/// @param  comm  The communicator.
///
static inline bool isCommRoot( const index_t root, const MPI_Comm comm ) noexcept {
  return (getCommRank(comm) == root);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Broadcasts a message from the process with rank root to all other processes of the group.
///
/// @attention  The size of @p buffer should be the same for all MPI nodes.
///
template <typename _Scalar, Layout _layout>
inline void bcast(
          DenseMatrix<_Scalar, _layout> buffer,
    const index_t root,
    const MPI_Comm comm
) noexcept {
  assert(buffer.isShrunk());
  MPI_Bcast(buffer.getValue(), buffer.getSize(), internal::MpiScalarTraits<_Scalar>::data_type, root, comm);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gathers values from a group of processes.
///
/// @attention  The size of @p send should be the same for all MPI nodes.
///
template <typename _Scalar, Layout _layout>
inline void gather(
    const DenseMatrix<_Scalar, _layout> send,
          DenseMatrix<_Scalar, _layout> recv,
    const index_t root,
    const MPI_Comm comm
) noexcept {
  assert(send.isShrunk());
  assert(recv.isShrunk());
  assert(isCommRoot(root, comm) ? send.getDim1()                     == recv.getDim1() : true);
  assert(isCommRoot(root, comm) ? send.getDim2() * getCommSize(comm) == recv.getDim2() : true);
  index_t size = send.getSize();
  MPI_Gather(send.getValue(), size, internal::MpiScalarTraits<_Scalar>::data_type,
             recv.getValue(), size, internal::MpiScalarTraits<_Scalar>::data_type, root, comm);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Combines values from all processes and distributes the result back to all processes.
///
/// @attention  The size of @p send and @p recv should be the same for all MPI nodes.
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
  index_t size = send.getSize();
  MPI_Allreduce(send.getValue(), recv.getValue(), size, internal::MpiScalarTraits<_Scalar>::data_type, op, comm);
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
  index_t size = send.getSize();
  MPI_Allreduce(send.getValue(), recv.getValue(), size, internal::MpiScalarTraits<_Scalar>::data_type, op, comm);
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
  index_t size = send.getSize();
  MPI_Allreduce(send.getValue(), recv.getValue(), size, internal::MpiScalarTraits<_Scalar>::data_type, op, comm);
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Combines values from all processes and distributes the result back to all processes. (in-place version)
///
/// @attention  The size of @p buffer should be the same for all MPI nodes.
///
//@{
template <typename _Scalar>
inline void allreduce(
          DenseVector<_Scalar> buffer,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  assert(buffer.isShrunk());
  index_t size = buffer.getSize();
  MPI_Allreduce(MPI_IN_PLACE, buffer.getValue(), size, internal::MpiScalarTraits<_Scalar>::data_type, op, comm);
}

template <typename _Scalar, Layout _layout>
inline void allreduce(
          DenseMatrix<_Scalar, _layout> buffer,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  assert(buffer.isShrunk());
  index_t size = buffer.getSize();
  MPI_Allreduce(MPI_IN_PLACE, buffer.getValue(), size, internal::MpiScalarTraits<_Scalar>::data_type, op, comm);
}

template <typename _Scalar, Layout _layout>
inline void allreduce(
          DenseCube<_Scalar, _layout> buffer,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  assert(buffer.isShrunk());
  index_t size = buffer.getSize();
  MPI_Allreduce(MPI_IN_PLACE, buffer.getValue(), size, internal::MpiScalarTraits<_Scalar>::data_type, op, comm);
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  All processes send data to all.
///
/// @attention  The size of @p send should be the same for all MPI nodes.
/// @attention  The size of @p recv should be the same for all MPI nodes.
///
template <typename _Scalar, Layout _layout>
inline void alltoall(
    const DenseMatrix<_Scalar, _layout> send,
          DenseCube<_Scalar, _layout> recv,
    const MPI_Comm comm
) noexcept {
  assert(send.isShrunk());
  assert(recv.isShrunk());
  assert(send.getDim1()  == recv.getDim1());
  assert(send.getDim2()  == recv.getDim2() * recv.getNpage());
  assert(recv.getNpage() == getCommSize(comm));
  index_t size = recv.getDim1() * recv.getDim2();
  MPI_Alltoall(send.getValue(), size, internal::MpiScalarTraits<_Scalar>::data_type,
               recv.getValue(), size, internal::MpiScalarTraits<_Scalar>::data_type, comm);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  All processes send data to all. (in-place version)
///
/// @attention  The size of @p buffer should be the same for all MPI nodes.
///
template <typename _Scalar, Layout _layout>
inline void alltoall(
          DenseCube<_Scalar, _layout> buffer,
    const MPI_Comm comm
) noexcept {
  assert(buffer.isShrunk());
  assert(buffer.getNpage() == getCommSize(comm));
  index_t size = buffer.getDim1() * buffer.getDim2();
  MPI_Alltoall(MPI_IN_PLACE, size, internal::MpiScalarTraits<_Scalar>::data_type,
               buffer.getValue(), size, internal::MpiScalarTraits<_Scalar>::data_type, comm);
}

}  // namespace mpi

}  // namespace isvd

#endif  // ISVD_UTILITY_MPI_HPP_
