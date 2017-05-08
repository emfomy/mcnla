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
/// @copydoc  mcnla::isvd::StageWrapper::StageWrapper
///
template <typename _Val>
Integrator<KolmogorovNagumoIntegratorTag, _Val>::Integrator(
    const Parameters<ValType> &parameters,
    const index_t max_iteration,
    const RealValType tolerance
) noexcept
  : BaseType(parameters) {
  setMaxIteration(max_iteration);
  setTolerance(tolerance);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::StageWrapper::initialize
///
template <typename _Val>
void Integrator<KolmogorovNagumoIntegratorTag, _Val>::initializeImpl() noexcept {

  const auto nrow            = parameters_.nrow();
  const auto dim_sketch      = parameters_.dimSketch();
  const auto dim_sketch_each = parameters_.dimSketchEach();

  matrix_b_.reconstruct(dim_sketch, dim_sketch_each);
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
/// @brief  Integrates.
///
/// @param  collection_q  The matrix collection Q.
/// @param  matrix_qbar   The matrix Qbar.
///
template <typename _Val>
void Integrator<KolmogorovNagumoIntegratorTag, _Val>::runImpl(
    const DenseMatrixCollection201<ValType> &collection_q,
          DenseMatrixRowMajor<ValType> &matrix_qbar
) noexcept {

  const auto mpi_comm        = parameters_.mpi_comm;
  const auto mpi_rank        = parameters_.mpi_rank;
  const auto nrow            = parameters_.nrow();
  const auto dim_sketch      = parameters_.dimSketch();
  const auto num_sketch      = parameters_.numSketch();
  const auto num_sketch_each = parameters_.numSketchEach();

  static_cast<void>(nrow);
  static_cast<void>(num_sketch_each);

  mcnla_assert_eq(collection_q.sizes(), std::make_tuple(nrow, dim_sketch, num_sketch_each));
  mcnla_assert_eq(matrix_qbar.sizes(),  std::make_tuple(nrow, dim_sketch));

  auto &matrix_qs = collection_q.unfold();  // matrix Qs.
  auto &matrix_qc = matrix_qbar;  // matrix Qc.

  double comm_moment, comm_time = 0;
  moments_.emplace_back(utility::getTime());  // copying Qc

  // Broadcast Q0 to Qc
  if ( mpi_rank == 0 ) {
    la::copy(collection_q(0), matrix_qc);
  }

  comm_moment = utility::getTime();
  mpi::bcast(matrix_qc, 0, mpi_comm);
  comm_time += utility::getTime() - comm_moment;

  comm_times_.emplace_back(comm_time);
  moments_.emplace_back(utility::getTime());  // iterating
  comm_time = 0;

  bool is_converged = false;
  for ( iteration_ = 0; iteration_ < max_iteration_ && !is_converged; ++iteration_ ) {

    // ================================================================================================================== //
    // X = (I - Qc * Qc') * sum(Qi * Qi')/N * Qc

    // B := sum( Qc' * Qs )
    la::mm(matrix_qc.t(), matrix_qs, matrix_b_);

    // D := B * B'
    la::rk(matrix_b_, matrix_d_.viewSymmetric());

    // X := 1/N * Qs * B'
    la::mm(matrix_qs, matrix_b_.t(), matrix_x_, 1.0/num_sketch);

    // X -= 1/N * Qc * D
    la::mm(matrix_qc, matrix_d_.viewSymmetric(), matrix_x_, -1.0/num_sketch, 1.0);

    // Reduce sum X
    comm_moment = utility::getTime();
    mpi::allreduce(matrix_x_, MPI_SUM, mpi_comm);
    comm_time += utility::getTime() - comm_moment;

    // ================================================================================================================== //
    // C := sqrt( I/2 + sqrt( I/4 - X' * X ) )

    // Z := sum(X' * X)
    la::rk(matrix_x_.t(), matrix_z_.viewSymmetric());

    // Compute the eigen-decomposition of Z -> Z' * E * Z
    syev_driver_(matrix_z_.viewSymmetric(), vector_e_);

    // E := sqrt( I/2 + sqrt( I/4 - E ) )
    for ( index_t i = 0; i < dim_sketch; ++i ) {
      vector_e_(i) = std::sqrt(0.5 + std::sqrt(0.25 - vector_e_(i)));
      vector_f_(i) = std::sqrt(vector_e_(i));
    }

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
    la::copy(matrix_qc.vectorize(), matrix_tmp_.vectorize());
    la::mm(matrix_tmp_, matrix_c_.viewSymmetric(), matrix_qc);

    // Qc += X * inv(C)
    la::mm(matrix_x_, matrix_d_.viewSymmetric(), matrix_qc, 1.0, 1.0);

    // ================================================================================================================== //
    // Check convergence
    for ( auto &v : vector_e_ ) {
      v -= 1.0;
    }
    is_converged = !(la::nrm2(vector_e_) / std::sqrt(dim_sketch) >= tolerance_);
  }

  comm_times_.emplace_back(comm_time);
  moments_.emplace_back(utility::getTime());  // end
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the maximum number of iteration.
///
template <typename _Val>
index_t Integrator<KolmogorovNagumoIntegratorTag, _Val>::maxIteration() const noexcept {
  return max_iteration_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the tolerance of convergence condition.
///
template <typename _Val>
RealValT<_Val> Integrator<KolmogorovNagumoIntegratorTag, _Val>::tolerance() const noexcept {
  return tolerance_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of iteration.
///
template <typename _Val>
index_t Integrator<KolmogorovNagumoIntegratorTag, _Val>::iteration() const noexcept {
  mcnla_assert_true(this->isComputed());
  return iteration_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the maximum number of iteration.
///
template <typename _Val>
Integrator<KolmogorovNagumoIntegratorTag, _Val>& Integrator<KolmogorovNagumoIntegratorTag, _Val>::setMaxIteration(
    const index_t max_iteration
) noexcept {
  mcnla_assert_ge(max_iteration, 0);
  max_iteration_ = max_iteration;
  initialized_ = false;
  computed_ = false;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the tolerance of convergence condition.
///
template <typename _Val>
Integrator<KolmogorovNagumoIntegratorTag, _Val>& Integrator<KolmogorovNagumoIntegratorTag, _Val>::setTolerance(
    const RealValType tolerance
) noexcept {
  mcnla_assert_ge(tolerance, 0);
  tolerance_ = tolerance;
  initialized_ = false;
  computed_ = false;
  return *this;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_KOLMOGOROV_NAGUMO_INTEGRATOR_HPP_
