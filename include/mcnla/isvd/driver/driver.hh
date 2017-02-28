////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/driver/driver.hh
/// @brief   The definition of iSVD driver.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_DRIVER_DRIVER_HH_
#define MCNLA_ISVD_DRIVER_DRIVER_HH_

#include <mcnla/isvd/def.hpp>
#include <mcnla/isvd/driver/parameters.hpp>
#include <mcnla/isvd/sketcher.hpp>
#include <mcnla/isvd/orthogonalizer.hpp>
#include <mcnla/isvd/integrator.hpp>
#include <mcnla/isvd/former.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/mpi.hpp>
#include <mcnla/core/utility/crtp.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_driver_module
/// The Integrated Singular Value Decomposition driver.
///
/// @tparam  _Val                The value type.
/// @tparam  _SketcherTag        The sketcher tag.
/// @tparam  _OrthogonalizerTag  The orthogonalizer tag.
/// @tparam  _IntegratorTag      The integrator tag.
/// @tparam  _FormerTag          The former tag.
///
/// @attention  The driver should have been @ref initialize "initialized" before calling #compute.
/// @attention  The driver should be @ref initialize "re-initialized" after changing parameters.
///
template <typename _Val,
          class _SketcherTag       = GaussianProjectionSketcherTag<0>,
          class _OrthogonalizerTag = SvdOrthogonalizerTag,
          class _IntegratorTag     = KolmogorovNagumoIntegratorTag,
          class _FormerTag         = SvdFormerTag>
class Driver {

 public:

  using ValType     = _Val;
  using RealValType = RealValT<_Val>;

  using ParametersType     = Parameters<ValType>;
  using SketcherType       = Sketcher<_SketcherTag, ValType>;
  using OrthogonalizerType = Orthogonalizer<_OrthogonalizerTag, ValType>;
  using IntegratorType     = Integrator<_IntegratorTag, ValType>;
  using FormerType         = Former<_FormerTag, ValType>;

 protected:

  /// The parameters.
  ParametersType parameters_;

  /// The MPI communicator.
  const MPI_Comm mpi_comm_;

  /// The MPI root.
  const mpi_int_t mpi_root_;

  /// The random seed.
  index_t seed_ = 0;

  /// The sketcher.
  SketcherType sketcher_;

  /// The orthogonalizer.
  OrthogonalizerType orthogonalizer_;

  /// The integrator.
  IntegratorType integrator_;

  /// The former.
  FormerType former_;

 public:

  // Constructor
  inline Driver( const MPI_Comm mpi_comm, const mpi_int_t mpi_root = 0 ) noexcept;

  // Initializes
  void initialize() noexcept;

  // Compute
  template<class _Matrix>
  void compute( const _Matrix &matrix ) noexcept;

  // Gets subdriver
  inline       SketcherType&       sketcher() noexcept;
  inline const SketcherType&       sketcher() const noexcept;
  inline       OrthogonalizerType& orthogonalizer() noexcept;
  inline const OrthogonalizerType& orthogonalizer() const noexcept;
  inline       IntegratorType&     integrator() noexcept;
  inline const IntegratorType&     integrator() const noexcept;
  inline       FormerType&         former() noexcept;
  inline const FormerType&         former() const noexcept;

  // Gets compute time
  inline double sketcherTime() const noexcept;
  inline double orthogonalizerTime() const noexcept;
  inline double integratorTime() const noexcept;
  inline double formerTime() const noexcept;

  // Gets information
  inline index_t integratorIteration() const noexcept;

  // Gets matrices
  inline const DenseVector<RealValType>& singularValues() const noexcept;
  inline const DenseMatrixColMajor<ValType>& leftSingularVectors() const noexcept;
  inline const DenseMatrixColMajor<ValType>& rightSingularVectors() const noexcept;
  inline const DenseMatrixRowMajor<ValType>& integratedOrthogonalBasis() const noexcept;

  // Gets parameters
  const ParametersType& parameters() const noexcept;

  // Sets parameters
  inline Driver& setSize( const index_t nrow, const index_t ncol ) noexcept;
  template<class _Matrix>
  inline Driver& setSize( const _Matrix &matrix ) noexcept;
  inline Driver& setRank( const index_t rank ) noexcept;
  inline Driver& setOverRank( const index_t over_rank ) noexcept;
  inline Driver& setNumSketch( const index_t num_sketch ) noexcept;
  inline Driver& setNumSketchEach( const index_t num_sketch_each ) noexcept;
  inline Driver& setMaxIteration( const index_t max_iteration ) noexcept;
  inline Driver& setTolerance( const RealValType tolerance ) noexcept;
  inline Driver& setSeed( const index_t seed ) noexcept;
  inline Driver& setSeeds( const index_t seed ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_DRIVER_DRIVER_HH_
