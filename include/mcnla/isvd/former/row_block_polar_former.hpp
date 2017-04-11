////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/former/row_block_polar_former.hpp
/// @brief   The polar former (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_FORMER_ROW_BLOCK_POLAR_FORMER_HPP_
#define MCNLA_ISVD_FORMER_ROW_BLOCK_POLAR_FORMER_HPP_

#include <mcnla/isvd/former/row_block_polar_former.hh>
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
Former<RowBlockPolarFormerTag, _Val>::Former(
    const Parameters<ValType> &parameters
) noexcept
  : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::ComponentWrapper::initialize
///
template <typename _Val>
void Former<RowBlockPolarFormerTag, _Val>::initializeImpl() noexcept {

  const auto nrow_each  = parameters_.nrowEach();
  const auto ncol       = parameters_.ncol();
  const auto ncol_each  = parameters_.ncolEach();
  const auto ncol_total = parameters_.ncolTotal();
  const auto dim_sketch = parameters_.dimSketch();
  const auto rank       = parameters_.rank();

  matrix_w_.reconstruct(dim_sketch, dim_sketch);
  vector_s_.reconstruct(dim_sketch);
  matrix_qta_.reconstruct(dim_sketch, ncol, ncol_total);
  matrix_qtaj_.reconstruct(dim_sketch, ncol_each);
  syev_driver_.reconstruct(dim_sketch);

  matrix_uj_cut_.reconstruct(nrow_each, rank);

  matrix_w_cut_  = matrix_w_("", {dim_sketch-rank, dim_sketch});
  vector_s_cut_  = vector_s_({dim_sketch-rank, dim_sketch});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Forms SVD.
///
/// @param  matrix_ajj  The matrix Aj (j-th row-block, where j is the MPI rank).
/// @param  matrix_qj  The matrix Qjbar (j-th row-block, where j is the MPI rank).
///
template <typename _Val> template <class _Matrix>
void Former<RowBlockPolarFormerTag, _Val>::runImpl(
    const _Matrix &matrix_aj,
    const DenseMatrixRowMajor<ValType> &matrix_qj
) noexcept {

  const auto mpi_comm   = parameters_.mpi_comm;
  const auto nrow_each  = parameters_.nrow();
  const auto ncol       = parameters_.ncol();
  const auto ncol_total = parameters_.ncolTotal();
  const auto dim_sketch = parameters_.dimSketch();

  mcnla_assert_eq(matrix_aj.sizes(), std::make_tuple(nrow_each, ncol));
  mcnla_assert_eq(matrix_qj.sizes(), std::make_tuple(nrow_each, dim_sketch));

  auto matrix_qta_full = matrix_qta_;
  matrix_qta_full.resize(dim_sketch, ncol_total);

  moments_.emplace_back(MPI_Wtime());  // start

  // QtA := sum( Qj' * Aj )
  la::mm(matrix_qj.t(), matrix_aj, matrix_qta_);
  la::memset0(matrix_qta_full("", {ncol, ncol_total}));
  mpi::reduceScatterBlock(matrix_qta_full, matrix_qtaj_, MPI_SUM, mpi_comm);

  // W := sum( QtAj * QtAj' )
  la::rk(matrix_qtaj_, matrix_w_.viewSymmetric());
  mpi::allreduce(matrix_w_, MPI_SUM, mpi_comm);

  // Compute the eigen-decomposition of W -> W * S * W'
  syev_driver_(matrix_w_.viewSymmetric(), vector_s_);

  // S := sqrt(S)
  vector_s_.val().valarray() = std::sqrt(vector_s_.val().valarray());

  // U := Q * W
  la::mm(matrix_qj, matrix_w_cut_, matrix_uj_cut_);

  moments_.emplace_back(MPI_Wtime());  // end
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the singular values.
///
template <typename _Val>
const DenseVector<RealValT<_Val>>& Former<RowBlockPolarFormerTag, _Val>::vectorS() const noexcept {
  mcnla_assert_true(this->isComputed());
  return vector_s_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the left singular vectors (row-block).
///
template <typename _Val>
const DenseMatrixRowMajor<_Val>& Former<RowBlockPolarFormerTag, _Val>::matrixUj() const noexcept {
  mcnla_assert_true(this->isComputed());
  return matrix_uj_cut_;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_FORMER_ROW_BLOCK_POLAR_FORMER_HPP_
