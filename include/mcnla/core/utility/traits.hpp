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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The traits interface.
///
/// @tparam  _Derived  The derived type.
///
template <typename _Derived>
  struct Traits {
  static_assert(std::integral_constant<_Derived, false>::value, "Error using non-specialized traits!");
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_module
/// The scalar type traits.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
struct ValTraits {
  static_assert(std::is_arithmetic<_Val>::value, "'_Val' must be a arithmetic type!");
  using RealType = _Val;
  using ComplexType = std::complex<_Val>;
  static constexpr bool is_real = true;
  static constexpr bool is_complex = false;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_module
/// @copydoc ValTraits
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
struct ValTraits<std::complex<_Val>> {
  static_assert(std::is_arithmetic<_Val>::value, "'_Val' must be a arithmetic type!");
  using RealType = _Val;
  using ComplexType = std::complex<_Val>;
  static constexpr bool is_real = false;
  static constexpr bool is_complex = true;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The true type.
///
template <class _Type>
struct True {
  static constexpr bool value = true;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The false type.
///
template <class _Type>
struct False {
  static constexpr bool value = false;
};

}  // namespace traits

/// @ingroup  utility_module
template <typename _Derived>
using RealT = typename traits::Traits<_Derived>::RealType;

/// @ingroup  utility_module
template <typename _Derived>
using ComplexT = typename traits::Traits<_Derived>::ComplexType;

/// @ingroup  utility_module
template <class _Derived>
using ValT = typename traits::Traits<_Derived>::ValType;

/// @ingroup  utility_module
template <class _Derived>
using IdxT = typename traits::Traits<_Derived>::IdxType;

/// @ingroup  utility_module
template <class _Derived>
using TupleT = typename traits::Traits<_Derived>::TupleType;

/// @ingroup  utility_module
template <class _Derived>
using VectorT = typename traits::Traits<_Derived>::VectorType;

/// @ingroup  utility_module
template <class _Derived>
using MatrixT = typename traits::Traits<_Derived>::MatrixType;

/// @ingroup  utility_module
template <class _Derived>
using CollectionT = typename traits::Traits<_Derived>::CollectionType;

/// @ingroup  utility_module
template <class _Derived>
using ContainerT = typename traits::Traits<_Derived>::ContainerType;

/// @ingroup  utility_module
template <class _Derived>
using IteratorT = typename traits::Traits<_Derived>::IteratorType;

/// @ingroup  utility_module
template <class _Derived>
using ConstIteratorT = typename traits::Traits<_Derived>::ConstIteratorType;

/// @ingroup  utility_module
template <typename _Val>
using RealValT = typename traits::ValTraits<_Val>::RealType;

/// @ingroup  utility_module
template <typename _Val>
using ComplexValT = typename traits::ValTraits<_Val>::ComplexType;

}  // namespace mcnla

#endif  // MCNLA_CORE_UTILITY_TRAITS_HPP_
