////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/utility/traits.hpp
/// @brief   The traits utilities.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_UTILITY_TRAITS_HPP_
#define MCNLA_CORE_UTILITY_TRAITS_HPP_

#include <mcnla/core/utility/def.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The traits namespace.
///
namespace traits {

/// @ingroup  utility_module
template <typename ..._Args>
using TrueType = std::true_type;

/// @ingroup  utility_module
template <typename ..._Args>
using FalseType = std::false_type;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
struct RealTraitsTag {};
struct ComplexTraitsTag {};
struct ValTraitsTag {};
struct VectorTraitsTag {};
struct MatrixTraitsTag {};
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_module
/// The traits interface.
///
/// @tparam  _Type  The type.
///
template <typename _Type, class _tag = void>
struct Traits;

#define MCNLA_TRAITS_DEF( _tag, _Type, _value ) \
  struct Traits<_Type, _tag ## TraitsTag> { using Type = _value; };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_module
/// The value type traits.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
struct ValTraits {
  static_assert(std::is_arithmetic<_Val>::value, "'_Val' must be a arithmetic type!");
  using RealType = _Val;
  using ComplexType = std::complex<_Val>;
  static constexpr bool is_real    = true;
  static constexpr bool is_complex = false;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_module
/// @copydoc  ValTraits
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
struct ValTraits<std::complex<_Val>> {
  static_assert(std::is_arithmetic<_Val>::value, "'_Val' must be a arithmetic type!");
  using RealType = _Val;
  using ComplexType = std::complex<_Val>;
  static constexpr bool is_real    = false;
  static constexpr bool is_complex = true;
};

}  // namespace traits

/// @ingroup  utility_module
template <typename _Derived>
using RealT = typename traits::Traits<_Derived, traits::RealTraitsTag>::Type;

/// @ingroup  utility_module
template <typename _Derived>
using ComplexT = typename traits::Traits<_Derived, traits::ComplexTraitsTag>::Type;

/// @ingroup  utility_module
template <class _Derived>
using ValT = typename traits::Traits<_Derived, traits::ValTraitsTag>::Type;

/// @ingroup  utility_module
template <class _Derived>
using VectorT = typename traits::Traits<_Derived, traits::VectorTraitsTag>::Type;

/// @ingroup  utility_module
template <class _Derived>
using MatrixT = typename traits::Traits<_Derived, traits::MatrixTraitsTag>::Type;

/// @ingroup  utility_module
template <typename _Val>
using RealValT = typename traits::ValTraits<_Val>::RealType;

/// @ingroup  utility_module
template <typename _Val>
using ComplexValT = typename traits::ValTraits<_Val>::ComplexType;

}  // namespace mcnla

#endif  // MCNLA_CORE_UTILITY_TRAITS_HPP_
