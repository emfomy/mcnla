////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/sketcher_base.ipp
/// @brief   The implementation of iSVD sketcher interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_BASE_IPP_
#define MCNLA_ISVD_SKETCHER_BASE_IPP_

#include <mcnla/isvd/sketcher/sketcher_base.hpp>

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
SketcherBase<_Derived>::SketcherBase(
    const Parameters<ScalarType> &parameters, index_t *seed
) noexcept : parameters_(parameters), seed_(seed) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Initializes.
///
template <class _Derived>
void SketcherBase<_Derived>::initialize() noexcept { this->derived().initializeImpl(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Random sketches.
///
template <class _Derived>
void SketcherBase<_Derived>::sketch(
    const MatrixType &matrix_a,
          DenseMatrixSet120<ScalarType> &set_q
) noexcept { this->derived().sketchImpl(matrix_a, set_q); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::Solver::getSketcherName
///
template <class _Derived>
constexpr const char* SketcherBase<_Derived>::getName() const noexcept {
  return this->derived().getNameImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::Solver::getSketcherTime
///
template <class _Derived>
double SketcherBase<_Derived>::getTime() const noexcept {
  return this->derived().getTimeImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::Solver::getSketcherTimes
///
template <class _Derived>
const std::vector<double> SketcherBase<_Derived>::getTimes() const noexcept {
  return this->derived().getTimesImpl();
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_BASE_IPP_
