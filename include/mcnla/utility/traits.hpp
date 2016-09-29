////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/utility/traits.hpp
/// @brief   The traits utilities.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_UTILITY_TRAITS_HPP_
#define MCNLA_UTILITY_TRAITS_HPP_

#include <mcnla/mcnla.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace.
//
namespace detail {

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

}  // namespace detail

}  // namespace mcnla

#endif  // MCNLA_UTILITY_TRAITS_HPP_
