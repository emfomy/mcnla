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

  const auto gesvd_sizes = std::make_pair(parameters_.getDimSketch(), parameters_.getNcol());
  if ( gesvd_driver_.getSizes() != gesvd_sizes ) {
    gesvd_driver_.resize(gesvd_sizes);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::internal::ReconstructorBase::reconstruct
///
template <class _Matrix>
void StandardReconstructor<_Matrix>::reconstructImpl(
    const _Matrix &matrix_a,
    const DenseMatrix<ScalarType, Layout::ROWMAJOR> &matrix_q,
          DenseVector<RealScalarType> &vector_s,
          DenseMatrix<ScalarType, Layout::COLMAJOR> &matrix_u,
          DenseMatrix<ScalarType, Layout::COLMAJOR> &matrix_vt
) noexcept {
  assert(parameters_.isInitialized());
  assert(matrix_a.getSizes()  == std::make_pair(parameters_.getNrow(), parameters_.getNcol()));
  assert(matrix_q.getSizes()  == std::make_pair(parameters_.getNrow(), parameters_.getDimSketch()));
  assert(vector_s.getSizes()  == parameters_.getDimSketch());
  assert(matrix_u.getSizes()  == std::make_pair(parameters_.getNrow(), parameters_.getDimSketch()));
  assert(matrix_vt.getSizes() == std::make_pair(parameters_.getDimSketch(), parameters_.getNcol()));

  // Vt := Q' * A
  blas::gemm<TransOption::TRANS, TransOption::NORMAL>(1.0, matrix_q, matrix_a, 0.0, matrix_vt);

  // Compute the SVD of Vt (W := left singular vectors, Vt := right singular vectors, S := singular values)
  gesvd_driver_(matrix_vt, vector_s, matrix_w_, matrix_empty_);

  // U := Q * W
  blas::gemm<TransOption::NORMAL, TransOption::NORMAL>(1.0, matrix_q, matrix_w_, 0.0, matrix_u);
}

}  // namespace isvd

#endif  // ISVD_CORE_RECONSTRUCTOR_STANDARD_RECONSTRUCTOR_IPP_
