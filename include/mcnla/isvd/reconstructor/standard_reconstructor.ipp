////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/reconstructor/standard_reconstructor.ipp
/// @brief   The implementation of standard reconstructor.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_RECONSTRUCTOR_STANDARD_RECONSTRUCTOR_IPP_
#define MCNLA_ISVD_RECONSTRUCTOR_STANDARD_RECONSTRUCTOR_IPP_

#include <mcnla/isvd/reconstructor/standard_reconstructor.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::ReconstructorBase::ReconstructorBase
///
template <class _Matrix>
StandardReconstructor<_Matrix>::StandardReconstructor(
    const Parameters<ScalarType> &parameters
) noexcept : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::ReconstructorBase::initialize
///
template <class _Matrix>
void StandardReconstructor<_Matrix>::initializeImpl() noexcept {

  const auto nrow            = parameters_.getNrow();
  const auto ncol            = parameters_.getNcol();
  const auto dim_sketch      = parameters_.getDimSketch();

  time0_ = 0;
  time1_ = 0;
  time2_ = 0;
  time3_ = 0;

  const auto matrix_w_sizes = std::make_pair(dim_sketch, dim_sketch);
  if ( matrix_w_.getSizes() != matrix_w_sizes ) {
    matrix_w_ = DenseMatrix<ScalarType, Layout::COLMAJOR>(matrix_w_sizes);
  }

  const auto vector_s_sizes = dim_sketch;
  if ( vector_s_.getSizes() != vector_s_sizes ) {
    vector_s_ = DenseVector<ScalarType>(vector_s_sizes);
  }

  const auto matrix_u_sizes = std::make_pair(nrow, dim_sketch);
  if ( matrix_u_.getSizes() != matrix_u_sizes ) {
    matrix_u_ = DenseMatrix<ScalarType, Layout::COLMAJOR>(matrix_u_sizes);
  }

  const auto matrix_vt_sizes = std::make_pair(dim_sketch, ncol);
  if ( matrix_vt_.getSizes() != matrix_vt_sizes ) {
    matrix_vt_ = DenseMatrix<ScalarType, Layout::COLMAJOR>(matrix_vt_sizes);
  }

  const auto gesvd_sizes = std::make_pair(dim_sketch, ncol);
  if ( gesvd_driver_.getSizes() != gesvd_sizes ) {
    gesvd_driver_.resize(gesvd_sizes);
  }

  vector_s_cut_  = vector_s_.getSegment({0, parameters_.getRank()});
  matrix_u_cut_  = matrix_u_.getCols({0, parameters_.getRank()});
  matrix_vt_cut_ = matrix_vt_.getRows({0, parameters_.getRank()});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::ReconstructorBase::reconstruct
///
template <class _Matrix>
void StandardReconstructor<_Matrix>::reconstructImpl(
    const _Matrix &matrix_a,
    const DenseMatrix<ScalarType, Layout::ROWMAJOR> &matrix_qc
) noexcept {
  if ( !mpi::isCommRoot(parameters_.mpi_root, parameters_.mpi_comm) ) {
    return;
  }

  mcnla_assert_true(parameters_.isInitialized());

  const auto nrow            = parameters_.getNrow();
  const auto ncol            = parameters_.getNcol();
  const auto dim_sketch      = parameters_.getDimSketch();

  mcnla_assert_eq(matrix_a.getSizes(),  std::make_pair(nrow, ncol));
  mcnla_assert_eq(matrix_qc.getSizes(), std::make_pair(nrow, dim_sketch));

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
/// @copydoc  mcnla::isvd::ReconstructorBase::getName
///
template <class _Matrix>
constexpr const char* StandardReconstructor<_Matrix>::getNameImpl() const noexcept {
  return name_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::ReconstructorBase::getTime
///
template <class _Matrix>
double StandardReconstructor<_Matrix>::getTimeImpl() const noexcept {
  return time3_-time0_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::ReconstructorBase::getTimes
///
template <class _Matrix>
const std::vector<double> StandardReconstructor<_Matrix>::getTimesImpl() const noexcept {
  return {time1_-time0_, time2_-time1_, time3_-time2_};
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::ReconstructorBase::getVectorS
///
template <class _Matrix>
const DenseVector<typename StandardReconstructor<_Matrix>::RealScalarType>&
    StandardReconstructor<_Matrix>::getVectorSImpl() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return vector_s_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::ReconstructorBase::getMatrixU
///
template <class _Matrix>
const DenseMatrix<typename StandardReconstructor<_Matrix>::ScalarType, Layout::COLMAJOR>&
    StandardReconstructor<_Matrix>::getMatrixUImpl() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return matrix_u_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::ReconstructorBase::getMatrixVt
///
template <class _Matrix>
const DenseMatrix<typename StandardReconstructor<_Matrix>::ScalarType, Layout::COLMAJOR>&
    StandardReconstructor<_Matrix>::getMatrixVtImpl() const noexcept {
  mcnla_assert_true(parameters_.isComputed());
  return matrix_vt_cut_;
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_RECONSTRUCTOR_STANDARD_RECONSTRUCTOR_IPP_
