////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/gaussian_projection_sketcher.hpp
/// @brief   The Gaussian projection sketcher.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HPP_
#define MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HPP_

#include <mcnla/isvd/sketcher/gaussian_projection_sketcher.hh>
#include <ctime>
#include <mcnla/core/la.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::SketcherWrapper
///
template <typename _Val, index_t _exponent>
Sketcher<GaussianProjectionSketcherTag<_exponent>, _Val>::Sketcher(
    const ParametersType &parameters,
    const MPI_Comm mpi_comm,
    const mpi_int_t mpi_root,
    const index_t seed
) noexcept
  : BaseType(parameters, mpi_comm, mpi_root),
    random_driver_(seed) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::initialize
///
template <typename _Val, index_t _exponent>
void Sketcher<GaussianProjectionSketcherTag<_exponent>, _Val>::initializeImpl() noexcept {

  const auto ncol            = parameters_.ncol();
  const auto num_sketch_each = parameters_.numSketchEach();
  const auto dim_sketch      = parameters_.dimSketch();

  time0_ = 0;
  time1_ = 0;
  time2_ = 0;

  matrix_omegas_.reconstruct(ncol, dim_sketch * num_sketch_each);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::sketch
///
template <typename _Val, index_t _exponent> template <class _Matrix>
void Sketcher<GaussianProjectionSketcherTag<_exponent>, _Val>::sketchImpl(
    const _Matrix &matrix_a,
          DenseMatrixCollection120<ValType> &collection_q
) noexcept {

  mcnla_assert_true(parameters_.isInitialized());

  const auto nrow            = parameters_.nrow();
  const auto ncol            = parameters_.ncol();
  const auto num_sketch_each = parameters_.numSketchEach();
  const auto dim_sketch      = parameters_.dimSketch();

  mcnla_assert_eq(matrix_a.sizes(), std::make_tuple(nrow, ncol));
  mcnla_assert_eq(collection_q.sizes(),    std::make_tuple(nrow, dim_sketch, num_sketch_each));

  time0_ = MPI_Wtime();

  // Random sample Omega using normal Gaussian distribution
  random_driver_.gaussian(matrix_omegas_.vectorize());
  time1_ = MPI_Wtime();

  // Q := A * Omega
  la::mm(matrix_a, matrix_omegas_, collection_q.unfold());
  for ( index_t i = 0; i < _exponent; ++i ) {
    la::mm(matrix_a.t(), collection_q.unfold(), matrix_omegas_);
    la::mm(matrix_a, matrix_omegas_, collection_q.unfold());
  }
  time2_ = MPI_Wtime();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::outputName
///
///
template <typename _Val, index_t _exponent>
std::ostream& Sketcher<GaussianProjectionSketcherTag<_exponent>, _Val>::outputNameImpl(
    std::ostream &os
) const noexcept {
  return (os << name_ << " (Power " << _exponent << ")");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::time
///
template <typename _Val, index_t _exponent>
double Sketcher<GaussianProjectionSketcherTag<_exponent>, _Val>::timeImpl() const noexcept {
  return time2_-time0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::time
///
template <typename _Val, index_t _exponent>
double Sketcher<GaussianProjectionSketcherTag<_exponent>, _Val>::time1() const noexcept {
  return time1_-time0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::time
///
template <typename _Val, index_t _exponent>
double Sketcher<GaussianProjectionSketcherTag<_exponent>, _Val>::time2() const noexcept {
  return time2_-time1_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::setSeed
///
template <typename _Val, index_t _exponent>
void Sketcher<GaussianProjectionSketcherTag<_exponent>, _Val>::setSeedImpl(
    const index_t seed
) noexcept {
  random_driver_.setSeed(seed);
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HPP_
