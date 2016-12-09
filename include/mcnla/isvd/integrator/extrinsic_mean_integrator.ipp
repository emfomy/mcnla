////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/extrinsic_mean_integrator.ipp
/// @brief   The implementation of extrinsic mean integrator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_EXTRINSIC_MEAN_INTEGRATOR_IPP_
#define MCNLA_ISVD_INTEGRATOR_EXTRINSIC_MEAN_INTEGRATOR_IPP_

#include <mcnla/isvd/integrator/extrinsic_mean_integrator.hpp>
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
ExtrinsicMeanIntegrator<_Matrix>::ExtrinsicMeanIntegrator(
    const Parameters<ScalarType> &parameters
) noexcept : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::initialize
///
template <class _Matrix>
void ExtrinsicMeanIntegrator<_Matrix>::initializeImpl() noexcept {

  const auto mpi_size        = parameters_.mpi_size;
  const auto nrow            = parameters_.getNrow();
  const auto num_sketch      = parameters_.getNumSketch();
  const auto num_sketch_each = parameters_.getNumSketchEach();
  const auto dim_sketch      = parameters_.getDimSketch();

  time0_ = 0;
  time1_ = 0;
  time2_ = 0;
  time3_ = 0;
  time4_ = 0;

  nrow_each_ = (nrow-1) / mpi_size + 1;
  nrow_all_  = nrow_each_ * mpi_size;

  const auto set_q_sizes = std::make_tuple(nrow_all_, dim_sketch, num_sketch_each);
  if ( set_q_.getSizes() != set_q_sizes || !set_q_.isShrunk() ) {
    set_q_ = DenseMatrixSet120<ScalarType>(set_q_sizes);
  }
  set_q_cut_ = set_q_.getMatrixRows({0, nrow});

  const auto matrix_tmp_sizes = std::make_pair(nrow_all_, dim_sketch * num_sketch_each);
  if ( matrix_tmp_.getSizes() != matrix_tmp_sizes ) {
    matrix_tmp_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_tmp_sizes);
  }

  const auto matrix_qjs_sizes = std::make_pair(nrow_each_, dim_sketch * num_sketch);
  if ( matrix_qjs_.getSizes() != matrix_qjs_sizes || !matrix_qjs_.isShrunk() ) {
    matrix_qjs_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_qjs_sizes);
  }

  const auto matrix_qbar_sizes = std::make_pair(nrow, dim_sketch);
  if ( matrix_qbar_.getSizes() != matrix_qbar_sizes || !matrix_qbar_.isShrunk() ) {
    matrix_qbar_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_qbar_sizes);
  }

  const auto matrix_bjs_sizes = std::make_pair(dim_sketch * num_sketch, dim_sketch * num_sketch);
  if ( matrix_bjs_.getSizes() != matrix_bjs_sizes || !matrix_bjs_.isShrunk() ) {
    matrix_bjs_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_bjs_sizes);
  }

  const auto matrix_bis_sizes = std::make_pair(dim_sketch * num_sketch_each, dim_sketch * num_sketch);
  if ( matrix_bis_.getSizes() != matrix_bis_sizes || !matrix_bis_.isShrunk() ) {
    matrix_bis_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_bis_sizes);
  }

  const auto set_g_sizes = std::make_tuple(dim_sketch, dim_sketch, num_sketch_each);
  if ( set_g_.getSizes() != set_g_sizes ) {
    set_g_ = DenseMatrixSet120<ScalarType>(set_g_sizes);
  }

  const auto matrix_g_sizes = std::make_pair(dim_sketch, dim_sketch);
  if ( matrix_g0_.getSizes() != matrix_g_sizes ) {
    matrix_g0_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_g_sizes);
  }
  if ( matrix_gb_.getSizes() != matrix_g_sizes ) {
    matrix_gb_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_g_sizes);
  }

  const auto vector_s_sizes = dim_sketch;
  if ( vector_s_.getSizes() != vector_s_sizes ) {
    vector_s_ = DenseVector<ScalarType>(vector_s_sizes);
  }

  const auto gesvd_sizes = std::make_pair(nrow, dim_sketch);
  if ( gesvd_driver_.getSizes() != gesvd_sizes ) {
    gesvd_driver_.resize(gesvd_sizes);
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
void ExtrinsicMeanIntegrator<_Matrix>::integrateImpl() noexcept {
  mcnla_assert_true(parameters_.isInitialized());

  const auto mpi_comm        = parameters_.mpi_comm;
  const auto mpi_size        = parameters_.mpi_size;
  const auto mpi_root        = parameters_.mpi_root;
  const auto mpi_rank        = mpi::getCommRank(mpi_comm);
  const auto nrow            = parameters_.getNrow();
  const auto dim_sketch      = parameters_.getDimSketch();
  const auto num_sketch_each = parameters_.getNumSketchEach();

  time0_ = MPI_Wtime();

  // Exchange Q
  blas::memset0(set_q_.getMatrixRows({nrow, nrow_all_}).unfold());
  mpi::alltoall(set_q_.unfold(), matrix_tmp_, mpi_comm);

  // Reform Qj
  for ( index_t j = 0; j < mpi_size; ++j ) {
    blas::omatcopy(1.0, matrix_tmp_.getRows(IdxRange{j, j+1} * nrow_each_),
                        matrix_qjs_.getCols(IdxRange{j, j+1} * dim_sketch * num_sketch_each));
  }

  time1_ = MPI_Wtime();

  // Bs := sum( Qjs' * Qjs )
  blas::gemm<TransOption::TRANS, TransOption::NORMAL>(1.0, matrix_qjs_, matrix_qjs_, 0.0, matrix_bjs_);
  mpi::reduceScatterBlock(matrix_bjs_, matrix_bis_, MPI_SUM, mpi_comm);

  time2_ = MPI_Wtime();

  for ( index_t i = 0; i < num_sketch_each; ++i ) {

    // Gi := Bis * Bis'
    blas::syrk<TransOption::NORMAL>(1.0, matrix_bis_.getRows(IdxRange{i, i+1}*dim_sketch), 0.0, set_g_(i));

    // Compute the eigen-decomposition of Gi -> Gi' * S * Gi
    syev_driver_(set_g_(i), vector_s_);

  }

  // Broadcast G0
  if ( mpi_rank == 0 ) {
    blas::omatcopy(1.0, set_g_(0), matrix_g0_);
  }
  mpi::bcast(matrix_g0_, 0, mpi_comm);

  time3_ = MPI_Wtime();

  // Qbar := 0
  blas::memset0(matrix_qbar_);

  for ( index_t i = 0; i < num_sketch_each; ++i ) {

    // Inverse Gi(j-row) if Gi(j-row) * Bi0 * G0(j-row)' < 0
    auto matirx_bi0 = matrix_bis_.getBlock(IdxRange{i, i+1}*dim_sketch, {0, dim_sketch});
    blas::gemm<TransOption::NORMAL, TransOption::TRANS>(1.0, matrix_g0_, matirx_bi0, 0.0, matrix_gb_);
    for ( index_t j = 0; j < dim_sketch; ++j ) {
      if ( blas::dot(set_g_(i).getRow(j), matrix_gb_.getRow(j)) < 0 ) {
        blas::scal(-1.0, set_g_(i).getRow(j));
      }
    }

    // Qbar += Qi * Gi'
    blas::gemm<TransOption::NORMAL, TransOption::TRANS>(1.0, set_q_cut_(i), set_g_(i), 1.0, matrix_qbar_);

  }

  time4_ = MPI_Wtime();

  // Qbar := SVD( Qbar )
  mpi::reduce(matrix_qbar_, MPI_SUM, mpi_root, mpi_comm);

  // Compute the left singular vectors of Qbar
  if ( mpi::isCommRoot(mpi_root, mpi_comm) ) {
    gesvd_driver_(matrix_qbar_, vector_s_, matrix_empty_, matrix_empty_);
  }

  time5_ = MPI_Wtime();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getName
///
template <class _Matrix>
constexpr const char* ExtrinsicMeanIntegrator<_Matrix>::getNameImpl() const noexcept {
  return name_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getTime
///
template <class _Matrix>
double ExtrinsicMeanIntegrator<_Matrix>::getTimeImpl() const noexcept {
  return time5_-time0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getTimes
///
template <class _Matrix>
const std::vector<double> ExtrinsicMeanIntegrator<_Matrix>::getTimesImpl() const noexcept {
  return {time1_-time0_, time2_-time1_, time3_-time2_, time4_-time3_, time5_-time4_};
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getIter
///
template <class _Matrix>
index_t ExtrinsicMeanIntegrator<_Matrix>::getIterImpl() const noexcept {
  return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getSetQ
///
template <class _Matrix>
DenseMatrixSet120<typename ExtrinsicMeanIntegrator<_Matrix>::ScalarType>&
    ExtrinsicMeanIntegrator<_Matrix>::getSetQImpl() noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return set_q_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getSetQ
///
template <class _Matrix>
const DenseMatrixSet120<typename ExtrinsicMeanIntegrator<_Matrix>::ScalarType>&
    ExtrinsicMeanIntegrator<_Matrix>::getSetQImpl() const noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return set_q_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getMatrixQbar
///
template <class _Matrix>
DenseMatrix<typename ExtrinsicMeanIntegrator<_Matrix>::ScalarType, Layout::ROWMAJOR>&
    ExtrinsicMeanIntegrator<_Matrix>::getMatrixQbarImpl() noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return matrix_qbar_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getMatrixQbar
///
template <class _Matrix>
const DenseMatrix<typename ExtrinsicMeanIntegrator<_Matrix>::ScalarType, Layout::ROWMAJOR>&
    ExtrinsicMeanIntegrator<_Matrix>::getMatrixQbarImpl() const noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return matrix_qbar_;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_EXTRINSIC_MEAN_INTEGRATOR_IPP_
