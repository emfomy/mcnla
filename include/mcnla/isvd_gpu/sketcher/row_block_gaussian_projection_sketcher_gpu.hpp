////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd_gpu/sketcher/row_block_gaussian_projection_sketcher_gpu.hpp
/// @brief   The Gaussian projection sketcher with GPU support (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_GPU_SKETCHER_ROW_BLOCK_GAUSSIAN_PROJECTION_SKETCHER_GPU_HPP_
#define MCNLA_ISVD_GPU_SKETCHER_ROW_BLOCK_GAUSSIAN_PROJECTION_SKETCHER_GPU_HPP_

#include <mcnla/isvd_gpu/sketcher/row_block_gaussian_projection_sketcher_gpu.hh>
#include <mcnla/core_gpu/matrix.hpp>
#include <mcnla/core_gpu/la.hpp>
#include <mcnla/core/random.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS  Sketcher<RowBlockGaussianProjectionSketcherGpuTag, _Val>
  #define MCNLA_ALIAS0 Sketcher
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS  RowBlockGaussianProjectionSketcherGpu<_Val>
  #define MCNLA_ALIAS0 RowBlockGaussianProjectionSketcherGpu
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

  const auto nrow_rank        = parameters_.nrowRank();
  const auto ncol             = parameters_.ncol();
  const auto dim_sketch_total = parameters_.dimSketchTotal();

  index_t melem     = kGpuMemorySize / sizeof(_Val);
  index_t nelem_used = nrow_rank * dim_sketch_total;

  mcnla_assert_ge(melem, nelem_used);
  index_t ncol_gpu = (melem - nelem_used) / (nrow_rank + dim_sketch_total);
  ncol_gpu_ = std::min((ncol_gpu / kBlockSizeGpu) * kBlockSizeGpu, ncol);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sketches.
///
/// @param  matrix_aj      The matrix Aj (j-th row-block, where j is the MPI rank).
/// @param  collection_qj  The matrix collection Qj (j-th row-block, where j is the MPI rank).
///
template <typename _Val>
void MCNLA_ALIAS::runImpl(
    const DenseMatrixRowMajor<_Val> &matrix_aj,
          DenseMatrixCollectionColBlockRowMajor<_Val> &collection_qj
) noexcept {

  const auto mpi_comm         = parameters_.mpi_comm;
  const auto mpi_root         = parameters_.mpi_root;
  const auto nrow_rank        = parameters_.nrowRank();
  const auto ncol             = parameters_.ncol();
  const auto dim_sketch       = parameters_.dimSketch();
  const auto num_sketch       = parameters_.numSketch();
  const auto dim_sketch_total = parameters_.dimSketchTotal();

  static_cast<void>(dim_sketch);
  static_cast<void>(num_sketch);

  mcnla_assert_eq(matrix_aj.sizes(),     std::make_tuple(nrow_rank, ncol));
  mcnla_assert_eq(collection_qj.sizes(), std::make_tuple(nrow_rank, dim_sketch, num_sketch));

  constexpr const MPI_Datatype datatype = traits::MpiValTraits<index_t>::datatype;
  index_t seed_tmp = seed_;
  MPI_Bcast(&seed_tmp, 1, datatype, mpi_root, mpi_comm);
  random::Streams streams(seed_tmp);

  double comm_time;
  this->tic(comm_time);
  // ====================================================================================================================== //
  // Allocate GPU memory

  DenseMatrixGpuRowMajor<_Val> matrix_aj_gpu(nrow_rank, ncol_gpu_);
  DenseMatrixGpuRowMajor<_Val> matrix_qjs_gpu(nrow_rank, dim_sketch_total);
  DenseMatrixGpuRowMajor<_Val> matrix_omegas_gpu(ncol_gpu_, dim_sketch_total);
  DenseMatrixRowMajor<_Val>    matrix_omegas(ncol_gpu_, dim_sketch_total);

  this->toc(comm_time);
  // ====================================================================================================================== //
  // Projection

  la::memset0(matrix_qjs_gpu);
  auto idxrange = I_{0, ncol_gpu_};
  for ( auto i = 0; i < ncol / ncol_gpu_; ++i ) {
    // Random sample Omega using normal Gaussian distribution
    random::gaussian(streams, matrix_omegas.vec());

    // Copy A and Omega
    la::copy(matrix_aj(""_, idxrange), matrix_aj_gpu);
    la::copy(matrix_omegas, matrix_omegas_gpu);

    // Q := A * Omega
    la::mm(matrix_aj_gpu, matrix_omegas_gpu, matrix_qjs_gpu, 1.0, 1.0);

    idxrange += ncol_gpu_;
  }

  idxrange.end = ncol;
  if ( idxrange.len() > 0 ) {
    auto idxrange0 = I_{0_i, idxrange.len()};

    // Random sample Omega using normal Gaussian distribution
    random::gaussian(streams, matrix_omegas.vec());

    // Copy A and Omega
    la::copy(matrix_aj(""_, idxrange), matrix_aj_gpu(""_, idxrange0));
    la::copy(matrix_omegas(idxrange0, ""_), matrix_omegas_gpu(idxrange0, ""_));

    // Q := A * Omega
    la::mm(matrix_aj_gpu(""_, idxrange0), matrix_omegas_gpu(idxrange0, ""_), matrix_qjs_gpu, 1.0, 1.0);
  }

  this->toc(comm_time);
  // ====================================================================================================================== //
  // Receiving data from GPU

  la::copy(matrix_qjs_gpu, collection_qj.unfold());

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

#endif  // MCNLA_ISVD_GPU_SKETCHER_ROW_BLOCK_GAUSSIAN_PROJECTION_SKETCHER_GPU_HPP_
