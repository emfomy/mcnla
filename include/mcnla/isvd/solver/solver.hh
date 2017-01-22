////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/solver/solver.hh
/// @brief   The definition of iSVD solver.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SOLVER_SOLVER_HH_
#define MCNLA_ISVD_SOLVER_SOLVER_HH_

#include <mcnla/isvd/def.hpp>
#include <mcnla/isvd/solver/parameters.hpp>
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
/// @ingroup  isvd_solver_module
///
/// The Integrated Singular Value Decomposition solver.
///
/// @tparam  _Scalar             The scalar type.
/// @tparam  _SketcherTag        The sketcher tag.
/// @tparam  _OrthogonalizerTag  The orthogonalizer tag.
/// @tparam  _IntegratorTag      The integrator tag.
/// @tparam  _FormerTag          The former tag.
///
/// @attention  The solver should have been @ref initialize "initialized" before calling #compute.
/// @attention  The solver should be @ref initialize "re-initialized" after changing parameters.
///
template <typename _Scalar,
          class _SketcherTag       = GaussianProjectionSketcherTag<0>,
          class _OrthogonalizerTag = SvdOrthogonalizerTag,
          class _IntegratorTag     = KolmogorovNagumoIntegratorTag,
          class _FormerTag         = SvdFormerTag>
class Solver {

 public:

  using ScalarType     = _Scalar;
  using RealScalarType = RealScalarT<_Scalar>;

  using ParametersType     = Parameters<ScalarType>;
  using SketcherType       = Sketcher<ScalarType, _SketcherTag>;
  using OrthogonalizerType = Orthogonalizer<ScalarType, _OrthogonalizerTag>;
  using IntegratorType     = Integrator<ScalarType, _IntegratorTag>;
  using FormerType         = Former<ScalarType, _FormerTag>;

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
  inline Solver( const MPI_Comm mpi_comm, const mpi_int_t mpi_root = 0 ) noexcept;

  // Initializes
  void initialize() noexcept;

  // Compute
  template<class _Matrix>
  void compute( const _Matrix &matrix ) noexcept;

  // Gets subsolver
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
  inline const DenseVector<RealScalarType>& singularValues() const noexcept;
  inline const DenseMatrixColMajor<ScalarType>& leftSingularVectors() const noexcept;
  inline const DenseMatrixColMajor<ScalarType>& rightSingularVectors() const noexcept;
  inline const DenseMatrixRowMajor<ScalarType>& integratedOrthogonalBasis() const noexcept;

  // Gets parameters
  const ParametersType& parameters() const noexcept;

  // Sets parameters
  inline Solver& setSize( const index_t nrow, const index_t ncol ) noexcept;
  template<class _Matrix>
  inline Solver& setSize( const _Matrix &matrix ) noexcept;
  inline Solver& setRank( const index_t rank ) noexcept;
  inline Solver& setOverRank( const index_t over_rank ) noexcept;
  inline Solver& setNumSketch( const index_t num_sketch ) noexcept;
  inline Solver& setNumSketchEach( const index_t num_sketch_each ) noexcept;
  inline Solver& setMaxIteration( const index_t max_iteration ) noexcept;
  inline Solver& setTolerance( const RealScalarType tolerance ) noexcept;
  inline Solver& setSeed( const index_t seed ) noexcept;
  inline Solver& setSeeds( const index_t seed ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SOLVER_SOLVER_HH_
