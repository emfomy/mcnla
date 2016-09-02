////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/core/solver.ipp
/// @brief   The implementation of iSVD solver.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_CORE_SOLVER_IPP_
#define ISVD_CORE_SOLVER_IPP_

#include <isvd/core/solver.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::Solver(
    const MPI_Comm mpi_comm
) noexcept
  : parameters_(mpi_comm),
    sketcher_(parameters_),
    integrator_(parameters_),
    reconstructor_(parameters_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Initializes.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
void Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::initialize() noexcept {
  assert(parameters_.getNcol() >= parameters_.getNrow() && parameters_.getNrow() > 0);
  assert(parameters_.getNrow() >= parameters_.getDimSketch());
  assert(parameters_.getRank() > 0 && parameters_.getOverRank() >= 0);
  assert(parameters_.getNumSketch() > 0);

  sketcher_.initialize();
  integrator_.initialize();
  reconstructor_.initialize();

  cube_q_ = DenseCubeType(parameters_.getNrow(), parameters_.getDimSketch(), parameters_.getNumSketch());

  parameters_.initialized_ = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the parameters.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
const internal::Parameters<typename Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::RealScalarType>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::getParameters() const noexcept {
  return parameters_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the sizes of the matrix.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::setSize( const index_t nrow, const index_t ncol ) noexcept {
  parameters_.nrow_ = nrow; parameters_.ncol_ = ncol;
  parameters_.initialized_ = false; return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  setSize
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::setSize( const _Matrix &matrix ) noexcept {
  return setSize(matrix.getNrow(), matrix.getNcol());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the desired rank of approximate SVD.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::setRank( const index_t rank ) noexcept {
  parameters_.rank_ = rank;
  parameters_.initialized_ = false; return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the dimension of random sketches.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::setOverRank( const index_t over_rank ) noexcept {
  parameters_.over_rank_ = over_rank;
  parameters_.initialized_ = false; return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the number of random sketches per MPI node.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::setNumSketch( const index_t num_sketch ) noexcept {
  parameters_.num_sketch_ = num_sketch;
  parameters_.initialized_ = false; return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the maximum iteration
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::setMaxIteration( const index_t max_iteration ) noexcept {
  parameters_.max_iteration_ = max_iteration;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the tolerance of converge condition.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::setTolerance( const RealScalarType tolerance ) noexcept {
  parameters_.tolerance_ = tolerance;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the random seed.
///
template <class _Matrix, class _Sketcher, class _Integrator, class _Reconstructor>
Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>&
    Solver<_Matrix, _Sketcher, _Integrator, _Reconstructor>::setSeed( const index_t seed[4] ) noexcept {
  for ( auto i = 0; i < 4; ++i ) {
    parameters_.seed_[i] = seed[i];
  }
  return *this;
}

}  // namespace isvd

#endif  // ISVD_CORE_SOLVER_IPP_
