////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/row_block_extrinsic_mean_integrator.hpp
/// @brief   The extrinsic mean integrator (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_EXTRINSIC_MEAN_INTEGRATOR_HPP_
#define MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_EXTRINSIC_MEAN_INTEGRATOR_HPP_

#include <mcnla/isvd/integrator/row_block_extrinsic_mean_integrator.hh>
#include <mcnla/core/la.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP Integrator<RowBlockExtrinsicMeanIntegratorTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP RowBlockExtrinsicMeanIntegrator<_Val>
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
    const Parameters<_Val> &parameters
) noexcept
  : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::StageWrapper::initialize
///
template <typename _Val>
void MCNLA_TMP::initializeImpl() noexcept {

  const auto nrow             = parameters_.nrow();
  const auto dim_sketch       = parameters_.dimSketch();
  const auto dim_sketch_total = parameters_.dimSketchTotal();
  const auto num_sketch_each  = parameters_.numSketchEach();

  matrix_bsj_.reconstruct(dim_sketch_total, dim_sketch_total);
  collection_bi_.reconstruct(dim_sketch, dim_sketch_total, num_sketch_each);
  collection_bi0_ = collection_bi_(""_, {0_i, dim_sketch}, ""_);

  collection_g_.reconstruct(dim_sketch, dim_sketch, num_sketch_each);
  matrix_g0_.reconstruct(dim_sketch, dim_sketch);
  matrix_gb_.reconstruct(dim_sketch, dim_sketch);

  vector_s_.reconstruct(dim_sketch);

  gesvd_driver_.reconstruct(nrow, dim_sketch);
  syev_driver_.reconstruct(dim_sketch);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Integrates.
///
/// @param  collection_qj  The matrix collection Qj (j-th row-block, where j is the MPI rank).
/// @param  collection_q   The matrix collection Q.
/// @param  matrix_qbar    The matrix Qbar.
///
template <typename _Val>
void MCNLA_TMP::runImpl(
    const DenseMatrixCollectionColBlockRowMajor<_Val> &collection_qj,
    const DenseMatrixCollectionColBlockRowMajor<_Val> &collection_q,
          DenseMatrixRowMajor<_Val>      &matrix_qbar
) noexcept {

  const auto mpi_comm        = parameters_.mpi_comm;
  const auto mpi_root        = parameters_.mpi_root;
  const auto mpi_rank        = parameters_.mpi_rank;
  const auto nrow            = parameters_.nrow();
  const auto nrow_rank       = parameters_.nrowRank();
  const auto dim_sketch      = parameters_.dimSketch();
  const auto num_sketch      = parameters_.numSketch();
  const auto num_sketch_each = parameters_.numSketchEach();

  static_cast<void>(nrow);
  static_cast<void>(nrow_rank);
  static_cast<void>(num_sketch);

  mcnla_assert_eq(collection_qj.sizes(), std::make_tuple(nrow_rank, dim_sketch, num_sketch));
  mcnla_assert_eq(collection_q.sizes(),  std::make_tuple(nrow, dim_sketch, num_sketch_each));
  mcnla_assert_eq(matrix_qbar.sizes(),   std::make_tuple(nrow, dim_sketch));

  auto &matrix_qsj = collection_qj.unfold();  // matrix Qs.

  this->tic(); double comm_moment, comm_time = 0;
  // ====================================================================================================================== //
  // Rotate

  // Bs := sum( Qsj' * Qsj )
  la::mm(matrix_qsj.t(), matrix_qsj, matrix_bsj_);
  comm_moment = utility::getTime();
  mpi::reduceScatterBlock(matrix_bsj_, collection_bi_.unfold(), MPI_SUM, mpi_comm);
  comm_time = utility::getTime() - comm_moment;

  for ( index_t i = 0; i < num_sketch_each; ++i ) {

    // Gi := Bi * Bi'
    la::rk(collection_bi_(i), collection_g_(i).sym());

    // Compute the eigen-decomposition of Gi -> Gi' * S * Gi
    syev_driver_(collection_g_(i).sym(), vector_s_);

  }

  this->toc(comm_time);
  // ====================================================================================================================== //
  // Flip

  // Broadcast G0
  if ( mpi_rank == 0 ) {
    la::omatcopy(collection_g_(0), matrix_g0_);
  }
  comm_moment = utility::getTime();
  mpi::bcast(matrix_g0_, 0, mpi_comm);
  comm_time = utility::getTime() - comm_moment;

  // Qbar := 0
  la::memset0(matrix_qbar);

  for ( index_t i = 0; i < num_sketch_each; ++i ) {

    // Inverse Gi(j-row) if Gi(j-row) * Bi0 * G0(j-row)' < 0
    la::mm(matrix_g0_, collection_bi0_(i).t(), matrix_gb_);

    for ( index_t j = 0; j < dim_sketch; ++j ) {
      if ( la::dot(collection_g_(i)(j, ""_), matrix_gb_(j, ""_)) < 0 ) {
        la::scal(collection_g_(i)(j, ""_), -1.0);
      }
    }

    // Qbar += Qi * Gi'
    la::mm(collection_q(i), collection_g_(i).t(), matrix_qbar, 1.0, 1.0);

  }

  this->toc(comm_time);
  // ====================================================================================================================== //
  // Sum

  // Qbar := sum( Qbar )
  comm_moment = utility::getTime();
  mpi::reduce(matrix_qbar, MPI_SUM, mpi_root, mpi_comm);
  comm_time = utility::getTime() - comm_moment;

  // Compute the left singular vectors of Qbar
  if ( mpi_rank == mpi_root ) {
    gesvd_driver_(matrix_qbar, vector_s_, matrix_empty_, matrix_empty_);
  }

  this->toc(comm_time);
}

}  // namespace isvd

}  // namespace mcnla

#undef MCNLA_TMP

#endif  // MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_EXTRINSIC_MEAN_INTEGRATOR_HPP_
