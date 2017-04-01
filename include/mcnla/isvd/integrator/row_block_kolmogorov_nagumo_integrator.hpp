////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/row_block_kolmogorov_nagumo_integrator.hpp
/// @brief   The Kolmogorov-Nagumo-type integrator.
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
/// @copydoc  mcnla::isvd::ComponentWrapper::ComponentWrapper
///
template <typename _Val>
Integrator<RowBlockKolmogorovNagumoIntegratorTag, _Val>::Integrator(
    const Parameters &parameters,
    const index_t max_iteration,
    const RealValType tolerance
) noexcept
  : BaseType(parameters) {
  setMaxIteration(max_iteration);
  setTolerance(tolerance);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::ComponentWrapper::initialize
///
template <typename _Val>
void Integrator<RowBlockKolmogorovNagumoIntegratorTag, _Val>::initializeImpl() noexcept {

  const auto nrow_each  = parameters_.nrowEach();
  const auto dim_sketch = parameters_.dimSketch();
  const auto num_sketch = parameters_.numSketch();

  matrix_bs_.reconstruct(dim_sketch, dim_sketch * num_sketch);

  matrix_d_.reconstruct(dim_sketch, dim_sketch);
  matrix_z_.reconstruct(dim_sketch, dim_sketch);
  matrix_c_.reconstruct(dim_sketch, dim_sketch);

  matrix_xj_.reconstruct(nrow_each, dim_sketch);
  matrix_tmp_.reconstruct(nrow_each, dim_sketch);

  vector_e_.reconstruct(dim_sketch);
  vector_f_.reconstruct(dim_sketch);

  syev_driver_.reconstruct(dim_sketch);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Integrates.
///
/// @param  collection_qj  The matrix collection Qj (row-block).
/// @param  matrix_qbarj   The matrix Qjbar (row-block)..
///
template <typename _Val>
void Integrator<RowBlockKolmogorovNagumoIntegratorTag, _Val>::runImpl(
    const DenseMatrixCollection120<ValType> &collection_qj,
          DenseMatrixRowMajor<ValType> &matrix_qbarj
) noexcept {

  const auto mpi_comm   = parameters_.mpi_comm;
  const auto nrow_each  = parameters_.nrowEach();
  const auto dim_sketch = parameters_.dimSketch();
  const auto num_sketch = parameters_.numSketch();

  mcnla_assert_eq(collection_qj.sizes(), std::make_tuple(nrow_each, dim_sketch, num_sketch));
  mcnla_assert_eq(matrix_qbarj.sizes(),  std::make_tuple(nrow_each, dim_sketch));

  auto &matrix_qjs = collection_qj.unfold();  // matrix Qs.
  auto &matrix_qcj = matrix_qbarj;  // matrix Qc.

  moments_.emplace_back(MPI_Wtime());  // copying Qc

  // Qc := Q0
  la::copy(collection_qj(0), matrix_qcj);

  moments_.emplace_back(MPI_Wtime());  // iterating

  time2c_ = 0;
  bool is_converged = false;
  double moment2c;
  for ( iteration_ = 0; iteration_ < max_iteration_ && !is_converged; ++iteration_ ) {

    // ================================================================================================================== //
    // X = (I - Qc * Qc') * sum(Qi * Qi')/N * Qc

    // Bs := sum( Qcj' * Qjs )
    la::mm(matrix_qcj.t(), matrix_qjs, matrix_bs_);
    moment2c = MPI_Wtime();
    mpi::allreduce(matrix_bs_, MPI_SUM, mpi_comm);
    time2c_ += MPI_Wtime() - moment2c;

    // D := Bs * Bs'
    la::rk(matrix_bs_, matrix_d_.viewSymmetric());

    // Xj := 1/N * Qjs * Bs'
    la::mm(matrix_qjs, matrix_bs_.t(), matrix_xj_, 1.0/num_sketch);

    // Xj -= 1/N * Qcj * D
    la::mm(matrix_qcj, matrix_d_.viewSymmetric(), matrix_xj_, -1.0/num_sketch, 1.0);

    // ================================================================================================================== //
    // C := sqrt( I/2 + sqrt( I/4 - X' * X ) )

    // Z := sum(Xj' * Xj)
    la::rk(matrix_xj_.t(), matrix_z_.viewSymmetric());
    moment2c = MPI_Wtime();
    mpi::allreduce(matrix_z_, MPI_SUM, mpi_comm);
    time2c_ += MPI_Wtime() - moment2c;

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
    la::copy(matrix_qcj.vectorize(), matrix_tmp_.vectorize());
    la::mm(matrix_tmp_, matrix_c_.viewSymmetric(), matrix_qcj);

    // Qc += X * inv(C)
    la::mm(matrix_xj_, matrix_d_.viewSymmetric(), matrix_qcj, 1.0, 1.0);

    // ================================================================================================================== //
    // Check convergence
    vector_e_.val().valarray() -= 1.0;
    is_converged = !(la::nrm2(vector_e_) / std::sqrt(dim_sketch) >= tolerance_);
  }

  moments_.emplace_back(MPI_Wtime());  // end
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
/// @brief  Gets the communication time of iterating.
///
template <typename _Val>
double Integrator<RowBlockKolmogorovNagumoIntegratorTag, _Val>::time2c() const noexcept {
  mcnla_assert_true(this->isComputed());
  return time2c_;
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
  return *this;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_KOLMOGOROV_NAGUMO_INTEGRATOR_HPP_