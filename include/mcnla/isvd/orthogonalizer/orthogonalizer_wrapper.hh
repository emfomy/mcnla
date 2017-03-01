////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/orthogonalizer/orthogonalizer_wrapper.hh
/// @brief   The definition of iSVD orthogonalizer wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_ORTHOGONALIZER_ORTHOGONALIZER_WRAPPER_HH_
#define MCNLA_ISVD_ORTHOGONALIZER_ORTHOGONALIZER_WRAPPER_HH_

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
/// @ingroup  isvd_orthogonalizer_module_detail
/// The iSVD orthogonalizer wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class OrthogonalizerWrapper : public utility::CrtpBase<_Derived, OrthogonalizerWrapper<_Derived>> {

 public:

  using ValType        = ValT<_Derived>;

  using ParametersType = Parameters<ValType>;

 protected:

  /// @copydoc  mcnla::isvd::Driver::parameters_
  const ParametersType &parameters_;

  /// @copydoc  mcnla::isvd::Driver::mpi_comm_
  const MPI_Comm mpi_comm_;

  /// @copydoc  mcnla::isvd::Driver::mpi_root_
  const mpi_int_t mpi_root_;

 protected:

  // Constructor
  inline OrthogonalizerWrapper( const ParametersType &parameters,
                                const MPI_Comm mpi_comm, const mpi_int_t mpi_root ) noexcept;

  // Outputs name
  inline std::ostream& outputName( std::ostream &os ) const noexcept;

 public:

  // Initializes
  inline void initialize() noexcept;

  // Orthogonalizes
  inline void orthogonalize( DenseMatrixCollection120<ValType> &collection_q ) noexcept;

  // Operators
  template <class __Derived>
  friend inline std::ostream& operator<<( std::ostream &os, const OrthogonalizerWrapper<__Derived> &wrapper );

  // Gets compute time
  inline double time() const noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_ORTHOGONALIZER_ORTHOGONALIZER_WRAPPER_HH_
