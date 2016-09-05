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
/// @copydoc  isvd::internal::ReconstructorBase::ReconstructorBase
///
template <class _Matrix>
StandardReconstructor<_Matrix>::StandardReconstructor(
    const internal::Parameters<ScalarType> &parameters
) noexcept : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::ReconstructorBase::initialize
///
template <class _Matrix>
void StandardReconstructor<_Matrix>::initializeImpl() noexcept {

  const auto matrix_w_sizes = std::make_pair(parameters_.getDimSketch(), parameters_.getDimSketch());
  if ( matrix_w_.getSizes() != matrix_w_sizes ) {
    matrix_w_ = DenseMatrix<ScalarType, Layout::COLMAJOR>(matrix_w_sizes);
  }

  const auto vector_sl_sizes = parameters_.getDimSketch();
  if ( vector_sl_.getSizes() != vector_sl_sizes ) {
    vector_sl_ = DenseVector<ScalarType>(vector_sl_sizes);
  }

  const auto matrix_ul_sizes = std::make_pair(parameters_.getNrow(), parameters_.getDimSketch());
  if ( matrix_ul_.getSizes() != matrix_ul_sizes ) {
    matrix_ul_ = DenseMatrix<ScalarType, Layout::COLMAJOR>(matrix_ul_sizes);
  }

  const auto matrix_vlt_sizes = std::make_pair(parameters_.getDimSketch(), parameters_.getNcol());
  if ( matrix_vlt_.getSizes() != matrix_vlt_sizes ) {
    matrix_vlt_ = DenseMatrix<ScalarType, Layout::COLMAJOR>(matrix_vlt_sizes);
  }

  const auto gesvd_sizes = std::make_pair(parameters_.getDimSketch(), parameters_.getNcol());
  if ( gesvd_driver_.getSizes() != gesvd_sizes ) {
    gesvd_driver_.resize(gesvd_sizes);
  }

  vector_s_  = vector_real_empty_;
  matrix_u_  = matrix_empty_;
  matrix_vt_ = matrix_empty_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::ReconstructorBase::reconstruct
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
  blas::gemm<TransOption::TRANS, TransOption::NORMAL>(1.0, matrix_qc, matrix_a, 0.0, matrix_vlt_);

  // Compute the SVD of Vt -> W * S * Vt
  gesvd_driver_(matrix_vlt_, vector_sl_, matrix_w_, matrix_empty_);

  // U := Q * W
  blas::gemm<TransOption::NORMAL, TransOption::NORMAL>(1.0, matrix_qc, matrix_w_, 0.0, matrix_ul_);

  // Cut the matrices
  vector_s_  = vector_sl_.getSegment({0, parameters_.getRank()});
  matrix_u_  = matrix_ul_.getCols({0, parameters_.getRank()});
  matrix_vt_ = matrix_vlt_.getRows({0, parameters_.getRank()});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::ReconstructorBase::getName
///
template <class _Matrix>
const char* StandardReconstructor<_Matrix>::getNameImpl() const noexcept {
  return name_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::ReconstructorBase::getSingularValues
///
template <class _Matrix>
const DenseVector<typename StandardReconstructor<_Matrix>::RealScalarType>&
    StandardReconstructor<_Matrix>::getSingularValuesImpl() const noexcept {
  assert(parameters_.isComputed());
  return vector_s_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::ReconstructorBase::getLeftSingularVectors
///
template <class _Matrix>
const DenseMatrix<typename StandardReconstructor<_Matrix>::ScalarType, Layout::COLMAJOR>&
    StandardReconstructor<_Matrix>::getLeftSingularVectorsImpl() const noexcept {
  assert(parameters_.isComputed());
  return matrix_u_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::ReconstructorBase::getRightSingularVectors
///
template <class _Matrix>
const DenseMatrix<typename StandardReconstructor<_Matrix>::ScalarType, Layout::COLMAJOR>&
    StandardReconstructor<_Matrix>::getRightSingularVectorsImpl() const noexcept {
  return matrix_vt_;
}

}  // namespace isvd

#endif  // ISVD_CORE_RECONSTRUCTOR_STANDARD_RECONSTRUCTOR_IPP_
