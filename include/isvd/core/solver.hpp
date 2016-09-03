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
  using ParametersType  = internal::Parameters<ScalarType>;

 protected:

  /// The parameters.
  ParametersType parameters_;

  /// @copydoc  isvd::internal::Parameters::mpi_comm
  const MPI_Comm &mpi_comm_ = parameters_.mpi_comm;

  /// @copydoc  isvd::internal::Parameters::mpi_size
  const index_t &mpi_size_ = parameters_.mpi_size;

  /// @copydoc  isvd::internal::Parameters::mpi_rank
  const index_t &mpi_rank_ = parameters_.mpi_rank;

  /// @copydoc  isvd::internal::Parameters::mpi_root
  const index_t &mpi_root_ = parameters_.mpi_root;

  /// The sketcher.
  _Sketcher sketcher_;

  /// The integrator.
  _Integrator integrator_;

  /// The reconstructor.
  _Reconstructor reconstructor_;

  /// The matrix Qc.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_qc_;

  /// The cube Q.
  DenseCube<ScalarType, Layout::ROWMAJOR> cube_q_;

  /// The vector S.
  DenseVector<RealScalarType> vector_s_;

  /// The vector Sl.
  DenseVector<RealScalarType> vector_sl_;

  /// The matrix U.
  DenseMatrix<ScalarType, Layout::COLMAJOR> matrix_u_;

  /// The matrix Ul.
  DenseMatrix<ScalarType, Layout::COLMAJOR> matrix_ul_;

  /// The matrix Vt.
  DenseMatrix<ScalarType, Layout::COLMAJOR> matrix_vt_;

  /// The matrix Vlt.
  DenseMatrix<ScalarType, Layout::COLMAJOR> matrix_vlt_;

 public:

  // Constructor
  Solver( const MPI_Comm mpi_comm, const index_t mpi_root ) noexcept;

  // Initializes
  void initialize() noexcept;

  // Compute
  void compute( const _Matrix &matrix ) noexcept;

  // Gets matrices
  inline const DenseVector<RealScalarType>& getSingularValues() const noexcept;
  inline const DenseMatrix<ScalarType, Layout::COLMAJOR>& getLeftSingularVectors() const noexcept;
  inline const DenseMatrix<ScalarType, Layout::COLMAJOR>& getRightSingularVectors() const noexcept;

  // Gets value
  inline const ParametersType& getParameters() const noexcept;

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
