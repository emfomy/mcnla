////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/kolmogorov_nagumo_integrator.hpp
/// @brief   The Kolmogorov-Nagumo-type integrator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_KOLMOGOROV_NAGUMO_INTEGRATOR_HPP_
#define MCNLA_ISVD_INTEGRATOR_KOLMOGOROV_NAGUMO_INTEGRATOR_HPP_

#include <mcnla/isvd/integrator/kolmogorov_nagumo_integrator.hh>
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
Integrator<_Scalar, KolmogorovNagumoIntegratorTag>::Integrator(
    const ParametersType &parameters,
    const MPI_Comm mpi_comm,
    const mpi_int_t mpi_root
) noexcept
  : BaseType(parameters, mpi_comm, mpi_root) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::initialize
///
template <typename _Scalar>
void Integrator<_Scalar, KolmogorovNagumoIntegratorTag>::initializeImpl() noexcept {

  const auto mpi_size        = mpi::commSize(mpi_comm_);
  const auto nrow            = parameters_.nrow();
  const auto num_sketch      = parameters_.numSketch();
  const auto num_sketch_each = parameters_.numSketchEach();
  const auto dim_sketch      = parameters_.dimSketch();

  time0_ = 0;
  time1_ = 0;
  time2_ = 0;
  time3_ = 0;

  nrow_each_ = (nrow-1) / mpi_size + 1;
  nrow_all_  = nrow_each_ * mpi_size;

  collection_q_.reconstruct(nrow_all_, dim_sketch, num_sketch_each);
  collection_q_cut_ = collection_q_({0, nrow}, "", "");
  matrix_qs_ = collection_q_.unfold();

  matrix_qjs_.reconstruct(nrow_each_, dim_sketch * num_sketch);

  matrix_qc_.reconstruct(nrow_all_, dim_sketch);
  matrix_qc_cut_ = matrix_qc_({0, nrow}, "");

  matrix_qcj_.reconstruct(nrow_each_, dim_sketch);

  matrix_bs_.reconstruct(dim_sketch, dim_sketch * num_sketch);

  matrix_d_.reconstruct(dim_sketch, dim_sketch);
  matrix_z_.reconstruct(dim_sketch, dim_sketch);
  matrix_c_.reconstruct(dim_sketch, dim_sketch);

  matrix_xj_.reconstruct(nrow_each_, dim_sketch);
  matrix_tmp_.reconstruct(nrow_each_, dim_sketch);

  vector_e_.reconstruct(dim_sketch);
  vector_f_.reconstruct(dim_sketch);

  syev_driver_.reconstruct(dim_sketch);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::integrate
///
template <typename _Scalar>
void Integrator<_Scalar, KolmogorovNagumoIntegratorTag>::integrateImpl() noexcept {
  mcnla_assert_true(parameters_.isInitialized());

  const auto mpi_size        = mpi::commSize(mpi_comm_);
  const auto nrow            = parameters_.nrow();
  const auto dim_sketch      = parameters_.dimSketch();
  const auto num_sketch_each = parameters_.numSketchEach();
  const auto num_sketch      = parameters_.numSketch();
  const auto max_iteration   = parameters_.maxIteration();
  const auto tolerance       = parameters_.tolerance();

  time0_ = MPI_Wtime();

  // Exchange Q
  la::memset0(collection_q_({nrow, nrow_all_}, "", "").unfold());
  mpi::alltoall(collection_q_.unfold(), mpi_comm_);

  // Rearrange Qj
  for ( index_t j = 0; j < mpi_size; ++j ) {
    la::copy(matrix_qs_(IdxRange{j, j+1} * nrow_each_, ""),
             matrix_qjs_("", IdxRange{j, j+1} * dim_sketch * num_sketch_each));
  }

  // Qc := Q0
  la::copy(matrix_qjs_("", {0, dim_sketch}), matrix_qcj_);

  time1_ = MPI_Wtime();

  bool is_converged = false;
  for ( iteration_ = 0; iteration_ < max_iteration && !is_converged; ++iteration_ ) {

    // ================================================================================================================== //
    // X = (I - Qc * Qc') * sum(Qi * Qi')/N * Qc

    // Bs := sum( Qcj' * Qjs )
    la::mm(matrix_qcj_.t(), matrix_qjs_, matrix_bs_);
    mpi::allreduce(matrix_bs_, MPI_SUM, mpi_comm_);

    // D  := Bs * Bs'
    la::rk(matrix_bs_, matrix_d_.viewSymmetric());

    // Xj := 1/N * Qjs * Bs'
    la::mm(matrix_qjs_, matrix_bs_.t(), matrix_xj_, 1.0/num_sketch);

    // Xj -= 1/N * Qcj * D
    la::mm(matrix_qcj_, matrix_d_.viewSymmetric(), matrix_xj_, -1.0/num_sketch, 1.0);

    // ================================================================================================================== //
    // C := sqrt( I/2 + sqrt( I/4 - X' * X ) )

    // Z := sum(Xj' * Xj)
    la::rk(matrix_xj_.t(), matrix_z_.viewSymmetric());
    mpi::allreduce(matrix_z_, MPI_SUM, mpi_comm_);

    // Compute the eigen-decomposition of Z -> Z' * E * Z
    syev_driver_(matrix_z_.viewSymmetric(), vector_e_);

    // E := sqrt( I/2 - sqrt( I/4 - E ) )
    vector_e_.val().valarray() = std::sqrt(0.5 + std::sqrt(0.25 - vector_e_.val().valarray()));

    // F := sqrt( E )
    vector_f_.val().valarray() = std::sqrt(vector_e_.val().valarray());

    // D := F \ Z
    la::sm(vector_f_.viewDiagonal().inv(), matrix_z_, matrix_d_);

    // Z := F * Z
    la::mm(vector_f_.viewDiagonal(), "", matrix_z_);

    // C := Z' * Z
    la::rk(matrix_z_.t(), matrix_c_.viewSymmetric());

    // inv(C) := D' * D
    la::rk(matrix_d_.t(), matrix_z_.viewSymmetric());

    // ================================================================================================================== //
    // Qc := Qc * C + X * inv(C)

    // Qc *= C
    la::copy(matrix_qcj_.vectorize(), matrix_tmp_.vectorize());
    la::mm(matrix_tmp_, matrix_c_.viewSymmetric(), matrix_qcj_);

    // Qc += X * inv(C)
    la::mm(matrix_xj_, matrix_z_.viewSymmetric(), matrix_qcj_, 1.0, 1.0);

    // ================================================================================================================== //
    // Check convergence
    vector_e_.val().valarray() -= 1.0;
    is_converged = !(la::nrm2(vector_e_) / std::sqrt(dim_sketch) > tolerance);
  }

  time2_ = MPI_Wtime();

  // Gather Qc
  mpi::gather(matrix_qcj_, matrix_qc_, mpi_root_, mpi_comm_);

  time3_ = MPI_Wtime();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::outputName
///
///
template <typename _Scalar>
std::ostream& Integrator<_Scalar, KolmogorovNagumoIntegratorTag>::outputNameImpl(
    std::ostream &os
) const noexcept {
  return (os << name_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::time
///
template <typename _Scalar>
double Integrator<_Scalar, KolmogorovNagumoIntegratorTag>::timeImpl() const noexcept {
  return time3_-time0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::time
///
template <typename _Scalar>
double Integrator<_Scalar, KolmogorovNagumoIntegratorTag>::time1() const noexcept {
  return time1_-time0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::time
///
template <typename _Scalar>
double Integrator<_Scalar, KolmogorovNagumoIntegratorTag>::time2() const noexcept {
  return time2_-time1_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::time
///
template <typename _Scalar>
double Integrator<_Scalar, KolmogorovNagumoIntegratorTag>::time3() const noexcept {
  return time3_-time2_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::collectionQ
///
template <typename _Scalar>
DenseMatrixCollection120<_Scalar>& Integrator<_Scalar, KolmogorovNagumoIntegratorTag>::collectionQImpl() noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return collection_q_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::collectionQ
///
template <typename _Scalar>
const DenseMatrixCollection120<_Scalar>& Integrator<_Scalar, KolmogorovNagumoIntegratorTag>::collectionQImpl() const noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return collection_q_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::matrixQ
///
template <typename _Scalar>
DenseMatrixRowMajor<_Scalar>& Integrator<_Scalar, KolmogorovNagumoIntegratorTag>::matrixQImpl() noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return matrix_qc_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::matrixQ
///
template <typename _Scalar>
const DenseMatrixRowMajor<_Scalar>& Integrator<_Scalar, KolmogorovNagumoIntegratorTag>::matrixQImpl() const noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return matrix_qc_cut_;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_KOLMOGOROV_NAGUMO_INTEGRATOR_HPP_
