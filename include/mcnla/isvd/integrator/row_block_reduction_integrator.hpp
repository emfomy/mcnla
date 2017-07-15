////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/row_block_reduction_integrator.hpp
/// @brief   The reduction integrator (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_REDUCTION_INTEGRATOR_HPP_
#define MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_REDUCTION_INTEGRATOR_HPP_

#include <mcnla/isvd/integrator/row_block_reduction_integrator.hh>
#include <mcnla/core/la.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS  Integrator<RowBlockReductionIntegratorTag, _Val>
  #define MCNLA_ALIAS0 Integrator
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS  RowBlockReductionIntegrator<_Val>
  #define MCNLA_ALIAS0 RowBlockReductionIntegrator
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
MCNLA_ALIAS::MCNLA_ALIAS0(
    const Parameters<_Val> &parameters
) noexcept
  : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::StageWrapper::initialize
///
template <typename _Val>
void MCNLA_ALIAS::initializeImpl() noexcept {

  const auto nrow_rank  = parameters_.nrowRank();
  const auto dim_sketch = parameters_.dimSketch();
  const auto num_sketch = parameters_.numSketch();

  collection_b_.reconstruct(dim_sketch, dim_sketch, (num_sketch+1)/2);

  matrix_t_.reconstruct(dim_sketch, dim_sketch);
  vector_s_.reconstruct(dim_sketch);

  matrix_tmp_.reconstruct(nrow_rank, dim_sketch);
  gesvd_driver_.reconstruct(collection_b_(0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Integrates.
///
/// @param  collection_qj  The matrix collection Qj (j-th row-block, where j is the MPI rank).
/// @param  matrix_qbarj   The matrix Qbarj (j-th row-block, where j is the MPI rank).
///
template <typename _Val>
void MCNLA_ALIAS::runImpl(
    DenseMatrixCollectionColBlockRowMajor<_Val> &collection_qj,
    DenseMatrixRowMajor<_Val> &matrix_qbarj
) noexcept {

  const auto mpi_comm   = parameters_.mpi_comm;
  const auto nrow_rank  = parameters_.nrowRank();
  const auto dim_sketch = parameters_.dimSketch();
  const auto num_sketch = parameters_.numSketch();

  static_cast<void>(nrow_rank);

  mcnla_assert_eq(collection_qj.sizes(), std::make_tuple(nrow_rank, dim_sketch, num_sketch));
  mcnla_assert_eq(matrix_qbarj.sizes(),  std::make_tuple(nrow_rank, dim_sketch));

  double comm_moment, comm_time;
  this->tic(comm_time);
  // ====================================================================================================================== //
  // Loop
  for ( auto N = num_sketch; N > 1; N = (N+1)/2 ) {
    const auto h = N / 2;

    // B(i) := Q(i)' * Q(i+h)
    for ( auto i = 0; i < h; ++i ) {
      la::mm(collection_qj(i).t(), collection_qj(i+h), collection_b_(i));
    }
    comm_moment = utility::getTime();
    mpi::allreduce(collection_b_({0, h}).unfold(), MPI_SUM, mpi_comm);
    comm_time += utility::getTime() - comm_moment;

    for ( auto i = 0; i < h; ++i ) {

      auto &&matrix_w    = collection_b_(i);  // matrix W
      auto &&matrix_qij  = collection_qj(i);  // matrix Q(i)
      auto &&matrix_qihj = collection_qj(i+h);  // matrix Q(i+h)

      // svd(B(i)) = W * S * T'
      gesvd_driver_(matrix_w, vector_s_, matrix_empty_, matrix_t_.t());

      // Q(i) := Q(i) * W + Q(i+h) * T
      la::copy(matrix_qij, matrix_tmp_);
      la::mm(matrix_tmp_, matrix_w, matrix_qij);
      la::mm(matrix_qihj, matrix_t_, matrix_qij, 1.0, 1.0);

      // Q(i) /= sqrt(2(I + S))
      for ( index_t ii = 0; ii < dim_sketch; ++ii ) {
        vector_s_(ii) = 1.0 / sqrt(2.0 * (1 + vector_s_(ii)));
      }
      la::mm(""_, vector_s_.diag(), matrix_qij);
    }
  }

  // Qbar := Q(i)
  la::copy(collection_qj(0), matrix_qbarj);

  this->toc(comm_time);
}

}  // namespace isvd

}  // namespace mcnla

#undef MCNLA_ALIAS
#undef MCNLA_ALIAS0

#endif  // MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_REDUCTION_INTEGRATOR_HPP_
