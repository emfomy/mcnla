////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/former/svd_former.hpp
/// @brief   The SVD former.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_FORMER_SVD_FORMER_HPP_
#define MCNLA_ISVD_FORMER_SVD_FORMER_HPP_

#include <mcnla/isvd/former/svd_former.hh>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::FormerWrapper::FormerWrapper
///
template <typename _Val>
Former<SvdFormerTag, _Val>::Former(
    const Parameters &parameters
) noexcept
  : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::FormerWrapper::initialize
///
template <typename _Val>
void Former<SvdFormerTag, _Val>::initializeImpl() noexcept {

  const auto nrow       = parameters_.nrow();
  const auto ncol       = parameters_.ncol();
  const auto dim_sketch = parameters_.dimSketch();
  const auto rank       = parameters_.rank();

  matrix_w_.reconstruct(dim_sketch, dim_sketch);
  vector_s_.reconstruct(dim_sketch);
  matrix_u_.reconstruct(nrow, dim_sketch);
  matrix_vt_.reconstruct(dim_sketch, ncol);
  gesvd_driver_.reconstruct(dim_sketch, ncol);

  vector_s_cut_  = vector_s_({0, rank});
  matrix_u_cut_  = matrix_u_("", {0, rank});
  matrix_vt_cut_ = matrix_vt_({0, rank}, "");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Integrates.
///
/// @param   matrix_a    The matrix A.
/// @param   matrix_q    The matrix Q.
///
template <typename _Val> template <class _Matrix>
void Former<SvdFormerTag, _Val>::runImpl(
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

  moments_.emplace_back(MPI_Wtime());  // Q' * A

  // Vt := Q' * A
  la::gemm(matrix_q.t(), matrix_a, matrix_vt_);

  moments_.emplace_back(MPI_Wtime());  // SVD

  // Compute the SVD of Vt -> W * S * Vt
  gesvd_driver_(matrix_vt_, vector_s_, matrix_w_, matrix_empty_);

  moments_.emplace_back(MPI_Wtime());  // Q * W

  // U := Q * W
  la::gemm(matrix_q, matrix_w_, matrix_u_);  // end

  moments_.emplace_back(MPI_Wtime());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::FormerWrapper::vectorS
///
template <typename _Val>
const DenseVector<RealValT<_Val>>& Former<SvdFormerTag, _Val>::vectorS() const noexcept {
  mcnla_assert_true(this->isComputed());
  return vector_s_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::FormerWrapper::matrixU
///
template <typename _Val>
const DenseMatrixColMajor<_Val>& Former<SvdFormerTag, _Val>::matrixU() const noexcept {
  mcnla_assert_true(this->isComputed());
  return matrix_u_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::FormerWrapper::matrixVt
///
template <typename _Val>
const DenseMatrixColMajor<_Val>& Former<SvdFormerTag, _Val>::matrixVt() const noexcept {
  mcnla_assert_true(this->isComputed());
  return matrix_vt_cut_;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_FORMER_SVD_FORMER_HPP_
