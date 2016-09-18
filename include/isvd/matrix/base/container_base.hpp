////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/base/container_base.hpp
/// @brief   The container interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_CONTAINER_BASE_HPP_
#define ISVD_MATRIX_CONTAINER_BASE_HPP_

#include <isvd/isvd.hpp>
#include <isvd/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of container.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class ContainerBase {

 private:

  using IteratorType      = typename Traits<_Derived>::IteratorType;
  using ConstIteratorType = typename Traits<_Derived>::ConstIteratorType;

 protected:

  // Constructors
  inline ContainerBase() noexcept {};

 public:

  // Gets iterator
  inline IteratorType      begin() noexcept;
  inline ConstIteratorType begin() const noexcept;
  inline ConstIteratorType cbegin() const noexcept;
  inline IteratorType      end() noexcept;
  inline ConstIteratorType end() const noexcept;
  inline ConstIteratorType cend() const noexcept;

 protected:

  // Gets derived class
  inline       _Derived& derived() noexcept;
  inline const _Derived& derived() const noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_CONTAINER_BASE_HPP_
