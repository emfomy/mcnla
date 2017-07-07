////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/base/matrix_ostream_wrapper.hpp
/// @brief   The matrix output-stream wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_BASE_MATRIX_OSTREAM_WRAPPER_HPP_
#define MCNLA_CORE_MATRIX_BASE_MATRIX_OSTREAM_WRAPPER_HPP_

#include <mcnla/core/matrix/base/matrix_ostream_wrapper.hh>
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
    const MatrixOstreamWrapper<_Args...> &wrapper
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

#endif  // MCNLA_CORE_MATRIX_BASE_MATRIX_OSTREAM_WRAPPER_HPP_
