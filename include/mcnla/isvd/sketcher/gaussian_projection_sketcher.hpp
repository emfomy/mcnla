////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/gaussian_projection_sketcher.hpp
/// @brief   The Gaussian projection sketcher.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HPP_
#define MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HPP_

#include <mcnla/isvd/sketcher/gaussian_projection_sketcher.hh>
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
Sketcher<_Scalar, GaussianProjectionSketcherTag>::Sketcher(
    const Parameters<ScalarType> &parameters,
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
void Sketcher<_Scalar, GaussianProjectionSketcherTag>::initializeImpl() noexcept {

  const auto ncol            = parameters_.ncol();
  const auto num_sketch_each = parameters_.numSketchEach();
  const auto dim_sketch      = parameters_.dimSketch();

  time0_ = 0;
  time1_ = 0;
  time2_ = 0;

  matrix_omegas_.reconstruct(ncol, dim_sketch * num_sketch_each);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::sketch
///
template <typename _Scalar> template <class _Matrix>
void Sketcher<_Scalar, GaussianProjectionSketcherTag>::sketchImpl(
    const _Matrix &matrix_a,
          DenseMatrixSet120<ScalarType> &set_q
) noexcept {

  mcnla_assert_true(parameters_.isInitialized());

  const auto nrow            = parameters_.nrow();
  const auto ncol            = parameters_.ncol();
  const auto num_sketch_each = parameters_.numSketchEach();
  const auto dim_sketch      = parameters_.dimSketch();

  mcnla_assert_eq(matrix_a.sizes(), std::make_tuple(nrow, ncol));
  mcnla_assert_eq(set_q.sizes(),    std::make_tuple(nrow, dim_sketch, num_sketch_each));

  time0_ = MPI_Wtime();

  // Random sample Omega using normal Gaussian distribution
  random_engine_.gaussian(matrix_omegas_.vectorize());
  time1_ = MPI_Wtime();

  // Q := A * Omega
  blas::mm(matrix_a, matrix_omegas_, set_q.unfold());
  time2_ = MPI_Wtime();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::name
///
template <typename _Scalar>
constexpr const char* Sketcher<_Scalar, GaussianProjectionSketcherTag>::nameImpl(
) const noexcept {
  return name_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::time
///
template <typename _Scalar>
double Sketcher<_Scalar, GaussianProjectionSketcherTag>::timeImpl() const noexcept {
  return time2_-time0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::time
///
template <typename _Scalar>
double Sketcher<_Scalar, GaussianProjectionSketcherTag>::time1() const noexcept {
  return time1_-time0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::time
///
template <typename _Scalar>
double Sketcher<_Scalar, GaussianProjectionSketcherTag>::time2() const noexcept {
  return time2_-time1_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::setSeed
///
template <typename _Scalar>
void Sketcher<_Scalar, GaussianProjectionSketcherTag>::setSeedImpl(
    const index_t seed
) noexcept {
  random_engine_.setSeed(seed);
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HPP_
