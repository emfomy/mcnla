////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/orthogonalizer/gramian_orthogonalizer.hpp
/// @brief   The Gramian orthogonalizer.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_ORTHOGONALIZER_GRAMIAN_ORTHOGONALIZER_HPP_
#define MCNLA_ISVD_ORTHOGONALIZER_GRAMIAN_ORTHOGONALIZER_HPP_

#include <mcnla/isvd/orthogonalizer/gramian_orthogonalizer.hh>
#include <mcnla/core/la.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS  Orthogonalizer<GramianOrthogonalizerTag, _Val>
  #define MCNLA_ALIAS0 Orthogonalizer
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS  GramianOrthogonalizer<_Val>
  #define MCNLA_ALIAS0 GramianOrthogonalizer
#endif  // DOXYGEN_SHOULD_SKIP_THIS

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
MCNLA_ALIAS::MCNLA_ALIAS0(
    const Parameters<_Val> &parameters
) noexcept
  : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::StageWrapper::initialize
///
template <typename _Val>
void MCNLA_ALIAS::initializeImpl() noexcept {

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
void MCNLA_ALIAS::runImpl(
    DenseMatrixCollectionColBlockRowMajor<_Val> &collection_q
) noexcept {

  const auto nrow            = parameters_.nrow();
  const auto num_sketch_each = parameters_.numSketchEach();
  const auto dim_sketch      = parameters_.dimSketch();

  static_cast<void>(nrow);
  static_cast<void>(dim_sketch);

  mcnla_assert_eq(collection_q.sizes(), std::make_tuple(nrow, dim_sketch, num_sketch_each));

  auto &matrix_qs = collection_q.unfold();  // matrix Qs.

  double comm_time;
  this->tic(comm_time);
  // ====================================================================================================================== //
  // Start

  // Wi := Qi' * Qi
  for ( index_t i = 0; i < num_sketch_each; ++i ) {
    la::mm(collection_q(i).t(), collection_q(i), collection_w_(i));
  }

  // eig(Wi) = Wi' * Si * Wi
  for ( index_t i = 0; i < num_sketch_each; ++i ) {
    gesvd_driver_(collection_w_(i), matrix_s_(""_, i), matrix_empty_, matrix_empty_);
  }

  // Qi := Qi * Wi' / sqrt(Si)
  for ( auto &v : matrix_s_ ) {
    v = std::sqrt(v);
  }
  la::copy(matrix_qs.vec(), collection_tmp_.unfold().vec());
  for ( index_t i = 0; i < num_sketch_each; ++i ) {
    la::sm(matrix_s_(""_, i).diag().inv(), collection_w_(i));
    la::mm(collection_tmp_(i), collection_w_(i).t(), collection_q(i));
  }

  this->toc(comm_time);
}

}  // namespace isvd

}  // namespace mcnla

#undef MCNLA_ALIAS
#undef MCNLA_ALIAS0

#endif  // MCNLA_ISVD_ORTHOGONALIZER_GRAMIAN_ORTHOGONALIZER_HPP_
