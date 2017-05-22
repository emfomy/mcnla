////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/gaussian_projection_sketcher.hpp
/// @brief   The Gaussian projection sketcher.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HPP_
#define MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HPP_

#include <mcnla/isvd/sketcher/gaussian_projection_sketcher.hh>
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
GaussianProjectionSketcher<_Val>::Sketcher(
    const Parameters<ValType> &parameters,
    const index_t seed,
    const index_t exponent
) noexcept
  : BaseType(parameters) {
  setSeed(seed);
  setExponent(exponent);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::StageWrapper::initialize
///
template <typename _Val>
void GaussianProjectionSketcher<_Val>::initializeImpl() noexcept {

  const auto ncol            = parameters_.ncol();
  const auto dim_sketch_each = parameters_.dimSketchEach();

  matrix_omegas_.reconstruct(ncol, dim_sketch_each);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sketches.
///
/// @param  matrix_a      The matrix A.
/// @param  collection_q  The matrix collection Q.
///
template <typename _Val> template <class _Matrix>
void GaussianProjectionSketcher<_Val>::runImpl(
    const _Matrix &matrix_a,
          DenseMatrixCollection201<ValType> &collection_q
) noexcept {

  const auto mpi_comm        = parameters_.mpi_comm;
  const auto mpi_root        = parameters_.mpi_root;
  const auto nrow            = parameters_.nrow();
  const auto ncol            = parameters_.ncol();
  const auto num_sketch_each = parameters_.numSketchEach();
  const auto dim_sketch      = parameters_.dimSketch();

  mcnla_assert_eq(matrix_a.sizes(),     std::make_tuple(nrow, ncol));
  mcnla_assert_eq(collection_q.sizes(), std::make_tuple(nrow, dim_sketch, num_sketch_each));

  random::Streams streams(seed_, mpi_root, mpi_comm);

  this->tic(); double comm_time = 0;
  // ====================================================================================================================== //
  // Random generating

  // Random sample Omega using normal Gaussian distribution
  random::gaussian(streams, matrix_omegas_.vectorize());

  this->toc(comm_time);
  // ====================================================================================================================== //
  // Projection

  // Q := A * Omega
  la::mm(matrix_a, matrix_omegas_, collection_q.unfold());
  for ( index_t i = 0; i < exponent_; ++i ) {
    la::mm(matrix_a.t(), collection_q.unfold(), matrix_omegas_);
    la::mm(matrix_a, matrix_omegas_, collection_q.unfold());
  }

  this->toc(comm_time);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::StageWrapper::outputName
///
///
template <typename _Val>
std::ostream& GaussianProjectionSketcher<_Val>::outputNameImpl(
    std::ostream &os
) const noexcept {
  return (os << name_ << " (Power " << exponent_ << ")");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the random seed.
///
template <typename _Val>
index_t GaussianProjectionSketcher<_Val>::seed() const noexcept {
  return seed_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the exponent of power method.
///
template <typename _Val>
index_t GaussianProjectionSketcher<_Val>::exponent() const noexcept {
  return exponent_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the random seed.
///
template <typename _Val>
GaussianProjectionSketcher<_Val>& GaussianProjectionSketcher<_Val>::setSeed(
    const index_t seed
) noexcept {
  seed_ = seed;
  computed_ = false;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the exponent of power method.
///
template <typename _Val>
GaussianProjectionSketcher<_Val>& GaussianProjectionSketcher<_Val>::setExponent(
    const index_t exponent
) noexcept {
  mcnla_assert_ge(exponent, 0);
  exponent_ = exponent;
  computed_ = false;
  return *this;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HPP_
