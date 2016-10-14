////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/bcast.hpp
/// @brief   The MPI BCAST routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_BCAST_HPP_
#define MCNLA_CORE_MPI_BCAST_HPP_

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
/// @ingroup  mpi_module
/// @brief  Broadcasts a message from the process with rank root to all other processes of the group.
///
/// @attention  The size of @a buffer should be the same for all MPI nodes.
/// @attention  @a buffer should be shrunk.
///
template <class _Derived>
inline void bcast(
          DenseBase<_Derived> &buffer,
    const mpi_int_t root,
    const MPI_Comm comm
) noexcept {
  constexpr const MPI_Datatype &data_type = traits::MpiScalarTraits<typename traits::Traits<_Derived>::ScalarType>::data_type;
  mcnla_assert_true(buffer.derived().isShrunk());
  MPI_Bcast(buffer.getValue(), buffer.derived().getNelem(), data_type, root, comm);
}

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_BCAST_HPP_
