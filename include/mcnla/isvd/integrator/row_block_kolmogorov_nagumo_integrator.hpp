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

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP Integrator<RowBlockKolmogorovNagumoIntegratorTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP RowBlockKolmogorovNagumoIntegrator<_Val>
#endif  // DOXYGEN_SHOULD_SKIP_THIS

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
MCNLA_TMP::Integrator(
    const Parameters<_Val> &parameters,
    const index_t max_iteration,
    const RealValT<_Val> tolerance
) noexcept
  : BaseType(parameters) {
  setMaxIteration(max_iteration);
  setTolerance(tolerance);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::StageWrapper::initialize
///
template <typename _Val>
void MCNLA_TMP::initializeImpl() noexcept {

  const auto nrow_rank        = parameters_.nrowRank();
  const auto dim_sketch       = parameters_.dimSketch();
  const auto dim_sketch_total = parameters_.dimSketchTotal();

  matrix_qpj_.reconstruct(nrow_rank, dim_sketch);
  matrix_gcj_.reconstruct(nrow_rank, dim_sketch);

  collection_b_.reconstruct(dim_sketch_total, dim_sketch, 2);
  matrix_bgc_.reconstruct(dim_sketch_total, dim_sketch);

  matrix_dc_.reconstruct(dim_sketch, dim_sketch);
  symatrix_z_.reconstruct(dim_sketch);
  matrix_c_.reconstruct(dim_sketch, dim_sketch);
  symatrix_cinv_.reconstruct(dim_sketch);

  vector_s_.reconstruct(dim_sketch);
  vector_ss_.reconstruct(dim_sketch);

  syev_driver_.reconstruct(dim_sketch);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Integrates.
///
/// @param  collection_qj  The matrix collection Qj (j-th row-block, where j is the MPI rank).
/// @param  matrix_qbarj   The matrix Qbarj (j-th row-block, where j is the MPI rank).
///
template <typename _Val>
void MCNLA_TMP::runImpl(
    const DenseMatrixCollectionColBlockRowMajor<_Val> &collection_qj,
          DenseMatrixRowMajor<_Val> &matrix_qbarj
) noexcept {

  const auto mpi_comm   = parameters_.mpi_comm;
  const auto nrow_rank  = parameters_.nrowRank();
  const auto dim_sketch = parameters_.dimSketch();
  const auto num_sketch = parameters_.numSketch();

  static_cast<void>(nrow_rank);

  mcnla_assert_eq(collection_qj.sizes(), std::make_tuple(nrow_rank, dim_sketch, num_sketch));
  mcnla_assert_eq(matrix_qbarj.sizes(),  std::make_tuple(nrow_rank, dim_sketch));

  auto &matrix_qsj = collection_qj.unfold();  // matrix Qs.

  _Val one_n = 1.0/num_sketch;
  this->tic(); double comm_moment, comm_time = 0;
  // ====================================================================================================================== //
  // Copying Qc

  // Qc := Q0
  la::copy(collection_qj(0), matrix_qbarj);

  // Bc := Qs' * Qc
  la::mm(matrix_qsj.t(), matrix_qbarj, collection_b_(0));
  comm_moment = utility::getTime();
  mpi::allreduce(collection_b_(0), MPI_SUM, mpi_comm);
  comm_time += utility::getTime() - comm_moment;

  this->toc(comm_time);
  // ====================================================================================================================== //
  // Iterating

  bool is_converged = false;
  bool is_odd = false;
  for ( iteration_ = 0; iteration_ < max_iteration_ && !is_converged; ++iteration_ ) {

    auto &&matrix_bc = collection_b_(is_odd);   // matrix Bc.
    auto &&matrix_bp = collection_b_(!is_odd);  // matrix B+.
    auto &matrix_qcj = !is_odd ? matrix_qbarj : matrix_qpj_;  // matrix Qc.
    auto &matrix_qpj =  is_odd ? matrix_qbarj : matrix_qpj_;  // matrix Q+.
    is_odd = !is_odd;

    // ================================================================================================================== //
    // Compute B, D, and G

    // Gcj := 1/N * Qsj * Bc
    la::mm(matrix_qsj, matrix_bc, matrix_gcj_, one_n);

    // Bgc := Qs' * Gc
    la::mm(matrix_qsj.t(), matrix_gcj_, matrix_bgc_);
    comm_moment = utility::getTime();
    mpi::allreduce(matrix_bgc_, MPI_SUM, mpi_comm);
    comm_time += utility::getTime() - comm_moment;

    // Dc := 1/N * Bc' * Bc
    la::mm(matrix_bc.t(), matrix_bc, matrix_dc_, one_n);

    // Dgc(Z) := 1/N * Bc' * Bgc
    la::mm(matrix_bc.t(), matrix_bgc_, symatrix_z_, one_n);

    // ================================================================================================================== //
    // Compute C and inv(C)

    // Z := Dgc - Dc^2
    la::rk(matrix_dc_, symatrix_z_, -1.0, 1.0);

    // Compute the eigen-decomposition of Z -> Z' * S * Z
    syev_driver_(symatrix_z_, vector_s_);

    // S := sqrt( I/2 + sqrt( I/4 - S ) )
    for ( index_t i = 0; i < dim_sketch; ++i ) {
      vector_s_(i) = std::sqrt(0.5 + std::sqrt(0.25 - vector_s_(i)));
      vector_ss_(i) = std::sqrt(vector_s_(i));
    }

    auto &matrix_sz    = symatrix_cinv_.full();
    auto &matrix_sinvz = symatrix_z_.full();

    // Compute sqrt(S) * Z
    la::mm(vector_ss_.diag(), symatrix_z_.full(), matrix_sz);

    // Compute sqrt(S) \ Z
    la::sm(vector_ss_.diag().inv(), matrix_sinvz);

    // C := Z' * S * Z
    la::mm(matrix_sz.t(), symatrix_cinv_.full(), matrix_c_);

    // inv(C) := Z' * inv(S) * Z
    la::rk(matrix_sinvz.t(), symatrix_cinv_);

    // ================================================================================================================== //
    // Compute F

    // Fc(C) := C - Dc * inv(C)
    la::mm(matrix_dc_, symatrix_cinv_, matrix_c_, -1.0, 1.0);

    // ================================================================================================================== //
    // Update Q

    // Q+ := Qc * Fc + Gc * inv(C)
    la::mm(matrix_qcj, matrix_c_, matrix_qpj);
    la::mm(matrix_gcj_, symatrix_cinv_, matrix_qpj, 1.0, 1.0);

    // ================================================================================================================== //
    // Update B

    // B+ := Bc * Fc + Bgc * inv(C)
    la::mm(matrix_bc, matrix_c_, matrix_bp);
    la::mm(matrix_bgc_, symatrix_cinv_, matrix_bp, 1.0, 1.0);

    // ================================================================================================================== //
    // Check convergence: || I - C ||_F < tol
    for ( auto &v : vector_s_ ) {
      v -= 1.0;
    }
    is_converged = !(la::nrm2(vector_s_) >= tolerance_);
  }

  if ( is_odd ) {
    la::copy(matrix_qpj_.vec(), matrix_qbarj.vec());
  }

  this->toc(comm_time);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the maximum number of iteration.
///
template <typename _Val>
index_t MCNLA_TMP::maxIteration() const noexcept {
  return max_iteration_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the tolerance of convergence condition.
///
template <typename _Val>
RealValT<_Val> MCNLA_TMP::tolerance() const noexcept {
  return tolerance_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of iteration.
///
template <typename _Val>
index_t MCNLA_TMP::iteration() const noexcept {
  mcnla_assert_true(this->isComputed());
  return iteration_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the maximum number of iteration.
///
template <typename _Val>
RowBlockKolmogorovNagumoIntegrator<_Val>& MCNLA_TMP::setMaxIteration(
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
RowBlockKolmogorovNagumoIntegrator<_Val>& MCNLA_TMP::setTolerance(
    const RealValT<_Val> tolerance
) noexcept {
  mcnla_assert_ge(tolerance, 0);
  tolerance_ = tolerance;
  initialized_ = false;
  computed_ = false;
  return *this;
}

}  // namespace isvd

}  // namespace mcnla

#undef MCNLA_TMP

#endif  // MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_KOLMOGOROV_NAGUMO_INTEGRATOR_HPP_
