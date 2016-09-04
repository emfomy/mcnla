////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/core/integrator/kolmogorov_nagumo_type_integrator.ipp
/// @brief   The implementation of Kolmogorov-Nagumo-type integrator.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_CORE_INTEGRATOR_KOLMOGOROV_NAGUMO_TYPE_INTEGRATOR_IPP_
#define ISVD_CORE_INTEGRATOR_KOLMOGOROV_NAGUMO_TYPE_INTEGRATOR_IPP_

#include <isvd/core/integrator/kolmogorov_nagumo_type_integrator.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::IntegratorBase::IntegratorBase
///
template <class _Matrix>
KolmogorovNagumoTypeIntegrator<_Matrix>::KolmogorovNagumoTypeIntegrator(
    const internal::Parameters<ScalarType> &parameters
) noexcept : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::IntegratorBase::initialize
///
template <class _Matrix>
void KolmogorovNagumoTypeIntegrator<_Matrix>::initializeImpl() noexcept {
  nrow_each_ = (parameters_.getNrow()-1) / parameters_.mpi_size + 1;
  nrow_all_  = nrow_each_ * parameters_.mpi_size;

  const auto cube_q_sizes = std::make_tuple(nrow_all_, parameters_.getDimSketch(), parameters_.getNumSketchEach());
  if ( cube_q_.getSizes() != cube_q_sizes || !cube_q_.isShrunk() ) {
    cube_q_ = DenseCube<ScalarType, Layout::ROWMAJOR>(cube_q_sizes);
  }
  cube_q_cut_ = cube_q_.getRowPages({0, parameters_.getNrow()});

  const auto cube_qj_sizes = std::make_tuple(nrow_each_, parameters_.getDimSketch(), parameters_.getNumSketch());
  if ( cube_qj_.getSizes() != cube_qj_sizes || !cube_qj_.isShrunk() ) {
    cube_qj_ = DenseCube<ScalarType, Layout::ROWMAJOR>(cube_qj_sizes);
  }

  const auto matrix_qc_sizes = std::make_pair(nrow_all_, parameters_.getDimSketch());
  if ( matrix_qc_.getSizes() != matrix_qc_sizes || !matrix_qc_.isShrunk() ) {
    matrix_qc_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_qc_sizes);
  }
  matrix_qc_cut_ = matrix_qc_.getRows({0, parameters_.getNrow()});

  const auto matrix_qcj_sizes = std::make_pair(nrow_each_, parameters_.getDimSketch());
  if ( matrix_qcj_.getSizes() != matrix_qcj_sizes ) {
    matrix_qcj_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_qcj_sizes);
  }
  if ( matrix_xj_.getSizes() != matrix_qcj_sizes ) {
    matrix_xj_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_qcj_sizes);
  }
  if ( matrix_tmp_.getSizes() != matrix_qcj_sizes ) {
    matrix_tmp_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_qcj_sizes);
  }

  const auto cube_b_sizes = std::make_tuple(parameters_.getDimSketch(), parameters_.getDimSketch(), parameters_.getNumSketch());
  if ( cube_b_.getSizes() != cube_b_sizes || !cube_b_.isShrunk() ) {
    cube_b_ = DenseCube<ScalarType, Layout::ROWMAJOR>(cube_b_sizes);
  }
  if ( cube_d_.getSizes() != cube_b_sizes || !cube_b_.isShrunk() ) {
    cube_d_ = DenseCube<ScalarType, Layout::ROWMAJOR>(cube_b_sizes);
  }

  const auto matrix_c_sizes = std::make_pair(parameters_.getDimSketch(), parameters_.getDimSketch());
  if ( matrix_c_.getSizes() != matrix_c_sizes ) {
    matrix_c_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_c_sizes);
  }

  const auto vector_e_sizes = parameters_.getDimSketch();
  if ( vector_e_.getSizes() != vector_e_sizes ) {
    vector_e_ = DenseVector<ScalarType>(vector_e_sizes);
  }

  const auto syev_sizes = parameters_.getDimSketch();
  if ( syev_driver_.getSizes() != syev_sizes ) {
    syev_driver_.resize(syev_sizes);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::IntegratorBase::integrate
///
template <class _Matrix>
void KolmogorovNagumoTypeIntegrator<_Matrix>::integrateImpl() noexcept {
  assert(parameters_.isInitialized());

  const auto mpi_size = parameters_.mpi_size;

  // Exchange Q
  for ( auto i = 0; i < cube_q_.getNpage(); ++i ) {
    cube_q_.getPage(i).getRows({parameters_.getNrow(), nrow_all_});
    mpi::Alltoall(cube_q_.getPage(i), cube_qj_.getPages({i*mpi_size, (i+1)*mpi_size}), parameters_.mpi_comm);
  }

  // Qc := Q[0-page]
  blas::copy(cube_qj_.getPage(0), matrix_qcj_);
#pragma todo

  // Gather Qc
  mpi::Gather(matrix_qcj_, matrix_qc_, parameters_.mpi_root, parameters_.mpi_comm);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::IntegratorBase::getCubeQ
///
template <class _Matrix>
DenseCube<typename KolmogorovNagumoTypeIntegrator<_Matrix>::ScalarType, Layout::ROWMAJOR>&
    KolmogorovNagumoTypeIntegrator<_Matrix>::getCubeQImpl() noexcept {
  assert(parameters_.isInitialized());
  return cube_q_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::IntegratorBase::integrate
///
template <class _Matrix>
DenseMatrix<typename KolmogorovNagumoTypeIntegrator<_Matrix>::ScalarType, Layout::ROWMAJOR>&
    KolmogorovNagumoTypeIntegrator<_Matrix>::getMatrixQcImpl() noexcept {
  assert(parameters_.isInitialized());
  return matrix_qc_cut_;
}

}  // namespace isvd

#endif  // ISVD_CORE_INTEGRATOR_KOLMOGOROV_NAGUMO_TYPE_INTEGRATOR_IPP_
