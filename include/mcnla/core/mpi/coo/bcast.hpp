////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/coo/bcast.hpp
/// @brief   The MPI BCAST routine for COO format.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_COO_BCAST_HPP_
#define MCNLA_CORE_MPI_COO_BCAST_HPP_

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
inline void bcastImpl(
          CooStorage<_Scalar> &buffer,
    const mpi_int_t root,
    const MPI_Comm comm,
    const index_t count
) noexcept {
  constexpr const MPI_Datatype &datatype = traits::MpiScalarTraits<_Scalar>::datatype;
  MPI_Bcast(buffer.valPtr(), count, datatype, root, comm);
}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_coo_module
/// @brief  Broadcasts a message from the process with rank root to all other processes of the group.
///
/// @attention  The dimensions of @a buffer should be the same for all MPI nodes.
/// @attention  @a buffer should be shrunk.
///
//@{
template <typename _Scalar>
inline void bcast(
          CooVector<_Scalar> &buffer,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  const index_t count = buffer.nelem();
  MPI_Bcast(buffer.valPtr(),  count, traits::MpiScalarTraits<_Scalar>::datatype, root, comm);
  MPI_Bcast(buffer.idx0Ptr(), count, traits::MpiScalarTraits<index_t>::datatype, root, comm);
}

template <typename _Scalar, Trans _trans>
inline void bcast(
          CooMatrix<_Scalar, _trans> &buffer,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  const index_t count = buffer.nelem();
  MPI_Bcast(buffer.valPtr(),  count, traits::MpiScalarTraits<_Scalar>::datatype, root, comm);
  MPI_Bcast(buffer.idx0Ptr(), count, traits::MpiScalarTraits<index_t>::datatype, root, comm);
  MPI_Bcast(buffer.idx1Ptr(), count, traits::MpiScalarTraits<index_t>::datatype, root, comm);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar>
inline void bcast(
          CooVector<_Scalar> &&buffer,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  bcast(buffer, root, comm);
}

template <typename _Scalar, Trans _trans>
inline void bcast(
          CooMatrix<_Scalar, _trans> &&buffer,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  bcast(buffer, root, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_COO_BCAST_HPP_
