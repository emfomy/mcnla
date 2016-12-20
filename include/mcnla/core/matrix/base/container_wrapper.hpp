////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/base/container_wrapper.hpp
/// @brief   The container wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_CONTAINER_WRAPPER_HPP_
#define MCNLA_CORE_MATRIX_CONTAINER_WRAPPER_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_module
/// The container wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class ContainerWrapper {

 private:

  using IteratorType      = typename traits::Traits<_Derived>::IteratorType;
  using ConstIteratorType = typename traits::Traits<_Derived>::ConstIteratorType;

 protected:

  // Constructors
  inline ContainerWrapper() noexcept = default;

 public:

  // Gets iterator
  inline IteratorType      begin() noexcept;
  inline ConstIteratorType begin() const noexcept;
  inline ConstIteratorType cbegin() const noexcept;
  inline IteratorType      end() noexcept;
  inline ConstIteratorType end() const noexcept;
  inline ConstIteratorType cend() const noexcept;

  // Gets derived class
  inline       _Derived& derived() noexcept;
  inline const _Derived& derived() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_CONTAINER_WRAPPER_HPP_
