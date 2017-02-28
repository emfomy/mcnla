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
/// @copydoc  mcnla::isvd::OrthogonalizerWrapper::OrthogonalizerWrapper
///
template <typename _Val>
Orthogonalizer<SvdOrthogonalizerTag, _Val>::Orthogonalizer(
    const ParametersType &parameters,
    const MPI_Comm mpi_comm,
    const mpi_int_t mpi_root
) noexcept
  : BaseType(parameters, mpi_comm, mpi_root) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::OrthogonalizerWrapper::initialize
///
template <typename _Val>
void Orthogonalizer<SvdOrthogonalizerTag, _Val>::initializeImpl() noexcept {

  const auto nrow            = parameters_.nrow();
  const auto dim_sketch      = parameters_.dimSketch();

  moment0_ = 0;
  moment1_ = 0;

  vector_s_.reconstruct(dim_sketch);
  gesvd_driver_.reconstruct(nrow, dim_sketch);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::OrthogonalizerWrapper::orthogonalize
///
template <typename _Val>
void Orthogonalizer<SvdOrthogonalizerTag, _Val>::orthogonalizeImpl(
          DenseMatrixCollection120<ValType> &collection_q
) noexcept {

  mcnla_assert_true(parameters_.isInitialized());

  const auto nrow            = parameters_.nrow();
  const auto num_sketch_each = parameters_.numSketchEach();
  const auto dim_sketch      = parameters_.dimSketch();

  mcnla_assert_eq(collection_q.sizes(), std::make_tuple(nrow, dim_sketch, num_sketch_each));

  moment0_ = MPI_Wtime();

  // Orthogonalizes
  for ( index_t i = 0; i < num_sketch_each; ++i ) {
    gesvd_driver_(collection_q(i), vector_s_, matrix_empty_, matrix_empty_);
  }
  moment1_ = MPI_Wtime();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::OrthogonalizerWrapper::outputName
///
///
template <typename _Val>
std::ostream& Orthogonalizer<SvdOrthogonalizerTag, _Val>::outputNameImpl(
    std::ostream &os
) const noexcept {
  return (os << name_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::OrthogonalizerWrapper::time
///
template <typename _Val>
double Orthogonalizer<SvdOrthogonalizerTag, _Val>::timeImpl() const noexcept {
  return moment1_-moment0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::OrthogonalizerWrapper::time
///
template <typename _Val>
double Orthogonalizer<SvdOrthogonalizerTag, _Val>::time1() const noexcept {
  return moment1_-moment0_;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_ORTHOGONALIZER_SVD_ORTHOGONALIZER_HPP_
