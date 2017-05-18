////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/row_block_kolmogorov_nagumo_integrator.hpp
/// @brief   The Kolmogorov-Nagumo-type integrator (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_KOLMOGOROV_NAGUMO_INTEGRATOR_HPP_
#define MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_KOLMOGOROV_NAGUMO_INTEGRATOR_HPP_

#include <mcnla/isvd/integrator/row_block_kolmogorov_nagumo_integrator.hh>
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
Integrator<RowBlockKolmogorovNagumoIntegratorTag, _Val>::Integrator(
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
void Integrator<RowBlockKolmogorovNagumoIntegratorTag, _Val>::initializeImpl() noexcept {

  const auto nrow_rank        = parameters_.nrowRank();
  const auto dim_sketch       = parameters_.dimSketch();
  const auto dim_sketch_total = parameters_.dimSketchTotal();

  matrix_b_.reconstruct(dim_sketch, dim_sketch_total);

  matrix_d_.reconstruct(dim_sketch, dim_sketch);
  matrix_z_.reconstruct(dim_sketch, dim_sketch);
  matrix_c_.reconstruct(dim_sketch, dim_sketch);

  matrix_xj_.reconstruct(nrow_rank, dim_sketch);
  matrix_tmp_.reconstruct(nrow_rank, dim_sketch);

  vector_e_.reconstruct(dim_sketch);
  vector_f_.reconstruct(dim_sketch);

  syev_driver_.reconstruct(dim_sketch);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Integrates.
///
/// @param  collection_qj  The matrix collection Qj (j-th row-block, where j is the MPI rank).
/// @param  matrix_qbarj   The matrix Qbarj (j-th row-block, where j is the MPI rank).
///
template <typename _Val>
void Integrator<RowBlockKolmogorovNagumoIntegratorTag, _Val>::runImpl(
    const DenseMatrixCollection201<ValType> &collection_qj,
          DenseMatrixRowMajor<ValType> &matrix_qbarj
) noexcept {

  const auto mpi_comm   = parameters_.mpi_comm;
  const auto nrow_rank  = parameters_.nrowRank();
  const auto dim_sketch = parameters_.dimSketch();
  const auto num_sketch = parameters_.numSketch();

  static_cast<void>(nrow_rank);

  mcnla_assert_eq(collection_qj.sizes(), std::make_tuple(nrow_rank, dim_sketch, num_sketch));
  mcnla_assert_eq(matrix_qbarj.sizes(),  std::make_tuple(nrow_rank, dim_sketch));

  auto &matrix_qsj = collection_qj.unfold();  // matrix Qs.
  auto &matrix_qcj = matrix_qbarj;  // matrix Qc.

  this->tic(); double comm_moment, comm_time = 0;
  // ====================================================================================================================== //
  // Copying Qc

  // Qc := Q0
  la::copy(collection_qj(0), matrix_qcj);

  comm_times_.emplace_back(comm_time);
  moments_.emplace_back(utility::getTime());  // iterating
  comm_time = 0;

  this->toc(comm_time);
  // ====================================================================================================================== //
  // Iterating

  bool is_converged = false;
  for ( iteration_ = 0; iteration_ < max_iteration_ && !is_converged; ++iteration_ ) {

    // ================================================================================================================== //
    // X = (I - Qc * Qc') * sum(Qi * Qi')/N * Qc

    // B := sum( Qcj' * Qsj )
    la::mm(matrix_qcj.t(), matrix_qsj, matrix_b_);
    comm_moment = utility::getTime();
    mpi::allreduce(matrix_b_, MPI_SUM, mpi_comm);
    comm_time += utility::getTime() - comm_moment;

    // D := B * B'
    la::rk(matrix_b_, matrix_d_.viewSymmetric());

    // Xj := 1/N * Qsj * B'
    la::mm(matrix_qsj, matrix_b_.t(), matrix_xj_, 1.0/num_sketch);

    // Xj -= 1/N * Qcj * D
    la::mm(matrix_qcj, matrix_d_.viewSymmetric(), matrix_xj_, -1.0/num_sketch, 1.0);

    // ================================================================================================================== //
    // C := sqrt( I/2 + sqrt( I/4 - X' * X ) )

    // Z := sum(Xj' * Xj)
    la::rk(matrix_xj_.t(), matrix_z_.viewSymmetric());
    comm_moment = utility::getTime();
    mpi::allreduce(matrix_z_, MPI_SUM, mpi_comm);
    comm_time += utility::getTime() - comm_moment;

    // Compute the eigen-decomposition of Z -> Z' * E * Z
    syev_driver_(matrix_z_.viewSymmetric(), vector_e_);

    // E := sqrt( I/2 + sqrt( I/4 - E ) )
    // F := sqrt( E )
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
    la::copy(matrix_qcj.vectorize(), matrix_tmp_.vectorize());
    la::mm(matrix_tmp_, matrix_c_.viewSymmetric(), matrix_qcj);

    // Qc += X * inv(C)
    la::mm(matrix_xj_, matrix_d_.viewSymmetric(), matrix_qcj, 1.0, 1.0);

    // ================================================================================================================== //
    // Check convergence
    for ( auto &v : vector_e_ ) {
      v -= 1.0;
    }
    is_converged = !(la::nrm2(vector_e_) / std::sqrt(dim_sketch) >= tolerance_);
  }

  this->toc(comm_time);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the maximum number of iteration.
///
template <typename _Val>
index_t Integrator<RowBlockKolmogorovNagumoIntegratorTag, _Val>::maxIteration() const noexcept {
  return max_iteration_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the tolerance of convergence condition.
///
template <typename _Val>
RealValT<_Val> Integrator<RowBlockKolmogorovNagumoIntegratorTag, _Val>::tolerance() const noexcept {
  return tolerance_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of iteration.
///
template <typename _Val>
index_t Integrator<RowBlockKolmogorovNagumoIntegratorTag, _Val>::iteration() const noexcept {
  mcnla_assert_true(this->isComputed());
  return iteration_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the maximum number of iteration.
///
template <typename _Val>
Integrator<RowBlockKolmogorovNagumoIntegratorTag, _Val>&
  Integrator<RowBlockKolmogorovNagumoIntegratorTag, _Val>::setMaxIteration(
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
Integrator<RowBlockKolmogorovNagumoIntegratorTag, _Val>&
  Integrator<RowBlockKolmogorovNagumoIntegratorTag, _Val>::setTolerance(
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

#endif  // MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_KOLMOGOROV_NAGUMO_INTEGRATOR_HPP_
