////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/utility/crtp.hpp
/// @brief   The curiously recurring template pattern utilities.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_UTILITY_CRTP_HPP_
#define ISVD_UTILITY_CRTP_HPP_

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
/// The CRTP interface.
///
/// @tparam  _Derived  The derived class type.
/// @tparam  _Base     The interface class type.
///
template <class _Derived, class _Base = void>
class CrtpBase {

  friend _Derived;
  friend _Base;

 private:

  CrtpBase() {};

 public:

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief  Gets the derived class.
  ///
  inline _Derived& derived() noexcept { return static_cast<_Derived&>(*this); };

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief  Gets the constant derived class.
  ///
  inline const _Derived& derived() const noexcept { return static_cast<const _Derived&>(*this); };

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_UTILITY_CRTP_HPP_
