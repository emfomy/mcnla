////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/matrix/base/container_base.hpp
/// @brief   The container interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_MATRIX_CONTAINER_BASE_HPP_
#define MCNLA_MATRIX_CONTAINER_BASE_HPP_

#include <mcnla/mcnla.hpp>
#include <mcnla/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of container.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class ContainerBase {

 private:

  using IteratorType      = typename detail::Traits<_Derived>::IteratorType;
  using ConstIteratorType = typename detail::Traits<_Derived>::ConstIteratorType;

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

}  // namespace mcnla

#endif  // MCNLA_MATRIX_CONTAINER_BASE_HPP_
