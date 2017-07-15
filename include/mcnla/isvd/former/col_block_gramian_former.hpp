////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/former/col_block_gramian_former.hpp
/// @brief   The Gramian former (column-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_FORMER_COL_BLOCK_GRAMIAN_FORMER_HPP_
#define MCNLA_ISVD_FORMER_COL_BLOCK_GRAMIAN_FORMER_HPP_

#include <mcnla/isvd/former/col_block_gramian_former.hh>
#include <mcnla/core/la.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS  Former<ColBlockGramianFormerTag<_jobv>, _Val>
  #define MCNLA_ALIAS0 Former
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS  ColBlockGramianFormer<_Val, _jobv>
  #define MCNLA_ALIAS0 ColBlockGramianFormer
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
template <typename _Val, bool _jobv>
MCNLA_ALIAS::MCNLA_ALIAS0(
    const Parameters<_Val> &parameters
) noexcept
  : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::StageWrapper::initialize
///
template <typename _Val, bool _jobv>
void MCNLA_ALIAS::initializeImpl() noexcept {

  const auto nrow       = parameters_.nrow();
  const auto ncol_rank  = parameters_.ncolRank();
  const auto ncol_each  = parameters_.ncolEach();
  const auto dim_sketch = parameters_.dimSketch();
  const auto rank       = parameters_.rank();

  matrix_w_.reconstruct(dim_sketch, dim_sketch);
  vector_s_.reconstruct(dim_sketch);
  gesvd_driver_.reconstruct(dim_sketch, dim_sketch);

  matrix_zj_.reconstruct(ncol_rank, dim_sketch);
  matrix_u_cut_.reconstruct(nrow, rank);
  if ( _jobv ) {
    matrix_vj_cut_.reconstruct(ncol_each, rank); matrix_vj_cut_.resize(ncol_rank, ""_);
  }

  matrix_w_cut_  = matrix_w_(""_, {0, rank});
  vector_s_cut_  = vector_s_({0, rank});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Forms SVD.
///
/// @param  matrix_ajc  The matrix Ajc (j-th column-block, where j is the MPI rank).
/// @param  matrix_q    The matrix Qbar.
///
template <typename _Val, bool _jobv> template <class _Matrix>
void MCNLA_ALIAS::runImpl(
    const _Matrix &matrix_ajc,
    const DenseMatrixRowMajor<_Val> &matrix_q
) noexcept {

  const auto mpi_comm   = parameters_.mpi_comm;
  const auto nrow       = parameters_.nrow();
  const auto ncol_rank  = parameters_.ncolRank();
  const auto dim_sketch = parameters_.dimSketch();

  static_cast<void>(nrow);
  static_cast<void>(ncol_rank);
  static_cast<void>(dim_sketch);

  mcnla_assert_eq(matrix_ajc.sizes(), std::make_tuple(nrow, ncol_rank));
  mcnla_assert_eq(matrix_q.sizes(), std::make_tuple(nrow, dim_sketch));

  double comm_moment, comm_time;
  this->tic(comm_time);
  // ====================================================================================================================== //
  // Compute Gramian

  // Zj := Ajc' * Q
  la::mm(matrix_ajc.t(), matrix_q, matrix_zj_);

  // W := sum( Zj' * Zj )
  la::mm(matrix_zj_.t(), matrix_zj_, matrix_w_);
  comm_moment = utility::getTime();
  mpi::allreduce(matrix_w_, MPI_SUM, mpi_comm);
  comm_time += utility::getTime() - comm_moment;

  this->toc(comm_time);
  // ====================================================================================================================== //
  // Compute eigen-decomposition

  // eig(W) = W * S * W'
  gesvd_driver_(matrix_w_, vector_s_, matrix_empty_, matrix_empty_);

  // S := sqrt(S)
  for ( auto &v : vector_s_ ) {
    v = std::sqrt(v);
  }

  this->toc(comm_time);
  // ====================================================================================================================== //
  // Form singular vectors

  // U := Q * W
  la::mm(matrix_q, matrix_w_cut_, matrix_u_cut_);

  if ( _jobv ) {
    // V := Z * W * inv(S)
    la::mm(matrix_zj_, matrix_w_cut_, matrix_vj_cut_);
    la::sm(matrix_vj_cut_, vector_s_cut_.diag().inv());
  }

  this->toc(comm_time);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the singular values.
///
template <typename _Val, bool _jobv>
const DenseVector<RealValT<_Val>>& MCNLA_ALIAS::vectorS() const noexcept {
  mcnla_assert_true(this->isComputed());
  return vector_s_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the left singular vectors.
///
template <typename _Val, bool _jobv>
const DenseMatrixColMajor<_Val>& MCNLA_ALIAS::matrixU() const noexcept {
  mcnla_assert_true(this->isComputed());
  return matrix_u_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the right singular vectors (row-block).
///
template <typename _Val, bool _jobv>
const DenseMatrixRowMajor<_Val>& MCNLA_ALIAS::matrixVj() const noexcept {
  mcnla_assert_true(this->isComputed());
  mcnla_assert_true(_jobv);
  return matrix_vj_cut_;
}

}  // namespace isvd

}  // namespace mcnla

#undef MCNLA_ALIAS
#undef MCNLA_ALIAS0

#endif  // MCNLA_ISVD_FORMER_COL_BLOCK_GRAMIAN_FORMER_HPP_
