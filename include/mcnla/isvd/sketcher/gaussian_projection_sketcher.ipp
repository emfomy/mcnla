////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/gaussian_projection_sketcher.ipp
/// @brief   The implementation of Gaussian projection sketcher.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_IPP_
#define MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_IPP_

#include <mcnla/isvd/sketcher/gaussian_projection_sketcher.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherBase::SketcherBase
///
template <class _Matrix>
GaussianProjectionSketcher<_Matrix>::GaussianProjectionSketcher(
    const Parameters<ScalarType> &parameters, index_t *seed
) noexcept : BaseType(parameters, seed) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherBase::initialize
///
template <class _Matrix>
void GaussianProjectionSketcher<_Matrix>::initializeImpl() noexcept {

  const auto nrow            = parameters_.nrow();
  const auto ncol            = parameters_.ncol();
  const auto num_sketch_each = parameters_.nvecumSketchEach();
  const auto dim_sketch      = parameters_.dimSketch();

  time0_ = 0;
  time1_ = 0;
  time2_ = 0;
  time3_ = 0;

  const auto set_omega_sizes = std::make_tuple(ncol, dim_sketch, num_sketch_each);
  if ( set_omega_.sizes() != set_omega_sizes ) {
    set_omega_ = DenseMatrixSet120<ScalarType>(set_omega_sizes);
  }

  const auto vector_s_sizes = dim_sketch;
  if ( vector_s_.sizes() != vector_s_sizes ) {
    vector_s_ = DenseVector<RealScalarType>(vector_s_sizes);
  }

  const auto gesvd_sizes = std::make_pair(nrow, dim_sketch);
  if ( gesvd_driver_.sizes() != gesvd_sizes ) {
    gesvd_driver_.resize(gesvd_sizes);
  }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherBase::sketch
///
template <class _Matrix>
void GaussianProjectionSketcher<_Matrix>::sketchImpl(
    const _Matrix &matrix_a,
          DenseMatrixSet120<ScalarType> &set_q
) noexcept {

  mcnla_assert_true(parameters_.isInitialized());

  const auto nrow            = parameters_.nrow();
  const auto ncol            = parameters_.ncol();
  const auto num_sketch_each = parameters_.nvecumSketchEach();
  const auto dim_sketch      = parameters_.dimSketch();

  mcnla_assert_eq(matrix_a.sizes(), std::make_pair(nrow, ncol));
  mcnla_assert_eq(set_q.sizes(),    std::make_tuple(nrow, dim_sketch, num_sketch_each));

  time0_ = MPI_Wtime();

  // Random sample Omega using normal Gaussian distribution
  lapack::larnv<3>(set_omega_.unfold().vectorize(), this->seed_);
  time1_ = MPI_Wtime();

  // Q := A * Omega
  blas::gemm(1.0, matrix_a, set_omega_.unfold(), 0.0, set_q.unfold());
  time2_ = MPI_Wtime();

  // Compute the left singular vectors of Q
  for ( index_t i = 0; i < num_sketch_each; ++i ) {
    gesvd_driver_(set_q(i), vector_s_, matrix_empty_, matrix_empty_);
  }
  time3_ = MPI_Wtime();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherBase::nvecame
///
template <class _Matrix>
constexpr const char* GaussianProjectionSketcher<_Matrix>::nvecameImpl() const noexcept {
  return name_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherBase::getTime
///
template <class _Matrix>
double GaussianProjectionSketcher<_Matrix>::getTimeImpl() const noexcept {
  return time3_-time0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherBase::getTimes
///
template <class _Matrix>
const std::vector<double> GaussianProjectionSketcher<_Matrix>::getTimesImpl() const noexcept {
  return {time1_-time0_, time2_-time1_, time3_-time2_};
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_IPP_
