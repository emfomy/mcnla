////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/utility/traits.hpp
/// @brief   The traits utilities.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_UTILITY_TRAITS_HPP_
#define ISVD_UTILITY_TRAITS_HPP_

#include <isvd/isvd.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The traits interface.
///
/// @tparam  _Derived  The derived class type.
///
template <typename _Derived> struct Traits;

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
  static const bool is_real = true;
  static const bool is_complex = false;
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
  static const bool is_real = false;
  static const bool is_complex = true;
};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_UTILITY_TRAITS_HPP_