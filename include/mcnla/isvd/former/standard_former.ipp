////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/former/standard_former.ipp
/// @brief   The implementation of standard former.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_FORMER_STANDARD_FORMER_IPP_
#define MCNLA_ISVD_FORMER_STANDARD_FORMER_IPP_

#include <mcnla/isvd/former/standard_former.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::FormerBase::FormerBase
///
template <class _Matrix>
StandardFormer<_Matrix>::StandardFormer(
    const Parameters<ScalarType> &parameters
) noexcept : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::FormerBase::initialize
///
template <class _Matrix>
void StandardFormer<_Matrix>::initializeImpl() noexcept {

  const auto nrow            = parameters_.nrow();
  const auto ncol            = parameters_.ncol();
  const auto dim_sketch      = parameters_.dimSketch();

  time0_ = 0;
  time1_ = 0;
  time2_ = 0;
  time3_ = 0;

  const auto matrix_w_sizes = std::make_pair(dim_sketch, dim_sketch);
  if ( matrix_w_.sizes() != matrix_w_sizes ) {
    matrix_w_ = DenseMatrix<ScalarType, Layout::COLMAJOR>(matrix_w_sizes);
  }

  const auto vector_s_sizes = dim_sketch;
  if ( vector_s_.sizes() != vector_s_sizes ) {
    vector_s_ = DenseVector<ScalarType>(vector_s_sizes);
  }

  const auto matrix_u_sizes = std::make_pair(nrow, dim_sketch);
  if ( matrix_u_.sizes() != matrix_u_sizes ) {
    matrix_u_ = DenseMatrix<ScalarType, Layout::COLMAJOR>(matrix_u_sizes);
  }

  const auto matrix_vt_sizes = std::make_pair(dim_sketch, ncol);
  if ( matrix_vt_.sizes() != matrix_vt_sizes ) {
    matrix_vt_ = DenseMatrix<ScalarType, Layout::COLMAJOR>(matrix_vt_sizes);
  }

  const auto gesvd_sizes = std::make_pair(dim_sketch, ncol);
  if ( gesvd_driver_.sizes() != gesvd_sizes ) {
    gesvd_driver_.resize(gesvd_sizes);
  }

  vector_s_cut_  = vector_s_.getSegment({0, parameters_.getRank()});
  matrix_u_cut_  = matrix_u_.getCols({0, parameters_.getRank()});
  matrix_vt_cut_ = matrix_vt_.getRows({0, parameters_.getRank()});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::FormerBase::form
///
template <class _Matrix>
void StandardFormer<_Matrix>::formImpl(
    const _Matrix &matrix_a,
    const DenseMatrix<ScalarType, Layout::ROWMAJOR> &matrix_qc
) noexcept {
  if ( !mpi::isCommRoot(parameters_.mpi_root, parameters_.mpi_comm) ) {
    return;
  }

  mcnla_assert_true(parameters_.isInitialized());

  const auto nrow            = parameters_.nrow();
  const auto ncol            = parameters_.ncol();
  const auto dim_sketch      = parameters_.dimSketch();

  mcnla_assert_eq(matrix_a.sizes(),  std::make_pair(nrow, ncol));
  mcnla_assert_eq(matrix_qc.sizes(), std::make_pair(nrow, dim_sketch));

  time0_ = MPI_Wtime();

  // Vt := Q' * A
  blas::gemm<Trans::TRANS, Trans::NORMAL>(1.0, matrix_qc, matrix_a, 0.0, matrix_vt_);
  time1_ = MPI_Wtime();

  // Compute the SVD of Vt -> W * S * Vt
  gesvd_driver_(matrix_vt_, vector_s_, matrix_w_, matrix_empty_);
  time2_ = MPI_Wtime();

  // U := Q * W
  blas::gemm<Trans::NORMAL, Trans::NORMAL>(1.0, matrix_qc, matrix_w_, 0.0, matrix_u_);
  time3_ = MPI_Wtime();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::FormerBase::nvecame
///
template <class _Matrix>
constexpr const char* StandardFormer<_Matrix>::nvecameImpl() const noexcept {
  return name_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::FormerBase::getTime
///
template <class _Matrix>
double StandardFormer<_Matrix>::getTimeImpl() const noexcept {
  return time3_-time0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::FormerBase::getTimes
///
template <class _Matrix>
const std::vector<double> StandardFormer<_Matrix>::getTimesImpl() const noexcept {
  return {time1_-time0_, time2_-time1_, time3_-time2_};
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::FormerBase::getVectorS
///
template <class _Matrix>
const DenseVector<typename StandardFormer<_Matrix>::RealScalarType>&
    StandardFormer<_Matrix>::getVectorSImpl() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return vector_s_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::FormerBase::getMatrixU
///
template <class _Matrix>
const DenseMatrix<typename StandardFormer<_Matrix>::ScalarType, Layout::COLMAJOR>&
    StandardFormer<_Matrix>::getMatrixUImpl() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return matrix_u_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::FormerBase::getMatrixVt
///
template <class _Matrix>
const DenseMatrix<typename StandardFormer<_Matrix>::ScalarType, Layout::COLMAJOR>&
    StandardFormer<_Matrix>::getMatrixVtImpl() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return matrix_vt_cut_;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_FORMER_STANDARD_FORMER_IPP_
