////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/former/row_block_symmetric_former.hpp
/// @brief   The former for symmetric matrix (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_FORMER_ROW_BLOCK_GRAMIAN_FORMER_HPP_
#define MCNLA_ISVD_FORMER_ROW_BLOCK_GRAMIAN_FORMER_HPP_

#include <mcnla/isvd/former/row_block_symmetric_former.hh>
#include <mcnla/core/la.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS  Former<RowBlockSymmetricFormerTag<_jobv>, _Val>
  #define MCNLA_ALIAS0 Former
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS  RowBlockSymmetricFormer<_Val, _jobv>
  #define MCNLA_ALIAS0 RowBlockSymmetricFormer
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
  const auto nrow_rank  = parameters_.nrowRank();
  const auto nrow_each  = parameters_.nrowEach();
  const auto nrow_total = parameters_.nrowTotal();
  const auto ncol       = parameters_.ncol();
  const auto dim_sketch = parameters_.dimSketch();
  const auto rank       = parameters_.rank();

  mcnla_assert_eq(nrow, ncol);

  matrix_w_.reconstruct(dim_sketch, dim_sketch);
  vector_s_.reconstruct(dim_sketch);
  syev_driver_.reconstruct(dim_sketch);

  matrix_z_.reconstruct(nrow_total, dim_sketch); matrix_z_.resize(nrow, ""_);
  matrix_zj_.reconstruct(nrow_each, dim_sketch); matrix_zj_.resize(nrow_rank, ""_);
  matrix_uj_cut_.reconstruct(nrow_each, rank);   matrix_uj_cut_.resize(nrow_rank, ""_);

  matrix_w_cut_  = matrix_w_(""_, {dim_sketch-rank, dim_sketch});
  vector_s_cut_  = vector_s_({dim_sketch-rank, dim_sketch});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Forms eigenvalue decomposition.
///
/// @param  matrix_aj  The matrix Aj (j-th row-block, where j is the MPI rank).
/// @param  matrix_qj  The matrix Qbarj (j-th row-block, where j is the MPI rank).
///
/// @attention  The full matrix A must be symmetric.
///
template <typename _Val, bool _jobv> template <class _Matrix>
void MCNLA_ALIAS::runImpl(
    const _Matrix &matrix_aj,
    const DenseMatrixRowMajor<_Val> &matrix_qj
) noexcept {

  const auto mpi_comm   = parameters_.mpi_comm;
  const auto nrow       = parameters_.nrow();
  const auto nrow_rank  = parameters_.nrowRank();
  const auto nrow_each  = parameters_.nrowEach();
  const auto nrow_total = parameters_.nrowTotal();
  const auto ncol       = parameters_.ncol();
  const auto dim_sketch = parameters_.dimSketch();

  mcnla_assert_eq(nrow, ncol);

  static_cast<void>(nrow);
  static_cast<void>(nrow_rank);
  static_cast<void>(dim_sketch);

  mcnla_assert_eq(matrix_aj.sizes(), std::make_tuple(nrow_rank, nrow));
  mcnla_assert_eq(matrix_qj.sizes(), std::make_tuple(nrow_rank, dim_sketch));

  auto matrix_z_full = matrix_z_;
  matrix_z_full.resize(nrow_total, ""_);
  auto matrix_zj_full = matrix_zj_;
  matrix_zj_full.resize(nrow_each, ""_);

  this->tic(); double comm_moment, comm_time = 0;
  // ====================================================================================================================== //
  // Start

  // Z := sum( Aj' * Qj )
  la::mm(matrix_aj.t(), matrix_qj, matrix_z_);
  comm_moment = utility::getTime();
  mpi::reduceScatterBlock(matrix_z_full, matrix_zj_full, MPI_SUM, mpi_comm);
  comm_time += utility::getTime() - comm_moment;

  // W := sum( Zj' * Qj )
  la::mm(matrix_zj_.t(), matrix_qj, matrix_w_.sym());
  comm_moment = utility::getTime();
  mpi::allreduce(matrix_w_, MPI_SUM, mpi_comm);
  comm_time += utility::getTime() - comm_moment;

  // eig(W) = W * S * W'
  syev_driver_(matrix_w_.sym(), vector_s_);

  // U := Q * W
  la::mm(matrix_qj, matrix_w_cut_, matrix_uj_cut_);

  this->toc(comm_time);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the eigenvalues.
///
/// @attention  The eigenvalues are sorted in ascending order.
///
template <typename _Val, bool _jobv>
const DenseVector<RealValT<_Val>>& MCNLA_ALIAS::vectorS() const noexcept {
  mcnla_assert_true(this->isComputed());
  return vector_s_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the left eigenvectors (row-block).
///
/// @attention  The eigenvalues are sorted in ascending order.
///
template <typename _Val, bool _jobv>
const DenseMatrixRowMajor<_Val>& MCNLA_ALIAS::matrixUj() const noexcept {
  mcnla_assert_true(this->isComputed());
  return matrix_uj_cut_;
}

}  // namespace isvd

}  // namespace mcnla

#undef MCNLA_ALIAS
#undef MCNLA_ALIAS0

#endif  // MCNLA_ISVD_FORMER_ROW_BLOCK_GRAMIAN_FORMER_HPP_
