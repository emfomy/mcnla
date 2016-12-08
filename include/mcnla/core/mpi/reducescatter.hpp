////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/mpi/reducescatter.hpp
/// @brief   The MPI RECUDESCATTER routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MPI_RECUDESCATTER_HPP_
#define MCNLA_CORE_MPI_RECUDESCATTER_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/mpi/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <algorithm>
#include <numeric>

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
/// @brief  Combines values and scatters the results.
///
/// @attention  The size of @a send should be equal to the sum of @a recvcounts.
/// @attention  The size of @a recv in rank @c i should be equal to @a recvcounts[i].
/// @attention  @a send and @a recv should be shrunk.
///
template <class _Derived>
inline void reducescatter(
    const DenseBase<_Derived> &send,
          DenseBase<_Derived> &recv,
    const mpi_int_t recvcounts[],
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  using ScalarType = typename traits::Traits<_Derived>::ScalarType;
  constexpr const MPI_Datatype &data_type = traits::MpiScalarTraits<ScalarType>::data_type;
  mcnla_assert_true(send.derived().isShrunk());
  mcnla_assert_true(recv.derived().isShrunk());
  mcnla_assert_eq(send.derived().getNelem(), std::accumulate(recvcounts, recvcounts + getCommSize(comm), 0));
  mcnla_assert_eq(recv.derived().getNelem(), recvcounts[getCommRank(comm)]);
  MPI_Reduce_scatter(send.getValue(), recv.getValue(), recvcounts, data_type, op, comm);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Derived>
inline void reducescatter(
    const DenseBase<_Derived> &send,
          DenseBase<_Derived> &&recv,
    const mpi_int_t recvcounts[],
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  reducescatter(send, recv, recvcounts, op, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  mpi_module
/// @brief  Combines values and scatters the results. (same-size version)
///
/// @attention  The size of @a send should be equal to the size of @a recv &times the number of MPI rank.
/// @attention  @a send and @a recv should be shrunk.
///
template <class _Derived>
inline void reducescatter(
    const DenseBase<_Derived> &send,
          DenseBase<_Derived> &recv,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  using ScalarType = typename traits::Traits<_Derived>::ScalarType;
  constexpr const MPI_Datatype &data_type = traits::MpiScalarTraits<ScalarType>::data_type;
  const auto mpi_size = getCommSize(comm);
  mcnla_assert_true(send.derived().isShrunk());
  mcnla_assert_true(recv.derived().isShrunk());
  mcnla_assert_eq(send.derived().getNelem(), recv.derived().getNelem() * mpi_size);
  auto recvcounts = new mpi_int_t[mpi_size];
  std::fill(recvcounts, recvcounts + mpi_size, recv.derived().getNelem());
  MPI_Reduce_scatter(send.getValue(), recv.getValue(), recvcounts, data_type, op, comm);
  delete[] recvcounts;
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Derived>
inline void reducescatter(
    const DenseBase<_Derived> &send,
          DenseBase<_Derived> &&recv,
    const MPI_Op op,
    const MPI_Comm comm
) noexcept {
  reducescatter(send, recv, op, comm);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace mpi

}  // namespace mcnla

#endif  // MCNLA_CORE_MPI_RECUDESCATTER_HPP_
