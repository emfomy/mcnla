////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd_gpu/former/row_block_gramian_former_gpu.hpp
/// @brief   The Gramian former with GPU support (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_GPU_FORMER_ROW_BLOCK_GRAMIAN_FORMER_GPU_HPP_
#define MCNLA_ISVD_GPU_FORMER_ROW_BLOCK_GRAMIAN_FORMER_GPU_HPP_

#include <mcnla/isvd_gpu/former/row_block_gramian_former_gpu.hh>
#include <mcnla/core_gpu/matrix.hpp>
#include <mcnla/core/la.hpp>
#include <mcnla/core_gpu/la.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS  Former<RowBlockGramianFormerGpuTag<_jobv>, _Val>
  #define MCNLA_ALIAS0 Former
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS  RowBlockGramianFormerGpu<_Val, _jobv>
  #define MCNLA_ALIAS0 RowBlockGramianFormerGpu
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

  const auto nrow_rank  = parameters_.nrowRank();
  const auto nrow_each  = parameters_.nrowEach();
  const auto ncol       = parameters_.ncol();
  const auto ncol_rank  = parameters_.ncolRank();
  const auto ncol_each  = parameters_.ncolEach();
  const auto ncol_total = parameters_.ncolTotal();
  const auto dim_sketch = parameters_.dimSketch();
  const auto rank       = parameters_.rank();

  index_t melem     = kGpuMemorySize / sizeof(_Val);
  index_t nelem_used = nrow_rank * dim_sketch;

  mcnla_assert_ge(melem, nelem_used);
  index_t ncol_gpu = (melem - nelem_used) / (nrow_rank + dim_sketch);
  ncol_gpu_ = std::min((ncol_gpu / kBlockSizeGpu) * kBlockSizeGpu, ncol);

  matrix_w_.reconstruct(dim_sketch, dim_sketch);
  vector_s_.reconstruct(dim_sketch);
  gesvd_driver_.reconstruct(dim_sketch, dim_sketch);

  matrix_z_.reconstruct(ncol_total, dim_sketch); matrix_z_.resize(ncol, ""_);
  matrix_zj_.reconstruct(ncol_each, dim_sketch); matrix_zj_.resize(ncol_rank, ""_);

  matrix_uj_cut_.reconstruct(nrow_each, rank);   matrix_uj_cut_.resize(nrow_rank, ""_);
  if ( _jobv ) {
    matrix_vj_cut_.reconstruct(ncol_each, rank); matrix_vj_cut_.resize(ncol_rank, ""_);
  }

  matrix_w_cut_  = matrix_w_(""_, {0, rank});
  vector_s_cut_  = vector_s_({0, rank});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Forms SVD.
///
/// @param  matrix_aj  The matrix Aj (j-th row-block, where j is the MPI rank).
/// @param  matrix_qj  The matrix Qbarj (j-th row-block, where j is the MPI rank).
///
template <typename _Val, bool _jobv> template <class _Matrix>
void MCNLA_ALIAS::runImpl(
    const _Matrix &matrix_aj,
    const DenseMatrixRowMajor<_Val> &matrix_qj
) noexcept {

  const auto mpi_comm   = parameters_.mpi_comm;
  const auto nrow_rank  = parameters_.nrowRank();
  const auto ncol       = parameters_.ncol();
  const auto ncol_each  = parameters_.ncolEach();
  const auto ncol_total = parameters_.ncolTotal();
  const auto dim_sketch = parameters_.dimSketch();

  mcnla_assert_eq(matrix_aj.sizes(), std::make_tuple(nrow_rank, ncol));
  mcnla_assert_eq(matrix_qj.sizes(), std::make_tuple(nrow_rank, dim_sketch));

  auto matrix_z_full = matrix_z_;
  matrix_z_full.resize(ncol_total, ""_);
  auto matrix_zj_full = matrix_zj_;
  matrix_zj_full.resize(ncol_each, ""_);

  double comm_moment, comm_time;
  this->tic(comm_time);
  // ====================================================================================================================== //
  // Allocate GPU memory

  DenseMatrixGpuRowMajor<_Val> matrix_aj_gpu(nrow_rank, ncol_gpu_);
  DenseMatrixGpuRowMajor<_Val> matrix_qj_gpu(nrow_rank, dim_sketch);
  DenseMatrixGpuRowMajor<_Val> matrix_z_gpu(ncol_gpu_, dim_sketch);

  this->toc(comm_time);
  // ====================================================================================================================== //
  // Projection

  // Send Q to GPU
  la::copy(matrix_qj, matrix_qj_gpu);

  auto idxrange = I_{0, ncol_gpu_};
  for ( auto i = 0; i < ncol / ncol_gpu_; ++i ) {
    // Copy A
    la::copy(matrix_aj(""_, idxrange), matrix_aj_gpu);

    // Z := A' * Q
    la::mm(matrix_aj_gpu.t(), matrix_qj_gpu, matrix_z_gpu);

    // Copy Z
    la::copy(matrix_z_gpu, matrix_z_(idxrange, ""_));

    idxrange += ncol_gpu_;
  }

  idxrange.end = ncol;
  if ( idxrange.len() > 0 ) {
    // Copy A
    la::copy(matrix_aj(""_, idxrange), matrix_aj_gpu(""_, {0_i, idxrange.len()}));

    // Z := A' * Q
    la::mm(matrix_aj_gpu(""_, {0_i, idxrange.len()}).t(), matrix_qj_gpu, matrix_z_gpu({0_i, idxrange.len()}, ""_));

    // Copy Z
    la::copy(matrix_z_gpu({0_i, idxrange.len()}, ""_), matrix_z_(idxrange, ""_));
  }

  // Rearrange Z
  comm_moment = utility::getTime();
  mpi::reduceScatterBlock(matrix_z_full, matrix_zj_full, MPI_SUM, mpi_comm);
  comm_time += utility::getTime() - comm_moment;

  this->toc(comm_time);
  // ====================================================================================================================== //
  // Compute eigen-decomposition

  // W := Z' * Z
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

  this->toc(comm_time);
  // ====================================================================================================================== //
  // Form singular vectors

  // U := Q * W
  la::mm(matrix_qj, matrix_w_cut_, matrix_uj_cut_);

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
/// @brief  Gets the left singular vectors (row-block).
///
template <typename _Val, bool _jobv>
const DenseMatrixRowMajor<_Val>& MCNLA_ALIAS::matrixUj() const noexcept {
  mcnla_assert_true(this->isComputed());
  return matrix_uj_cut_;
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

#endif  // MCNLA_ISVD_GPU_FORMER_ROW_BLOCK_GRAMIAN_FORMER_GPU_HPP_
