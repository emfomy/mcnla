////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/integrator.hpp
/// @brief   The iSVD integrator interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_INTEGRATOR_HPP_
#define MCNLA_ISVD_INTEGRATOR_INTEGRATOR_HPP_

#include <mcnla/isvd/def.hpp>
#include <mcnla/isvd/integrator/integrator_wrapper.hpp>
#include <mcnla/core/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, class _Tag> class Integrator;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace isvd

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The integrator traits.
///
template <typename _Scalar, class _Tag>
struct Traits<isvd::Integrator<_Scalar, _Tag>> {
  using ScalarType = _Scalar;
};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_integrator_module
///
/// The interface of iSVD integrator.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Tag     The integrator tag.
///
template <typename _Scalar, class _Tag>
class Integrator : public IntegratorWrapper<Integrator<_Scalar, _Tag>> {};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_INTEGRATOR_HPP_