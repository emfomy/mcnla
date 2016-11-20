////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/send.hpp
/// @brief   The MPI SEND routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_SEND_HPP_
#define MCNLA_CORE_MPI_SEND_HPP_

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
/// @brief  Performs a blocking send
///
/// @attention  @a buffer should be shrunk.
///
template <class _Derived>
inline void send(
          DenseBase<_Derived> &buffer,
    const mpi_int_t dest,
    const mpi_int_t tag,
    const MPI_Comm comm
) noexcept {
  constexpr const MPI_Datatype &data_type = traits::MpiScalarTraits<typename traits::Traits<_Derived>::ScalarType>::data_type;
  mcnla_assert_true(buffer.derived().isShrunk());
  MPI_Send(buffer.getValue(), buffer.derived().getNelem(), data_type, dest, tag, comm);
}

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_SEND_HPP_