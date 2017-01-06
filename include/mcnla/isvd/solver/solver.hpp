////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/solver/solver.hpp
/// @brief   The iSVD solver.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SOLVER_SOLVER_HPP_
#define MCNLA_ISVD_SOLVER_SOLVER_HPP_

#include <mcnla/def.hpp>
#include <mcnla/isvd/def.hpp>
#include <vector>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/utility.hpp>
#include <mcnla/isvd/solver/parameters.hpp>
#include <mcnla/isvd/sketcher.hpp>
#include <mcnla/isvd/integrator.hpp>
#include <mcnla/isvd/former.hpp>
#include <mpi.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_module
///
/// The Integrated Singular Value Decomposition solver.
///
/// @tparam  _Matrix         The matrix type.
/// @tparam  _Sketcher       The sketcher type.
/// @tparam  _Integrator     The integrator type.
/// @tparam  _Former  The former type.
///
/// @attention  The solver should have been @link initialize() initialized@endlink before calling #compute.
/// @attention  The solver should be @link initialize() re-initialized@endlink after changing parameters.
///
template <class _Matrix,
          class _Sketcher   = GaussianProjectionSketcher<_Matrix>,
          class _Integrator = KolmogorovNagumoIntegrator<_Matrix>,
          class _Former     = StandardFormer<_Matrix>>
class Solver {

  static_assert(std::is_base_of<MatrixBase<_Matrix>, _Matrix>::value,
                "'_Matrix' is not a matrix!");
  static_assert(std::is_base_of<SketcherWrapper<_Sketcher>, _Sketcher>::value,
                "'_Sketcher' is not a sketcher!");
  static_assert(std::is_base_of<IntegratorBase<_Integrator>, _Integrator>::value,
                "'_Integrator' is not a integrator!");
  static_assert(std::is_base_of<FormerBase<_Former>, _Former>::value,
                "'_Former' is not a former!");

  static_assert(std::is_same<_Matrix, MatrixT<_Sketcher>>::value,   "The matrix type does not fit!");
  static_assert(std::is_same<_Matrix, MatrixT<_Integrator>>::value, "The matrix type does not fit!");
  static_assert(std::is_same<_Matrix, MatrixT<_Former>>::value,     "The matrix type does not fit!");

 public:

  using MatrixType      = _Matrix;
  using ScalarType      = ScalarT<MatrixType>;
  using RealScalarType  = typename MatrixType::RealScalarType;
  using ParametersType  = Parameters<ScalarType>;

 protected:

  /// The parameters.
  ParametersType parameters_;

  /// The MPI communicator.
  const MPI_Comm mpi_comm_;

  /// The MPI root.
  const mpi_int_t mpi_root_;

  /// The random seed
  index_t seed_[4] = {rand()%4096, rand()%4096, rand()%4096, (rand()%2048)*2+1};

  /// The sketcher.
  _Sketcher sketcher_;

  /// The integrator.
  _Integrator integrator_;

  /// The former.
  _Former former_;

 public:

  // Constructor
  inline Solver( const MPI_Comm mpi_comm, const mpi_int_t mpi_root = 0 ) noexcept;

  // Initializes
  void initialize() noexcept;

  // Compute
  void compute( const _Matrix &matrix ) noexcept;

  // Gets name
  inline constexpr const char* sketcherName() const noexcept;
  inline constexpr const char* integratorName() const noexcept;
  inline constexpr const char* reconstructorName() const noexcept;

  // Gets compute time
  inline double sketcherTime() const noexcept;
  inline double integratorTime() const noexcept;
  inline double reconstructorTime() const noexcept;

  // Gets matrices
  inline const DenseVector<RealScalarType>& singularValues() const noexcept;
  inline const DenseMatrixColMajor<ScalarType>& leftSingularVectors() const noexcept;
  inline const DenseMatrixColMajor<ScalarType>& rightSingularVectors() const noexcept;
  inline const DenseMatrixRowMajor<ScalarType>& integratedOrthogonalBasis() const noexcept;

  // Gets parameters
  const ParametersType& parameters() const noexcept;

  // Sets parameters
  inline Solver& setSize( const index_t nrow, const index_t ncol ) noexcept;
  inline Solver& setSize( const _Matrix &matrix ) noexcept;
  inline Solver& setRank( const index_t rank ) noexcept;
  inline Solver& setOverRank( const index_t over_rank ) noexcept;
  inline Solver& setNumSketch( const index_t num_sketch ) noexcept;
  inline Solver& setNumSketchEach( const index_t num_sketch_each ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SOLVER_SOLVER_HPP_
