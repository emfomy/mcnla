////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/base/dense_vector_wrapper.hpp
/// @brief   The dense vector wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_BASE_DENSE_VECTOR_WRAPPER_HPP_
#define MCNLA_CORE_MATRIX_BASE_DENSE_VECTOR_WRAPPER_HPP_

#include <mcnla/core/matrix/base/dense_vector_wrapper.hh>
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
    const DenseVectorWrapper<__Derived> &wrapper
) {
  auto &vector = wrapper.derived();
  for ( index_t i = 0; i < vector.length(); ++i ) {
    os << std::setw(kOsValWidth) << vector(i) << "  ";
  }
  return os << '\n';
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_BASE_DENSE_VECTOR_WRAPPER_HPP_
