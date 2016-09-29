////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/utility/traits.hpp
/// @brief   The traits utilities.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_UTILITY_TRAITS_HPP_
#define MCNLA_CORE_UTILITY_TRAITS_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>

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
template <typename _Derived> struct Traits {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The scalar type traits.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
struct ScalarTraits {
  static_assert(std::is_floating_point<_Scalar>::value, "'_Scalar' must be a floating point type!");
  using RealType = _Scalar;
  using ComplexType = std::complex<_Scalar>;
  static constexpr bool is_real = true;
  static constexpr bool is_complex = false;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc ScalarTraits
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
struct ScalarTraits<std::complex<_Scalar>> {
  static_assert(std::is_floating_point<_Scalar>::value, "'_Scalar' must be a floating point type!");
  using RealType = _Scalar;
  using ComplexType = std::complex<_Scalar>;
  static constexpr bool is_real = false;
  static constexpr bool is_complex = true;
};

}  // namespace traits

}  // namespace mcnla

#endif  // MCNLA_CORE_UTILITY_TRAITS_HPP_
