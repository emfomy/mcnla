////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/kolmogorov_nagumo_integrator.ipp
/// @brief   The implementation of Kolmogorov-Nagumo-type integrator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_KOLMOGOROV_NAGUMO_INTEGRATOR_IPP_
#define MCNLA_ISVD_INTEGRATOR_KOLMOGOROV_NAGUMO_INTEGRATOR_IPP_

#include <mcnla/isvd/integrator/kolmogorov_nagumo_integrator.hpp>
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
KolmogorovNagumoIntegrator<_Matrix>::KolmogorovNagumoIntegrator(
    const Parameters<ScalarType> &parameters
) noexcept : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::initialize
///
template <class _Matrix>
void KolmogorovNagumoIntegrator<_Matrix>::initializeImpl() noexcept {

  const auto mpi_size        = parameters_.mpi_size;
  const auto nrow            = parameters_.getNrow();
  const auto num_sketch      = parameters_.getNumSketch();
  const auto num_sketch_each = parameters_.getNumSketchEach();
  const auto dim_sketch      = parameters_.getDimSketch();

  time0_ = 0;
  time1_ = 0;
  time2_ = 0;
  time3_ = 0;

  nrow_each_ = (nrow-1) / mpi_size + 1;
  nrow_all_  = nrow_each_ * mpi_size;
  iter_      = -1;

  const auto set_q_sizes = std::make_tuple(nrow_all_, dim_sketch, num_sketch_each);
  if ( set_q_.getSizes() != set_q_sizes || !set_q_.isShrunk() ) {
    set_q_ = DenseMatrixSet120<ScalarType>(set_q_sizes);
  }
  set_q_cut_ = set_q_.getMatrixRows({0, nrow});
  matrix_qs_ = set_q_.unfold();

  const auto matrix_qjs_sizes = std::make_pair(nrow_each_, dim_sketch * num_sketch);
  if ( matrix_qjs_.getSizes() != matrix_qjs_sizes || !matrix_qjs_.isShrunk() ) {
    matrix_qjs_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_qjs_sizes);
  }

  const auto matrix_qc_sizes = std::make_pair(nrow_all_, dim_sketch);
  if ( matrix_qc_.getSizes() != matrix_qc_sizes || !matrix_qc_.isShrunk() ) {
    matrix_qc_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_qc_sizes);
  }
  matrix_qc_cut_ = matrix_qc_.getRows({0, nrow});

  const auto matrix_qcj_sizes = std::make_pair(nrow_each_, dim_sketch);
  if ( matrix_qcj_.getSizes() != matrix_qcj_sizes ) {
    matrix_qcj_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_qcj_sizes);
  }
  if ( matrix_xj_.getSizes() != matrix_qcj_sizes ) {
    matrix_xj_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_qcj_sizes);
  }
  if ( matrix_tmp_.getSizes() != matrix_qcj_sizes ) {
    matrix_tmp_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_qcj_sizes);
  }

  const auto matrix_bs_sizes = std::make_pair(dim_sketch, dim_sketch * num_sketch);
  if ( matrix_bs_.getSizes() != matrix_bs_sizes || !matrix_bs_.isShrunk() ) {
    matrix_bs_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_bs_sizes);
  }

  const auto matrix_c_sizes = std::make_pair(dim_sketch, dim_sketch);
  if ( matrix_c_.getSizes() != matrix_c_sizes ) {
    matrix_c_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_c_sizes);
  }
  if ( matrix_d_.getSizes() != matrix_c_sizes ) {
    matrix_d_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_c_sizes);
  }
  if ( matrix_f_.getSizes() != matrix_c_sizes ) {
    matrix_f_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_c_sizes);
  }

  const auto vector_e_sizes = dim_sketch;
  if ( vector_e_.getSizes() != vector_e_sizes ) {
    vector_e_ = DenseVector<ScalarType>(vector_e_sizes);
  }

  const auto syev_sizes = dim_sketch;
  if ( syev_driver_.getSizes() != syev_sizes ) {
    syev_driver_.resize(syev_sizes);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::integrate
///
template <class _Matrix>
void KolmogorovNagumoIntegrator<_Matrix>::integrateImpl() noexcept {
  mcnla_assert_true(parameters_.isInitialized());

  const auto mpi_comm        = parameters_.mpi_comm;
  const auto mpi_size        = parameters_.mpi_size;
  const auto mpi_root        = parameters_.mpi_root;
  const auto nrow            = parameters_.getNrow();
  const auto dim_sketch      = parameters_.getDimSketch();
  const auto num_sketch_each = parameters_.getNumSketchEach();
  const auto num_sketch      = parameters_.getNumSketch();
  const auto max_iteration   = parameters_.getMaxIteration();
  const auto tolerance       = parameters_.getTolerance();

  time0_ = MPI_Wtime();

  // Exchange Q
  blas::memset0(set_q_.getMatrixRows({nrow, nrow_all_}).unfold());
  mpi::alltoall(set_q_.unfold(), mpi_comm);

  // Reform Qj
  for ( index_t j = 0; j < mpi_size; ++j ) {
    blas::omatcopy(1.0, matrix_qs_.getRows(IdxRange{j, j+1} * nrow_each_),
                        matrix_qjs_.getCols(IdxRange{j, j+1} * dim_sketch * num_sketch_each));
  }

  // Qc := Q0
  blas::omatcopy(1.0, matrix_qjs_.getCols({0, dim_sketch}), matrix_qcj_);

  time1_ = MPI_Wtime();

  bool is_converged = false;
  for ( iter_ = 0; iter_ < max_iteration && !is_converged; ++iter_ ) {

    // ================================================================================================================== //
    // X = (I - Qc * Qc') * sum(Qi * Qi')/N * Qc

    // Bs := sum( Qcj' * Qjs )
    blas::gemm<TransOption::TRANS, TransOption::NORMAL>(1.0, matrix_qcj_, matrix_qjs_, 0.0, matrix_bs_);
    mpi::allreduce(matrix_bs_, MPI_SUM, mpi_comm);

    // D  := Bs' * Bs
    blas::syrk<TransOption::NORMAL>(1.0, matrix_bs_, 0.0, matrix_d_);

    // Xj := 1/N * Qjs * Bs'
    blas::gemm<TransOption::NORMAL, TransOption::TRANS>(1.0/num_sketch, matrix_qjs_, matrix_bs_, 0.0, matrix_xj_);

    // Xj -= 1/N * Qcj * D
    blas::symm<SideOption::RIGHT>(-1.0/num_sketch, matrix_d_, matrix_qcj_, 1.0, matrix_xj_);

    // ================================================================================================================== //
    // C := sqrt( I/2 + sqrt( I/4 - X' * X ) )

    // D := I/4 - sum(Xj' * Xj)
    blas::syrk<TransOption::TRANS>(-1.0, matrix_xj_, 0.0, matrix_d_);
    mpi::allreduce(matrix_d_, MPI_SUM, mpi_comm);
    for ( index_t i = 0; i < dim_sketch; ++i ) {
      matrix_d_(i, i) += 0.25;
    }

    // Compute the eigen-decomposition of D -> D' * E * D
    syev_driver_(matrix_d_, vector_e_);

    // D := E^(1/4) * D
    for ( index_t i = 0; i < dim_sketch; ++i ) {
      blas::scal(std::pow(vector_e_(i), 0.25), matrix_d_.getRow(i));
    }

    // F := I/2 + D' * D
    blas::syrk<TransOption::TRANS>(1.0, matrix_d_, 0.0, matrix_f_);
    for ( index_t i = 0; i < dim_sketch; ++i ) {
      matrix_f_(i, i) += 0.5;
    }

    // Compute the eigen-decomposition of F -> F' * E * F
    syev_driver_(matrix_f_, vector_e_);

    // D := F
    blas::copy(matrix_f_, matrix_d_);

    // F := E^(1/4) * F; D := E^(-1/4) * D
    for ( index_t i = 0; i < dim_sketch; ++i ) {
      blas::scal(std::pow(vector_e_(i),  0.25), matrix_f_.getRow(i));
      blas::scal(std::pow(vector_e_(i), -0.25), matrix_d_.getRow(i));
    }

    // C := F' * F
    blas::syrk<TransOption::TRANS>(1.0, matrix_f_, 0.0, matrix_c_);

    // inv(C) := D' * D
    blas::syrk<TransOption::TRANS>(1.0, matrix_d_, 0.0, matrix_f_);

    // ================================================================================================================== //
    // Qc := Qc * C + X * inv(C)

    // Qcj := Qcj * C
    blas::copy(matrix_qcj_, matrix_tmp_);
    blas::symm<SideOption::RIGHT>(1.0, matrix_c_, matrix_tmp_, 0.0, matrix_qcj_);

    // Qcj += Xj * inv(C)
    blas::symm<SideOption::RIGHT>(1.0, matrix_f_, matrix_xj_, 1.0, matrix_qcj_);

    // ================================================================================================================== //
    // Check convergence
    for ( index_t i = 0; i < dim_sketch; ++i ) {
      vector_e_(i) = std::sqrt(vector_e_(i)) - 1.0;
    }
    is_converged = !(blas::nrm2(vector_e_) / std::sqrt(dim_sketch) > tolerance);
  }

  time2_ = MPI_Wtime();

  // Gather Qc
  mpi::gather(matrix_qcj_, matrix_qc_, mpi_root, mpi_comm);

  time3_ = MPI_Wtime();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getName
///
template <class _Matrix>
constexpr const char* KolmogorovNagumoIntegrator<_Matrix>::getNameImpl() const noexcept {
  return name_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getTime
///
template <class _Matrix>
double KolmogorovNagumoIntegrator<_Matrix>::getTimeImpl() const noexcept {
  return time3_-time0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getTimes
///
template <class _Matrix>
const std::vector<double> KolmogorovNagumoIntegrator<_Matrix>::getTimesImpl() const noexcept {
  return {time1_-time0_, time2_-time1_, time3_-time2_};
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getIter
///
template <class _Matrix>
index_t KolmogorovNagumoIntegrator<_Matrix>::getIterImpl() const noexcept {
  return iter_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getSetQ
///
template <class _Matrix>
DenseMatrixSet120<typename KolmogorovNagumoIntegrator<_Matrix>::ScalarType>&
    KolmogorovNagumoIntegrator<_Matrix>::getSetQImpl() noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return set_q_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getSetQ
///
template <class _Matrix>
const DenseMatrixSet120<typename KolmogorovNagumoIntegrator<_Matrix>::ScalarType>&
    KolmogorovNagumoIntegrator<_Matrix>::getSetQImpl() const noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return set_q_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getMatrixQbar
///
template <class _Matrix>
DenseMatrix<typename KolmogorovNagumoIntegrator<_Matrix>::ScalarType, Layout::ROWMAJOR>&
    KolmogorovNagumoIntegrator<_Matrix>::getMatrixQbarImpl() noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return matrix_qc_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getMatrixQbar
///
template <class _Matrix>
const DenseMatrix<typename KolmogorovNagumoIntegrator<_Matrix>::ScalarType, Layout::ROWMAJOR>&
    KolmogorovNagumoIntegrator<_Matrix>::getMatrixQbarImpl() const noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return matrix_qc_cut_;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_KOLMOGOROV_NAGUMO_INTEGRATOR_IPP_
