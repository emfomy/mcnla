////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/solver/solver.hpp
/// @brief   The iSVD solver.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SOLVER_SOLVER_HPP_
#define MCNLA_ISVD_SOLVER_SOLVER_HPP_

#include <mcnla/isvd/solver/solver.hh>

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
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::Solver(
    const MPI_Comm mpi_comm,
    const mpi_int_t mpi_root
) noexcept
  : parameters_(mpi_comm),
    mpi_comm_(mpi_comm),
    mpi_root_(mpi_root),
    sketcher_(parameters_, mpi_comm, mpi_root, seed_),
    orthogonalizer_(parameters_, mpi_comm, mpi_root),
    integrator_(parameters_, mpi_comm, mpi_root),
    former_(parameters_, mpi_comm, mpi_root) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Initializes.
/// Broadcasts the parameters to all MPI ranks and allocates the memories.
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
void Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::initialize() noexcept {

  // Broadcast parameters
  MPI_Bcast(&parameters_, sizeof(parameters_), MPI_BYTE, mpi_root_, mpi_comm_);

  // Update random seeds
  sketcher_.setSeeds(seed_);

  // Check parameters
  mcnla_assert_ge(parameters_.ncol(), parameters_.nrow());
  mcnla_assert_gt(parameters_.nrow(), 0);
  mcnla_assert_ge(parameters_.nrow(), parameters_.dimSketch());

  mcnla_assert_gt(parameters_.rank(), 0);
  mcnla_assert_ge(parameters_.overRank(), 0);

  mcnla_assert_gt(parameters_.numSketchEach(), 0);

  sketcher_.initialize();
  orthogonalizer_.initialize();
  integrator_.initialize();
  former_.initialize();

  parameters_.initialized_ = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes the SVD decomposition.
///
/// @attention  The solver should have be initialized.
/// @attention  @a matrix_a should be the same in each MPI node.
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
template <class _Matrix>
void Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::compute(
    const _Matrix &matrix_a
) noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  mcnla_assert_eq(matrix_a.sizes(), std::make_tuple(parameters_.nrow(), parameters_.ncol()));

  sketcher_.sketch(matrix_a, integrator_.collectionQ());

  orthogonalizer_.orthogonalize(integrator_.collectionQ());

  integrator_.integrate();

  former_.form(matrix_a, integrator_.matrixQ());

  parameters_.computed_ = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the sketcher.
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
Sketcher<_Scalar, _SketcherTag>&
    Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::sketcher(
) noexcept {
  return sketcher_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  sketcher
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
const Sketcher<_Scalar, _SketcherTag>&
    Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::sketcher(
) const noexcept {
  return sketcher_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the orthogonalizer.
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
Orthogonalizer<_Scalar, _OrthogonalizerTag>&
    Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::orthogonalizer(
) noexcept {
  return integrator_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  orthogonalizer
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
const Orthogonalizer<_Scalar, _OrthogonalizerTag>&
    Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::orthogonalizer(
) const noexcept {
  return integrator_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the integrator.
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
Integrator<_Scalar, _IntegratorTag>&
    Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::integrator(
) noexcept {
  return integrator_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  integrator
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
const Integrator<_Scalar, _IntegratorTag>&
    Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::integrator(
) const noexcept {
  return integrator_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the former.
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
Former<_Scalar, _FormerTag>&
    Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::former(
) noexcept {
  return former_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  former
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
const Former<_Scalar, _FormerTag>&
    Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::former(
) const noexcept {
  return former_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the time of running sketcher.
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
double Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::sketcherTime() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return sketcher_.time();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the time of running integrator.
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
double Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::integratorTime() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return integrator_.time();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the time of running former.
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
double Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::formerTime() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return former_.time();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of iterator when running integrator.
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
index_t Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::integratorIteration() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return integrator_.iteration();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the approximate singular values.
///
/// @attention  The solver should have be computed.
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
const DenseVector<RealScalarT<_Scalar>>&
    Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::singularValues() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return former_.vectorS();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the approximate left singular vectors.
///
/// @attention  The solver should have be computed.
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
const DenseMatrixColMajor<_Scalar>&
    Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::leftSingularVectors() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return former_.matrixU();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the approximate right singular vectors.
///
/// @attention  The solver should have be computed.
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
const DenseMatrixColMajor<_Scalar>&
    Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::rightSingularVectors() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return former_.matrixVt();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the integrated orthogonal basis of the sketched subspace.
///
/// @attention  The solver should have be computed.
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
const DenseMatrixRowMajor<_Scalar>&
    Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::integratedOrthogonalBasis() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return integrator_.matrixQ();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the parameters.
///
/// @attention  Only affects on root node.
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
const typename Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::ParametersType&
    Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::parameters() const noexcept {
  mcnla_assert_true(mpi::isCommRoot(mpi_root_, mpi_comm_));
  return parameters_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the sizes of the matrix.
///
/// @attention  Only affects on root node.
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>&
  Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::setSize(
    const index_t nrow,
    const index_t ncol
) noexcept {
  if ( !mpi::isCommRoot(mpi_root_, mpi_comm_) ) {
    return *this;
  }
  parameters_.nrow_ = nrow;
  parameters_.ncol_ = ncol;
  parameters_.initialized_ = false;
  parameters_.computed_ = false;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  setSize
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
template <class _Matrix>
Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>&
  Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::setSize(
    const _Matrix &matrix
) noexcept {
  return setSize(matrix.nrow(), matrix.ncol());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the desired rank of approximate SVD.
///
/// @attention  Only affects on root node.
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>&
  Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::setRank(
    const index_t rank
) noexcept {
  if ( !mpi::isCommRoot(mpi_root_, mpi_comm_) ) {
    return *this;
  }
  parameters_.rank_ = rank;
  parameters_.initialized_ = false;
  parameters_.computed_ = false;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the dimension of random sketches.
///
/// @attention  Only affects on root node.
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>&
  Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::setOverRank(
    const index_t over_rank
  ) noexcept {
  if ( !mpi::isCommRoot(mpi_root_, mpi_comm_) ) {
    return *this;
  }
  parameters_.over_rank_ = over_rank;
  parameters_.initialized_ = false;
  parameters_.computed_ = false;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the number of total random sketches
///
/// @attention  @a num_sketch must be a multiple of @link mcnla::mpi::commSize mpi_size@endlink.
/// @attention  Only affects on root node.
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>&
  Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::setNumSketch(
    const index_t num_sketch
) noexcept {
  if ( !mpi::isCommRoot(mpi_root_, mpi_comm_) ) {
    return *this;
  }
  parameters_.num_sketch_each_ = num_sketch / parameters_.mpi_rank_;
  parameters_.initialized_ = false;
  parameters_.computed_ = false;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the number of random sketches per MPI node.
///
/// @attention  Only affects on root node.
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>&
  Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::setNumSketchEach(
    const index_t num_sketch_each
) noexcept {
  if ( !mpi::isCommRoot(mpi_root_, mpi_comm_) ) {
    return *this;
  }
  parameters_.num_sketch_each_ = num_sketch_each;
  parameters_.initialized_ = false;
  parameters_.computed_ = false;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the maximum number of iteration
///
/// @attention  Only affects on root node.
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>&
  Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::setMaxIteration(
    const index_t max_iteration
) noexcept {
  if ( !mpi::isCommRoot(mpi_root_, mpi_comm_) ) {
    return *this;
  }
  parameters_.max_iteration_ = max_iteration;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the tolerance of converge condition.
///
/// @attention  Only affects on root node.
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>&
  Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::setTolerance(
    const RealScalarType tolerance
) noexcept {
  if ( !mpi::isCommRoot(mpi_root_, mpi_comm_) ) {
    return *this;
  }
  parameters_.tolerance_ = tolerance;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the random seed.
///
/// @attention  Affects on current node only.
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>&
  Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::setSeed(
    const index_t seed
) noexcept {
  sketcher_.setSeed(seed);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Generate the random seeds and send to each MPI nodes.
///
/// @attention  Affects on all MPI nodes.
///
template <class _Scalar, class _SketcherTag, class _OrthogonalizerTag, class _IntegratorTag, class _FormerTag>
Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>&
  Solver<_Scalar, _SketcherTag, _OrthogonalizerTag, _IntegratorTag, _FormerTag>::setSeeds(
    const index_t seed
) noexcept {
  sketcher_.setSeeds(seed);
  return *this;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SOLVER_SOLVER_HPP_
