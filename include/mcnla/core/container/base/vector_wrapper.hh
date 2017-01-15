////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/container/base/vector_wrapper.hh
/// @brief   The definition of vector wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_CONTAINER_BASE_VECTOR_WRAPPER_HH_
#define MCNLA_CORE_CONTAINER_BASE_VECTOR_WRAPPER_HH_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <iostream>
#include <tuple>
#include <mcnla/core/utility/crtp.hpp>
#include <mcnla/core/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The container namespace.
//
namespace container {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  container_module
/// The vector wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class VectorWrapper : public utility::CrtpBase<_Derived, VectorWrapper<_Derived>> {

 private:

  using SizesType = std::tuple<index_t>;

 protected:

  // Constructors
  inline VectorWrapper() noexcept = default;

 public:

  // Operators
  template <class __Derived>
  friend inline std::ostream& operator<<( std::ostream &out, const VectorWrapper<__Derived> &wrapper );

  // Gets information
  inline index_t   length() const noexcept;
  inline index_t   nelem() const noexcept;
  inline SizesType sizes() const noexcept;

};

}  // namespace container

}  // namespace mcnla

#endif  // MCNLA_CORE_CONTAINER_BASE_VECTOR_WRAPPER_HH_
