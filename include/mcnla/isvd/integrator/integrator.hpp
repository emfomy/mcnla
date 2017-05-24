////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/integrator.hpp
/// @brief   The iSVD integrator interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_INTEGRATOR_HPP_
#define MCNLA_ISVD_INTEGRATOR_INTEGRATOR_HPP_

#include <mcnla/isvd/def.hpp>
#include <mcnla/isvd/core/stage_wrapper.hpp>
#include <mcnla/core/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of iSVD integrator.
///
/// @tparam  _Tag  The integrator tag.
/// @tparam  _Val  The value type.
///
template <class _Tag, typename _Val>
class Integrator : public StageWrapper<Integrator<_Tag, _Val>, _Val> {
  static_assert(traits::FalseType<_Tag>::value, "Error using non-specialized iSVD integrator!");
};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_INTEGRATOR_HPP_
