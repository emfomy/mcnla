////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/orthogonalizer/orthogonalizer_wrapper.hh
/// @brief   The definition of iSVD orthogonalizer wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_ORTHOGONALIZER_ORTHOGONALIZER_WRAPPER_HH_
#define MCNLA_ISVD_ORTHOGONALIZER_ORTHOGONALIZER_WRAPPER_HH_

#include <mcnla/def.hpp>
#include <mcnla/isvd/def.hpp>
#include <mcnla/isvd/solver.hpp>
#include <mcnla/core/container.hpp>
#include <mcnla/core/utility/crtp.hpp>
#include <mcnla/core/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_orthogonalizer_module
///
/// The iSVD orthogonalizer wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class OrthogonalizerWrapper : public utility::CrtpBase<_Derived, OrthogonalizerWrapper<_Derived>> {

 public:

  using ScalarType = ScalarT<_Derived>;

 protected:

  /// @copydoc  mcnla::isvd::Solver::parameters_
  const Parameters &parameters_;

  /// @copydoc  mcnla::isvd::Solver::mpi_comm_
  const MPI_Comm mpi_comm_;

  /// @copydoc  mcnla::isvd::Solver::mpi_root_
  const mpi_int_t mpi_root_;

 protected:

  // Constructor
  inline OrthogonalizerWrapper( const Parameters &parameters,
                                const MPI_Comm mpi_comm, const mpi_int_t mpi_root ) noexcept;

 public:

  // Initializes
  inline void initialize() noexcept;

  // Orthogonalizes
  inline void orthogonalize( DenseMatrixSet120<ScalarType> &set_q ) noexcept;

  // Gets name
  inline constexpr const char* name() const noexcept;

  // Gets compute time
  inline double time() const noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_ORTHOGONALIZER_ORTHOGONALIZER_WRAPPER_HH_
