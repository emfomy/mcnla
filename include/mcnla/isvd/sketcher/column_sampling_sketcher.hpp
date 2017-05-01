////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/column_sampling_sketcher.hpp
/// @brief   The Gaussian projection sketcher.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_HPP_
#define MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_HPP_

#include <mcnla/isvd/sketcher/column_sampling_sketcher.hh>
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
Sketcher<ColumnSamplingSketcherTag, _Val>::Sketcher(
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
void Sketcher<ColumnSamplingSketcherTag, _Val>::initializeImpl() noexcept {

  const auto dim_sketch      = parameters_.dimSketch();
  const auto num_sketch_each = parameters_.numSketchEach();

  vector_idxs_.reconstruct(dim_sketch * num_sketch_each);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sketches.
///
/// @param  matrix_a      The matrix A.
/// @param  collection_q  The matrix collection Q.
///
template <typename _Val> template <class _Matrix>
void Sketcher<ColumnSamplingSketcherTag, _Val>::runImpl(
    const _Matrix &matrix_a,
          DenseMatrixCollection201<ValType> &collection_q
) noexcept {

  const auto mpi_comm        = parameters_.mpi_comm;
  const auto mpi_root        = parameters_.mpi_root;
  const auto nrow            = parameters_.nrow();
  const auto ncol            = parameters_.ncol();
  const auto dim_sketch      = parameters_.dimSketch();
  const auto num_sketch_each = parameters_.numSketchEach();

  mcnla_assert_eq(matrix_a.sizes(),     std::make_tuple(nrow, ncol));
  mcnla_assert_eq(collection_q.sizes(), std::make_tuple(nrow, dim_sketch, num_sketch_each));

  random::Streams streams(seed_, mpi_root, mpi_comm);

  moments_.emplace_back(MPI_Wtime());  // random generating

  // Random sample Idxs using uniform distribution
  random::uniformBits(streams, vector_idxs_);

  moments_.emplace_back(MPI_Wtime());  // projection

  // Copy columns
  for ( index_t i = 0; i < dim_sketch * num_sketch_each; ++i ) {
    la::copy(matrix_a(""_, abs(vector_idxs_(i)) % ncol), collection_q.unfold()(""_, i));
  }

  moments_.emplace_back(MPI_Wtime());  // end
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the random seed.
///
template <typename _Val>
index_t Sketcher<ColumnSamplingSketcherTag, _Val>::seed() const noexcept {
  return seed_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the random seed.
///
template <typename _Val>
Sketcher<ColumnSamplingSketcherTag, _Val>& Sketcher<ColumnSamplingSketcherTag, _Val>::setSeed(
    const index_t seed
) noexcept {
  seed_ = seed;
  computed_ = false;
  return *this;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_HPP_
