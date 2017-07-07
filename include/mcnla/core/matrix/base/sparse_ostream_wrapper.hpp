////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/base/sparse_ostream_wrapper.hpp
/// @brief   The displayable container wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_BASE_SPARSE_OSTREAM_WRAPPER_HPP_
#define MCNLA_CORE_MATRIX_BASE_SPARSE_OSTREAM_WRAPPER_HPP_

#include <mcnla/core/matrix/base/sparse_ostream_wrapper.hh>
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
template <typename ..._Args>
std::ostream& operator<<(
    std::ostream &os,
    const SparseOstreamWrapper<_Args...> &wrapper
) noexcept {
  for ( auto tuple : wrapper.derived() ) {
    os << tuple << '\n';
  }
  return os;
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_BASE_SPARSE_OSTREAM_WRAPPER_HPP_
