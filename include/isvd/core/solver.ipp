////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/core/solver.ipp
/// @brief   The implementation of iSVD solver.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_CORE_SOLVER_IPP_
#define ISVD_CORE_SOLVER_IPP_

#include <isvd/core/solver.hpp>

#pragma wanring
#include <isvd/blas.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::Solver(
    const MPI_Comm mpi_comm,
    const index_t mpi_root
) noexcept
  : parameters_(mpi_comm, mpi_root),
    sketcher_(parameters_),
    integrator_(parameters_),
    reconstructor_(parameters_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Initializes.
/// Broadcasts the parameters to all MPI ranks and allocates the memories.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
void Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::initialize() noexcept {

  MPI_Bcast(&parameters_, sizeof(internal::Parameters<ScalarType>), MPI_BYTE, mpi_root_, mpi_comm_);

  assert(parameters_.getNcol() >= parameters_.getNrow() && parameters_.getNrow() > 0);
  assert(parameters_.getNrow() >= parameters_.getDimSketch());
  assert(parameters_.getRank() > 0 && parameters_.getOverRank() >= 0);
  assert(parameters_.getNumSketch() > 0);

  sketcher_.initialize();
  integrator_.initialize();
  reconstructor_.initialize();

  const auto matrix_qc_sizes = std::make_pair(parameters_.getNrow(), parameters_.getDimSketch());
  if ( matrix_qc_.getSizes() != matrix_qc_sizes ) {
    matrix_qc_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_qc_sizes);
  }

  const auto cube_q_sizes = std::make_tuple(parameters_.getNrow(), parameters_.getDimSketch(), parameters_.getNumSketch());
  if ( cube_q_.getSizes() != cube_q_sizes ) {
    cube_q_ = DenseCube<ScalarType, Layout::ROWMAJOR>(cube_q_sizes);
  }

  const auto vector_sl_sizes = parameters_.getDimSketch();
  if ( vector_sl_.getSizes() != vector_sl_sizes ) {
    vector_sl_ = DenseVector<ScalarType>(vector_sl_sizes);
  }

  const auto matrix_ul_sizes = std::make_pair(parameters_.getNrow(), parameters_.getDimSketch());
  if ( matrix_ul_.getSizes() != matrix_ul_sizes ) {
    matrix_ul_ = DenseMatrix<ScalarType, Layout::COLMAJOR>(matrix_ul_sizes);
  }

  const auto matrix_vlt_sizes = std::make_pair(parameters_.getDimSketch(), parameters_.getNcol());
  if ( matrix_vlt_.getSizes() != matrix_vlt_sizes ) {
    matrix_vlt_ = DenseMatrix<ScalarType, Layout::COLMAJOR>(matrix_vlt_sizes);
  }

  parameters_.initialized_ = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes the iSVD decomposition.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
void Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::compute( const _Matrix &matrix_a ) noexcept {
  assert(parameters_.isInitialized());
  assert(matrix_a.getSizes()  == std::make_pair(parameters_.getNrow(), parameters_.getNcol()));

  sketcher_.sketch(matrix_a, cube_q_);

#pragma warning
  blas::copy(cube_q_.getPage(0), matrix_qc_);

  reconstructor_.reconstruct(matrix_a, matrix_qc_, vector_sl_, matrix_ul_, matrix_vlt_);

  vector_s_  = vector_sl_.getSegment({0, parameters_.getRank()});
  matrix_u_  = matrix_ul_.getCols({0, parameters_.getRank()});
  matrix_vt_ = matrix_vlt_.getRows({0, parameters_.getRank()});

  parameters_.computed_ = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the singular values.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
const DenseVector<typename Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::RealScalarType>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::getSingularValues() const noexcept {
  assert(parameters_.isComputed());
  return vector_s_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the left singular vectors.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
const DenseMatrix<typename Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::ScalarType, Layout::COLMAJOR>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::getLeftSingularVectors() const noexcept {
  assert(parameters_.isComputed());
  return matrix_u_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the right singular vectors.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
const DenseMatrix<typename Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::ScalarType, Layout::COLMAJOR>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::getRightSingularVectors() const noexcept {
  assert(parameters_.isComputed());
  return matrix_vt_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the parameters.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
const typename Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::ParametersType&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::getParameters() const noexcept {
  return parameters_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the sizes of the matrix.
///
/// @attention  Only affects on root rank.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::setSize( const index_t nrow, const index_t ncol ) noexcept {
  if ( mpi_rank_ != mpi_root_ ) { return *this; }
  parameters_.nrow_ = nrow; parameters_.ncol_ = ncol;
  parameters_.initialized_ = false; parameters_.computed_ = false; return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  setSize
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::setSize( const _Matrix &matrix ) noexcept {
  if ( mpi_rank_ != mpi_root_ ) { return *this; }
  return setSize(matrix.getNrow(), matrix.getNcol());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the desired rank of approximate SVD.
///
/// @attention  Only affects on root rank.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::setRank( const index_t rank ) noexcept {
  if ( mpi_rank_ != mpi_root_ ) { return *this; }
  parameters_.rank_ = rank;
  parameters_.initialized_ = false; parameters_.computed_ = false; return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the dimension of random sketches.
///
/// @attention  Only affects on root rank.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::setOverRank( const index_t over_rank ) noexcept {
  if ( mpi_rank_ != mpi_root_ ) { return *this; }
  parameters_.over_rank_ = over_rank;
  parameters_.initialized_ = false; parameters_.computed_ = false; return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the number of random sketches per MPI node.
///
/// @attention  Only affects on root rank.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::setNumSketch( const index_t num_sketch ) noexcept {
  if ( mpi_rank_ != mpi_root_ ) { return *this; }
  parameters_.num_sketch_ = num_sketch;
  parameters_.initialized_ = false; parameters_.computed_ = false; return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the maximum iteration.
///
/// @attention  Only affects on root rank.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::setMaxIteration( const index_t max_iteration ) noexcept {
  if ( mpi_rank_ != mpi_root_ ) { return *this; }
  parameters_.max_iteration_ = max_iteration;
  parameters_.initialized_ = false; parameters_.computed_ = false; return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the tolerance of converge condition.
///
/// @attention  Only affects on root rank.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::setTolerance( const RealScalarType tolerance ) noexcept {
  if ( mpi_rank_ != mpi_root_ ) { return *this; }
  parameters_.tolerance_ = tolerance;
  parameters_.initialized_ = false; parameters_.computed_ = false; return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the random seed.
///
/// @attention  Only affects on root rank.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::setSeed( const index_t seed[4] ) noexcept {
  if ( mpi_rank_ != mpi_root_ ) { return *this; }
  for ( auto i = 0; i < 4; ++i ) {
    parameters_.seed_[i] = seed[i];
  }
  parameters_.initialized_ = false; parameters_.computed_ = false; return *this;
}

}  // namespace isvd

#endif  // ISVD_CORE_SOLVER_IPP_
