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
/// @copydoc  mcnla::isvd::IntegratorWrapper::IntegratorWrapper
///
template <typename _Scalar>
Integrator<_Scalar, ExtrinsicMeanIntegratorTag>::Integrator(
    const ParametersType &parameters,
    const MPI_Comm mpi_comm,
    const mpi_int_t mpi_root
) noexcept
  : BaseType(parameters, mpi_comm, mpi_root) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::initialize
///
template <typename _Scalar>
void Integrator<_Scalar, ExtrinsicMeanIntegratorTag>::initializeImpl() noexcept {

  const auto mpi_size        = mpi::commSize(mpi_comm_);
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

  collection_q_.reconstruct(nrow_all_, dim_sketch, num_sketch_each);
  collection_q_cut_ = collection_q_({0, nrow}, "", "");

  matrix_qjs_.reconstruct(nrow_each_, dim_sketch * num_sketch);
  matrix_qbar_.reconstruct(nrow, dim_sketch);

  matrix_bjs_.reconstruct(dim_sketch * num_sketch, dim_sketch * num_sketch);
  collection_bi_.reconstruct(dim_sketch, dim_sketch * num_sketch, num_sketch_each);
  collection_bi0_ = collection_bi_("", {0, dim_sketch}, "");

  collection_g_.reconstruct(dim_sketch, dim_sketch, num_sketch_each);
  matrix_g0_.reconstruct(dim_sketch, dim_sketch);
  matrix_gb_.reconstruct(dim_sketch, dim_sketch);

  vector_s_.reconstruct(dim_sketch);

  matrix_tmp_.reconstruct(nrow_all_, dim_sketch * num_sketch_each);

  gesvd_engine_.reconstruct(nrow, dim_sketch);
  syev_engine_.reconstruct(dim_sketch);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::integrate
///
template <typename _Scalar>
void Integrator<_Scalar, ExtrinsicMeanIntegratorTag>::integrateImpl() noexcept {
  mcnla_assert_true(parameters_.isInitialized());

  const auto mpi_size        = mpi::commSize(mpi_comm_);
  const auto mpi_rank        = mpi::commRank(mpi_comm_);
  const auto nrow            = parameters_.nrow();
  const auto dim_sketch      = parameters_.dimSketch();
  const auto num_sketch_each = parameters_.numSketchEach();

  time0_ = MPI_Wtime();

  // Exchange Q
  la::memset0(collection_q_({nrow, nrow_all_}, "", "").unfold());
  mpi::alltoall(collection_q_.unfold(), matrix_tmp_, mpi_comm_);

  // Rearrange Qj
  for ( index_t j = 0; j < mpi_size; ++j ) {
    la::copy(matrix_tmp_(IdxRange{j, j+1} * nrow_each_, ""),
               matrix_qjs_("", IdxRange{j, j+1} * dim_sketch * num_sketch_each));
  }

  time1_ = MPI_Wtime();

  // Bs := sum( Qjs' * Qjs )
  la::mm(matrix_qjs_.t(), matrix_qjs_, matrix_bjs_);
  mpi::reduceScatterBlock(matrix_bjs_, collection_bi_.unfold(), MPI_SUM, mpi_comm_);

  time2_ = MPI_Wtime();

  for ( index_t i = 0; i < num_sketch_each; ++i ) {

    // Gi := Bi * Bi'
    la::rk(collection_bi_(i), collection_g_(i).viewSymmetric());

    // Compute the eigen-decomposition of Gi -> Gi' * S * Gi
    syev_engine_(collection_g_(i).viewSymmetric(), vector_s_);

  }

  // Broadcast G0
  if ( mpi_rank == 0 ) {
    la::omatcopy(collection_g_(0), matrix_g0_);
  }
  mpi::bcast(matrix_g0_, 0, mpi_comm_);

  time3_ = MPI_Wtime();

  // Qbar := 0
  la::memset0(matrix_qbar_);

  for ( index_t i = 0; i < num_sketch_each; ++i ) {

    // Inverse Gi(j-row) if Gi(j-row) * Bi0 * G0(j-row)' < 0
    la::mm(matrix_g0_, collection_bi0_(i).t(), matrix_gb_);

    for ( index_t j = 0; j < dim_sketch; ++j ) {
      if ( la::dot(collection_g_(i)(j, ""), matrix_gb_(j, "")) < 0 ) {
        la::scal(collection_g_(i)(j, ""), -1.0);
      }
    }

    // Qbar += Qi * Gi'
    la::mm(collection_q_cut_(i), collection_g_(i).t(), matrix_qbar_, 1.0, 1.0);

  }

  time4_ = MPI_Wtime();

  // Qbar := sum( Qbar )
  mpi::reduce(matrix_qbar_, MPI_SUM, mpi_root_, mpi_comm_);

  // Compute the left singular vectors of Qbar
  if ( mpi_rank == mpi_root_ ) {
    gesvd_engine_(matrix_qbar_, vector_s_, matrix_empty_, matrix_empty_);
  }

  time5_ = MPI_Wtime();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::outputName
///
///
template <typename _Scalar>
std::ostream& Integrator<_Scalar, ExtrinsicMeanIntegratorTag>::outputNameImpl(
    std::ostream &os
) const noexcept {
  return (os << name_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::time
///
template <typename _Scalar>
double Integrator<_Scalar, ExtrinsicMeanIntegratorTag>::timeImpl() const noexcept {
  return time5_-time0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::time
///
template <typename _Scalar>
double Integrator<_Scalar, ExtrinsicMeanIntegratorTag>::time1() const noexcept {
  return time1_-time0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::time
///
template <typename _Scalar>
double Integrator<_Scalar, ExtrinsicMeanIntegratorTag>::time2() const noexcept {
  return time2_-time1_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::time
///
template <typename _Scalar>
double Integrator<_Scalar, ExtrinsicMeanIntegratorTag>::time3() const noexcept {
  return time3_-time2_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::time
///
template <typename _Scalar>
double Integrator<_Scalar, ExtrinsicMeanIntegratorTag>::time4() const noexcept {
  return time4_-time3_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::time
///
template <typename _Scalar>
double Integrator<_Scalar, ExtrinsicMeanIntegratorTag>::time5() const noexcept {
  return time5_-time4_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::collectionQ
///
template <typename _Scalar>
DenseMatrixCollection120<_Scalar>& Integrator<_Scalar, ExtrinsicMeanIntegratorTag>::collectionQImpl() noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return collection_q_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::collectionQ
///
template <typename _Scalar>
const DenseMatrixCollection120<_Scalar>& Integrator<_Scalar, ExtrinsicMeanIntegratorTag>::collectionQImpl() const noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return collection_q_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::matrixQ
///
template <typename _Scalar>
DenseMatrixRowMajor<_Scalar>& Integrator<_Scalar, ExtrinsicMeanIntegratorTag>::matrixQImpl() noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return matrix_qbar_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::matrixQ
///
template <typename _Scalar>
const DenseMatrixRowMajor<_Scalar>& Integrator<_Scalar, ExtrinsicMeanIntegratorTag>::matrixQImpl() const noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return matrix_qbar_;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_EXTRINSIC_MEAN_INTEGRATOR_HPP_
