////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/column_sampling_sketcher.ipp
/// @brief   The implementation of column sampling sketcher.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_IPP_
#define MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_IPP_

#include <mcnla/isvd/sketcher/column_sampling_sketcher.hpp>
#include <ctime>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::SketcherWrapper
///
template <class _Matrix>
Sketcher<_Matrix, DenseMatrixSet120<ScalarT<_Matrix>>, ColumnSamplingSketcherTag>::Sketcher(
    const Parameters<ScalarType> &parameters,
    const MPI_Comm mpi_comm,
    const mpi_int_t mpi_root
) noexcept
  : BaseType(parameters, mpi_comm, mpi_root),
    seed_(time(NULL)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::initialize
///
template <class _Matrix>
void ColumnSamplingSketcher<_Matrix>::initializeImpl() noexcept {

  const auto vector_s_sizes = parameters_.dimSketch();
  if ( vector_s_.sizes() != vector_s_sizes ) {
    vector_s_ = DenseVector<RealScalarType>(vector_s_sizes);
  }

  const auto gesvd_sizes = std::make_tuple(parameters_.nrow(), parameters_.dimSketch());
  if ( gesvd_driver_.sizes() != gesvd_sizes ) {
    gesvd_driver_.resize(gesvd_sizes);
  }

  srand(this->seed_[0]);
  random_distribution_ = std::uniform_int_distribution<index_t>(0, parameters_.ncol()-1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::sketch
///
template <class _Matrix>
void ColumnSamplingSketcher<_Matrix>::sketchImpl(
    const _Matrix &matrix_a,
          DenseMatrixSet120<ScalarType> &set_q
) noexcept {
  mcnla_assert_true(parameters_.isInitialized());
  mcnla_assert_eq(matrix_a.sizes(), std::make_tuple(parameters_.nrow(), parameters_.ncol()));
  mcnla_assert_eq(set_q.sizes(),   std::make_tuple(parameters_.nrow(), parameters_.dimSketch(),
                                                       parameters_.numSketchEach()));

  for ( index_t i = 0; i < parameters_.numSketchEach(); ++i ) {
    for ( index_t j = 0; j < parameters_.dimSketch(); ++j ) {
      blas::copy(matrix_a.getCol(random_distribution_(random_generator_)), set_q.getCol(j, i));
    }
    gesvd_driver_(set_q.getPage(i), vector_s_, matrix_empty_, matrix_empty_);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::name
///
template <class _Matrix>
constexpr const char* ColumnSamplingSketcher<_Matrix>::nameImpl() const noexcept {
  return name_;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_IPP_
