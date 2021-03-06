////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/former/svd_former.hpp
/// @brief   The SVD former.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_FORMER_SVD_FORMER_HPP_
#define MCNLA_ISVD_FORMER_SVD_FORMER_HPP_

#include <mcnla/isvd/former/svd_former.hh>
#include <mcnla/core/la.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS  Former<SvdFormerTag<_jobv>, _Val>
  #define MCNLA_ALIAS0 Former
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS  SvdFormer<_Val, _jobv>
  #define MCNLA_ALIAS0 SvdFormer
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
template <typename _Val, bool _jobv>
MCNLA_ALIAS::MCNLA_ALIAS0(
    const Parameters<_Val> &parameters
) noexcept
  : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::StageWrapper::initialize
///
template <typename _Val, bool _jobv>
void MCNLA_ALIAS::initializeImpl() noexcept {

  const auto nrow       = parameters_.nrow();
  const auto ncol       = parameters_.ncol();
  const auto dim_sketch = parameters_.dimSketch();
  const auto rank       = parameters_.rank();

  matrix_w_.reconstruct(dim_sketch, dim_sketch);
  vector_s_.reconstruct(dim_sketch);
  matrix_vt_.reconstruct(dim_sketch, ncol);
  gesvd_driver_.reconstruct(dim_sketch, ncol);

  matrix_u_cut_.reconstruct(nrow, rank);

  matrix_w_cut_  = matrix_w_(""_, {0_i, rank});
  vector_s_cut_  = vector_s_({0_i, rank});
  matrix_vt_cut_ = matrix_vt_({0_i, rank}, ""_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Forms SVD.
///
/// @param  matrix_a  The matrix A.
/// @param  matrix_q  The matrix Q.
///
template <typename _Val, bool _jobv> template <class _Matrix>
void MCNLA_ALIAS::runImpl(
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

  double comm_time;
  this->tic(comm_time);
  // ====================================================================================================================== //
  // Projection

  // Vt := Q' * A
  la::mm(matrix_q.t(), matrix_a, matrix_vt_);

  this->toc(comm_time);
  // ====================================================================================================================== //
  // Compute SVD

  // svd(Vt) = W * S * Vt
  gesvd_driver_(matrix_vt_, vector_s_, matrix_w_, matrix_empty_);

  this->toc(comm_time);
  // ====================================================================================================================== //
  // Form singular vectors

  // U := Q * W
  la::mm(matrix_q, matrix_w_cut_, matrix_u_cut_);

  this->toc(comm_time);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the singular values.
///
template <typename _Val, bool _jobv>
const DenseVector<RealValT<_Val>>& MCNLA_ALIAS::vectorS() const noexcept {
  mcnla_assert_true(this->isComputed());
  return vector_s_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the left singular vectors.
///
template <typename _Val, bool _jobv>
const DenseMatrixColMajor<_Val>& MCNLA_ALIAS::matrixU() const noexcept {
  mcnla_assert_true(this->isComputed());
  return matrix_u_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the right singular vectors.
///
template <typename _Val, bool _jobv>
const DenseMatrixRowMajor<_Val>& MCNLA_ALIAS::matrixV() const noexcept {
  mcnla_assert_true(this->isComputed());
  mcnla_assert_true(_jobv);
  return matrix_vt_cut_.t();
}

}  // namespace isvd

}  // namespace mcnla

#undef MCNLA_ALIAS
#undef MCNLA_ALIAS0

#endif  // MCNLA_ISVD_FORMER_SVD_FORMER_HPP_
