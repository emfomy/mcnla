////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/column_sampling_sketcher.ipp
/// @brief   The implementation of column sampling sketcher.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_IPP_
#define MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_IPP_

#include <mcnla/isvd/sketcher/column_sampling_sketcher.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherBase::SketcherBase
///
template <class _Matrix>
ColumnSamplingSketcher<_Matrix>::ColumnSamplingSketcher(
    const Parameters<ScalarType> &parameters, index_t *seed
) noexcept : BaseType(parameters, seed) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherBase::initialize
///
template <class _Matrix>
void ColumnSamplingSketcher<_Matrix>::initializeImpl() noexcept {

  const auto vector_s_sizes = parameters_.getDimSketch();
  if ( vector_s_.getSizes() != vector_s_sizes ) {
    vector_s_ = DenseVector<RealScalarType>(vector_s_sizes);
  }

  const auto gesvd_sizes = std::make_pair(parameters_.getNrow(), parameters_.getDimSketch());
  if ( gesvd_driver_.getSizes() != gesvd_sizes ) {
    gesvd_driver_.resize(gesvd_sizes);
  }

  srand(this->seed_[0]);
  random_distribution_ = std::uniform_int_distribution<index_t>(0, parameters_.getNcol()-1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherBase::sketch
///
template <class _Matrix>
void ColumnSamplingSketcher<_Matrix>::sketchImpl(
    const _Matrix &matrix_a,
          DenseCube<ScalarType, Layout::ROWMAJOR> &cube_q
) noexcept {
  assert(parameters_.isInitialized());
  assert(matrix_a.getSizes() == std::make_pair(parameters_.getNrow(), parameters_.getNcol()));
  assert(cube_q.getSizes()   == std::make_tuple(parameters_.getNrow(), parameters_.getDimSketch(),
                                                                       parameters_.getNumSketchEach()));

  for ( index_t i = 0; i < parameters_.getNumSketchEach(); ++i ) {
    for ( index_t j = 0; j < parameters_.getDimSketch(); ++j ) {
      blas::copy(matrix_a.getCol(random_distribution_(random_generator_)), cube_q.getCol(j, i));
    }
    gesvd_driver_(cube_q.getPage(i), vector_s_, matrix_empty_, matrix_empty_);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherBase::getName
///
template <class _Matrix>
constexpr const char* ColumnSamplingSketcher<_Matrix>::getNameImpl() const noexcept {
  return name_;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_IPP_
