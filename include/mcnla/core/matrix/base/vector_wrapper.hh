////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/base/vector_wrapper.hh
/// @brief   The definition of vector wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_BASE_VECTOR_WRAPPER_HH_
#define MCNLA_CORE_MATRIX_BASE_VECTOR_WRAPPER_HH_

#include <mcnla/core/matrix/def.hpp>
#include <tuple>
#include <mcnla/core/utility/crtp.hpp>
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
/// @ingroup  matrix_base_module
/// The vector wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class VectorWrapper : public utility::CrtpBase<_Derived, VectorWrapper<_Derived>> {

 public:

  static constexpr index_t ndim = 1;

 private:

  using SizesType = std::tuple<index_t>;

 protected:

  // Constructors
  inline VectorWrapper() noexcept = default;

 public:

  // Gets information
  inline index_t   length() const noexcept;
  inline index_t   nelem() const noexcept;
  inline SizesType sizes() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_BASE_VECTOR_WRAPPER_HH_
