////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/former/polar_former.hpp
/// @brief   The Polar former.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_FORMER_POLAR_FORMER_HPP_
#define MCNLA_ISVD_FORMER_POLAR_FORMER_HPP_

#include <mcnla/isvd/former/polar_former.hh>
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
Former<PolarFormerTag, _Val>::Former(
    const Parameters<ValType> &parameters
) noexcept
  : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::ComponentWrapper::initialize
///
template <typename _Val>
void Former<PolarFormerTag, _Val>::initializeImpl() noexcept {

  const auto nrow       = parameters_.nrow();
  const auto ncol       = parameters_.ncol();
  const auto dim_sketch = parameters_.dimSketch();
  const auto rank       = parameters_.rank();

  matrix_w_.reconstruct(dim_sketch, dim_sketch);
  vector_s_.reconstruct(dim_sketch);
  matrix_qta_.reconstruct(dim_sketch, ncol);
  syev_driver_.reconstruct(dim_sketch);

  matrix_u_cut_.reconstruct(nrow, rank);

  matrix_w_cut_  = matrix_w_("", {dim_sketch-rank, dim_sketch});
  vector_s_cut_  = vector_s_({dim_sketch-rank, dim_sketch});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Forms SVD.
///
/// @param   matrix_a    The matrix A.
/// @param   matrix_q    The matrix Q.
///
template <typename _Val> template <class _Matrix>
void Former<PolarFormerTag, _Val>::runImpl(
    const _Matrix &matrix_a,
    const DenseMatrixRowMajor<ValType> &matrix_q
) noexcept {

  const auto mpi_root   = parameters_.mpi_root;
  const auto mpi_rank   = parameters_.mpi_rank;
  const auto nrow       = parameters_.nrow();
  const auto ncol       = parameters_.ncol();
  const auto dim_sketch = parameters_.dimSketch();

  if ( mpi_rank != mpi_root ) {
    return;
  }

  mcnla_assert_eq(matrix_a.sizes(), std::make_tuple(nrow, ncol));
  mcnla_assert_eq(matrix_q.sizes(), std::make_tuple(nrow, dim_sketch));

  moments_.emplace_back(MPI_Wtime());  // start

  // QtA := Q' * A
  la::mm(matrix_q.t(), matrix_a, matrix_qta_);

  // W := QtA * QtA'
  la::rk(matrix_qta_, matrix_w_.viewSymmetric());

  // Compute the eigen-decomposition of W -> W * S * W'
  syev_driver_(matrix_w_.viewSymmetric(), vector_s_);

  // S := sqrt(S)
  vector_s_.val().valarray() = std::sqrt(vector_s_.val().valarray());

  // U := Q * W
  la::mm(matrix_q, matrix_w_cut_, matrix_u_cut_);

  moments_.emplace_back(MPI_Wtime());  // end
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the singular values.
///
template <typename _Val>
const DenseVector<RealValT<_Val>>& Former<PolarFormerTag, _Val>::vectorS() const noexcept {
  mcnla_assert_true(this->isComputed());
  return vector_s_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the left singular vectors.
///
template <typename _Val>
const DenseMatrixColMajor<_Val>& Former<PolarFormerTag, _Val>::matrixU() const noexcept {
  mcnla_assert_true(this->isComputed());
  return matrix_u_cut_;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_FORMER_POLAR_FORMER_HPP_
