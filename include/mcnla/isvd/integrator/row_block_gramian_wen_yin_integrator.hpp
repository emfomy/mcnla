////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/row_block_gramian_wen_yin_integrator.hpp
/// @brief   The Gramian Wen-Yin line search integrator (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_GRAMIAN_WEN_YIN_INTEGRATOR_HPP_
#define MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_GRAMIAN_WEN_YIN_INTEGRATOR_HPP_

#include <mcnla/isvd/integrator/row_block_gramian_wen_yin_integrator.hh>
#include <mcnla/core/la.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP Integrator<RowBlockGramianWenYinIntegratorTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP RowBlockGramianWenYinIntegrator<_Val>
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

  collection_bc_.reconstruct(dim_sketch_total, dim_sketch, 2);
  matrix_bgc_.reconstruct(dim_sketch_total, dim_sketch);

  collection_dc_.reconstruct(dim_sketch, dim_sketch, 2);
  matrix_dgc_.reconstruct(dim_sketch, dim_sketch);

  matrix_c_.reconstruct(2*dim_sketch, 2*dim_sketch);

  collection_ff_.reconstruct(dim_sketch, dim_sketch, 2);
  collection_ee_.reconstruct(dim_sketch_total, dim_sketch, 2);

  matrix_phi1_.reconstruct(dim_sketch, dim_sketch);
  matrix_phi2_.reconstruct(dim_sketch, dim_sketch);
  matrix_upsolon1_.reconstruct(dim_sketch_total, dim_sketch);
  matrix_upsolon2_.reconstruct(dim_sketch_total, dim_sketch);

  matrix_bct_upsolon1_.reconstruct(dim_sketch, dim_sketch);
  matrix_bct_upsolon2_.reconstruct(dim_sketch, dim_sketch);
  matrix_bs_upsolon_.reconstruct(dim_sketch_total, dim_sketch);

  getrfi_driver_.reconstruct(matrix_c_);
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

  auto &matrix_qsj  = collection_qj.unfold();  // matrix Qs.
  auto &matrix_q0j  = collection_qj(0);        // matrix Q0.
  auto &symatrix_bs = matrix_bs_.syml();       // matrix Bs.

  _Val one_n = 1.0/num_sketch, one_2n = 0.5/num_sketch;
  _Val taug, zeta, phi, mu;

  this->tic(); double comm_moment, comm_time = 0;
  // ====================================================================================================================== //
  // Initializing

  {

    auto &&matrix_bc  = collection_bc_(0);  // matrix Bc.
    auto &&matrix_dc  = collection_dc_(0);  // matrix Dc.
    auto &&matrix_ffc = collection_ff_(0);  // matrix F~c.
    auto &&matrix_eec = collection_ee_(0);  // matrix E~c.

    la::memset0(matrix_bs_({0, dim_sketch}, ""_));

    // Bs := Qs' * Qs
    la::rk(matrix_qsj.t(), symatrix_bs);
    comm_moment = utility::getTime();
    mpi::allreduce(matrix_bs_, MPI_SUM, mpi_comm);
    comm_time = utility::getTime() - comm_moment;

    // Bc := Qs' * Q0
    la::copy(matrix_bs_(""_, {0, dim_sketch}), matrix_bc);

    // Bgc := 1/N * Bs * Bc
    la::mm(symatrix_bs, matrix_bc, matrix_bgc_, one_n);

    // Dc := 1/N * Bc' * Bc
    la::mm(matrix_bc.t(), matrix_bc, matrix_dc, one_n);

    // Dgc := 1/N * Bc' * Bgc
    la::mm(matrix_bc.t(), matrix_bgc_, matrix_dgc_, one_n);

    // F~ := I, E~ := O
    la::memset0(matrix_ffc);
    la::memset0(matrix_eec);
    for ( index_t i = 0; i < dim_sketch; ++i ) {
      matrix_ffc(i, i) = 1.0;
    }

    // taug := tau0; zeta := 1; phi := 1/2N * norm( Bc )_F
    taug = tau0_, zeta = 1.0, phi = one_2n * la::dot(matrix_bc.vec());

    // mu := tr( Dgc ) - norm( Dc )_F
    mu = la::asum(matrix_dgc_.diag().vec()) - la::dot(matrix_dc.vec());

  }

  this->toc(comm_time);
  // ====================================================================================================================== //
  // Iterating

  bool is_converged = false;
  bool is_odd = false;
  for ( iteration_ = 0; iteration_ < max_iteration_ && !is_converged; ++iteration_ ) {

    auto idxs1 = I_{0_i, dim_sketch};
    auto idxs2 = idxs1 + dim_sketch;
    auto &&matrix_c11 = matrix_c_(idxs1, idxs1);  // matrix C11
    auto &&matrix_c12 = matrix_c_(idxs1, idxs2);  // matrix C12
    auto &&matrix_c21 = matrix_c_(idxs2, idxs1);  // matrix C21
    auto &&matrix_c22 = matrix_c_(idxs2, idxs2);  // matrix C22
    auto &&matrix_cs1 = matrix_c_(""_, idxs1);    // matrix C#1
    auto &&matrix_cs2 = matrix_c_(""_, idxs2);    // matrix C#2

    auto &&matrix_bc  = collection_bc_(is_odd);   // matrix Bc.
    auto &&matrix_bp  = collection_bc_(!is_odd);  // matrix B+.
    auto &&matrix_dc  = collection_dc_(is_odd);   // matrix Dc.
    auto &&matrix_dp  = collection_dc_(!is_odd);  // matrix D+.
    auto &&matrix_ffc = collection_ff_(is_odd);   // matrix F~c.
    auto &&matrix_ffp = collection_ff_(!is_odd);  // matrix F~+.
    auto &&matrix_eec = collection_ee_(is_odd);   // matrix E~c.
    auto &&matrix_eep = collection_ee_(!is_odd);  // matrix E~+.
    auto &matrix_fc   = matrix_c21;  // matrix Fc
    auto &matrix_fgc  = matrix_c11;  // matrix Fgc
    is_odd = !is_odd;

    // ================================================================================================================== //
    // Find step size
    _Val tau = taug, phit = phi;
    for ( auto tauiter = 0; tauiter < taumaxiter_; ++tauiter, tau *= beta_ ) {

      // C := [ Dc/2 - I/tau , I/2          ;
      //       -Dgc/2,        -Dc/2 - I/tau ]
      la::memset0(matrix_c_);
      la::omatcopy(matrix_dc,  matrix_c11,  0.5);
      la::omatcopy(matrix_dgc_, matrix_c21, -0.5);
      la::omatcopy(matrix_dc,  matrix_c22, -0.5);
      for ( auto &v : matrix_c11.getDiag() ) { v -= 1.0/tau; }
      for ( auto &v : matrix_c12.getDiag() ) { v += 0.5; }
      for ( auto &v : matrix_c22.getDiag() ) { v -= 1.0/tau; }

      // Compute inv(C)
      getrfi_driver_(matrix_c_);

      // Fc  [in C21] := I + inv(C22) * Dc - inv(C21)
      // Fgc [in C11] :=     inv(C12) * Dc - inv(C21)
      la::mm(matrix_cs2, matrix_dc, matrix_cs1, 1.0, -1.0);
      for ( auto &v : matrix_c21.getDiag() ) { v += 1.0; }

      // B+ := Bc * Fc + Bgc * Fgc
      la::mm(matrix_bc,   matrix_fc, matrix_bp);
      la::mm(matrix_bgc_, matrix_fgc, matrix_bp, 1.0, 1.0);

      // ~phi := 1/2N * norm( Bp )_F
      phit = one_2n * la::dot(matrix_bp.vec());

      // Check condition
      if ( phit >= phi + tau * sigma_ * mu ) {
        break;
      }
    }

    // ================================================================================================================== //
    // Update for next iteration

    // Update phi and zeta
    phi = (eta_ * zeta * phi + phit) / (eta_ * zeta + 1);
    zeta = eta_ * zeta + 1;

    // Ec [in Upsilon1] := 1/N * Bc * Fgc
    la::mm(matrix_bc, matrix_fgc, matrix_upsolon1_, one_n);

    // F~p := F~c * Fc
    la::mm(matrix_ffc, matrix_fc, matrix_ffp);

    // E~p := E~c * Fc + Ec [in Upsilon1]
    la::copy(matrix_upsolon1_, matrix_eep);
    la::mm(matrix_eec, matrix_fc, matrix_upsolon1_, 1.0, 1.0);

    // Bg+[in Bgc] := 1/N * Bs * B+
    la::mm(symatrix_bs, matrix_bp, matrix_bgc_, one_n);

    // D+ := 1/N * B+' * B+
    la::mm(matrix_bp.t(), matrix_bp, matrix_dp, one_n);

    // Dg+ [in Dgc] := 1/N * Bc' * Bg+ [in Bgc]
    la::mm(matrix_bc.t(), matrix_bgc_, matrix_dgc_, one_n);

    // mu := tr( Dg+ [in Dgc] ) - norm( D+ )_F
    mu = la::asum(matrix_dgc_.diag().vec()) - la::dot(matrix_dp.vec());

    // ================================================================================================================== //
    // Check convergence: mu  < tol^2
    if ( mu < tolerance_ * tolerance_ ) {
      ++iteration_;
      break;
    }

    // ================================================================================================================== //
    // Update taug

    // Phi2 := Dc - Fc * D+
    la::copy(matrix_dc, matrix_phi2_);
    la::mm(matrix_fc, matrix_dp, matrix_phi2_, -1.0, 1.0);

    // Phi1 := Fc - I
    la::copy(matrix_fc, matrix_phi1_);
    for ( auto &v : matrix_fc.getDiag() ) { v -= 1.0; }

    // Upsilon2 := 1/N * (B+ - Bc) - Ec [in Upsilon1] * D+
    la::copy(matrix_bp, matrix_upsolon2_);
    la::axpy(matrix_bc.vec(), matrix_upsolon2_.vec(), -1.0);
    la::mm(matrix_upsolon1_, matrix_dp, matrix_upsolon2_, -1.0, one_n);

    // Compute Bc' * Upsilon1
    la::mm(matrix_bc.t(), matrix_upsolon1_, matrix_bct_upsolon1_);

    // Compute Bc' * Upsilon2
    la::mm(matrix_bc.t(), matrix_upsolon2_, matrix_bct_upsolon2_);

    // Update taug
    _Val t1, t2;

    if ( is_odd ) {
      // Compute Bs * Upsilon1
      la::mm(symatrix_bs, matrix_upsolon1_, matrix_bs_upsolon_);

      // t1 := tr( Phi1' * Phi1 ) + 2 tr( Phi1' * Bc' * Upsilon1 ) + tr( Upsilon1' * Bs * Upsilon1 )
      t1 = la::dot(matrix_phi1_.vec())
         + 2 * la::dot(matrix_phi1_.vec(), matrix_bct_upsolon1_.vec())
         + la::dot(matrix_upsolon1_.vec(), matrix_bs_upsolon_.vec());

      // t2 := tr( Phi1' * Phi2 ) + tr( Phi1' * Bc' * Upsilon2 )
      //     + tr( Phi2' * Bc' * Upsilon1 ) + tr( Upsilon2' * Bs * Upsilon1 )
      t2 = la::dot(matrix_phi1_.vec(), matrix_phi2_.vec())
         + la::dot(matrix_phi1_.vec(), matrix_bct_upsolon2_.vec())
         + la::dot(matrix_phi2_.vec(), matrix_bct_upsolon1_.vec())
         + la::dot(matrix_upsolon2_.vec(), matrix_bs_upsolon_.vec());
    } else {
      // Compute Bs * Upsilon2
      la::mm(symatrix_bs, matrix_upsolon2_, matrix_bs_upsolon_);

      // t1 := tr( Phi1' * Phi2 ) + tr( Phi1' * Bc' * Upsilon2 )
      //     + tr( Phi2' * Bc' * Upsilon1 ) + tr( Upsilon1' * Bs * Upsilon2 )
      t1 = la::dot(matrix_phi1_.vec(), matrix_phi2_.vec())
         + la::dot(matrix_phi1_.vec(), matrix_bct_upsolon2_.vec())
         + la::dot(matrix_phi2_.vec(), matrix_bct_upsolon1_.vec())
         + la::dot(matrix_upsolon1_.vec(), matrix_bs_upsolon_.vec());

      // t2 := tr( Phi2' * Phi2 ) + 2 tr( Phi2' * Bc' * Upsilon2 ) + tr( Upsilon2' * Bs * Upsilon2 )
      t2 = la::dot(matrix_phi2_.vec())
         + 2 * la::dot(matrix_phi2_.vec(), matrix_bct_upsolon2_.vec())
         + la::dot(matrix_upsolon2_.vec(), matrix_bs_upsolon_.vec());
    }

    taug = std::abs(t1/t2);
    if ( taug < taumin_ ) { taug = taumin_; }
    if ( taug > taumax_ ) { taug = taumax_; }

  }

  this->toc(comm_time);
  // ====================================================================================================================== //
  // Forming Qbar

  auto &&matrix_ff = collection_ff_(is_odd);  // matrix F~.
  auto &&matrix_ee = collection_ee_(is_odd);  // matrix E~.

  // Qbar := Q0 * F~ + Qs * E~
  la::mm(matrix_q0j, matrix_ff, matrix_qbarj);
  la::mm(matrix_qsj, matrix_ee, matrix_qbarj, 1.0, 1.0);

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
RowBlockGramianWenYinIntegrator<_Val>& MCNLA_TMP::setMaxIteration(
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
RowBlockGramianWenYinIntegrator<_Val>& MCNLA_TMP::setTolerance(
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

#endif  // MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_GRAMIAN_WEN_YIN_INTEGRATOR_HPP_
