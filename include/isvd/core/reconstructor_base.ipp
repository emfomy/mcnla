////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/core/reconstructor_base.ipp
/// @brief   The implementation of iSVD reconstructor interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_CORE_RECONSTRUCTOR_BASE_IPP_
#define ISVD_CORE_RECONSTRUCTOR_BASE_IPP_

#include <isvd/core/reconstructor_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given parameters.
///
template <class _Derived>
ReconstructorBase<_Derived>::ReconstructorBase(
    const internal::Parameters<ScalarType> &parameters
) noexcept : parameters_(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Initializes.
///
template <class _Derived>
void ReconstructorBase<_Derived>::initialize() noexcept { this->derived().initializeImpl(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstructs SVD.
///
template <class _Derived>
void ReconstructorBase<_Derived>::reconstruct(
    const MatrixType &matrix_a,
    const DenseMatrix<ScalarType, Layout::ROWMAJOR> &matrix_q,
          DenseVector<RealScalarType> &vector_s,
          DenseMatrix<ScalarType, Layout::COLMAJOR> &matrix_u,
          DenseMatrix<ScalarType, Layout::COLMAJOR> &matrix_vt
) noexcept { this->derived().reconstructImpl(matrix_a, matrix_q, vector_s, matrix_u, matrix_vt); }

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_CORE_RECONSTRUCTOR_BASE_IPP_
