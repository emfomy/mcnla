////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/core/sketcher/gaussian_projection_sketcher.ipp
/// @brief   The implementation of Gaussian projection sketcher.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_CORE_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_IPP_
#define ISVD_CORE_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_IPP_

#include <isvd/core/sketcher/gaussian_projection_sketcher.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::SketcherBase::SketcherBase
///
template <class _Matrix>
GaussianProjectionSketcher<_Matrix>::GaussianProjectionSketcher(
    const internal::Parameters<ScalarType> &parameters
) noexcept : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::SketcherBase::initialize
///
template <class _Matrix>
void GaussianProjectionSketcher<_Matrix>::initializeImpl() noexcept {

  const auto matrix_omega_sizes = std::make_pair(parameters_.getNcol(), parameters_.getDimSketch());
  if ( matrix_omega_.getSizes() != matrix_omega_sizes ) {
    matrix_omega_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_omega_sizes);
  }

  const auto vector_s_sizes = parameters_.getDimSketch();
  if ( vector_s_.getSizes() != vector_s_sizes ) {
    vector_s_ = DenseVector<RealScalarType>(vector_s_sizes);
  }

  const auto gesvd_sizes = std::make_pair(parameters_.getNrow(), parameters_.getDimSketch());
  if ( gesvd_driver_.getSizes() != gesvd_sizes ) {
    gesvd_driver_.resize(gesvd_sizes);
  }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::SketcherBase::sketch
///
template <class _Matrix>
void GaussianProjectionSketcher<_Matrix>::sketchImpl(
    const _Matrix &matrix_a,
          DenseCube<ScalarType, Layout::ROWMAJOR> &cube_q
) noexcept {
  assert(parameters_.isInitialized());
  assert(matrix_a.getSizes() == std::make_pair(parameters_.getNrow(), parameters_.getNcol()));
  assert(cube_q.getSizes()   == std::make_tuple(parameters_.getNrow(), parameters_.getDimSketch(), parameters_.getNumSketch()));

  for ( auto i = 0; i < parameters_.getNumSketch(); ++i ) {
    lapack::larnv<3>(matrix_omega_.vectorize(), parameters_.getSeed());
    blas::gemm(1.0, matrix_a, matrix_omega_, 0.0, cube_q.getPage(i));
    gesvd_driver_(cube_q.getPage(i), vector_s_, matrix_empty_, matrix_empty_);
  }
}

}  // namespace isvd

#endif  // ISVD_CORE_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_IPP_
