////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd_gpu/sketcher/row_block_gaussian_projection_sketcher_gpu.hpp
/// @brief   The Gaussian projection sketcher with GPU support (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_GPU_SKETCHER_ROW_BLOCK_GAUSSIAN_PROJECTION_SKETCHER_GPU_HPP_
#define MCNLA_ISVD_GPU_SKETCHER_ROW_BLOCK_GAUSSIAN_PROJECTION_SKETCHER_GPU_HPP_

#include <mcnla/isvd_gpu/sketcher/row_block_gaussian_projection_sketcher_gpu.hh>
#include <mcnla/core_gpu/la.hpp>
#include <mcnla/core/random.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP Sketcher<RowBlockGaussianProjectionSketcherGpuTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP RowBlockGaussianProjectionSketcherGpu<_Val>
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
MCNLA_TMP::Sketcher(
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
void MCNLA_TMP::initializeImpl() noexcept {

  const auto nrow_rank        = parameters_.nrowRank();
  const auto ncol             = parameters_.ncol();
  const auto dim_sketch_total = parameters_.dimSketchTotal();

  index_t ncol_gpu = (kGpuMemorySize / sizeof(_Val) - (nrow_rank * dim_sketch_total + ncol * dim_sketch_total)) / nrow_rank;
  ncol_gpu_ = std::min((ncol_gpu/kBlockSizeGpu)*kBlockSizeGpu, ncol);

  matrix_aj_gpu_.reconstruct(nrow_rank, ncol_gpu_);
  matrix_qjs_gpu_.reconstruct(nrow_rank, dim_sketch_total);

  matrix_omegas_.reconstruct(ncol, dim_sketch_total);
  matrix_omegas_gpu_.reconstruct(ncol, dim_sketch_total);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sketches.
///
/// @param  matrix_aj      The matrix Aj (j-th row-block, where j is the MPI rank).
/// @param  collection_qj  The matrix collection Qj (j-th row-block, where j is the MPI rank).
///
template <typename _Val>
void MCNLA_TMP::runImpl(
    const DenseMatrixRowMajor<_Val> &matrix_aj,
          DenseMatrixCollectionColBlockRowMajor<_Val> &collection_qj
) noexcept {

  const auto mpi_comm   = parameters_.mpi_comm;
  const auto mpi_root   = parameters_.mpi_root;
  const auto nrow_rank  = parameters_.nrowRank();
  const auto ncol       = parameters_.ncol();
  const auto dim_sketch = parameters_.dimSketch();
  const auto num_sketch = parameters_.numSketch();

  mcnla_assert_eq(matrix_aj.sizes(),     std::make_tuple(nrow_rank, ncol));
  mcnla_assert_eq(collection_qj.sizes(), std::make_tuple(nrow_rank, dim_sketch, num_sketch));

  constexpr const MPI_Datatype datatype = traits::MpiValTraits<index_t>::datatype;
  index_t seed_tmp = seed_;
  MPI_Bcast(&seed_tmp, 1, datatype, mpi_root, mpi_comm);
  random::Streams streams(seed_tmp);

  this->tic(); double comm_time = 0;
  // ====================================================================================================================== //
  // Random generating

  // Random sample Omega using normal Gaussian distribution
  random::gaussian(streams, matrix_omegas_.vec());
  la::copy(matrix_omegas_, matrix_omegas_gpu_);

  this->toc(comm_time);
  // ====================================================================================================================== //
  // Projection

  auto idxrange = I_{0, ncol_gpu_};
  for ( auto i = 0; i < ncol / ncol_gpu_; ++i ) {
    // Copy A
    la::copy(matrix_aj(""_, idxrange), matrix_aj_gpu_);

    // Q := A * Omega
    la::mm(matrix_aj_gpu_, matrix_omegas_gpu_(idxrange, ""_), matrix_qjs_gpu_);

    idxrange += ncol_gpu_;
  }

  idxrange.end = ncol;
  if ( idxrange.len() > 0 ) {
    // Copy A
    la::copy(matrix_aj(""_, idxrange), matrix_aj_gpu_(""_, {0_i, idxrange.len()}));

    // Q := A * Omega
    la::mm(matrix_aj_gpu_(""_, {0_i, idxrange.len()}), matrix_omegas_gpu_(idxrange, ""_), matrix_qjs_gpu_);

    idxrange += ncol_gpu_;
  }

  this->toc(comm_time);
  // ====================================================================================================================== //
  // Receiving data from GPU

  la::copy(matrix_qjs_gpu_, collection_qj.unfold());

  this->toc(comm_time);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::StageWrapper::outputName
///
///
template <typename _Val>
std::ostream& MCNLA_TMP::outputNameImpl(
    std::ostream &os
) const noexcept {
  return (os << name_ << " (Power 0)");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the random seed.
///
template <typename _Val>
index_t MCNLA_TMP::seed() const noexcept {
  return seed_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the random seed.
///
template <typename _Val>
RowBlockGaussianProjectionSketcherGpu<_Val>& MCNLA_TMP::setSeed(
    const index_t seed
) noexcept {
  seed_ = seed;
  computed_ = false;
  return *this;
}

}  // namespace isvd

}  // namespace mcnla

#undef MCNLA_TMP

#endif  // MCNLA_ISVD_GPU_SKETCHER_ROW_BLOCK_GAUSSIAN_PROJECTION_SKETCHER_GPU_HPP_
