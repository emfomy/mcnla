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
#include <mcnla/core/blas.hpp>

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
template <typename _Scalar>
Sketcher<_Scalar, ColumnSamplingSketcherTag>::Sketcher(
    const ParametersType &parameters,
    const MPI_Comm mpi_comm,
    const mpi_int_t mpi_root,
    const index_t seed
) noexcept
  : BaseType(parameters, mpi_comm, mpi_root),
    random_engine_(seed) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::initialize
///
template <typename _Scalar>
void Sketcher<_Scalar, ColumnSamplingSketcherTag>::initializeImpl() noexcept {

  const auto num_sketch_each = parameters_.numSketchEach();
  const auto dim_sketch      = parameters_.dimSketch();

  time0_ = 0;
  time1_ = 0;
  time2_ = 0;

  vector_idxs_.reconstruct(dim_sketch * num_sketch_each);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::sketch
 ///
template <typename _Scalar> template <class _Matrix>
void Sketcher<_Scalar, ColumnSamplingSketcherTag>::sketchImpl(
    const _Matrix &matrix_a,
          DenseMatrixCollection120<ScalarType> &collection_q
) noexcept {

  mcnla_assert_true(parameters_.isInitialized());

  const auto nrow            = parameters_.nrow();
  const auto ncol            = parameters_.ncol();
  const auto num_sketch_each = parameters_.numSketchEach();
  const auto dim_sketch      = parameters_.dimSketch();

  mcnla_assert_eq(matrix_a.sizes(), std::make_tuple(nrow, ncol));
  mcnla_assert_eq(collection_q.sizes(),    std::make_tuple(nrow, dim_sketch, num_sketch_each));

  time0_ = MPI_Wtime();

  // Random sample Idxs using uniform distribution
  random_engine_.uniform(vector_idxs_, 0, ncol);
  time1_ = MPI_Wtime();

  // Copy columns
  for ( index_t i = 0; i < dim_sketch * num_sketch_each; ++i ) {
    blas::copy(matrix_a("", vector_idxs_(i)), collection_q.unfold()("", i));
  }
  time2_ = MPI_Wtime();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::outputName
///
///
template <typename _Scalar>
std::ostream&Sketcher<_Scalar, ColumnSamplingSketcherTag>::outputNameImpl(
    std::ostream &os
) const noexcept {
  return (os << name_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::time
///
template <typename _Scalar>
double Sketcher<_Scalar, ColumnSamplingSketcherTag>::timeImpl() const noexcept {
  return time2_-time0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::time
///
template <typename _Scalar>
double Sketcher<_Scalar, ColumnSamplingSketcherTag>::time1() const noexcept {
  return time1_-time0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::time
///
template <typename _Scalar>
double Sketcher<_Scalar, ColumnSamplingSketcherTag>::time2() const noexcept {
  return time2_-time1_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::setSeed
///
template <typename _Scalar>
void Sketcher<_Scalar, ColumnSamplingSketcherTag>::setSeedImpl(
    const index_t seed
) noexcept {
  random_engine_.setSeed(seed);
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_HPP_
