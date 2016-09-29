////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/solver.hpp
/// @brief   The MCNLA solver.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SOLVER_HPP_
#define MCNLA_ISVD_SOLVER_HPP_

#include <mcnla/def.hpp>
#include <mcnla/isvd/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/utility.hpp>
#include <mcnla/isvd/parameters.hpp>
#include <mcnla/isvd/sketcher.hpp>
#include <mcnla/isvd/integrator.hpp>
#include <mcnla/isvd/reconstructor.hpp>
#include <mpi.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

/// @addtogroup  isvd_module
//@{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The MCNLA solver.
///
/// @tparam  _Matrix         The matrix type.
/// @tparam  _Sketcher       The sketcher type.
/// @tparam  _Integrator     The integrator type.
/// @tparam  _Reconstructor  The reconstructor type.
///
/// @attention  The solver should have been #initialize&zwnj;d before calling #compute.
/// @attention  The solver should be re-#initialize&zwnj;d after changing parameters.
///
template <class _Matrix,
          class _Sketcher = GaussianProjectionSketcher<_Matrix>,
          class _Integrator = KolmogorovNagumoTypeIntegrator<_Matrix>,
          class _Reconstructor = StandardReconstructor<_Matrix>>
class Solver {

  static_assert(std::is_base_of<MatrixBase<_Matrix>, _Matrix>::value,
                "'_Matrix' is not a matrix!");
  static_assert(std::is_base_of<SketcherBase<_Sketcher>, _Sketcher>::value,
                "'_Sketcher' is not a sketcher!");
  static_assert(std::is_base_of<IntegratorBase<_Integrator>, _Integrator>::value,
                "'_Integrator' is not a integrator!");
  static_assert(std::is_base_of<ReconstructorBase<_Reconstructor>, _Reconstructor>::value,
                "'_Reconstructor' is not a reconstructor!");

  static_assert(std::is_same<_Matrix, typename SketcherBase<_Sketcher>::MatrixType>::value,
                "The matrix type does not fit!");
  static_assert(std::is_same<_Matrix, typename IntegratorBase<_Sketcher>::MatrixType>::value,
                "The matrix type does not fit!");
  static_assert(std::is_same<_Matrix, typename ReconstructorBase<_Sketcher>::MatrixType>::value,
                "The matrix type does not fit!");


 public:

  using MatrixType      = _Matrix;
  using ScalarType      = typename MatrixType::ScalarType;
  using RealScalarType  = typename MatrixType::RealScalarType;
  using ParametersType  = Parameters<ScalarType>;

 protected:

  /// The parameters.
  ParametersType parameters_;

  /// @copydoc  mcnla::isvd::Parameters::mpi_comm
  const MPI_Comm &mpi_comm_ = parameters_.mpi_comm;

  /// @copydoc  mcnla::isvd::Parameters::mpi_size
  const mpi_int_t &mpi_size_ = parameters_.mpi_size;

  /// @copydoc  mcnla::isvd::Parameters::mpi_root
  const mpi_int_t &mpi_root_ = parameters_.mpi_root;

  /// The MPI rank.
  const mpi_int_t mpi_rank_;

  /// The random seed
  index_t seed_[4] = {rand()%4096, rand()%4096, rand()%4096, (rand()%2048)*2+1};

  /// The sketcher.
  _Sketcher sketcher_;

  /// The integrator.
  _Integrator integrator_;

  /// The reconstructor.
  _Reconstructor reconstructor_;

 public:

  // Constructor
  inline Solver( const MPI_Comm mpi_comm, const mpi_int_t mpi_root = 0 ) noexcept;

  // Initializes
  void initialize() noexcept;

  // Compute
  void compute( const _Matrix &matrix ) noexcept;

  // Gets name
  inline constexpr const char* getSketcherName() const noexcept;
  inline constexpr const char* getIntegratorName() const noexcept;
  inline constexpr const char* getReconstructorName() const noexcept;

  // Gets matrices
  inline const DenseVector<RealScalarType>& getSingularValues() const noexcept;
  inline const DenseMatrix<ScalarType, Layout::COLMAJOR>& getLeftSingularVectors() const noexcept;
  inline const DenseMatrix<ScalarType, Layout::COLMAJOR>& getRightSingularVectors() const noexcept;
  inline const DenseMatrix<ScalarType, Layout::ROWMAJOR>& getIntegratedOrthonormalBasis() const noexcept;

  // Sets value
  inline Solver& setSize( const index_t nrow, const index_t ncol ) noexcept;
  inline Solver& setSize( const _Matrix &matrix ) noexcept;
  inline Solver& setRank( const index_t rank ) noexcept;
  inline Solver& setOverRank( const index_t over_rank ) noexcept;
  inline Solver& setNumSketch( const index_t num_sketch_each_each ) noexcept;
  inline Solver& setMaxIteration( const index_t max_iteration ) noexcept;
  inline Solver& setTolerance( const RealScalarType tolerance ) noexcept;
  inline Solver& setSeed( const index_t seed[4] ) noexcept;

};

//@}  isvd_module

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SOLVER_HPP_
