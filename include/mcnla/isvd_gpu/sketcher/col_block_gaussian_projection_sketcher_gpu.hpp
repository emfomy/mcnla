////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd_gpu/sketcher/col_block_gaussian_projection_sketcher_gpu.hpp
/// @brief   The Gaussian projection sketcher with GPU support (column-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_GPU_SKETCHER_COL_BLOCK_GAUSSIAN_PROJECTION_SKETCHER_GPU_HPP_
#define MCNLA_ISVD_GPU_SKETCHER_COL_BLOCK_GAUSSIAN_PROJECTION_SKETCHER_GPU_HPP_

#include <mcnla/isvd_gpu/sketcher/col_block_gaussian_projection_sketcher_gpu.hh>
#include <mcnla/core_gpu/matrix.hpp>
#include <mcnla/core_gpu/la.hpp>
#include <mcnla/core/random.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS  Sketcher<ColBlockGaussianProjectionSketcherGpuTag, _Val>
  #define MCNLA_ALIAS0 Sketcher
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS  ColBlockGaussianProjectionSketcherGpu<_Val>
  #define MCNLA_ALIAS0 ColBlockGaussianProjectionSketcherGpu
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
    const Parameters<_Val> &parameters,
    const index_t seed
) noexcept
  : BaseType(parameters) {
  setSeed(seed);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::StageWrapper::initialize
///
template <typename _Val>
void MCNLA_ALIAS::initializeImpl() noexcept {

  const auto nrow             = parameters_.nrow();
  const auto ncol_rank        = parameters_.ncolRank();
  const auto dim_sketch_total = parameters_.dimSketchTotal();

  index_t melem      = kGpuMemorySize / sizeof(_Val);
  index_t nelem_used = nrow * dim_sketch_total;

  mcnla_assert_ge(melem, nelem_used);
  index_t ncol_gpu = (melem - nelem_used) / (nrow + dim_sketch_total);
  ncol_gpu_ = std::min((ncol_gpu / kBlockSizeGpu) * kBlockSizeGpu, ncol_rank);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sketches.
///
/// @param  matrix_ajc      The matrix Ajc (j-th column-block, where j is the MPI rank).
/// @param  collection_qjp  The matrix collection Qjp (j-th partial-sum, where j is the MPI rank).
///
template <typename _Val>
void MCNLA_ALIAS::runImpl(
    const DenseMatrixColMajor<_Val> &matrix_ajc,
          DenseMatrixCollectionColBlockRowMajor<_Val> &collection_qjp
) noexcept {

  const auto mpi_comm         = parameters_.mpi_comm;
  const auto mpi_root         = parameters_.mpi_root;
  const auto nrow             = parameters_.nrow();
  const auto ncol_rank        = parameters_.ncolRank();
  const auto dim_sketch       = parameters_.dimSketch();
  const auto num_sketch       = parameters_.numSketch();
  const auto dim_sketch_total = parameters_.dimSketchTotal();

  mcnla_assert_eq(matrix_ajc.sizes(),     std::make_tuple(nrow, ncol_rank));
  mcnla_assert_eq(collection_qjp.sizes(), std::make_tuple(nrow, dim_sketch, num_sketch));

  random::Streams streams(seed_, mpi_root, mpi_comm);

  double comm_time;
  this->tic(comm_time);
  // ====================================================================================================================== //
  // Allocate GPU memory

  DenseMatrixGpuColMajor<_Val> matrix_ajc_gpu(nrow, ncol_gpu_);
  DenseMatrixGpuRowMajor<_Val> matrix_qjp_gpu(nrow, dim_sketch_total);
  DenseMatrixGpuRowMajor<_Val> matrix_omegajs_gpu(ncol_gpu_, dim_sketch_total);
  DenseMatrixRowMajor<_Val>    matrix_omegajs(ncol_gpu_, dim_sketch_total);

  this->toc(comm_time);
  // ====================================================================================================================== //
  // Projection

  la::memset0(matrix_qjp_gpu);
  auto idxrange = I_{0, ncol_gpu_};
  for ( auto i = 0; i < ncol_rank / ncol_gpu_; ++i ) {
    // Random sample Omega using normal Gaussian distribution
    random::gaussian(streams, matrix_omegajs.vec());

    // Copy A and Omega
    la::copy(matrix_ajc(""_, idxrange), matrix_ajc_gpu);
    la::copy(matrix_omegajs, matrix_omegajs_gpu);

    // Q := A * Omega
    la::mm(matrix_ajc_gpu, matrix_omegajs_gpu, matrix_qjp_gpu, 1.0, 1.0);

    idxrange += ncol_gpu_;
  }

  idxrange.end = ncol_rank;
  if ( idxrange.len() > 0 ) {
    auto idxrange0 = I_{0_i, idxrange.len()};

    // Random sample Omega using normal Gaussian distribution
    random::gaussian(streams, matrix_omegajs.vec());

    // Copy A and Omega
    la::copy(matrix_ajc(""_, idxrange), matrix_ajc_gpu(""_, idxrange0));
    la::copy(matrix_omegajs(idxrange0, ""_), matrix_omegajs_gpu(idxrange0, ""_));

    // Q := A * Omega
    la::mm(matrix_ajc_gpu(""_, idxrange0), matrix_omegajs_gpu(idxrange0, ""_), matrix_qjp_gpu, 1.0, 1.0);
  }

  this->toc(comm_time);
  // ====================================================================================================================== //
  // Receiving data from GPU

  la::copy(matrix_qjp_gpu, collection_qjp.unfold());

  this->toc(comm_time);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::StageWrapper::outputName
///
///
template <typename _Val>
std::ostream& MCNLA_ALIAS::outputNameImpl(
    std::ostream &os
) const noexcept {
  return (os << name_ << " (Power 0)");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the random seed.
///
template <typename _Val>
index_t MCNLA_ALIAS::seed() const noexcept {
  return seed_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the random seed.
///
template <typename _Val>
MCNLA_ALIAS& MCNLA_ALIAS::setSeed(
    const index_t seed
) noexcept {
  seed_ = seed;
  computed_ = false;
  return *this;
}

}  // namespace isvd

}  // namespace mcnla

#undef MCNLA_ALIAS
#undef MCNLA_ALIAS0

#endif  // MCNLA_ISVD_GPU_SKETCHER_COL_BLOCK_GAUSSIAN_PROJECTION_SKETCHER_GPU_HPP_
