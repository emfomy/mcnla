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
/// @ingroup  utility_module
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
/// @ingroup  utility_module
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

/// @ingroup  utility_module
template <typename _Derived>
using RealT = typename traits::Traits<_Derived>::RealType;

/// @ingroup  utility_module
template <typename _Derived>
using ComplexT = typename traits::Traits<_Derived>::ComplexType;

/// @ingroup  utility_module
template <class _Derived>
using ScalarT = typename traits::Traits<_Derived>::ScalarType;

/// @ingroup  utility_module
template <class _Derived>
using VectorT = typename traits::Traits<_Derived>::VectorType;

/// @ingroup  utility_module
template <class _Derived>
using MatrixT = typename traits::Traits<_Derived>::MatrixType;

/// @ingroup  utility_module
template <class _Derived>
using SetT = typename traits::Traits<_Derived>::SetType;

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
template <typename _Scalar>
using RealScalarT = typename traits::ScalarTraits<_Scalar>::RealType;

/// @ingroup  utility_module
template <typename _Scalar>
using ComplexScalarT = typename traits::ScalarTraits<_Scalar>::ComplexType;

}  // namespace mcnla

#endif  // MCNLA_CORE_UTILITY_TRAITS_HPP_
