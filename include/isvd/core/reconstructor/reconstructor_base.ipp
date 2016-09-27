////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/core/reconstructor/reconstructor_base.ipp
/// @brief   The implementation of iSVD reconstructor interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef ISVD_CORE_RECONSTRUCTOR_BASE_IPP_
#define ISVD_CORE_RECONSTRUCTOR_BASE_IPP_

#include <isvd/core/reconstructor/reconstructor_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given parameters.
///
template <class _Derived>
ReconstructorBase<_Derived>::ReconstructorBase(
    const Parameters<ScalarType> &parameters
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
constexpr const char* ReconstructorBase<_Derived>::getName() const noexcept {
  return this->derived().getNameImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the vector S.
///
template <class _Derived>
const DenseVector<typename ReconstructorBase<_Derived>::RealScalarType>&
    ReconstructorBase<_Derived>::getVectorS() const noexcept {
  return this->derived().getVectorSImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the matrix U.
///
template <class _Derived>
const DenseMatrix<typename ReconstructorBase<_Derived>::ScalarType, Layout::COLMAJOR>&
    ReconstructorBase<_Derived>::getMatrixU() const noexcept {
  return this->derived().getMatrixUImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the transpose of the matrix V.
///
template <class _Derived>
const DenseMatrix<typename ReconstructorBase<_Derived>::ScalarType, Layout::COLMAJOR>&
    ReconstructorBase<_Derived>::getMatrixVt() const noexcept {
  return this->derived().getMatrixVtImpl();
}

}  // namespace isvd

#endif  // ISVD_CORE_RECONSTRUCTOR_BASE_IPP_
