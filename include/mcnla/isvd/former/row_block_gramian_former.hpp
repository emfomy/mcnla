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

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP Former<RowBlockGramianFormerTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP RowBlockGramianFormer<_Val>
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
MCNLA_TMP::Former(
    const Parameters<_Val> &parameters
) noexcept
  : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::StageWrapper::initialize
///
template <typename _Val>
void MCNLA_TMP::initializeImpl() noexcept {

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
  gesvd_driver_.reconstruct(dim_sketch, dim_sketch);

  matrix_z_.reconstruct(ncol_total, dim_sketch); matrix_z_.resize(ncol, ""_);
  matrix_zj_.reconstruct(ncol_each, dim_sketch); matrix_zj_.resize(ncol_rank, ""_);
  matrix_uj_cut_.reconstruct(nrow_each, rank);   matrix_uj_cut_.resize(nrow_rank, ""_);

  matrix_w_cut_  = matrix_w_(""_, {0, rank});
  vector_s_cut_  = vector_s_({0, rank});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Forms SVD.
///
/// @param  matrix_aj  The matrix Aj (j-th row-block, where j is the MPI rank).
/// @param  matrix_qj  The matrix Qbarj (j-th row-block, where j is the MPI rank).
///
template <typename _Val> template <class _Matrix>
void MCNLA_TMP::runImpl(
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

  auto matrix_z_full = matrix_z_;
  matrix_z_full.resize(ncol_total, ""_);
  auto matrix_zj_full = matrix_zj_;
  matrix_zj_full.resize(ncol_each, ""_);

  this->tic(); double comm_moment, comm_time = 0;
  // ====================================================================================================================== //
  // Start

  // Z := sum( Aj' * Qj )
  la::mm(matrix_aj.t(), matrix_qj, matrix_z_);
  comm_moment = utility::getTime();
  mpi::reduceScatterBlock(matrix_z_full, matrix_zj_full, MPI_SUM, mpi_comm);
  comm_time += utility::getTime() - comm_moment;

  // W := sum( Zj' * Zj )
  la::mm(matrix_zj_.t(), matrix_zj_, matrix_w_);
  comm_moment = utility::getTime();
  mpi::allreduce(matrix_w_, MPI_SUM, mpi_comm);
  comm_time += utility::getTime() - comm_moment;

  // eig(W) = W * S * W'
  gesvd_driver_(matrix_w_, vector_s_, matrix_empty_, matrix_empty_);

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
const DenseVector<RealValT<_Val>>& MCNLA_TMP::vectorS() const noexcept {
  mcnla_assert_true(this->isComputed());
  return vector_s_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the left singular vectors (row-block).
///
template <typename _Val>
const DenseMatrixRowMajor<_Val>& MCNLA_TMP::matrixUj() const noexcept {
  mcnla_assert_true(this->isComputed());
  return matrix_uj_cut_;
}

}  // namespace isvd

}  // namespace mcnla

#undef MCNLA_TMP

#endif  // MCNLA_ISVD_FORMER_ROW_BLOCK_GRAMIAN_FORMER_HPP_
