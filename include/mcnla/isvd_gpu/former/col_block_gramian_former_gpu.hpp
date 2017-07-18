////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd_gpu/former/col_block_gramian_former_gpu.hpp
/// @brief   The Gramian former with GPU support (column-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_GPU_FORMER_COL_BLOCK_GRAMIAN_FORMER_GPU_HPP_
#define MCNLA_ISVD_GPU_FORMER_COL_BLOCK_GRAMIAN_FORMER_GPU_HPP_

#include <mcnla/isvd_gpu/former/col_block_gramian_former_gpu.hh>
#include <mcnla/core_gpu/matrix.hpp>
#include <mcnla/core/la.hpp>
#include <mcnla/core_gpu/la.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS  Former<ColBlockGramianFormerGpuTag<_jobv>, _Val>
  #define MCNLA_ALIAS0 Former
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS  ColBlockGramianFormerGpu<_Val, _jobv>
  #define MCNLA_ALIAS0 ColBlockGramianFormerGpu
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

  index_t melem      = kGpuMemorySize / sizeof(_Val);
  index_t nelem_used = nrow * dim_sketch;

  mcnla_assert_ge(melem, nelem_used);
  index_t ncol_gpu = (melem - nelem_used) / (nrow + dim_sketch);
  ncol_gpu_ = std::min((ncol_gpu / kBlockSizeGpu) * kBlockSizeGpu, ncol_rank);

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

  mcnla_assert_eq(matrix_ajc.sizes(), std::make_tuple(nrow, ncol_rank));
  mcnla_assert_eq(matrix_q.sizes(), std::make_tuple(nrow, dim_sketch));

  double comm_moment, comm_time;
  this->tic(comm_time);
  // ====================================================================================================================== //
  // Allocate GPU memory

  DenseMatrixGpuColMajor<_Val> matrix_ajc_gpu(nrow, ncol_gpu_);
  DenseMatrixGpuRowMajor<_Val> matrix_q_gpu(nrow, dim_sketch);
  DenseMatrixGpuRowMajor<_Val> matrix_zj_gpu(ncol_gpu_, dim_sketch);

  this->toc(comm_time);
  // ====================================================================================================================== //
  // Projection

  // Send Q to GPU
  la::copy(matrix_q, matrix_q_gpu);

  auto idxrange = I_{0, ncol_gpu_};
  for ( auto i = 0; i < ncol_rank / ncol_gpu_; ++i ) {
    // Copy A
    la::copy(matrix_ajc(""_, idxrange), matrix_ajc_gpu);

    // Z := A' * Q
    la::mm(matrix_ajc_gpu.t(), matrix_q_gpu, matrix_zj_gpu);

    // Copy Z
    la::copy(matrix_zj_gpu, matrix_zj_(idxrange, ""_));

    idxrange += ncol_gpu_;
  }

  idxrange.end = ncol_rank;
  if ( idxrange.len() > 0 ) {
    // Copy A
    la::copy(matrix_ajc(""_, idxrange), matrix_ajc_gpu(""_, {0_i, idxrange.len()}));

    // Z := A' * Q
    la::mm(matrix_ajc_gpu(""_, {0_i, idxrange.len()}).t(), matrix_q_gpu, matrix_zj_gpu({0_i, idxrange.len()}, ""_));

    // Copy Z
    la::copy(matrix_zj_gpu({0_i, idxrange.len()}, ""_), matrix_zj_(idxrange, ""_));
  }

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

#endif  // MCNLA_ISVD_GPU_FORMER_COL_BLOCK_GRAMIAN_FORMER_GPU_HPP_
