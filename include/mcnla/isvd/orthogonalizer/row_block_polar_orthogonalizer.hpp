////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/orthogonalizer/row_block_polar_orthogonalizer.hpp
/// @brief   The polar orthogonalizer (row-block version).
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
/// @copydoc  mcnla::isvd::StageWrapper::StageWrapper
///
template <typename _Val>
Orthogonalizer<RowBlockPolarOrthogonalizerTag, _Val>::Orthogonalizer(
    const Parameters<ValType> &parameters
) noexcept
  : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::StageWrapper::initialize
///
template <typename _Val>
void Orthogonalizer<RowBlockPolarOrthogonalizerTag, _Val>::initializeImpl() noexcept {

  const auto nrow_rank  = parameters_.nrowRank();
  const auto num_sketch = parameters_.numSketch();
  const auto dim_sketch = parameters_.dimSketch();

  collection_w_.reconstruct(dim_sketch, dim_sketch, num_sketch);
  matrix_s_.reconstruct(dim_sketch, num_sketch);
  collection_tmp_.reconstruct(nrow_rank, dim_sketch, num_sketch);
  gesvd_driver_.reconstruct(dim_sketch, dim_sketch);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Orthogonalizes.
///
/// @param  collection_qj  The matrix collection Qj (j-th row-block, where j is the MPI rank).
///
template <typename _Val>
void Orthogonalizer<RowBlockPolarOrthogonalizerTag, _Val>::runImpl(
    DenseMatrixCollection201<ValType> &collection_qj
) noexcept {

  const auto mpi_comm   = parameters_.mpi_comm;
  const auto nrow_rank  = parameters_.nrowRank();
  const auto num_sketch = parameters_.numSketch();
  const auto dim_sketch = parameters_.dimSketch();

  mcnla_assert_eq(collection_qj.sizes(), std::make_tuple(nrow_rank, dim_sketch, num_sketch));

  auto &matrix_qjs = collection_qj.unfold();  // matrix Qs.

  moments_.emplace_back(MPI_Wtime());  // orthogonalization

  // Wi := Qi' * Qi
  for ( index_t i = 0; i < num_sketch; ++i ) {
    la::mm(collection_qj(i).t(), collection_qj(i), collection_w_(i));
  }

  // Reduce sum Wi
  mpi::allreduce(collection_w_.unfold(), MPI_SUM, mpi_comm);

  // Compute the eigen-decomposition of Wi -> Wi' * Si * Wi
  for ( index_t i = 0; i < num_sketch; ++i ) {
    gesvd_driver_(collection_w_(i), matrix_s_(""_, i), matrix_empty_, matrix_empty_);
  }

  // Qi := Qi * Wi' / sqrt( Si )
  matrix_s_.val().valarray() = std::sqrt(matrix_s_.val().valarray());
  la::copy(matrix_qjs.vectorize(), collection_tmp_.unfold().vectorize());
  for ( index_t i = 0; i < num_sketch; ++i ) {
    la::sm(matrix_s_(""_, i).viewDiagonal().inv(), collection_w_(i));
    la::mm(collection_tmp_(i), collection_w_(i).t(), collection_qj(i));
  }

  moments_.emplace_back(MPI_Wtime());  // end
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_ORTHOGONALIZER_ROW_BLOCK_POLAR_ORTHOGONALIZER_HPP_
