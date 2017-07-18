////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/former/row_block_symmetric_former_gpu.hpp
/// @brief   The former for symmetric matrix with GPU support (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_GPU_FORMER_ROW_BLOCK_GRAMIAN_FORMER_GPU_HPP_
#define MCNLA_ISVD_GPU_FORMER_ROW_BLOCK_GRAMIAN_FORMER_GPU_HPP_

#include <mcnla/isvd_gpu/former/row_block_symmetric_former_gpu.hh>
#include <mcnla/core_gpu/matrix.hpp>
#include <mcnla/core/la.hpp>
#include <mcnla/core_gpu/la.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS  Former<RowBlockSymmetricFormerGpuTag<_jobv>, _Val>
  #define MCNLA_ALIAS0 Former
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS  RowBlockSymmetricFormerGpu<_Val, _jobv>
  #define MCNLA_ALIAS0 RowBlockSymmetricFormerGpu
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

  index_t melem     = kGpuMemorySize / sizeof(_Val);
  index_t nelem_used = nrow_rank * dim_sketch;

  mcnla_assert_eq(nrow, ncol);

  mcnla_assert_ge(melem, nelem_used);
  index_t ncol_gpu = (melem - nelem_used) / (nrow_rank + dim_sketch);
  ncol_gpu_ = std::min((ncol_gpu / kBlockSizeGpu) * kBlockSizeGpu, ncol);

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

  // W := Z' * Q
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

#endif  // MCNLA_ISVD_GPU_FORMER_ROW_BLOCK_GRAMIAN_FORMER_GPU_HPP_
