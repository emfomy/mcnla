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
    mpi_rank_(mpi::getCommRank(mpi_comm)),
    sketcher_(parameters_, seed_),
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
  assert(parameters_.getNumSketchEach() > 0);

  sketcher_.initialize();
  integrator_.initialize();
  reconstructor_.initialize();

  parameters_.initialized_ = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes the iSVD decomposition.
///
/// @attention  @p matrix_a should be the same in each MPI node.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
void Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::compute( const _Matrix &matrix_a ) noexcept {
  assert(parameters_.isInitialized());
  assert(matrix_a.getSizes() == std::make_pair(parameters_.getNrow(), parameters_.getNcol()));

  sketcher_.sketch(matrix_a, integrator_.getCubeQ());
  integrator_.integrate();
  reconstructor_.reconstruct(matrix_a, integrator_.getMatrixQc());

  parameters_.computed_ = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the singular values.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
const DenseVector<typename Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::RealScalarType>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::getSingularValues() const noexcept {
  return reconstructor_.getSingularValues();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the left singular vectors.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
const DenseMatrix<typename Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::ScalarType, Layout::COLMAJOR>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::getLeftSingularVectors() const noexcept {
  return reconstructor_.getLeftSingularVectors();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the right singular vectors.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
const DenseMatrix<typename Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::ScalarType, Layout::COLMAJOR>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::getRightSingularVectors() const noexcept {
  return reconstructor_.getRightSingularVectors();
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
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::setNumSketch( const index_t num_sketch_each ) noexcept {
  if ( mpi_rank_ != mpi_root_ ) { return *this; }
  parameters_.num_sketch_each_ = num_sketch_each;
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
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::setSeed( const index_t seed[4] ) noexcept {
  for ( auto i = 0; i < 4; ++i ) {
    seed_[i] = seed[i];
  }
  return *this;
}

}  // namespace isvd

#endif  // ISVD_CORE_SOLVER_IPP_
