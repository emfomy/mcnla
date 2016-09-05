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
    const DenseMatrix<ScalarType, Layout::ROWMAJOR> &matrix_qc
) noexcept { this->derived().reconstructImpl(matrix_a, matrix_qc); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::Solver::getReconstructorName
///
template <class _Derived>
const char* ReconstructorBase<_Derived>::getName() const noexcept {
  return this->derived().getNameImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::Solver::getSingularValues
///
template <class _Derived>
const DenseVector<typename ReconstructorBase<_Derived>::RealScalarType>&
    ReconstructorBase<_Derived>::getSingularValues() const noexcept {
  return this->derived().getSingularValuesImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::Solver::getLeftSingularVectors
///
template <class _Derived>
const DenseMatrix<typename ReconstructorBase<_Derived>::ScalarType, Layout::COLMAJOR>&
    ReconstructorBase<_Derived>::getLeftSingularVectors() const noexcept {
  return this->derived().getLeftSingularVectorsImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::Solver::getRightSingularVectors
///
template <class _Derived>
const DenseMatrix<typename ReconstructorBase<_Derived>::ScalarType, Layout::COLMAJOR>&
    ReconstructorBase<_Derived>::getRightSingularVectors() const noexcept {
  return this->derived().getRightSingularVectorsImpl();
}

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_CORE_RECONSTRUCTOR_BASE_IPP_
