////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/orthogonalizer/svd_orthogonalizer.hpp
/// @brief   The SVD orthogonalizer.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_ORTHOGONALIZER_SVD_ORTHOGONALIZER_HPP_
#define MCNLA_ISVD_ORTHOGONALIZER_SVD_ORTHOGONALIZER_HPP_

#include <mcnla/isvd/orthogonalizer/svd_orthogonalizer.hh>
#include <mcnla/core/la.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS  Orthogonalizer<SvdOrthogonalizerTag, _Val>
  #define MCNLA_ALIAS0 Orthogonalizer
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS  SvdOrthogonalizer<_Val>
  #define MCNLA_ALIAS0 SvdOrthogonalizer
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
  const auto dim_sketch      = parameters_.dimSketch();

  vector_s_.reconstruct(dim_sketch);
  gesvd_driver_.reconstruct(nrow, dim_sketch);
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

  mcnla_assert_eq(collection_q.sizes(), std::make_tuple(nrow, dim_sketch, num_sketch_each));

  double comm_time;
  this->tic(comm_time);
  // ====================================================================================================================== //
  // Start

  // Orthogonalizes
  for ( index_t i = 0; i < num_sketch_each; ++i ) {
    gesvd_driver_(collection_q(i), vector_s_, matrix_empty_, matrix_empty_);
  }

  this->toc(comm_time);
}

}  // namespace isvd

}  // namespace mcnla

#undef MCNLA_ALIAS
#undef MCNLA_ALIAS0

#endif  // MCNLA_ISVD_ORTHOGONALIZER_SVD_ORTHOGONALIZER_HPP_
