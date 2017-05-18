////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/dense/bcast.hpp
/// @brief   The MPI BCAST routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_DENSE_BCAST_HPP_
#define MCNLA_CORE_MPI_DENSE_BCAST_HPP_

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
          DenseStorage<CoreTag, _Val> &buffer,
    const mpi_int_t count,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  constexpr const MPI_Datatype &datatype = traits::MpiValTraits<_Val>::datatype;
  MPI_Bcast(buffer.valPtr(), count, datatype, root, comm);
}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_dense_module
/// @brief  Broadcasts a message from the process with rank root to all other processes of the group.
///
/// @attention  The dimensions of @a buffer should be the same for all MPI nodes.
/// @attention  @a buffer should be shrunk.
///
//@{
template <typename _Val>
inline void bcast(
          DenseVector<_Val> &buffer,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(buffer.isShrunk());
  detail::bcastImpl(buffer, buffer.nelem(), root, comm);
}

template <typename _Val, Trans _trans>
inline void bcast(
          DenseMatrix<_Val, _trans> &buffer,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  mcnla_assert_true(buffer.isShrunk());
  detail::bcastImpl(buffer, buffer.nelem(), root, comm);
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void bcast(
          DenseVector<_Val> &&buffer,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  bcast(buffer, root, comm);
}

template <typename _Val, Trans _trans>
inline void bcast(
          DenseMatrix<_Val, _trans> &&buffer,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  bcast(buffer, root, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_DENSE_BCAST_HPP_
