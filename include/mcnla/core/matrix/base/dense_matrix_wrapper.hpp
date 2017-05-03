////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/base/dense_matrix_wrapper.hpp
/// @brief   The dense matrix wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_BASE_DENSE_MATRIX_WRAPPER_HPP_
#define MCNLA_CORE_MATRIX_BASE_DENSE_MATRIX_WRAPPER_HPP_

#include <mcnla/core/matrix/base/dense_matrix_wrapper.hh>
#include <iomanip>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Output to stream.
///
template <class __Derived>
std::ostream& operator<<(
    std::ostream &os,
    const DenseMatrixWrapper<__Derived> &wrapper
) noexcept {
  auto &matrix = wrapper.derived();
  for ( index_t i = 0; i < matrix.nrow(); ++i ) {
    for ( index_t j = 0; j < matrix.ncol(); ++j ) {
      os << std::setw(kOsValWidth) << matrix(i, j) << "  ";
    }
    os << '\n';
  }
  return os;
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_BASE_DENSE_MATRIX_WRAPPER_HPP_
