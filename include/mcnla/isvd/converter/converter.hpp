////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/converter/converter.hpp
/// @brief   The iSVD converter interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CONVERTER_CONVERTER_HPP_
#define MCNLA_ISVD_CONVERTER_CONVERTER_HPP_

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
/// The interface of iSVD converter.
///
/// @tparam  _Tag  The converter tag.
/// @tparam  _Val  The value type.
///
template <class _Tag, typename _Val>
class Converter : public StageWrapper<Converter<_Tag, _Val>, _Val> {
  static_assert(traits::FalseType<_Tag>::value, "Error using non-specialized iSVD converter!");
};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CONVERTER_CONVERTER_HPP_
