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
/// @copydoc  mcnla::isvd::ComponentWrapper::ComponentWrapper
///
template <typename _Val>
Orthogonalizer<PolarOrthogonalizerTag, _Val>::Orthogonalizer(
    const Parameters<ValType> &parameters
) noexcept
  : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::ComponentWrapper::initialize
///
template <typename _Val>
void Orthogonalizer<PolarOrthogonalizerTag, _Val>::initializeImpl() noexcept {

  const auto nrow            = parameters_.nrow();
  const auto num_sketch_each = parameters_.numSketchEach();
  const auto dim_sketch      = parameters_.dimSketch();

  collection_p_.reconstruct(dim_sketch, dim_sketch, num_sketch_each);
  matrix_e_.reconstruct(dim_sketch, num_sketch_each);
  collection_tmp_.reconstruct(nrow, dim_sketch, num_sketch_each);
  syev_driver_.reconstruct(dim_sketch);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Orthogonalizes.
///
/// @param  collection_q  The matrix collection Q.
///
template <typename _Val>
void Orthogonalizer<PolarOrthogonalizerTag, _Val>::runImpl(
    DenseMatrixCollection120<ValType> &collection_q
) noexcept {

  const auto nrow            = parameters_.nrow();
  const auto num_sketch_each = parameters_.numSketchEach();
  const auto dim_sketch      = parameters_.dimSketch();

  mcnla_assert_eq(collection_q.sizes(), std::make_tuple(nrow, dim_sketch, num_sketch_each));

  auto &matrix_qs = collection_q.unfold();  // matrix Qs.

  moments_.emplace_back(MPI_Wtime());  // orthogonalization

  // Pi := Qi' * Qi
  for ( index_t i = 0; i < num_sketch_each; ++i ) {
    la::rk(collection_q(i).t(), collection_p_(i).viewSymmetric());
  }

  // Compute the eigen-decomposition of Pi -> Pi' * Ei * Pi
  for ( index_t i = 0; i < num_sketch_each; ++i ) {
    syev_driver_(collection_p_(i).viewSymmetric(), matrix_e_("", i));
  }

  // Qi := Qi * Pi' / sqrt(Ei)
  matrix_e_.val().valarray() = std::sqrt(matrix_e_.val().valarray());
  la::copy(matrix_qs.vectorize(), collection_tmp_.unfold().vectorize());
  for ( index_t i = 0; i < num_sketch_each; ++i ) {
    la::sm(matrix_e_("", i).viewDiagonal().inv(), collection_p_(i));
    la::mm(collection_tmp_(i), collection_p_(i).t(), collection_q(i));
  }

  moments_.emplace_back(MPI_Wtime());  // end
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_ORTHOGONALIZER_POLAR_ORTHOGONALIZER_HPP_
