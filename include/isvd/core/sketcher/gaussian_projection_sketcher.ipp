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

  matrix_omega_ = DenseMatrixType(parameters_.getNrow(), parameters_.getDimSketch());
  matrix_tau_   = DenseVectorType(parameters_.getDimSketch());

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
  assert(cube_q.getNrow() == matrix_a.getNrow());
  assert(cube_q.getNcol() == matrix_omega_.getNcol());
  assert(cube_q.getNpage() == parameters_.getNumSketch());

  for ( auto i = 0; i < parameters_.getNumSketch(); ++i ) {
    // LAPACKE_dlarnv(3, iseed, k*n, matrix_oit);
    // cblas_dgemm(CblasColMajor, CblasNoTrans, CblasTrans,
    //             k, m0, n, 1.0, matrix_oit, k, matrix_a, m0, 0.0, matrices_qjt+i*k*m, k);
    // LAPACKE_dgeqrf(LAPACK_ROW_MAJOR, m0, k, matrices_qjt+i*k*m, k, vector_tau);
    // LAPACKE_dorgqr(LAPACK_ROW_MAJOR, m0, k, k, matrices_qjt+i*k*m, k, vector_tau);

    lapack::larnv<3>(matrix_omega_, parameters_.getSeed());
    blas::gemm(1.0, matrix_a, matrix_omega_, 0.0, cube_q.getPage(i));
  }
  #pragma warning "todo"
}

}  // namespace isvd

#endif  // ISVD_CORE_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_IPP_
