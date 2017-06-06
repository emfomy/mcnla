////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/row_block_gramian_kolmogorov_nagumo_integrator.hpp
/// @brief   The Gramian Kolmogorov-Nagumo-type integrator (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_GRAMIAN_KOLMOGOROV_NAGUMO_INTEGRATOR_HPP_
#define MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_GRAMIAN_KOLMOGOROV_NAGUMO_INTEGRATOR_HPP_

#include <mcnla/isvd/integrator/row_block_gramian_kolmogorov_nagumo_integrator.hh>
#include <mcnla/core/la.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP Integrator<RowBlockGramianKolmogorovNagumoIntegratorTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP RowBlockGramianKolmogorovNagumoIntegrator<_Val>
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

  const auto dim_sketch       = parameters_.dimSketch();
  const auto dim_sketch_total = parameters_.dimSketchTotal();

  matrix_bs_.reconstruct(dim_sketch_total, dim_sketch_total);
  collection_b_.reconstruct(dim_sketch, dim_sketch_total, 2);

  matrix_d_.reconstruct(dim_sketch, dim_sketch);
  matrix_z_.reconstruct(dim_sketch, dim_sketch);
  matrix_c_.reconstruct(dim_sketch, dim_sketch);
  matrix_cinv_.reconstruct(dim_sketch, dim_sketch);

  collection_ft_.reconstruct(dim_sketch, dim_sketch, 2);
  collection_et_.reconstruct(dim_sketch_total, dim_sketch, 2);

  vector_l_.reconstruct(dim_sketch);
  vector_ls_.reconstruct(dim_sketch);

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

  auto &matrix_qsj  = collection_qj.unfold();                  // matrix Qs.
  auto &matrix_q0j  = collection_qj(0);                        // matrix Q0.
  auto &symatrix_bs = matrix_bs_.template sym<Uplo::UPPER>();  // matrix Bs.

  _Val one_n = 1.0/num_sketch, one_n2 = (1.0/num_sketch)/num_sketch;
  this->tic(); double comm_moment, comm_time = 0;
  // ====================================================================================================================== //
  // Initializing

  la::memset0(matrix_bs_({0, dim_sketch}, ""_));

  // Bs := Qs' * Qs
  la::rk(matrix_qsj.t(), symatrix_bs);
  comm_moment = utility::getTime();
  mpi::allreduce(matrix_bs_, MPI_SUM, mpi_comm);
  comm_time = utility::getTime() - comm_moment;

  // Bc := Q0' * Qs
  la::copy(matrix_bs_({0, dim_sketch}, ""_), collection_b_(0));

  // F := I, E := O
  la::memset0(collection_ft_(0));
  la::memset0(collection_et_(0));
  for ( index_t i = 0; i < dim_sketch; ++i ) {
    collection_ft_(0)(i, i) = 1.0;
  }

  this->toc(comm_time);
  // ====================================================================================================================== //
  // Iterating

  bool is_converged = false;
  bool is_odd = false;
  for ( iteration_ = 0; iteration_ < max_iteration_ && !is_converged; ++iteration_ ) {

    auto &&matrix_bc  = collection_b_(is_odd);    // matrix Bc.
    auto &&matrix_ftc = collection_ft_(is_odd);   // matrix ~Fc.
    auto &&matrix_etc = collection_et_(is_odd);   // matrix ~Ec.
    auto &&matrix_bp  = collection_b_(!is_odd);   // matrix B+.
    auto &&matrix_ffp = collection_ft_(!is_odd);  // matrix ~F+.
    auto &&matrix_efp = collection_et_(!is_odd);  // matrix ~E+.
    auto &matrix_f    = matrix_c_;                // matrix F.
    auto &matrix_e    = matrix_efp;               // matrix E.
    is_odd = !is_odd;

    // ================================================================================================================== //
    // Z := 1/N^2 * Bc * Bs * Bc' - 1/N^2 * Bc * Bc' * Bc * Bc'

    // Dc := 1/N * Bc * Bc'
    la::mm(matrix_bc, matrix_bc.t(), matrix_d_, one_n);

    // Z := 1/N^2 * Bc * Bs * Bc' - Dc^2
    la::mm(matrix_bc, symatrix_bs, matrix_bp);
    la::mm(matrix_bp, matrix_bc.t(), matrix_z_, one_n2);
    la::rk(matrix_d_, matrix_z_.sym(), -1.0, 1.0);

    // ================================================================================================================== //
    // C := sqrt( I/2 + sqrt( I/4 - Z ) )

    // Compute the eigen-decomposition of Z -> Z' * L * Z
    syev_driver_(matrix_z_.sym(), vector_l_);

    // L := sqrt( I/2 + sqrt( I/4 - L ) )
    for ( index_t i = 0; i < dim_sketch; ++i ) {
      vector_l_(i) = std::sqrt(0.5 + std::sqrt(0.25 - vector_l_(i)));
      vector_ls_(i) = std::sqrt(vector_l_(i));
    }

    // Tmp := L * Z
    la::mm(vector_ls_.diag(), matrix_z_, matrix_cinv_);

    // Z := L \ Z
    la::sm(vector_ls_.diag().inv(), matrix_z_);

    // C := Tmp' * Tmp
    la::mm(matrix_cinv_.t(), matrix_cinv_, matrix_c_);

    // inv(C) := Z' * Z
    la::mm(matrix_z_.t(), matrix_z_, matrix_cinv_);

    // ================================================================================================================== //
    // Compute F and E

    // Fc := C - Dc * inv(C)
    la::mm(matrix_d_, matrix_cinv_, matrix_f, -1.0, 1.0);

    // Ec := 1/N * Bc' * inv(C)
    la::mm(matrix_bc.t(), matrix_cinv_, matrix_e, one_n);

    // ================================================================================================================== //
    // Update Bc

    // Bp := Fc' * Bc + Ec' * Bs
    la::mm(matrix_f.t(), matrix_bc, matrix_bp);
    la::mm(matrix_e.t(), symatrix_bs, matrix_bp, 1.0, 1.0);

    // ================================================================================================================== //
    // Update ~F and ~E

    // ~Fp := ~Fc * Fc
    la::mm(matrix_ftc, matrix_f, matrix_ffp);

    // ~Ep := ~Ec * Fc + Ec
    la::mm(matrix_etc, matrix_f, matrix_efp, 1.0, 1.0);

    // ================================================================================================================== //
    // Check convergence: || I - C ||_F / sqrt(k) < tol
    for ( auto &v : vector_l_ ) {
      v -= 1.0;
    }
    is_converged = !(la::nrm2(vector_l_) / std::sqrt(dim_sketch) >= tolerance_);
  }

  this->toc(comm_time);
  // ====================================================================================================================== //
  // Forming Qbar

  auto &&matrix_ft = collection_ft_(is_odd);  // matrix ~F.
  auto &&matrix_et = collection_et_(is_odd);  // matrix ~E.

  // Qj := Q0j * ~F + Qsj * ~E
  la::mm(matrix_q0j, matrix_ft, matrix_qbarj);
  la::mm(matrix_qsj, matrix_et, matrix_qbarj, 1.0, 1.0);

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
RowBlockGramianKolmogorovNagumoIntegrator<_Val>& MCNLA_TMP::setMaxIteration(
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
RowBlockGramianKolmogorovNagumoIntegrator<_Val>& MCNLA_TMP::setTolerance(
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

#endif  // MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_GRAMIAN_KOLMOGOROV_NAGUMO_INTEGRATOR_HPP_
