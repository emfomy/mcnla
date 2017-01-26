////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/sketcher_wrapper.hh
/// @brief   The definition of iSVD sketcher wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_SKETCHER_WRAPPER_HH_
#define MCNLA_ISVD_SKETCHER_SKETCHER_WRAPPER_HH_

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
/// @ingroup  isvd_sketcher_module
///
/// The iSVD sketcher wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class SketcherWrapper : public utility::CrtpBase<_Derived, SketcherWrapper<_Derived>> {

 public:

  using ScalarType = ScalarT<_Derived>;

  using ParametersType = Parameters<ScalarType>;

 protected:

  /// @copydoc  mcnla::isvd::Driver::parameters_
  const ParametersType &parameters_;

  /// @copydoc  mcnla::isvd::Driver::mpi_comm_
  const MPI_Comm mpi_comm_;

  /// @copydoc  mcnla::isvd::Driver::mpi_root_
  const mpi_int_t mpi_root_;

 protected:

  // Constructor
  inline SketcherWrapper( const ParametersType &parameters,
                          const MPI_Comm mpi_comm, const mpi_int_t mpi_root ) noexcept;

  // Outputs name
  inline std::ostream& outputName( std::ostream &os ) const noexcept;

 public:

  // Initializes
  inline void initialize() noexcept;

  // Random sketches
  template <class _Matrix>
  inline void sketch( const _Matrix &matrix_a, DenseMatrixCollection120<ScalarType> &collection_q ) noexcept;

  // Operators
  template <class __Derived>
  friend inline std::ostream& operator<<( std::ostream &os, const SketcherWrapper<__Derived> &wrapper );

  // Gets compute time
  inline double time() const noexcept;

  // Sets seed
  inline _Derived& setSeed( const index_t seed ) noexcept;
  inline _Derived& setSeeds( const index_t seed ) noexcept;


};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_SKETCHER_WRAPPER_HH_
