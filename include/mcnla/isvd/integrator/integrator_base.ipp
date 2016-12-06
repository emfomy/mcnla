////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/integrator_base.ipp
/// @brief   The implementation of iSVD integrator interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_BASE_IPP_
#define MCNLA_ISVD_INTEGRATOR_BASE_IPP_

#include <mcnla/isvd/integrator/integrator_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given parameters.
///
template <class _Derived>
IntegratorBase<_Derived>::IntegratorBase(
    const Parameters<ScalarType> &parameters
) noexcept : parameters_(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Initializes.
///
template <class _Derived>
void IntegratorBase<_Derived>::initialize() noexcept {
  this->derived().initializeImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Integrates.
///
template <class _Derived>
void IntegratorBase<_Derived>::integrate() noexcept {
  this->derived().integrateImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::Solver::getIntegratorName
///
template <class _Derived>
constexpr const char* IntegratorBase<_Derived>::getName() const noexcept {
  return this->derived().getNameImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::Solver::getIntegratorIter
///
template <class _Derived>
index_t IntegratorBase<_Derived>::getIter() const noexcept {
  return this->derived().getIterImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the set Q.
///
template <class _Derived>
DenseMatrixSet120<typename IntegratorBase<_Derived>::ScalarType>& IntegratorBase<_Derived>::getSetQ() noexcept {
  return this->derived().getSetQImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getSetQ
///
template <class _Derived>
const DenseMatrixSet120<typename IntegratorBase<_Derived>::ScalarType>& IntegratorBase<_Derived>::getSetQ() const noexcept {
  return this->derived().getSetQImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the matrix Qc.
///
template <class _Derived>
DenseMatrix<typename IntegratorBase<_Derived>::ScalarType, Layout::ROWMAJOR>&
    IntegratorBase<_Derived>::getMatrixQbar() noexcept {
  return this->derived().getMatrixQbarImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getMatrixQbar
///
template <class _Derived>
const DenseMatrix<typename IntegratorBase<_Derived>::ScalarType, Layout::ROWMAJOR>&
    IntegratorBase<_Derived>::getMatrixQbar() const noexcept {
  return this->derived().getMatrixQbarImpl();
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_BASE_IPP_
