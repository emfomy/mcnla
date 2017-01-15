////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/orthogonalizer/svd_orthogonalizer.hpp
/// @brief   The SVD orthogonalizer.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_ORTHOGONALIZER_SVD_ORTHOGONALIZER_HPP_
#define MCNLA_ISVD_ORTHOGONALIZER_SVD_ORTHOGONALIZER_HPP_

#include <mcnla/isvd/orthogonalizer/svd_orthogonalizer.hh>
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
/// @copydoc  mcnla::isvd::OrthogonalizerWrapper::OrthogonalizerWrapper
///
template <typename _Scalar>
Orthogonalizer<_Scalar, SvdOrthogonalizerTag>::Orthogonalizer(
    const Parameters &parameters,
    const MPI_Comm mpi_comm,
    const mpi_int_t mpi_root
) noexcept
  : BaseType(parameters, mpi_comm, mpi_root) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::OrthogonalizerWrapper::initialize
///
template <typename _Scalar>
void Orthogonalizer<_Scalar, SvdOrthogonalizerTag>::initializeImpl() noexcept {

  const auto nrow            = parameters_.nrow();
  const auto dim_sketch      = parameters_.dimSketch();

  time0_ = 0;
  time1_ = 0;

  vector_s_.reconstruct(dim_sketch);
  gesvd_engine_.reconstruct(nrow, dim_sketch);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::OrthogonalizerWrapper::orthogonalize
///
template <typename _Scalar>
void Orthogonalizer<_Scalar, SvdOrthogonalizerTag>::orthogonalizeImpl(
          DenseMatrixCollection120<ScalarType> &collection_q
) noexcept {

  mcnla_assert_true(parameters_.isInitialized());

  const auto nrow            = parameters_.nrow();
  const auto num_sketch_each = parameters_.numSketchEach();
  const auto dim_sketch      = parameters_.dimSketch();

  mcnla_assert_eq(collection_q.sizes(), std::make_tuple(nrow, dim_sketch, num_sketch_each));

  time0_ = MPI_Wtime();

  // Orthogonalizes
  for ( index_t i = 0; i < num_sketch_each; ++i ) {
    gesvd_engine_(collection_q(i), vector_s_, matrix_empty_, matrix_empty_);
  }
  time1_ = MPI_Wtime();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::OrthogonalizerWrapper::name
///
template <typename _Scalar>
constexpr const char* Orthogonalizer<_Scalar, SvdOrthogonalizerTag>::nameImpl(
) const noexcept {
  return name_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::OrthogonalizerWrapper::time
///
template <typename _Scalar>
double Orthogonalizer<_Scalar, SvdOrthogonalizerTag>::timeImpl() const noexcept {
  return time1_-time0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::OrthogonalizerWrapper::time
///
template <typename _Scalar>
double Orthogonalizer<_Scalar, SvdOrthogonalizerTag>::time1() const noexcept {
  return time1_-time0_;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_ORTHOGONALIZER_SVD_ORTHOGONALIZER_HPP_
