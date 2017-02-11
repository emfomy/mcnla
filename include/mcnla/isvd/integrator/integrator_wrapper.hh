////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/integrator_wrapper.hh
/// @brief   The definition of iSVD integrator wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_INTEGRATOR_WRAPPER_HH_
#define MCNLA_ISVD_INTEGRATOR_INTEGRATOR_WRAPPER_HH_

#include <mcnla/isvd/def.hpp>
#include <iostream>
#include <mcnla/isvd/driver/parameters.hpp>
#include <mcnla/core/matrix.hpp>
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
/// @ingroup  isvd_integrator_module_detail
/// The iSVD integrator wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class IntegratorWrapper : public utility::CrtpBase<_Derived, IntegratorWrapper<_Derived>> {

 public:

  using ValType = ValT<_Derived>;

  using ParametersType = Parameters<ValType>;

 protected:

  /// @copydoc  mcnla::isvd::Driver::parameters_
  const ParametersType &parameters_;

  /// @copydoc  mcnla::isvd::Driver::mpi_comm_
  const MPI_Comm mpi_comm_;

  /// @copydoc  mcnla::isvd::Driver::mpi_root_
  const mpi_int_t mpi_root_;

  /// The number of iteration.
  index_t iteration_;

 protected:

  // Constructor
  inline IntegratorWrapper( const ParametersType &parameters,
                            const MPI_Comm mpi_comm, const mpi_int_t mpi_root ) noexcept;

  // Outputs name
  inline std::ostream& outputName( std::ostream &os ) const noexcept;

 public:

  // Initializes
  inline void initialize() noexcept;

  // Integrates
  inline void integrate() noexcept;

  // Operators
  template <class __Derived>
  friend inline std::ostream& operator<<( std::ostream &os, const IntegratorWrapper<__Derived> &wrapper );

  // Gets compute time
  inline double time() const noexcept;

  // Gets iteration number
  inline index_t iteration() const noexcept;

  // Gets matrices
  inline       DenseMatrixCollection120<ValType>& collectionQ() noexcept;
  inline const DenseMatrixCollection120<ValType>& collectionQ() const noexcept;
  inline       DenseMatrixRowMajor<ValType>& matrixQ() noexcept;
  inline const DenseMatrixRowMajor<ValType>& matrixQ() const noexcept;


};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_INTEGRATOR_WRAPPER_HH_
