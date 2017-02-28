////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/naive_kolmogorov_nagumo_integrator.hpp
/// @brief   The naive Kolmogorov-Nagumo-type integrator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_NAIVE_KOLMOGOROV_NAGUMO_INTEGRATOR_HPP_
#define MCNLA_ISVD_INTEGRATOR_NAIVE_KOLMOGOROV_NAGUMO_INTEGRATOR_HPP_

#include <mcnla/isvd/integrator/naive_kolmogorov_nagumo_integrator.hh>
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
template <typename _Val>
Integrator<NaiveKolmogorovNagumoIntegratorTag, _Val>::Integrator(
    const ParametersType &parameters,
    const MPI_Comm mpi_comm,
    const mpi_int_t mpi_root
) noexcept
  : BaseType(parameters, mpi_comm, mpi_root) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::initialize
///
template <typename _Val>
void Integrator<NaiveKolmogorovNagumoIntegratorTag, _Val>::initializeImpl() noexcept {

  const auto nrow            = parameters_.nrow();
  const auto dim_sketch      = parameters_.dimSketch();
  const auto num_sketch_each = parameters_.numSketchEach();

  moment0_ = 0;
  moment1_ = 0;
  moment2_ = 0;
  moment3_ = 0;

  collection_q_.reconstruct(nrow, dim_sketch, num_sketch_each);
  matrix_qs_ = collection_q_.unfold();

  matrix_qc_.reconstruct(nrow, dim_sketch);

  matrix_bs_.reconstruct(dim_sketch, dim_sketch * num_sketch_each);
  matrix_d_.reconstruct(dim_sketch, dim_sketch);
  matrix_z_.reconstruct(dim_sketch, dim_sketch);
  matrix_c_.reconstruct(dim_sketch, dim_sketch);

  matrix_x_.reconstruct(nrow, dim_sketch);
  matrix_tmp_.reconstruct(nrow, dim_sketch);

  vector_e_.reconstruct(dim_sketch);
  vector_f_.reconstruct(dim_sketch);

  syev_driver_.reconstruct(dim_sketch);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::integrate
///
template <typename _Val>
void Integrator<NaiveKolmogorovNagumoIntegratorTag, _Val>::integrateImpl() noexcept {
  mcnla_assert_true(parameters_.isInitialized());

  const auto dim_sketch      = parameters_.dimSketch();
  const auto num_sketch      = parameters_.numSketch();
  const auto max_iteration   = parameters_.maxIteration();
  const auto tolerance       = parameters_.tolerance();

  moment0_ = MPI_Wtime();

  // Broadcast Q0 to Qc
  if ( mpi::isCommRoot(mpi_root_, mpi_comm_) ) {
    la::copy(collection_q_(0), matrix_qc_);
  }
  mpi::bcast(matrix_qc_, mpi_root_, mpi_comm_);

  moment1_ = MPI_Wtime();

  time2c_ = 0;

  bool is_converged = false;
  for ( iteration_ = 0; iteration_ < max_iteration && !is_converged; ++iteration_ ) {
    double moment2c;

    // ================================================================================================================== //
    // X = (I - Qc * Qc') * sum(Qi * Qi')/N * Qc

    // Bs := sum( Qc' * Qs )
    la::mm(matrix_qc_.t(), matrix_qs_, matrix_bs_);

    // D := Bs * Bs'
    la::rk(matrix_bs_, matrix_d_.viewSymmetric());

    // X := 1/N * Qs * Bs'
    la::mm(matrix_qs_, matrix_bs_.t(), matrix_x_, 1.0/num_sketch);

    // X -= 1/N * Qc * D
    la::mm(matrix_qc_, matrix_d_.viewSymmetric(), matrix_x_, -1.0/num_sketch, 1.0);

    // Reduce sum X
    moment2c = MPI_Wtime();
    mpi::allreduce(matrix_x_, MPI_SUM, mpi_comm_);
    time2c_ += MPI_Wtime() - moment2c;

    // ================================================================================================================== //
    // C := sqrt( I/2 + sqrt( I/4 - X' * X ) )

    // Z := sum(X' * X)
    la::rk(matrix_x_.t(), matrix_z_.viewSymmetric());

    // Compute the eigen-decomposition of Z -> Z' * E * Z
    syev_driver_(matrix_z_.viewSymmetric(), vector_e_);

    // E := sqrt( I/2 - sqrt( I/4 - E ) )
    vector_e_.val().valarray() = std::sqrt(0.5 + std::sqrt(0.25 - vector_e_.val().valarray()));

    // F := sqrt( E )
    vector_f_.val().valarray() = std::sqrt(vector_e_.val().valarray());

    // D := F * Z
    la::mm(vector_f_.viewDiagonal(), matrix_z_, matrix_d_);

    // Z := F \ Z
    la::sm(vector_f_.viewDiagonal().inv(), matrix_z_);

    // C := D' * D
    la::rk(matrix_d_.t(), matrix_c_.viewSymmetric());

    // inv(C) := Z' * Z
    la::rk(matrix_z_.t(), matrix_d_.viewSymmetric());

    // ================================================================================================================== //
    // Qc := Qc * C + X * inv(C)

    // Qc *= C
    la::copy(matrix_qc_.vectorize(), matrix_tmp_.vectorize());
    la::mm(matrix_tmp_, matrix_c_.viewSymmetric(), matrix_qc_);

    // Qc += X * inv(C)
    la::mm(matrix_x_, matrix_d_.viewSymmetric(), matrix_qc_, 1.0, 1.0);

    // ================================================================================================================== //
    // Check convergence
    vector_e_.val().valarray() -= 1.0;
    is_converged = !(la::nrm2(vector_e_) / std::sqrt(dim_sketch) > tolerance);
  }

  moment2_ = MPI_Wtime();

  moment3_ = MPI_Wtime();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::outputName
///
///
template <typename _Val>
std::ostream& Integrator<NaiveKolmogorovNagumoIntegratorTag, _Val>::outputNameImpl(
    std::ostream &os
) const noexcept {
  return (os << name_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::time
///
template <typename _Val>
double Integrator<NaiveKolmogorovNagumoIntegratorTag, _Val>::timeImpl() const noexcept {
  return moment3_-moment0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::time
///
template <typename _Val>
double Integrator<NaiveKolmogorovNagumoIntegratorTag, _Val>::time1() const noexcept {
  return moment1_-moment0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::time
///
template <typename _Val>
double Integrator<NaiveKolmogorovNagumoIntegratorTag, _Val>::time2() const noexcept {
  return moment2_-moment1_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::time
///
template <typename _Val>
double Integrator<NaiveKolmogorovNagumoIntegratorTag, _Val>::time2c() const noexcept {
  return time2c_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::time
///
template <typename _Val>
double Integrator<NaiveKolmogorovNagumoIntegratorTag, _Val>::time3() const noexcept {
  return moment3_-moment2_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::collectionQ
///
template <typename _Val>
DenseMatrixCollection120<_Val>& Integrator<NaiveKolmogorovNagumoIntegratorTag, _Val>::collectionQImpl() noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return collection_q_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::collectionQ
///
template <typename _Val>
const DenseMatrixCollection120<_Val>& Integrator<NaiveKolmogorovNagumoIntegratorTag, _Val>::collectionQImpl()
    const noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return collection_q_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::matrixQ
///
template <typename _Val>
DenseMatrixRowMajor<_Val>& Integrator<NaiveKolmogorovNagumoIntegratorTag, _Val>::matrixQImpl() noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return matrix_qc_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::IntegratorWrapper::matrixQ
///
template <typename _Val>
const DenseMatrixRowMajor<_Val>& Integrator<NaiveKolmogorovNagumoIntegratorTag, _Val>::matrixQImpl() const noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  return matrix_qc_;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_NAIVE_KOLMOGOROV_NAGUMO_INTEGRATOR_HPP_
