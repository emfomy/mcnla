////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/base/vector_wrapper.ipp
/// @brief   The implementation of vector wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_BASE_VECTOR_WRAPPER_IPP_
#define MCNLA_CORE_MATRIX_BASE_VECTOR_WRAPPER_IPP_

#include <mcnla/core/matrix/base/vector_wrapper.hpp>
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
/// @brief  Print to stream.
///
template <class __Derived>
std::ostream& operator<< (
    std::ostream &out,
    const VectorWrapper<__Derived> &wrapper
) {
  auto &vector = wrapper.derived();
  for ( index_t i = 0; i < vector.length(); ++i ) {
    out << std::setw(ios_width) << vector(i) << "  ";
  }
  return out << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the length.
///
template <class _Derived>
index_t VectorWrapper<_Derived>::length() const noexcept {
  return this->derived().lengthImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of elements.
///
template <class _Derived>
index_t VectorWrapper<_Derived>::nelem() const noexcept {
  return length();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size of dimensions in interface order. [ length ]
///
template <class _Derived>
std::tuple<index_t> VectorWrapper<_Derived>::sizes() const noexcept {
  return std::make_tuple(length());
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_BASE_VECTOR_WRAPPER_IPP_
