////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/orthogonalizer/orthogonalizer.hpp
/// @brief   The iSVD orthogonalizer interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_ORTHOGONALIZER_ORTHOGONALIZER_HPP_
#define MCNLA_ISVD_ORTHOGONALIZER_ORTHOGONALIZER_HPP_

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

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Tag, typename _Val> class Orthogonalizer;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace isvd

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

template <class _Tag, typename _Val>
MCNLA_TRAITS_DEF(VAL, isvd::Orthogonalizer<_Tag MCNLA_COMMA _Val>, _Val)

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of iSVD orthogonalizer.
///
/// @tparam  _Tag  The orthogonalizer tag.
/// @tparam  _Val  The value type.
///
template <class _Tag, typename _Val>
class Orthogonalizer : public StageWrapper<Orthogonalizer<_Tag, _Val>> {
  static_assert(traits::FalseType<_Tag>::value, "Error using non-specialized iSVD orthogonalizer!");
};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_ORTHOGONALIZER_ORTHOGONALIZER_HPP_
