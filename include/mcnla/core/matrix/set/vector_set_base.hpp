////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/set/vector_set_base.hpp
/// @brief   The vector set interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_SET_VECTOR_SET_BASE_HPP_
#define MCNLA_CORE_MATRIX_SET_VECTOR_SET_BASE_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/utility/traits.hpp>
#include <mcnla/core/utility/crtp.hpp>

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
/// The interface of vector set.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class VectorSetBase : public utility::CrtpBase<_Derived, VectorSetBase<_Derived>> {

 private:

  using VectorType = typename traits::Traits<_Derived>::VectorType;

 protected:

  // Constructors
  inline VectorSetBase() noexcept;

 public:

  // Gets information
  inline index_t getLength() const noexcept;
  inline index_t getNvec() const noexcept;

  // Gets vector
  inline       VectorType getVector( const index_t idx ) noexcept;
  inline const VectorType getVector( const index_t idx ) const noexcept;
  inline       VectorType operator()( const index_t idx ) noexcept;
  inline const VectorType operator()( const index_t idx ) const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_SET_VECTOR_SET_BASE_HPP_
