////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/core/solver.hpp
/// @brief   The iSVD solver.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_CORE_SOLVER_HPP_
#define ISVD_CORE_SOLVER_HPP_

#include <isvd/isvd.hpp>
#include <isvd/matrix.hpp>
#include <isvd/utility.hpp>
#include <isvd/core/parameters.hpp>
#include <isvd/core/sketcher_base.hpp>
#include <mpi.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The iSVD solver.
///
/// @tparam  _Matrix         The matrix type.
/// @tparam  _Sketcher       The sketcher type.
/// @tparam  _Integrator     The integrator type.
/// @tparam  _Reconstructor  The reconstructor type.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
class Solver {

  static_assert(std::is_base_of<internal::MatrixBase<_Matrix>, _Matrix>::value,
                "'_Matrix' is not a matrix!");
  static_assert(std::is_base_of<internal::SketcherBase<_Sketcher>, _Sketcher>::value,
                "'_Sketcher' is not a sketcher!");

 public:

  using ScalarType      = typename _Matrix::ScalarType;
  using RealScalarType  = typename _Matrix::RealScalarType;
  using DenseVectorType = isvd::DenseVector<ScalarType>;
  using DenseMatrixType = isvd::DenseMatrix<ScalarType, Layout::ROWMAJOR>;
  using DenseCubeType   = isvd::DenseCube<ScalarType, Layout::ROWMAJOR>;

 protected:

  /// The parameters.
  internal::Parameters<RealScalarType> parameters_;

  /// @copydoc  isvd::internal::Parameters::mpi_comm
  const MPI_Comm &mpi_comm_ = parameters_.mpi_comm;

  /// @copydoc  isvd::internal::Parameters::mpi_size
  const index_t &mpi_size_ = parameters_.mpi_size;

  /// @copydoc  isvd::internal::Parameters::mpi_rank
  const index_t &mpi_rank_ = parameters_.mpi_rank;

  /// The sketcher.
  _Sketcher sketcher_;

  /// The integrator.
  _Integrator integrator_;

  /// The reconstructor.
  _Sketcher reconstructor_;

  /// The cube Q.
  DenseCubeType cube_q_;

 public:

  // Constructor
  Solver( const MPI_Comm mpi_comm ) noexcept;

  // Initializes
  void initialize() noexcept;

  // Gets value
  const internal::Parameters<RealScalarType>& getParameters() const noexcept;

  // Sets value
  inline Solver& setSize( const index_t nrow, const index_t ncol ) noexcept;
  inline Solver& setSize( const _Matrix &matrix ) noexcept;
  inline Solver& setRank( const index_t rank ) noexcept;
  inline Solver& setOverRank( const index_t over_rank ) noexcept;
  inline Solver& setNumSketch( const index_t num_sketch_each ) noexcept;
  inline Solver& setMaxIteration( const index_t max_iteration ) noexcept;
  inline Solver& setTolerance( const RealScalarType tolerance ) noexcept;
  inline Solver& setSeed( const index_t seed[4] ) noexcept;

};

}  // namespace isvd

#endif  // ISVD_CORE_SOLVER_HPP_
