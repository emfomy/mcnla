////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/base/dense_matrix_wrapper.hpp
/// @brief   The dense matrix wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_BASE_DENSE_MATRIX_WRAPPER_HPP_
#define MCNLA_CORE_MATRIX_BASE_DENSE_MATRIX_WRAPPER_HPP_

#include <mcnla/core/matrix/base/dense_matrix_wrapper.hh>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the maximum number of rows.
///
template <class _Derived>
index_t DenseMatrixWrapper<_Derived>::mrow() const noexcept {
  return this->derived().mrowImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the maximum number of columns.
///
template <class _Derived>
index_t DenseMatrixWrapper<_Derived>::mcol() const noexcept {
  return this->derived().mcolImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the maximum number of elements.
///
template <class _Derived>
index_t DenseMatrixWrapper<_Derived>::melem() const noexcept {
  return mrow() * mcol();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the maximum size of dimensions in interface order: `{ #mrow, #mcol }`.
///
template <class _Derived>
std::tuple<index_t, index_t> DenseMatrixWrapper<_Derived>::msizes() const noexcept {
  return std::make_tuple(mrow(), mcol());
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_BASE_DENSE_MATRIX_WRAPPER_HPP_
