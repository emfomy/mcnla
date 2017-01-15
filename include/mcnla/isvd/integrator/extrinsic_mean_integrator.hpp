////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/extrinsic_mean_integrator.hpp
/// @brief   The extrinsic mean integrator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_EXTRINSIC_MEAN_INTEGRATOR_HPP_
#define MCNLA_ISVD_INTEGRATOR_EXTRINSIC_MEAN_INTEGRATOR_HPP_

#include <mcnla/isvd/integrator/extrinsic_mean_integrator.hh>
#include <cmath>
#include <mcnla/core/blas.hpp>

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
    const Parameters &parameters
) noexcept : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::initialize
///
template <class _Matrix>
void ExtrinsicMeanIntegrator<_Matrix>::initializeImpl() noexcept {

  const auto mpi_size        = parameters_.mpi_size;
  const auto nrow            = parameters_.nrow();
  const auto num_sketch      = parameters_.numSketch();
  const auto num_sketch_each = parameters_.numSketchEach();
  const auto dim_sketch      = parameters_.dimSketch();

  time0_ = 0;
  time1_ = 0;
  time2_ = 0;
  time3_ = 0;
  time4_ = 0;

  nrow_each_ = (nrow-1) / mpi_size + 1;
  nrow_all_  = nrow_each_ * mpi_size;

  const auto collection_q_sizes = std::make_tuple(nrow_all_, dim_sketch, num_sketch_each);
  if ( collection_q_.sizes() != collection_q_sizes || !collection_q_.isShrunk() ) {
    collection_q_ = DenseMatrixCollection120<ScalarType>(collection_q_sizes);
  }
  collection_q_cut_ = collection_q_.getMatrixRows({0, nrow});

  const auto matrix_tmp_sizes = std::make_tuple(nrow_all_, dim_sketch * num_sketch_each);
  if ( matrix_tmp_.sizes() != matrix_tmp_sizes ) {
    matrix_tmp_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_tmp_sizes);
  }

  const auto matrix_qjs_sizes = std::make_tuple(nrow_each_, dim_sketch * num_sketch);
  if ( matrix_qjs_.sizes() != matrix_qjs_sizes || !matrix_qjs_.isShrunk() ) {
    matrix_qjs_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_qjs_sizes);
  }

  const auto matrix_qbar_sizes = std::make_tuple(nrow, dim_sketch);
  if ( matrix_qbar_.sizes() != matrix_qbar_sizes || !matrix_qbar_.isShrunk() ) {
    matrix_qbar_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_qbar_sizes);
  }

  const auto matrix_bjs_sizes = std::make_tuple(dim_sketch * num_sketch, dim_sketch * num_sketch);
  if ( matrix_bjs_.sizes() != matrix_bjs_sizes || !matrix_bjs_.isShrunk() ) {
    matrix_bjs_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_bjs_sizes);
  }

  const auto matrix_bis_sizes = std::make_tuple(dim_sketch * num_sketch_each, dim_sketch * num_sketch);
  if ( matrix_bis_.sizes() != matrix_bis_sizes || !matrix_bis_.isShrunk() ) {
    matrix_bis_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_bis_sizes);
  }

  const auto set_g_sizes = std::make_tuple(dim_sketch, dim_sketch, num_sketch_each);
  if ( set_g_.sizes() != set_g_sizes ) {
    set_g_ = DenseMatrixCollection120<ScalarType>(set_g_sizes);
  }

  const auto matrix_g_sizes = std::make_tuple(dim_sketch, dim_sketch);
  if ( matrix_g0_.sizes() != matrix_g_sizes ) {
    matrix_g0_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_g_sizes);
  }
  if ( matrix_gb_.sizes() != matrix_g_sizes ) {
    matrix_gb_ = DenseMatrix<ScalarType, Layout::ROWMAJOR>(matrix_g_sizes);
  }

  const auto vector_s_sizes = dim_sketch;
  if ( vector_s_.sizes() != vector_s_sizes ) {
    vector_s_ = DenseVector<ScalarType>(vector_s_sizes);
  }

  const auto gesvd_sizes = std::make_tuple(nrow, dim_sketch);
  if ( gesvd_engine_.sizes() != gesvd_sizes ) {
    gesvd_engine_.resize(gesvd_sizes);
  }

  const auto syev_sizes = dim_sketch;
  if ( syev_engine_.sizes() != syev_sizes ) {
    syev_engine_.resize(syev_sizes);
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
  const auto mpi_rank        = mpi::commRank(mpi_comm);
  const auto nrow            = parameters_.nrow();
  const auto dim_sketch      = parameters_.dimSketch();
  const auto num_sketch_each = parameters_.numSketchEach();

  time0_ = MPI_Wtime();

  // Exchange Q
  blas::memset0(collection_q_.getMatrixRows({nrow, nrow_all_}).unfold());
  mpi::alltoall(collection_q_.unfold(), matrix_tmp_, mpi_comm);

  // Rearrange Qj
  for ( index_t j = 0; j < mpi_size; ++j ) {
    blas::omatcopy(1.0, matrix_tmp_.getRows(IdxRange{j, j+1} * nrow_each_),
                        matrix_qjs_.getCols(IdxRange{j, j+1} * dim_sketch * num_sketch_each));
  }

  time1_ = MPI_Wtime();

  // Bs := sum( Qjs' * Qjs )
  blas::gemm<Trans::TRANS, Trans::NORMAL>(1.0, matrix_qjs_, matrix_qjs_, 0.0, matrix_bjs_);
  mpi::reduceScatterBlock(matrix_bjs_, matrix_bis_, MPI_SUM, mpi_comm);

  time2_ = MPI_Wtime();

  for ( index_t i = 0; i < num_sketch_each; ++i ) {

    // Gi := Bis * Bis'
    blas::syrk<Trans::NORMAL>(1.0, matrix_bis_.getRows(IdxRange{i, i+1}*dim_sketch), 0.0, set_g_(i));

    // Compute the eigen-decomposition of Gi -> Gi' * S * Gi
    syev_engine_(set_g_(i), vector_s_);

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
    auto matrix_bi0 = matrix_bis_.getBlock(IdxRange{i, i+1}*dim_sketch, {0, dim_sketch});
    blas::gemm<Trans::NORMAL, Trans::TRANS>(1.0, matrix_g0_, matrix_bi0, 0.0, matrix_gb_);
    for ( index_t j = 0; j < dim_sketch; ++j ) {
      if ( blas::dot(set_g_(i).getRow(j), matrix_gb_.getRow(j)) < 0 ) {
        blas::scal(-1.0, set_g_(i).getRow(j));
      }
    }

    // Qbar += Qi * Gi'
    blas::gemm<Trans::NORMAL, Trans::TRANS>(1.0, collection_q_cut_(i), set_g_(i), 1.0, matrix_qbar_);

  }

  time4_ = MPI_Wtime();

  // Qbar := SVD( Qbar )
  mpi::reduce(matrix_qbar_, MPI_SUM, mpi_root, mpi_comm);

  // Compute the left singular vectors of Qbar
  if ( mpi::isCommRoot(mpi_root, mpi_comm) ) {
    gesvd_engine_(matrix_qbar_, vector_s_, matrix_empty_, matrix_empty_);
  }

  time5_ = MPI_Wtime();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::name
///
template <class _Matrix>
constexpr const char* ExtrinsicMeanIntegrator<_Matrix>::nameImpl() const noexcept {
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
/// @copydoc  mcnla::isvd::IntegratorBase::getCollectionQ
///
template <class _Matrix>
DenseMatrixCollection120<ScalarT<ExtrinsicMeanIntegrator<_Matrix>>>&
    ExtrinsicMeanIntegrator<_Matrix>::getCollectionQImpl() noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return collection_q_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getCollectionQ
///
template <class _Matrix>
const DenseMatrixCollection120<ScalarT<ExtrinsicMeanIntegrator<_Matrix>>>&
    ExtrinsicMeanIntegrator<_Matrix>::getCollectionQImpl() const noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return collection_q_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getMatrixQbar
///
template <class _Matrix>
DenseMatrix<ScalarT<ExtrinsicMeanIntegrator<_Matrix>>, Layout::ROWMAJOR>&
    ExtrinsicMeanIntegrator<_Matrix>::getMatrixQbarImpl() noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return matrix_qbar_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorBase::getMatrixQbar
///
template <class _Matrix>
const DenseMatrix<ScalarT<ExtrinsicMeanIntegrator<_Matrix>>, Layout::ROWMAJOR>&
    ExtrinsicMeanIntegrator<_Matrix>::getMatrixQbarImpl() const noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return matrix_qbar_;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_EXTRINSIC_MEAN_INTEGRATOR_HPP_
