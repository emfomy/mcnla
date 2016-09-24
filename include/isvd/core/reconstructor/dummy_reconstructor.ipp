////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/core/reconstructor/dummy_reconstructor.ipp
/// @brief   The implementation of dummy reconstructor.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_CORE_RECONSTRUCTOR_DUMMY_RECONSTRUCTOR_IPP_
#define ISVD_CORE_RECONSTRUCTOR_DUMMY_RECONSTRUCTOR_IPP_

#include <isvd/core/reconstructor/dummy_reconstructor.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::ReconstructorBase::ReconstructorBase
///
template <class _Matrix>
DummyReconstructor<_Matrix>::DummyReconstructor(
    const Parameters<ScalarType> &parameters
) noexcept : BaseType(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::ReconstructorBase::initialize
///
template <class _Matrix>
void DummyReconstructor<_Matrix>::initializeImpl() noexcept {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::ReconstructorBase::reconstruct
///
template <class _Matrix>
void DummyReconstructor<_Matrix>::reconstructImpl(
    const _Matrix &matrix_a,
    const DenseMatrix<ScalarType, Layout::ROWMAJOR> &matrix_qc
) noexcept { static_cast<void>(matrix_a); static_cast<void>(matrix_qc); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::ReconstructorBase::getName
///
template <class _Matrix>
constexpr const char* DummyReconstructor<_Matrix>::getNameImpl() const noexcept {
  return name_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @fn  DummyReconstructor::getVectorSImpl
/// @copydoc  isvd::ReconstructorBase::getVectorS
///
/// @attention  This routine is not available.
///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @fn  DummyReconstructor::getMatrixUImpl
/// @copydoc  isvd::ReconstructorBase::getMatrixU
///
/// @attention  This routine is not available.
///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @fn  DummyReconstructor::getMatrixVtImpl
/// @copydoc  isvd::ReconstructorBase::getMatrixVt
///
/// @attention  This routine is not available.
///

}  // namespace isvd

#endif  // ISVD_CORE_RECONSTRUCTOR_DUMMY_RECONSTRUCTOR_IPP_
