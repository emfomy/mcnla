////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/set/vector_set_wrapper.hpp
/// @brief   The vector set wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_SET_VECTOR_SET_WRAPPER_HPP_
#define MCNLA_CORE_MATRIX_SET_VECTOR_SET_WRAPPER_HPP_

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
/// @ingroup  matrix_set_module
/// The vector set wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class VectorSetWrapper : public utility::CrtpBase<_Derived, VectorSetWrapper<_Derived>> {

 private:

  using VectorType = typename traits::Traits<_Derived>::VectorType;

 protected:

  // Constructors
  inline VectorSetWrapper() noexcept;

 public:

  // Gets information
  inline index_t length() const noexcept;
  inline index_t nvecvec() const noexcept;
  inline std::pair<index_t, index_t> sizes() const noexcept;

  // Gets vector
  inline       VectorType operator()( const index_t idx ) noexcept;
  inline const VectorType operator()( const index_t idx ) const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_SET_VECTOR_SET_WRAPPER_HPP_
