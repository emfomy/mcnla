////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/orthogonalizer/row_block_polar_orthogonalizer.hpp
/// @brief   The SVD orthogonalizer.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_ORTHOGONALIZER_ROW_BLOCK_POLAR_ORTHOGONALIZER_HPP_
#define MCNLA_ISVD_ORTHOGONALIZER_ROW_BLOCK_POLAR_ORTHOGONALIZER_HPP_

#include <mcnla/isvd/orthogonalizer/row_block_polar_orthogonalizer.hh>
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
Orthogonalizer<RowBlockPolarOrthogonalizerTag, _Val>::Orthogonalizer(
    const Parameters<ValType> &parameters
) noexcept
  : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::ComponentWrapper::initialize
///
template <typename _Val>
void Orthogonalizer<RowBlockPolarOrthogonalizerTag, _Val>::initializeImpl() noexcept {

  const auto nrow_each  = parameters_.nrowEach();
  const auto num_sketch = parameters_.numSketch();
  const auto dim_sketch = parameters_.dimSketch();

  collection_v_.reconstruct(dim_sketch, dim_sketch, num_sketch);
  vector_e_.reconstruct(dim_sketch);
  collection_tmp_.reconstruct(nrow_each, dim_sketch, num_sketch);
  syev_driver_.reconstruct(dim_sketch);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Orthogonalizes.
///
/// @param  collection_qj  The matrix collection Qj (j-th row-block, where j is the MPI rank).
///
template <typename _Val>
void Orthogonalizer<RowBlockPolarOrthogonalizerTag, _Val>::runImpl(
    DenseMatrixCollection120<ValType> &collection_qj
) noexcept {

  const auto mpi_comm   = parameters_.mpi_comm;
  const auto nrow_each  = parameters_.nrowEach();
  const auto num_sketch = parameters_.numSketch();
  const auto dim_sketch = parameters_.dimSketch();

  mcnla_assert_eq(collection_qj.sizes(), std::make_tuple(nrow_each, dim_sketch, num_sketch));

  auto &matrix_qjs = collection_qj.unfold();  // matrix Qs.

  moments_.emplace_back(MPI_Wtime());  // orthogonalization

  // Vi := Qi' * Qi
  for ( index_t i = 0; i < num_sketch; ++i ) {
    la::rk(collection_qj(i).t(), collection_v_(i).viewSymmetric());
  }

  // Reduce sum Vi
  mpi::allreduce(collection_v_.unfold(), MPI_SUM, mpi_comm);

  // Compute the eigen-decomposition of V -> V' * E * V
  for ( index_t i = 0; i < num_sketch; ++i ) {
    syev_driver_(collection_v_(i).viewSymmetric(), vector_e_);
  }

  // Q *= V
  la::copy(matrix_qjs.vectorize(), collection_tmp_.unfold().vectorize());
  for ( index_t i = 0; i < num_sketch; ++i ) {
    la::mm(collection_tmp_(i), collection_v_(i).viewSymmetric(), collection_qj(i));
  }

  // Normalize columns of Q
  for ( index_t i = 0; i < collection_qj.unfold().ncol(); ++i ) {
    auto nrm = la::nrm2(matrix_qjs("", i));
    la::scal(matrix_qjs("", i), 1.0/nrm);
  }

  moments_.emplace_back(MPI_Wtime());  // end
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_ORTHOGONALIZER_ROW_BLOCK_POLAR_ORTHOGONALIZER_HPP_
