////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/functor/matrix_functor_base.ipp
/// @brief   The implementation of matrix functor interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_FUNCTOR_MATRIX_FUNCTOR_BASE_IPP_
#define MCNLA_CORE_MATRIX_FUNCTOR_MATRIX_FUNCTOR_BASE_IPP_

#include <mcnla/core/matrix/functor/matrix_functor_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <class _Derived>
MatrixFunctorBase<_Derived>::MatrixFunctorBase() noexcept {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of elements output vector.
///
template <class _Derived>
index_t MatrixFunctorBase<_Derived>::getNrow() const noexcept { return this->derived().getNrowImpl(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of elements input vector.
///
template <class _Derived>
index_t MatrixFunctorBase<_Derived>::getNcol() const noexcept { return this->derived().getNcolImpl(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Apply this matrix functor.
///
template <class _Derived>
void MatrixFunctorBase<_Derived>::operator()( const VectorType &input, VectorType &output ) const noexcept {
  return this->derived().operator()(input, output);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Derived>
void MatrixFunctorBase<_Derived>::operator()( const VectorType &input, VectorType &&output ) const noexcept {
  operator()(input, output);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_FUNCTOR_MATRIX_FUNCTOR_BASE_IPP_
