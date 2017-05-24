////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/base/matrix_ostream_wrapper.hh
/// @brief   The definition of matrix output-stream wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_BASE_MATRIX_OSTREAM_WRAPPER_HH_
#define MCNLA_CORE_MATRIX_BASE_MATRIX_OSTREAM_WRAPPER_HH_

#include <mcnla/core/matrix/def.hpp>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The matrix output-stream wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class MatrixOstreamWrapper {

 protected:

  // Constructors
  inline MatrixOstreamWrapper() noexcept = default;

 public:

  // Operators
  template <typename ..._Args>
  friend inline std::ostream& operator<<( std::ostream &os, const MatrixOstreamWrapper<_Args...> &wrapper ) noexcept;

 protected:

  MCNLA_CRTP_DERIVED(_Derived)

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_BASE_MATRIX_OSTREAM_WRAPPER_HH_
