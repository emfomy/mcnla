////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/core/sketcher/gaussian_projection_sketcher.ipp
/// @brief   The implementation of Gaussian projection sketcher.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_CORE_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_IPP_
#define ISVD_CORE_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_IPP_

#include <isvd/core/sketcher/gaussian_projection_sketcher.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given parameters.
///
template <class _Matrix>
GaussianProjectionSketcher<_Matrix>::GaussianProjectionSketcher(
    const internal::Parameters<RealScalarType> &parameters
) noexcept : parameters_(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Initializes.
///
template <class _Matrix>
void GaussianProjectionSketcher<_Matrix>::initializeImpl() noexcept {
  #pragma warning "todo"
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Random sketches.
///
template <class _Matrix>
void GaussianProjectionSketcher<_Matrix>::sketchImpl(
    const _Matrix &matrix_a,
          DenseCubeType &cube_qj
) noexcept {
  #pragma warning "todo"
}

}  // namespace isvd

#endif  // ISVD_CORE_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_IPP_
