////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/kolmogorov_nagumo_type_integrator.ipp
/// @brief   The implementation of Kolmogorov-Nagumo-type integrator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_KOLMOGOROV_NAGUMO_TYPE_INTEGRATOR_IPP_
#define MCNLA_ISVD_INTEGRATOR_KOLMOGOROV_NAGUMO_TYPE_INTEGRATOR_IPP_

#include <mcnla/isvd/integrator/kolmogorov_nagumo_type_integrator.hpp>
#include <cmath>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::IntegratorBase
///
template <class _Matrix>
KolmogorovNagumoTypeIntegrator<_Matrix>::KolmogorovNagumoTypeIntegrator(
    const Parameters<ScalarType> &parameters
) noexcept : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::initialize
///
template <class _Matrix>
void KolmogorovNagumoTypeIntegrator<_Matrix>::initializeImpl() noexcept {

  nrow_each_ = (parameters_.getNrow()-1) / parameters_.mpi_size + 1;
  nrow_all_  = nrow_each_ * parameters_.mpi_size;
  iter_      = -1;

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
  matrix_b_ = cube_b_.getPage(0);

  const auto matrix_b_sizes = matrix_b_.getSizes();
  if ( matrix_d_.getSizes() != matrix_b_sizes ) {
    matrix_d_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_b_sizes);
  }
  if ( matrix_c_.getSizes() != matrix_b_sizes ) {
    matrix_c_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_b_sizes);
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
/// @copydoc  mcnla::isvd::IntegratorBase::integrate
///
template <class _Matrix>
void KolmogorovNagumoTypeIntegrator<_Matrix>::integrateImpl() noexcept {
  mcnla_assert_true(parameters_.isInitialized());

  const auto mpi_comm = parameters_.mpi_comm;
  const auto mpi_size = parameters_.mpi_size;
  const auto mpi_root = parameters_.mpi_root;
  const auto num_sketch    = parameters_.getNumSketch();
  const auto dim_sketch    = parameters_.getDimSketch();
  const auto max_iteration = parameters_.getMaxIteration();
  const auto tolerance     = parameters_.getTolerance();

  // Exchange Q
  for ( index_t i = 0; i < cube_q_.getNpage(); ++i ) {
    blas::memset0(cube_q_.getPage(i).getRows({parameters_.getNrow(), nrow_all_}));
    mpi::alltoall(cube_q_.getPage(i), cube_qj_.getPages({i*mpi_size, (i+1)*mpi_size}), mpi_comm);
  }

  // Qc := Q0
  blas::copy(cube_qj_.getPage(0), matrix_qcj_);

  bool is_converged = false;
  for ( iter_ = 0; iter_ < max_iteration && !is_converged; ++iter_ ) {

    // ================================================================================================================== //
    // X = (I - Qc * Qc') * sum(Qi * Qi')/N * Qc

    // Bi := sum( Qij' * Qcj )
    for ( index_t i = 0; i < num_sketch; ++i ) {
      blas::gemm<TransOption::TRANS, TransOption::NORMAL>(1.0, cube_qj_.getPage(i), matrix_qcj_, 0.0, cube_b_.getPage(i));
    }
    mpi::allreduce(cube_b_, MPI_SUM, mpi_comm);

    // Xj := 0; D := 0
    blas::memset0(matrix_xj_);
    blas::memset0(matrix_d_);

    for ( index_t i = 0; i < num_sketch; ++i ) {
      // D += Bi' * Bi
      blas::syrk<TransOption::TRANS>(1.0, cube_b_.getPage(i), 1.0, matrix_d_);

      // Xj += Qij * Bi
      blas::gemm<TransOption::NORMAL, TransOption::NORMAL>(1.0, cube_qj_.getPage(i), cube_b_.getPage(i), 1.0, matrix_xj_);
    }

    // Xj -= Qcj * D
    blas::symm<SideOption::RIGHT>(-1.0, matrix_d_, matrix_qcj_, 1.0, matrix_xj_);

    // Xj /= N
    blas::scal(1.0/num_sketch, matrix_xj_.vectorize());

    // ================================================================================================================== //
    // C := sqrt( I/2 + sqrt( I/4 - X' * X ) )

    // B := I/4 - sum(Xj' * Xj)
    blas::syrk<TransOption::TRANS>(-1.0, matrix_xj_, 0.0, matrix_b_);
    mpi::allreduce(matrix_b_, MPI_SUM, mpi_comm);
    for ( index_t i = 0; i < dim_sketch; ++i ) {
      matrix_b_(i, i) += 0.25;
    }

    // Compute the eigen-decomposition of B -> B' * E * B
    syev_driver_(matrix_b_, vector_e_);

    // B := E^(1/4) * B
    for ( index_t i = 0; i < dim_sketch; ++i ) {
      blas::scal(pow(vector_e_(i), 0.25), matrix_b_.getRow(i));
    }

    // D := I/2 + B' * B
    blas::syrk<TransOption::TRANS>(1.0, matrix_b_, 0.0, matrix_d_);
    for ( index_t i = 0; i < dim_sketch; ++i ) {
      matrix_d_(i, i) += 0.5;
    }

    // Compute the eigen-decomposition of D -> D' * E * D
    syev_driver_(matrix_d_, vector_e_);

    // B := D
    blas::copy(matrix_d_, matrix_b_);

    // D := E^(1/4) * D; B := E^(-1/4) * B
    for ( index_t i = 0; i < dim_sketch; ++i ) {
      blas::scal(pow(vector_e_(i),  0.25), matrix_d_.getRow(i));
      blas::scal(pow(vector_e_(i), -0.25), matrix_b_.getRow(i));
    }

    // C := D' * D
    blas::syrk<TransOption::TRANS>(1.0, matrix_d_, 0.0, matrix_c_);

    // inv(C) := B' * B
    blas::syrk<TransOption::TRANS>(1.0, matrix_b_, 0.0, matrix_d_);

    // ================================================================================================================== //
    // Qc := Qc * C + X * inv(C)

    // Qcj := Qcj * C
    blas::copy(matrix_qcj_, matrix_tmp_);
    blas::symm<SideOption::RIGHT>(1.0, matrix_c_, matrix_tmp_, 0.0, matrix_qcj_);

    // Qcj += Xj * inv(C)
    blas::symm<SideOption::RIGHT>(1.0, matrix_d_, matrix_xj_, 1.0, matrix_qcj_);

    // ================================================================================================================== //
    // Check convergence
    if ( mpi::isCommRoot(mpi_root, mpi_comm) ) {
      vector_e_.getValueValarray() = std::sqrt(vector_e_.getValueValarray()) - 1.0;
      is_converged = !(blas::nrm2(vector_e_) / std::sqrt(dim_sketch) > tolerance);
    }
    MPI_Bcast(&is_converged, 1, MPI_BYTE, mpi_root, mpi_comm);
  }

  // Gather Qc
  mpi::gather(matrix_qcj_, matrix_qc_, mpi_root, mpi_comm);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getName
///
template <class _Matrix>
constexpr const char* KolmogorovNagumoTypeIntegrator<_Matrix>::getNameImpl() const noexcept {
  return name_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getIter
///
template <class _Matrix>
index_t KolmogorovNagumoTypeIntegrator<_Matrix>::getIterImpl() const noexcept {
  return iter_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getCubeQ
///
template <class _Matrix>
DenseCube<typename KolmogorovNagumoTypeIntegrator<_Matrix>::ScalarType, Layout::ROWMAJOR>&
    KolmogorovNagumoTypeIntegrator<_Matrix>::getCubeQImpl() noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return cube_q_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getCubeQ
///
template <class _Matrix>
const DenseCube<typename KolmogorovNagumoTypeIntegrator<_Matrix>::ScalarType, Layout::ROWMAJOR>&
    KolmogorovNagumoTypeIntegrator<_Matrix>::getCubeQImpl() const noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return cube_q_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getMatrixQc
///
template <class _Matrix>
DenseMatrix<typename KolmogorovNagumoTypeIntegrator<_Matrix>::ScalarType, Layout::ROWMAJOR>&
    KolmogorovNagumoTypeIntegrator<_Matrix>::getMatrixQcImpl() noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return matrix_qc_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getMatrixQc
///
template <class _Matrix>
const DenseMatrix<typename KolmogorovNagumoTypeIntegrator<_Matrix>::ScalarType, Layout::ROWMAJOR>&
    KolmogorovNagumoTypeIntegrator<_Matrix>::getMatrixQcImpl() const noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return matrix_qc_cut_;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_KOLMOGOROV_NAGUMO_TYPE_INTEGRATOR_IPP_
