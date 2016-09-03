////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/core/sketcher/gaussian_projection_sketcher.ipp
/// @brief   The implementation of Gaussian projection sketcher.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_CORE_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_IPP_
#define ISVD_CORE_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_IPP_

#include <isvd/core/sketcher/gaussian_projection_sketcher.hpp>
#include <isvd/blas.hpp>
#include <isvd/lapack.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given parameters.
///
template <class _Matrix>
GaussianProjectionSketcher<_Matrix>::GaussianProjectionSketcher(
    const internal::Parameters<RealScalarType> &parameters
) noexcept : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Initializes.
///
template <class _Matrix>
void GaussianProjectionSketcher<_Matrix>::initializeImpl() noexcept {

  if ( matrix_omega_.getNrow() != parameters_.getNcol() ||
       matrix_omega_.getNcol() != parameters_.getDimSketch() ) {
    matrix_omega_ = DenseMatrixType(parameters_.getNcol(), parameters_.getDimSketch());
  }

  if ( vector_s_.getLength() != parameters_.getDimSketch() ) {
    vector_s_ = DenseVectorType(parameters_.getDimSketch());
  }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Random sketches.
///
template <class _Matrix>
void GaussianProjectionSketcher<_Matrix>::sketchImpl(
    const _Matrix &matrix_a,
          DenseCubeType &cube_q
) noexcept {
  assert(parameters_.isInitialized());
  assert(matrix_a.getNcol() == matrix_omega_.getNrow());
  assert(cube_q.getNrow()   == matrix_a.getNrow());
  assert(cube_q.getNcol()   == matrix_omega_.getNcol());
  assert(cube_q.getNpage()  == parameters_.getNumSketch());

  lapack::GesvdDriver<_Matrix, 'O', 'N'> gesvd_driver(cube_q.getPage(0));
  _Matrix matrix_empty;

  for ( auto i = 0; i < parameters_.getNumSketch(); ++i ) {
    lapack::larnv<3>(matrix_omega_.vectorize(), parameters_.getSeed());
    blas::gemm<TransOption::NORMAL, TransOption::TRANS>(1.0, matrix_a, matrix_omega_, 0.0, cube_q.getPage(i));
    gesvd_driver(cube_q.getPage(i), vector_s_, matrix_empty, matrix_empty);
  }
  #pragma warning "todo"
}

}  // namespace isvd

#endif  // ISVD_CORE_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_IPP_
