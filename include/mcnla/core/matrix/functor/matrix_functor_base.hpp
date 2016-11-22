////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/functor/matrix_functor_base.hpp
/// @brief   The matrix functor interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_FUNCTOR_MATRIX_FUNCTOR_BASE_HPP_
#define MCNLA_CORE_MATRIX_FUNCTOR_MATRIX_FUNCTOR_BASE_HPP_

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
/// @ingroup  matrix_functor_module
/// The interface of matrix functor.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class MatrixFunctorBase : public utility::CrtpBase<_Derived, MatrixFunctorBase<_Derived>> {

 private:

  using VectorType = typename traits::Traits<_Derived>::VectorType;

 protected:

  // Constructors
  inline MatrixFunctorBase() noexcept;

 public:

  // Gets information
  inline index_t getNrow() const noexcept;
  inline index_t getNcol() const noexcept;

  // Gets matrix
  inline void operator()( const VectorType &input, VectorType &output ) const noexcept;
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  inline void operator()( const VectorType &input, VectorType &&output ) const noexcept;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_FUNCTOR_MATRIX_FUNCTOR_BASE_HPP_
