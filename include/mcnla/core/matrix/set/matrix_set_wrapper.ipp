////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/set/matrix_set_wrapper.ipp
/// @brief   The implementation of matrix set wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_SET_MATRIX_SET_WRAPPER_IPP_
#define MCNLA_CORE_MATRIX_SET_MATRIX_SET_WRAPPER_IPP_

#include <mcnla/core/matrix/set/matrix_set_wrapper.hpp>

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
MatrixSetWrapper<_Derived>::MatrixSetWrapper() noexcept {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of rows of matrix.
///
template <class _Derived>
index_t MatrixSetWrapper<_Derived>::getNrow() const noexcept {
  return this->derived().getNrowImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of column of matrix.
///
template <class _Derived>
index_t MatrixSetWrapper<_Derived>::getNcol() const noexcept {
  return this->derived().getNcolImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of matrices.
///
template <class _Derived>
index_t MatrixSetWrapper<_Derived>::getNmat() const noexcept {
  return this->derived().getNmatImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the sizes.
///
template <class _Derived>
std::tuple<index_t, index_t, index_t> MatrixSetWrapper<_Derived>::getSizes() const noexcept {
  return std::make_tuple(getNrow(), getNcol(), getNmat());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a matrix.
///
template <class _Derived>
typename MatrixSetWrapper<_Derived>::MatrixType MatrixSetWrapper<_Derived>::operator()(
    const index_t idx
) noexcept {
  return this->derived().getMatrixImpl(idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const index_t )
///
template <class _Derived>
const typename MatrixSetWrapper<_Derived>::MatrixType MatrixSetWrapper<_Derived>::operator()(
    const index_t idx
) const noexcept {
  return this->derived().getMatrixImpl(idx);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_SET_MATRIX_SET_WRAPPER_IPP_
