////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/gaussian_projection_sketcher.ipp
/// @brief   The implementation of Gaussian projection sketcher.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_IPP_
#define MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_IPP_

#include <mcnla/isvd/sketcher/gaussian_projection_sketcher.hpp>
#include <omp.h>

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
Sketcher<_Matrix, DenseMatrixSet120<ScalarT<_Matrix>>, GaussianProjectionSketcherTag>::Sketcher(
    const Parameters<ScalarType> &parameters,
    const MPI_Comm mpi_comm,
    const mpi_int_t mpi_root
) noexcept
  : BaseType(parameters, mpi_comm, mpi_root),
    seed_{(rand()^mpi::commRank(mpi_comm))%4096, (rand()^mpi::commRank(mpi_comm))%4096,
          (rand()^mpi::commRank(mpi_comm))%4096, ((rand()^mpi::commRank(mpi_comm))%2048)*2+1} {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::initialize
///
template <class _Matrix>
void Sketcher<_Matrix, DenseMatrixSet120<ScalarT<_Matrix>>, GaussianProjectionSketcherTag>::initializeImpl() noexcept {

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
template <class _Matrix>
void Sketcher<_Matrix, DenseMatrixSet120<ScalarT<_Matrix>>, GaussianProjectionSketcherTag>::sketchImpl(
    const _Matrix &matrix_a,
          DenseMatrixSet120<ScalarType> &set_y
) noexcept {

  mcnla_assert_true(parameters_.isInitialized());

  const auto nrow            = parameters_.nrow();
  const auto ncol            = parameters_.ncol();
  const auto num_sketch_each = parameters_.numSketchEach();
  const auto dim_sketch      = parameters_.dimSketch();

  mcnla_assert_eq(matrix_a.sizes(), std::make_tuple(nrow, ncol));
  mcnla_assert_eq(set_y.sizes(),    std::make_tuple(nrow, dim_sketch, num_sketch_each));

  time0_ = MPI_Wtime();

  // Random sample Omega using normal Gaussian distribution
  lapack::larnv<3>(matrix_omegas_.vectorize(), seed_);
  time1_ = MPI_Wtime();

  // Q := A * Omega
  blas::mm(matrix_a, matrix_omegas_, set_y.unfold());
  time2_ = MPI_Wtime();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::name
///
template <class _Matrix>
constexpr const char* Sketcher<_Matrix, DenseMatrixSet120<ScalarT<_Matrix>>, GaussianProjectionSketcherTag>::nameImpl(
) const noexcept {
  return name_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::time
///
template <class _Matrix>
double Sketcher<_Matrix, DenseMatrixSet120<ScalarT<_Matrix>>, GaussianProjectionSketcherTag>::timeImpl() const noexcept {
  return time2_-time0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::time
///
template <class _Matrix>
double Sketcher<_Matrix, DenseMatrixSet120<ScalarT<_Matrix>>, GaussianProjectionSketcherTag>::time1() const noexcept {
  return time1_-time0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::SketcherWrapper::time
///
template <class _Matrix>
double Sketcher<_Matrix, DenseMatrixSet120<ScalarT<_Matrix>>, GaussianProjectionSketcherTag>::time2() const noexcept {
  return time2_-time1_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the random seed.
///
template <class _Matrix>
Sketcher<_Matrix, DenseMatrixSet120<ScalarT<_Matrix>>, GaussianProjectionSketcherTag>&
  Sketcher<_Matrix, DenseMatrixSet120<ScalarT<_Matrix>>, GaussianProjectionSketcherTag>::setSeed(
    const index_t seed[4]
) noexcept {
  for ( index_t i = 0; i < 4; ++i ) {
    seed_[i] = seed[i];
  }
  return *this;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_IPP_
