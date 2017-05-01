////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/orthogonalizer/polar_orthogonalizer.hpp
/// @brief   The polar orthogonalizer.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_ORTHOGONALIZER_POLAR_ORTHOGONALIZER_HPP_
#define MCNLA_ISVD_ORTHOGONALIZER_POLAR_ORTHOGONALIZER_HPP_

#include <mcnla/isvd/orthogonalizer/polar_orthogonalizer.hh>
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
/// @copydoc  mcnla::isvd::StageWrapper::StageWrapper
///
template <typename _Val>
Orthogonalizer<PolarOrthogonalizerTag, _Val>::Orthogonalizer(
    const Parameters<ValType> &parameters
) noexcept
  : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::StageWrapper::initialize
///
template <typename _Val>
void Orthogonalizer<PolarOrthogonalizerTag, _Val>::initializeImpl() noexcept {

  const auto nrow            = parameters_.nrow();
  const auto num_sketch_each = parameters_.numSketchEach();
  const auto dim_sketch      = parameters_.dimSketch();

  collection_w_.reconstruct(dim_sketch, dim_sketch, num_sketch_each);
  matrix_s_.reconstruct(dim_sketch, num_sketch_each);
  collection_tmp_.reconstruct(nrow, dim_sketch, num_sketch_each);
  gesvd_driver_.reconstruct(dim_sketch, dim_sketch);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Orthogonalizes.
///
/// @param  collection_q  The matrix collection Q.
///
template <typename _Val>
void Orthogonalizer<PolarOrthogonalizerTag, _Val>::runImpl(
    DenseMatrixCollection201<ValType> &collection_q
) noexcept {

  const auto nrow            = parameters_.nrow();
  const auto num_sketch_each = parameters_.numSketchEach();
  const auto dim_sketch      = parameters_.dimSketch();

  mcnla_assert_eq(collection_q.sizes(), std::make_tuple(nrow, dim_sketch, num_sketch_each));

  auto &matrix_qs = collection_q.unfold();  // matrix Qs.

  moments_.emplace_back(utility::getTime());  // orthogonalization

  // Wi := Qi' * Qi
  for ( index_t i = 0; i < num_sketch_each; ++i ) {
    la::mm(collection_q(i).t(), collection_q(i), collection_w_(i));
  }

  // Compute the eigen-decomposition of Wi -> Wi' * Si * Wi
  for ( index_t i = 0; i < num_sketch_each; ++i ) {
    gesvd_driver_(collection_w_(i), matrix_s_(""_, i), matrix_empty_, matrix_empty_);
  }

  // Qi := Qi * Wi' / sqrt(Si)
  for ( auto &v : matrix_s_ ) {
    v = std::sqrt(v);
  }
  la::copy(matrix_qs.vectorize(), collection_tmp_.unfold().vectorize());
  for ( index_t i = 0; i < num_sketch_each; ++i ) {
    la::sm(matrix_s_(""_, i).viewDiagonal().inv(), collection_w_(i));
    la::mm(collection_tmp_(i), collection_w_(i).t(), collection_q(i));
  }

  moments_.emplace_back(utility::getTime());  // end
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_ORTHOGONALIZER_POLAR_ORTHOGONALIZER_HPP_
