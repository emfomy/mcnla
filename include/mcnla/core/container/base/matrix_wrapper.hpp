////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/container/base/matrix_wrapper.hpp
/// @brief   The matrix wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_CONTAINER_BASE_MATRIX_WRAPPER_HPP_
#define MCNLA_CORE_CONTAINER_BASE_MATRIX_WRAPPER_HPP_

#include <mcnla/core/container/base/matrix_wrapper.hh>
#include <iomanip>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The container namespace.
//
namespace container {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Output to stream.
///
template <class __Derived>
std::ostream& operator<< (
    std::ostream &os,
    const MatrixWrapper<__Derived> &wrapper
) {
  auto &matrix = wrapper.derived();
  for ( index_t i = 0; i < matrix.nrow(); ++i ) {
    for ( index_t j = 0; j < matrix.ncol(); ++j ) {
      os << std::setw(ios_width) << matrix(i, j) << "  ";
    }
    os << '\n';
  }
  return os;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of rows.
///
template <class _Derived>
index_t MatrixWrapper<_Derived>::nrow() const noexcept {
  return this->derived().nrowImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of columns.
///
template <class _Derived>
index_t MatrixWrapper<_Derived>::ncol() const noexcept {
  return this->derived().ncolImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of elements.
///
template <class _Derived>
index_t MatrixWrapper<_Derived>::nelem() const noexcept {
  return nrow() * ncol();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size of dimensions in interface order. [ nrow, ncol ]
///
template <class _Derived>
std::tuple<index_t, index_t> MatrixWrapper<_Derived>::sizes() const noexcept {
  return std::make_tuple(nrow(), ncol());
}

}  // namespace container

}  // namespace mcnla

#endif  // MCNLA_CORE_CONTAINER_BASE_MATRIX_WRAPPER_HPP_
