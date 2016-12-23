////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/base/vector_wrapper.hpp
/// @brief   The vector wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_BASE_VECTOR_WRAPPER_HPP_
#define MCNLA_CORE_MATRIX_BASE_VECTOR_WRAPPER_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
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
/// @ingroup  matrix_module
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

  // Gets information
  inline index_t   getLength() const noexcept;
  inline index_t   getNelem() const noexcept;
  inline SizesType getSizes() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_BASE_VECTOR_WRAPPER_HPP_
