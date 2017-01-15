////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/integrator_wrapper.hh
/// @brief   The definition of iSVD integrator wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_INTEGRATOR_WRAPPER_HH_
#define MCNLA_ISVD_INTEGRATOR_INTEGRATOR_WRAPPER_HH_

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
/// @ingroup  isvd_integrator_module
///
/// The iSVD integrator wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class IntegratorWrapper : public utility::CrtpBase<_Derived, IntegratorWrapper<_Derived>> {

 public:

  using ScalarType = ScalarT<_Derived>;

  using ParametersType = Parameters<ScalarType>;

 protected:

  /// @copydoc  mcnla::isvd::Solver::parameters_
  const ParametersType &parameters_;

  /// @copydoc  mcnla::isvd::Solver::mpi_comm_
  const MPI_Comm mpi_comm_;

  /// @copydoc  mcnla::isvd::Solver::mpi_root_
  const mpi_int_t mpi_root_;

  /// The number of iteration.
  index_t iteration_;

 protected:

  // Constructor
  inline IntegratorWrapper( const ParametersType &parameters,
                            const MPI_Comm mpi_comm, const mpi_int_t mpi_root ) noexcept;

 public:

  // Initializes
  inline void initialize() noexcept;

  // Integrates
  inline void integrate() noexcept;

  // Gets name
  inline constexpr const char* name() const noexcept;

  // Gets compute time
  inline double time() const noexcept;

  // Gets iteration number
  inline index_t iteration() const noexcept;

  // Gets matrices
  inline       DenseMatrixCollection120<ScalarType>& collectionQ() noexcept;
  inline const DenseMatrixCollection120<ScalarType>& collectionQ() const noexcept;
  inline       DenseMatrixRowMajor<ScalarType>& matrixQ() noexcept;
  inline const DenseMatrixRowMajor<ScalarType>& matrixQ() const noexcept;


};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_INTEGRATOR_WRAPPER_HH_
