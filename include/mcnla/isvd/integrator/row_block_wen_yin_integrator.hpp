////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/row_block_wen_yin_integrator.hpp
/// @brief   The Wen-Yin line search integrator (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_WEN_YIN_INTEGRATOR_HPP_
#define MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_WEN_YIN_INTEGRATOR_HPP_

#include <mcnla/isvd/integrator/row_block_wen_yin_integrator.hh>
#include <mcnla/core/la.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP  Integrator<RowBlockWenYinIntegratorTag, _Val>
  #define MCNLA_TMP0 Integrator
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP  RowBlockWenYinIntegrator<_Val>
  #define MCNLA_TMP0 RowBlockWenYinIntegrator
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
MCNLA_TMP::MCNLA_TMP0(
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

  collection_qcj_.reconstruct(nrow_rank, dim_sketch, 2);
  matrix_gcj_.reconstruct(nrow_rank, dim_sketch);
  collection_xcj_.reconstruct(nrow_rank, dim_sketch, 2);

  collection_bc_.reconstruct(dim_sketch_total, dim_sketch, 2);
  matrix_bgc_.reconstruct(dim_sketch_total, dim_sketch);

  matrix_dc_.reconstruct(dim_sketch, dim_sketch);
  matrix_dgc_.reconstruct(dim_sketch, dim_sketch);

  matrix_c_.reconstruct(2*dim_sketch, 2*dim_sketch);

  vector_t_.reconstruct(2);

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

  auto &matrix_qsj = collection_qj.unfold();  // matrix Qs.

  _Val one_n = 1.0/num_sketch, one_2n = 0.5/num_sketch;
  _Val taug, zeta, phi, mu;

  this->tic(); double comm_moment, comm_time = 0;
  // ====================================================================================================================== //
  // Initializing

  {

    auto &&matrix_bc  = collection_bc_(0);   // matrix Bc.
    auto &&matrix_qcj = collection_qcj_(0);  // matrix Qc.
    auto &&matrix_xcj = collection_xcj_(0);  // matrix Xc.

    // Qc := Q0
    la::copy(collection_qj(0), matrix_qcj);

    // Bc := Qs' * Qc
    la::mm(matrix_qsj.t(), matrix_qcj, matrix_bc);
    comm_moment = utility::getTime();
    mpi::allreduce(matrix_bc, MPI_SUM, mpi_comm);
    comm_time += utility::getTime() - comm_moment;

    // Dc := 1/N * Bc' * Bc
    la::mm(matrix_bc.t(), matrix_bc, matrix_dc_, one_n);

    // Gc := 1/N * Qs * Bc
    la::mm(matrix_qsj, matrix_bc, matrix_gcj_, one_n);

    // Bgc := Qs' * Gc
    la::mm(matrix_qsj.t(), matrix_gcj_, matrix_bgc_);
    comm_moment = utility::getTime();
    mpi::allreduce(matrix_bgc_, MPI_SUM, mpi_comm);
    comm_time += utility::getTime() - comm_moment;

    // Dgc := 1/N * Bc' * Bgc
    la::mm(matrix_bc.t(), matrix_bgc_, matrix_dgc_, one_n);

    // Xc := Gc - Qc * Dc
    la::copy(matrix_gcj_, matrix_xcj);
    la::mm(matrix_qcj, matrix_dc_, matrix_xcj, -1.0, 1.0);

    // taug := tau0; zeta := 1; phi := 1/2N * norm( Bc )_F
    taug = tau0_, zeta = 1.0, phi = one_2n * la::dot(matrix_bc.vec());

    // mu := tr( Dgc ) - norm( Dc )_F
    mu = la::asum(matrix_dgc_.diag().vec()) - la::dot(matrix_dc_.vec());

  }

  this->toc(comm_time);
  // ====================================================================================================================== //
  // Iterating

  bool is_odd = false;
  for ( iteration_ = 0; iteration_ < max_iteration_; ++iteration_ ) {

    auto idxs1 = I_{0_i, dim_sketch};
    auto idxs2 = idxs1 + dim_sketch;
    auto &&matrix_c11 = matrix_c_(idxs1, idxs1);  // matrix C11
    auto &&matrix_c12 = matrix_c_(idxs1, idxs2);  // matrix C12
    auto &&matrix_c21 = matrix_c_(idxs2, idxs1);  // matrix C21
    auto &&matrix_c22 = matrix_c_(idxs2, idxs2);  // matrix C22
    auto &&matrix_cs1 = matrix_c_(""_, idxs1);    // matrix C#1
    auto &&matrix_cs2 = matrix_c_(""_, idxs2);    // matrix C#2

    auto &&matrix_bc  = collection_bc_(is_odd);    // matrix Bc.
    auto &&matrix_bp  = collection_bc_(!is_odd);   // matrix B+.
    auto &&matrix_qcj = collection_qcj_(is_odd);   // matrix Qc.
    auto &&matrix_qpj = collection_qcj_(!is_odd);  // matrix Q+.
    auto &&matrix_xcj = collection_xcj_(is_odd);   // matrix Xc.
    auto &&matrix_xpj = collection_xcj_(!is_odd);  // matrix X+.
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
      la::omatcopy(matrix_dc_,  matrix_c11,  0.5);
      la::omatcopy(matrix_dgc_, matrix_c21, -0.5);
      la::omatcopy(matrix_dc_,  matrix_c22, -0.5);
      for ( auto &v : matrix_c11.getDiag() ) { v -= 1.0/tau; }
      for ( auto &v : matrix_c12.getDiag() ) { v += 0.5; }
      for ( auto &v : matrix_c22.getDiag() ) { v -= 1.0/tau; }

      // Compute inv(C)
      getrfi_driver_(matrix_c_);

      // Fc  [in C21] := I + inv(C22) * Dc - inv(C21)
      // Fgc [in C11] :=     inv(C12) * Dc - inv(C21)
      la::mm(matrix_cs2, matrix_dc_, matrix_cs1, 1.0, -1.0);
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

    // Q+ := Qc * Fc + Gc * Fgc
    la::mm(matrix_qcj, matrix_fc, matrix_qpj);
    la::mm(matrix_gcj_, matrix_fgc, matrix_qpj, 1.0, 1.0);

    // D+ [in Dc] := 1/N * B+' * B+
    la::mm(matrix_bp.t(), matrix_bp, matrix_dc_, one_n);

    // G+ [in Gc] := 1/N * Qs * B+
    la::mm(matrix_qsj, matrix_bp, matrix_gcj_, one_n);

    // Bg+ [in Bgc] := Qs' * G+ [in Gc]
    la::mm(matrix_qsj.t(), matrix_gcj_, matrix_bgc_);
    comm_moment = utility::getTime();
    mpi::allreduce(matrix_bgc_, MPI_SUM, mpi_comm);
    comm_time += utility::getTime() - comm_moment;

    // Dg+ [in Dgc] := 1/N * B+' * Bg+ [in Bgc]
    la::mm(matrix_bp.t(), matrix_bgc_, matrix_dgc_, one_n);

    // mu := tr( Dg+ [in Dgc] ) - norm( D+ [in Dc] )_F
    mu = la::asum(matrix_dgc_.diag().vec()) - la::dot(matrix_dc_.vec());

    // ================================================================================================================== //
    // Check convergence: mu  < tol^2
    if ( mu < tolerance_ * tolerance_ ) {
      ++iteration_;
      break;
    }

    // ================================================================================================================== //
    // Update taug

    // X+ := G+ [in Gc] - Q+ * D+ [in Dc]
    la::copy(matrix_gcj_, matrix_xpj);
    la::mm(matrix_qpj, matrix_dc_, matrix_xpj, -1.0, 1.0);

    // Delta1 [in Qc] := Qc - Q+; Delta2 [in Xc] := Xc - X+
    la::axpy(matrix_qpj.vec(), matrix_qcj.vec(), -1.0);
    la::axpy(matrix_xpj.vec(), matrix_xcj.vec(), -1.0);

    // Update taug
    auto &t1 = vector_t_(0);
    auto &t2 = vector_t_(1);

    if ( is_odd ) {
      t1 = la::dot(matrix_qcj.vec());
      t2 = la::dot(matrix_qcj.vec(), matrix_xcj.vec());
    } else {
      t1 = la::dot(matrix_qcj.vec(), matrix_xcj.vec());
      t2 = la::dot(matrix_xcj.vec());
    }

    comm_moment = utility::getTime();
    mpi::allreduce(vector_t_, MPI_SUM, mpi_comm);
    comm_time += utility::getTime() - comm_moment;

    taug = std::abs(t1/t2);
    if ( taug < taumin_ ) { taug = taumin_; }
    if ( taug > taumax_ ) { taug = taumax_; }
  }

  // Copy Qbar
  la::copy(collection_qcj_(is_odd).vec(), matrix_qbarj.vec());

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
MCNLA_TMP& MCNLA_TMP::setMaxIteration(
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
MCNLA_TMP& MCNLA_TMP::setTolerance(
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
#undef MCNLA_TMP0

#endif  // MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_WEN_YIN_INTEGRATOR_HPP_
