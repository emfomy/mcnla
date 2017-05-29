////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/former/row_block_gramian_former.hpp
/// @brief   The Gramian former (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_FORMER_ROW_BLOCK_GRAMIAN_FORMER_HPP_
#define MCNLA_ISVD_FORMER_ROW_BLOCK_GRAMIAN_FORMER_HPP_

#include <mcnla/isvd/former/row_block_gramian_former.hh>
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
Former<RowBlockGramianFormerTag, _Val>::Former(
    const Parameters<_Val> &parameters
) noexcept
  : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::StageWrapper::initialize
///
template <typename _Val>
void Former<RowBlockGramianFormerTag, _Val>::initializeImpl() noexcept {

  const auto nrow_rank  = parameters_.nrowRank();
  const auto nrow_each  = parameters_.nrowEach();
  const auto ncol       = parameters_.ncol();
  const auto ncol_rank  = parameters_.ncolRank();
  const auto ncol_each  = parameters_.ncolEach();
  const auto ncol_total = parameters_.ncolTotal();
  const auto dim_sketch = parameters_.dimSketch();
  const auto rank       = parameters_.rank();

  matrix_w_.reconstruct(dim_sketch, dim_sketch);
  vector_s_.reconstruct(dim_sketch);
  syev_driver_.reconstruct(dim_sketch);

  matrix_qta_.reconstruct(dim_sketch, ncol_total); matrix_qta_.resize(""_, ncol);
  matrix_qtaj_.reconstruct(dim_sketch, ncol_each); matrix_qtaj_.resize(""_, ncol_rank);
  matrix_uj_cut_.reconstruct(nrow_each, rank);     matrix_uj_cut_.resize(nrow_rank, ""_);

  matrix_w_cut_  = matrix_w_(""_, {dim_sketch-rank, dim_sketch});
  vector_s_cut_  = vector_s_({dim_sketch-rank, dim_sketch});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Forms SVD.
///
/// @param  matrix_aj  The matrix Aj (j-th row-block, where j is the MPI rank).
/// @param  matrix_qj  The matrix Qbarj (j-th row-block, where j is the MPI rank).
///
template <typename _Val> template <class _Matrix>
void Former<RowBlockGramianFormerTag, _Val>::runImpl(
    const _Matrix &matrix_aj,
    const DenseMatrixRowMajor<_Val> &matrix_qj
) noexcept {

  const auto mpi_comm   = parameters_.mpi_comm;
  const auto nrow_rank  = parameters_.nrowRank();
  const auto ncol       = parameters_.ncol();
  const auto ncol_each  = parameters_.ncolEach();
  const auto ncol_total = parameters_.ncolTotal();
  const auto dim_sketch = parameters_.dimSketch();

  static_cast<void>(nrow_rank);
  static_cast<void>(ncol);
  static_cast<void>(dim_sketch);

  mcnla_assert_eq(matrix_aj.sizes(), std::make_tuple(nrow_rank, ncol));
  mcnla_assert_eq(matrix_qj.sizes(), std::make_tuple(nrow_rank, dim_sketch));

  auto matrix_qta_full = matrix_qta_;
  matrix_qta_full.resize(""_, ncol_total);
  auto matrix_qtaj_full = matrix_qtaj_;
  matrix_qtaj_full.resize(""_, ncol_each);

  this->tic(); double comm_moment, comm_time = 0;
  // ====================================================================================================================== //
  // Start

  // QtA := sum( Qj' * Aj )
  la::mm(matrix_qj.t(), matrix_aj, matrix_qta_);
  comm_moment = utility::getTime();
  mpi::reduceScatterBlock(matrix_qta_full, matrix_qtaj_full, MPI_SUM, mpi_comm);
  comm_time += utility::getTime() - comm_moment;

  // W := sum( QtAj * QtAj' )
  la::rk(matrix_qtaj_, matrix_w_.sym());
  comm_moment = utility::getTime();
  mpi::allreduce(matrix_w_, MPI_SUM, mpi_comm);
  comm_time += utility::getTime() - comm_moment;

  // Compute the eigen-decomposition of W -> W * S * W'
  syev_driver_(matrix_w_.sym(), vector_s_);

  // S := sqrt(S)
  for ( auto &v : vector_s_ ) {
    v = std::sqrt(v);
  }

  // U := Q * W
  la::mm(matrix_qj, matrix_w_cut_, matrix_uj_cut_);

  this->toc(comm_time);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the singular values.
///
template <typename _Val>
const DenseVector<RealValT<_Val>>& Former<RowBlockGramianFormerTag, _Val>::vectorS() const noexcept {
  mcnla_assert_true(this->isComputed());
  return vector_s_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the left singular vectors (row-block).
///
template <typename _Val>
const DenseMatrixRowMajor<_Val>& Former<RowBlockGramianFormerTag, _Val>::matrixUj() const noexcept {
  mcnla_assert_true(this->isComputed());
  return matrix_uj_cut_;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_FORMER_ROW_BLOCK_GRAMIAN_FORMER_HPP_
