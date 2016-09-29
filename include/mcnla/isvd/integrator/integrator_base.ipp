////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/integrator_base.ipp
/// @brief   The implementation of MCNLA integrator interface.
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
void IntegratorBase<_Derived>::initialize() noexcept { this->derived().initializeImpl(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Integrates.
///
template <class _Derived>
void IntegratorBase<_Derived>::integrate() noexcept { this->derived().integrateImpl(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::Solver::getIntegratorName
///
template <class _Derived>
constexpr const char* IntegratorBase<_Derived>::getName() const noexcept {
  return this->derived().getNameImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the cube Q.
///
template <class _Derived>
DenseCube<typename IntegratorBase<_Derived>::ScalarType, Layout::ROWMAJOR>&
    IntegratorBase<_Derived>::getCubeQ() noexcept {
  return this->derived().getCubeQImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getCubeQ
///
template <class _Derived>
const DenseCube<typename IntegratorBase<_Derived>::ScalarType, Layout::ROWMAJOR>&
    IntegratorBase<_Derived>::getCubeQ() const noexcept {
  return this->derived().getCubeQImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the matrix Qc.
///
template <class _Derived>
DenseMatrix<typename IntegratorBase<_Derived>::ScalarType, Layout::ROWMAJOR>&
    IntegratorBase<_Derived>::getMatrixQc() noexcept {
  return this->derived().getMatrixQcImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getMatrixQc
///
template <class _Derived>
const DenseMatrix<typename IntegratorBase<_Derived>::ScalarType, Layout::ROWMAJOR>&
    IntegratorBase<_Derived>::getMatrixQc() const noexcept {
  return this->derived().getMatrixQcImpl();
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_BASE_IPP_
