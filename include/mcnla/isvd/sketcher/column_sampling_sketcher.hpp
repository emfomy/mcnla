////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/column_sampling_sketcher.hpp
/// @brief   The column sampling sketcher.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_HPP_
#define MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_HPP_

#include <mcnla/isvd/sketcher/column_sampling_sketcher.hh>
#include <ctime>
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
/// @copydoc  mcnla::isvd::SketcherWrapper::SketcherWrapper
///
template <typename _Val>
Sketcher<ColumnSamplingSketcherTag, _Val>::Sketcher(
    const ParametersType &parameters,
    const MPI_Comm mpi_comm,
    const mpi_int_t mpi_root,
    const index_t seed
) noexcept
  : BaseType(parameters, mpi_comm, mpi_root),
    random_driver_(seed) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::initialize
///
template <typename _Val>
void Sketcher<ColumnSamplingSketcherTag, _Val>::initializeImpl() noexcept {

  const auto num_sketch_each = parameters_.numSketchEach();
  const auto dim_sketch      = parameters_.dimSketch();

  moment0_ = 0;
  moment1_ = 0;
  moment2_ = 0;

  vector_idxs_.reconstruct(dim_sketch * num_sketch_each);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::sketch
 ///
template <typename _Val> template <class _Matrix>
void Sketcher<ColumnSamplingSketcherTag, _Val>::sketchImpl(
    const _Matrix &matrix_a,
          DenseMatrixCollection120<ValType> &collection_q
) noexcept {

  mcnla_assert_true(parameters_.isInitialized());

  const auto nrow            = parameters_.nrow();
  const auto ncol            = parameters_.ncol();
  const auto num_sketch_each = parameters_.numSketchEach();
  const auto dim_sketch      = parameters_.dimSketch();

  mcnla_assert_eq(matrix_a.sizes(), std::make_tuple(nrow, ncol));
  mcnla_assert_eq(collection_q.sizes(),    std::make_tuple(nrow, dim_sketch, num_sketch_each));

  moment0_ = MPI_Wtime();

  // Random sample Idxs using uniform distribution
  random_driver_.uniform(vector_idxs_, 0, ncol);
  moment1_ = MPI_Wtime();

  // Copy columns
  for ( index_t i = 0; i < dim_sketch * num_sketch_each; ++i ) {
    la::copy(matrix_a("", vector_idxs_(i)), collection_q.unfold()("", i));
  }
  moment2_ = MPI_Wtime();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::outputName
///
///
template <typename _Val>
std::ostream& Sketcher<ColumnSamplingSketcherTag, _Val>::outputNameImpl(
    std::ostream &os
) const noexcept {
  return (os << name_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::time
///
template <typename _Val>
double Sketcher<ColumnSamplingSketcherTag, _Val>::timeImpl() const noexcept {
  return moment2_-moment0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::time
///
template <typename _Val>
double Sketcher<ColumnSamplingSketcherTag, _Val>::time1() const noexcept {
  return moment1_-moment0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::time
///
template <typename _Val>
double Sketcher<ColumnSamplingSketcherTag, _Val>::time2() const noexcept {
  return moment2_-moment1_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::setSeed
///
template <typename _Val>
void Sketcher<ColumnSamplingSketcherTag, _Val>::setSeedImpl(
    const index_t seed
) noexcept {
  random_driver_.setSeed(seed);
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_HPP_
