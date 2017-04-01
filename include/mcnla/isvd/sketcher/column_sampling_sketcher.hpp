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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::ComponentWrapper::ComponentWrapper
///
template <typename _Val>
Sketcher<ColumnSamplingSketcherTag, _Val>::Sketcher(
    const Parameters &parameters
) noexcept
  : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::ComponentWrapper::initialize
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
          DenseMatrixCollection120<ValType> &collection_q
) noexcept {

  const auto nrow            = parameters_.nrow();
  const auto ncol            = parameters_.ncol();
  const auto dim_sketch      = parameters_.dimSketch();
  const auto num_sketch_each = parameters_.numSketchEach();
  const auto &streams        = parameters_.streams();

  mcnla_assert_eq(matrix_a.sizes(),     std::make_tuple(nrow, ncol));
  mcnla_assert_eq(collection_q.sizes(), std::make_tuple(nrow, dim_sketch, num_sketch_each));

  moments_.emplace_back(MPI_Wtime());  // random generating

  // Random sample Idxs using uniform distribution
  random::uniform(streams, vector_idxs_, 0, ncol);

  moments_.emplace_back(MPI_Wtime());  // random sketching

  // Copy columns
  for ( index_t i = 0; i < dim_sketch * num_sketch_each; ++i ) {
    la::copy(matrix_a("", vector_idxs_(i)), collection_q.unfold()("", i));
  }

  moments_.emplace_back(MPI_Wtime()); // end
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_HPP_
