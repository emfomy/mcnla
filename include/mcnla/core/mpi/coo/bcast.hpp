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

template <typename _Val>
inline void bcastImpl(
          CooStorage<_Val> &buffer,
    const mpi_int_t root,
    const MPI_Comm comm,
    const mpi_int_t count
) noexcept {
  constexpr const MPI_Datatype &datatype = traits::MpiValTraits<_Val>::datatype;
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
template <typename _Val>
inline void bcast(
          CooVector<_Val> &buffer,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  const mpi_int_t count = buffer.nelem();
  MPI_Bcast(buffer.valPtr(),  count, traits::MpiValTraits<_Val>::datatype, root, comm);
  MPI_Bcast(buffer.idx0Ptr(), count, traits::MpiValTraits<index_t>::datatype, root, comm);
}

template <typename _Val, Trans _trans>
inline void bcast(
          CooMatrix<_Val, _trans> &buffer,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  const mpi_int_t count = buffer.nelem();
  MPI_Bcast(buffer.valPtr(),  count, traits::MpiValTraits<_Val>::datatype, root, comm);
  MPI_Bcast(buffer.idx0Ptr(), count, traits::MpiValTraits<index_t>::datatype, root, comm);
  MPI_Bcast(buffer.idx1Ptr(), count, traits::MpiValTraits<index_t>::datatype, root, comm);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void bcast(
          CooVector<_Val> &&buffer,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  bcast(buffer, root, comm);
}

template <typename _Val, Trans _trans>
inline void bcast(
          CooMatrix<_Val, _trans> &&buffer,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  bcast(buffer, root, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_COO_BCAST_HPP_
