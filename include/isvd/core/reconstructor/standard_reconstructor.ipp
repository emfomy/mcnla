////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/core/reconstructor/standard_reconstructor.ipp
/// @brief   The implementation of standard reconstructor.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_CORE_RECONSTRUCTOR_STANDARD_RECONSTRUCTOR_IPP_
#define ISVD_CORE_RECONSTRUCTOR_STANDARD_RECONSTRUCTOR_IPP_

#include <isvd/core/reconstructor/standard_reconstructor.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::ReconstructorBase::ReconstructorBase
///
template <class _Matrix>
StandardReconstructor<_Matrix>::StandardReconstructor(
    const Parameters<ScalarType> &parameters
) noexcept : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::ReconstructorBase::initialize
///
template <class _Matrix>
void StandardReconstructor<_Matrix>::initializeImpl() noexcept {

  const auto matrix_w_sizes = std::make_pair(parameters_.getDimSketch(), parameters_.getDimSketch());
  if ( matrix_w_.getSizes() != matrix_w_sizes ) {
    matrix_w_ = DenseMatrix<ScalarType, Layout::COLMAJOR>(matrix_w_sizes);
  }

  const auto vector_s_sizes = parameters_.getDimSketch();
  if ( vector_s_.getSizes() != vector_s_sizes ) {
    vector_s_ = DenseVector<ScalarType>(vector_s_sizes);
  }

  const auto matrix_u_sizes = std::make_pair(parameters_.getNrow(), parameters_.getDimSketch());
  if ( matrix_u_.getSizes() != matrix_u_sizes ) {
    matrix_u_ = DenseMatrix<ScalarType, Layout::COLMAJOR>(matrix_u_sizes);
  }

  const auto matrix_vt_sizes = std::make_pair(parameters_.getDimSketch(), parameters_.getNcol());
  if ( matrix_vt_.getSizes() != matrix_vt_sizes ) {
    matrix_vt_ = DenseMatrix<ScalarType, Layout::COLMAJOR>(matrix_vt_sizes);
  }

  const auto gesvd_sizes = std::make_pair(parameters_.getDimSketch(), parameters_.getNcol());
  if ( gesvd_driver_.getSizes() != gesvd_sizes ) {
    gesvd_driver_.resize(gesvd_sizes);
  }

  vector_s_cut_  = vector_s_.getSegment({0, parameters_.getRank()});
  matrix_u_cut_  = matrix_u_.getCols({0, parameters_.getRank()});
  matrix_vt_cut_ = matrix_vt_.getRows({0, parameters_.getRank()});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::ReconstructorBase::reconstruct
///
template <class _Matrix>
void StandardReconstructor<_Matrix>::reconstructImpl(
    const _Matrix &matrix_a,
    const DenseMatrix<ScalarType, Layout::ROWMAJOR> &matrix_qc
) noexcept {
  if ( !mpi::isCommRoot(parameters_.mpi_root, parameters_.mpi_comm) ) {
    return;
  }

  assert(parameters_.isInitialized());
  assert(matrix_a.getSizes()  == std::make_pair(parameters_.getNrow(), parameters_.getNcol()));
  assert(matrix_qc.getSizes() == std::make_pair(parameters_.getNrow(), parameters_.getDimSketch()));

  // Vt := Q' * A
  blas::gemm<TransOption::TRANS, TransOption::NORMAL>(1.0, matrix_qc, matrix_a, 0.0, matrix_vt_);

  // Compute the SVD of Vt -> W * S * Vt
  gesvd_driver_(matrix_vt_, vector_s_, matrix_w_, matrix_empty_);

  // U := Q * W
  blas::gemm<TransOption::NORMAL, TransOption::NORMAL>(1.0, matrix_qc, matrix_w_, 0.0, matrix_u_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::ReconstructorBase::getName
///
template <class _Matrix>
constexpr const char* StandardReconstructor<_Matrix>::getNameImpl() const noexcept {
  return name_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::ReconstructorBase::getVectorS
///
template <class _Matrix>
const DenseVector<typename StandardReconstructor<_Matrix>::RealScalarType>&
    StandardReconstructor<_Matrix>::getVectorSImpl() const noexcept {
  assert(parameters_.isComputed());
  return vector_s_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::ReconstructorBase::getMatrixU
///
template <class _Matrix>
const DenseMatrix<typename StandardReconstructor<_Matrix>::ScalarType, Layout::COLMAJOR>&
    StandardReconstructor<_Matrix>::getMatrixUImpl() const noexcept {
  assert(parameters_.isComputed());
  return matrix_u_cut_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::ReconstructorBase::getMatrixVt
///
template <class _Matrix>
const DenseMatrix<typename StandardReconstructor<_Matrix>::ScalarType, Layout::COLMAJOR>&
    StandardReconstructor<_Matrix>::getMatrixVtImpl() const noexcept {
  assert(parameters_.isComputed());
  return matrix_vt_cut_;
}

}  // namespace isvd

#endif  // ISVD_CORE_RECONSTRUCTOR_STANDARD_RECONSTRUCTOR_IPP_
