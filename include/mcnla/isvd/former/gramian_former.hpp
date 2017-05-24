////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/former/gramian_former.hpp
/// @brief   The Gramian former.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_FORMER_GRAMIAN_FORMER_HPP_
#define MCNLA_ISVD_FORMER_GRAMIAN_FORMER_HPP_

#include <mcnla/isvd/former/gramian_former.hh>
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
GramianFormer<_Val>::Former(
    const Parameters<_Val> &parameters
) noexcept
  : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::StageWrapper::initialize
///
template <typename _Val>
void GramianFormer<_Val>::initializeImpl() noexcept {

  const auto nrow       = parameters_.nrow();
  const auto ncol       = parameters_.ncol();
  const auto dim_sketch = parameters_.dimSketch();
  const auto rank       = parameters_.rank();

  matrix_w_.reconstruct(dim_sketch, dim_sketch);
  vector_s_.reconstruct(dim_sketch);
  matrix_qta_.reconstruct(dim_sketch, ncol);
  syev_driver_.reconstruct(dim_sketch);

  matrix_u_cut_.reconstruct(nrow, rank);

  matrix_w_cut_  = matrix_w_(""_, {dim_sketch-rank, dim_sketch});
  vector_s_cut_  = vector_s_({dim_sketch-rank, dim_sketch});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Forms SVD.
///
/// @param  matrix_a    The matrix A.
/// @param  matrix_q    The matrix Q.
///
template <typename _Val> template <class _Matrix>
void GramianFormer<_Val>::runImpl(
    const _Matrix &matrix_a,
    const DenseMatrixRowMajor<_Val> &matrix_q
) noexcept {

  const auto mpi_root   = parameters_.mpi_root;
  const auto mpi_rank   = parameters_.mpi_rank;
  const auto nrow       = parameters_.nrow();
  const auto ncol       = parameters_.ncol();
  const auto dim_sketch = parameters_.dimSketch();

  static_cast<void>(nrow);
  static_cast<void>(ncol);
  static_cast<void>(dim_sketch);

  if ( mpi_rank != mpi_root ) {
    return;
  }

  mcnla_assert_eq(matrix_a.sizes(), std::make_tuple(nrow, ncol));
  mcnla_assert_eq(matrix_q.sizes(), std::make_tuple(nrow, dim_sketch));

  this->tic(); double comm_time = 0;
  // ====================================================================================================================== //
  // Start

  // QtA := Q' * A
  la::mm(matrix_q.t(), matrix_a, matrix_qta_);

  // W := QtA * QtA'
  la::rk(matrix_qta_, matrix_w_.viewSymmetric());

  // Compute the eigen-decomposition of W -> W * S * W'
  syev_driver_(matrix_w_.viewSymmetric(), vector_s_);

  // S := sqrt(S)
  for ( auto &v : vector_s_ ) {
    v = std::sqrt(v);
  }

  // U := Q * W
  la::mm(matrix_q, matrix_w_cut_, matrix_u_cut_);

  this->toc(comm_time);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the singular values.
///
template <typename _Val>
const DenseVector<RealValT<_Val>>& GramianFormer<_Val>::vectorS() const noexcept {
  mcnla_assert_true(this->isComputed());
  return vector_s_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the left singular vectors.
///
template <typename _Val>
const DenseMatrixColMajor<_Val>& GramianFormer<_Val>::matrixU() const noexcept {
  mcnla_assert_true(this->isComputed());
  return matrix_u_cut_;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_FORMER_GRAMIAN_FORMER_HPP_