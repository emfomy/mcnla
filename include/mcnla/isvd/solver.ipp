////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/solver.ipp
/// @brief   The implementation of iSVD solver.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SOLVER_IPP_
#define MCNLA_ISVD_SOLVER_IPP_

#include <mcnla/isvd/solver.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

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
    const mpi_int_t mpi_root
) noexcept
  : parameters_(mpi::getCommSize(mpi_comm)),
    mpi_comm_(mpi_comm),
    mpi_root_(mpi_root),
    sketcher_(parameters_, mpi_comm, mpi_root, seed_),
    integrator_(parameters_, mpi_comm, mpi_root),
    reconstructor_(parameters_, mpi_comm, mpi_root) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Initializes.
/// Broadcasts the parameters to all MPI ranks and allocates the memories.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
void Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::initialize() noexcept {
  MPI_Bcast(&parameters_, sizeof(parameters_), MPI_BYTE, mpi_root_, mpi_comm_);

  mcnla_assert_ge(parameters_.getNcol(), parameters_.getNrow());
  mcnla_assert_gt(parameters_.getNrow(), 0);
  mcnla_assert_ge(parameters_.getNrow(), parameters_.getDimSketch());

  mcnla_assert_gt(parameters_.getRank(), 0);
  mcnla_assert_ge(parameters_.getOverRank(), 0);

  mcnla_assert_gt(parameters_.getNumSketchEach(), 0);

  sketcher_.initialize();
  integrator_.initialize();
  reconstructor_.initialize();

  parameters_.initialized_ = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes the iSVD decomposition.
///
/// @attention  The solver should have be initialized.
/// @attention  @a matrix_a should be the same in each MPI node.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
void Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::compute( const _Matrix &matrix_a ) noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  mcnla_assert_eq(matrix_a.getSizes(), std::make_pair(parameters_.getNrow(), parameters_.getNcol()));

  sketcher_.sketch(matrix_a, integrator_.getSetQ());

  integrator_.integrate();

  reconstructor_.reconstruct(matrix_a, integrator_.getMatrixQbar());

  parameters_.computed_ = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the name of the sketcher.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
constexpr const char* Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::getSketcherName() const noexcept {
  return sketcher_.getName();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the name of the integrator.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
constexpr const char* Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::getIntegratorName() const noexcept {
  return integrator_.getName();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the name of the reconstructor.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
constexpr const char* Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::getReconstructorName() const noexcept {
  return reconstructor_.getName();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the time of running sketcher.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
double Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::getSketcherTime() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return sketcher_.getTime();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the time of running integrator.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
double Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::getIntegratorTime() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return integrator_.getTime();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the time of running reconstructor.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
double Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::getReconstructorTime() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return reconstructor_.getTime();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the times of running each steps of sketcher.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
const std::vector<double> Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::getSketcherTimes() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return sketcher_.getTimes();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the times of running each steps of integrator.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
const std::vector<double> Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::getIntegratorTimes() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return integrator_.getTimes();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the times of running each steps of reconstructor.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
const std::vector<double> Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::getReconstructorTimes() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return reconstructor_.getTimes();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of iterator in integrator.
///
/// @attention  The solver should have be computed.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
index_t Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::getIntegratorIter() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return integrator_.getIter();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the approximate singular values.
///
/// @attention  The solver should have be computed.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
const DenseVector<typename Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::RealScalarType>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::getSingularValues() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return reconstructor_.getVectorS();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the approximate left singular vectors.
///
/// @attention  The solver should have be computed.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
const DenseMatrix<typename Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::ScalarType, Layout::COLMAJOR>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::getLeftSingularVectors() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return reconstructor_.getMatrixU();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the approximate right singular vectors.
///
/// @attention  The solver should have be computed.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
const DenseMatrix<typename Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::ScalarType, Layout::COLMAJOR>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::getRightSingularVectors() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return reconstructor_.getMatrixVt();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the integrated orthonormal basis of the sketched subspace.
///
/// @attention  The solver should have be computed.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
const DenseMatrix<typename Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::ScalarType, Layout::ROWMAJOR>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::getIntegratedOrthonormalBasis() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return integrator_.getMatrixQbar();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the parameters.
///
/// @attention  Only affects on root rank.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
const typename Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::ParametersType&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::getParameters() const noexcept {
  mcnla_assert_true(mpi::isCommRoot(mpi_root_, mpi_comm_));
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
  if ( !mpi::isCommRoot(mpi_root_, mpi_comm_) ) { return *this; }
  parameters_.nrow_ = nrow; parameters_.ncol_ = ncol;
  parameters_.initialized_ = false; parameters_.computed_ = false; return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  setSize
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::setSize( const _Matrix &matrix ) noexcept {
  if ( !mpi::isCommRoot(mpi_root_, mpi_comm_) ) { return *this; }
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
  if ( !mpi::isCommRoot(mpi_root_, mpi_comm_) ) { return *this; }
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
  if ( !mpi::isCommRoot(mpi_root_, mpi_comm_) ) { return *this; }
  parameters_.over_rank_ = over_rank;
  parameters_.initialized_ = false; parameters_.computed_ = false; return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the number of total random sketches
///
/// @attention  @a num_sketch must be a multiple of #mpi_size_.
/// @attention  Only affects on root rank.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::setNumSketch( const index_t num_sketch ) noexcept {
  if ( !mpi::isCommRoot(mpi_root_, mpi_comm_) ) { return *this; }
  parameters_.num_sketch_each_ = num_sketch / mpi::getCommSize(mpi_comm_);
  parameters_.initialized_ = false; parameters_.computed_ = false; return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the number of random sketches per MPI node.
///
/// @attention  Only affects on root rank.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::setNumSketchEach( const index_t num_sketch_each ) noexcept {
  if ( !mpi::isCommRoot(mpi_root_, mpi_comm_) ) { return *this; }
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
  if ( !mpi::isCommRoot(mpi_root_, mpi_comm_) ) { return *this; }
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
  if ( !mpi::isCommRoot(mpi_root_, mpi_comm_) ) { return *this; }
  parameters_.tolerance_ = tolerance;
  parameters_.initialized_ = false; parameters_.computed_ = false; return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the random seed.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::setSeed( const index_t seed[4] ) noexcept {
  for ( index_t i = 0; i < 4; ++i ) {
    seed_[i] = seed[i];
  }
  return *this;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SOLVER_IPP_
