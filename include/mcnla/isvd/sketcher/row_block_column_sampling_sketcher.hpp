////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/row_block_column_sampling_sketcher.hpp
/// @brief   The Gaussian projection sketcher (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_ROW_BLOCK_COLUMN_SAMPLING_SKETCHER_HPP_
#define MCNLA_ISVD_SKETCHER_ROW_BLOCK_COLUMN_SAMPLING_SKETCHER_HPP_

#include <mcnla/isvd/sketcher/row_block_column_sampling_sketcher.hh>
#include <mcnla/core/la.hpp>
#include <mcnla/core/random.hpp>

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
Sketcher<RowBlockColumnSamplingSketcherTag, _Val>::Sketcher(
    const Parameters<ValType> &parameters,
    const index_t seed
) noexcept
  : BaseType(parameters) {
  setSeed(seed);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::StageWrapper::initialize
///
template <typename _Val>
void Sketcher<RowBlockColumnSamplingSketcherTag, _Val>::initializeImpl() noexcept {

  const auto dim_sketch = parameters_.dimSketch();
  const auto num_sketch = parameters_.numSketch();

  vector_idxs_.reconstruct(dim_sketch * num_sketch);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sketches.
///
/// @param  matrix_aj      The matrix Aj (j-th row-block, where j is the MPI rank).
/// @param  collection_qj  The matrix collection Qj (j-th row-block, where j is the MPI rank).
///
template <typename _Val> template <class _Matrix>
void Sketcher<RowBlockColumnSamplingSketcherTag, _Val>::runImpl(
    const _Matrix &matrix_aj,
          DenseMatrixCollection201<ValType> &collection_qj
) noexcept {

  const auto mpi_comm   = parameters_.mpi_comm;
  const auto mpi_root   = parameters_.mpi_root;
  const auto nrow_rank  = parameters_.nrowRank();
  const auto ncol       = parameters_.ncol();
  const auto dim_sketch = parameters_.dimSketch();
  const auto num_sketch = parameters_.numSketch();

  mcnla_assert_eq(matrix_aj.sizes(),     std::make_tuple(nrow_rank, ncol));
  mcnla_assert_eq(collection_qj.sizes(), std::make_tuple(nrow_rank, dim_sketch, num_sketch));

  constexpr const MPI_Datatype &datatype = traits::MpiValTraits<index_t>::datatype;
  index_t seed_tmp = seed_;
  MPI_Bcast(&seed_tmp, 1, datatype, mpi_root, mpi_comm);
  random::Streams streams(seed_tmp);

  moments_.emplace_back(MPI_Wtime());  // random generating

  // Random sample Idxs using uniform distribution
  random::uniform(streams, vector_idxs_, 0, ncol);

  moments_.emplace_back(MPI_Wtime());  // random sketching

  // Copy columns
  for ( index_t i = 0; i < dim_sketch * num_sketch; ++i ) {
    la::copy(matrix_aj("", vector_idxs_(i)), collection_qj.unfold()("", i));
  }

  moments_.emplace_back(MPI_Wtime());  // end
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the random seed.
///
template <typename _Val>
index_t Sketcher<RowBlockColumnSamplingSketcherTag, _Val>::seed() const noexcept {
  return seed_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the random seed.
///
template <typename _Val>
Sketcher<RowBlockColumnSamplingSketcherTag, _Val>& Sketcher<RowBlockColumnSamplingSketcherTag, _Val>::setSeed(
    const index_t seed
) noexcept {
  seed_ = seed;
  computed_ = false;
  return *this;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_ROW_BLOCK_COLUMN_SAMPLING_SKETCHER_HPP_
