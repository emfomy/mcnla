////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/base/vector_ostream_wrapper.hh
/// @brief   The definition of vector output-stream wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_BASE_VECTOR_OSTREAM_WRAPPER_HH_
#define MCNLA_CORE_MATRIX_BASE_VECTOR_OSTREAM_WRAPPER_HH_

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
/// @ingroup  matrix_base_module
/// The vector output-stream wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class VectorOstreamWrapper {

 protected:

  // Constructors
  inline VectorOstreamWrapper() noexcept = default;

 public:

  // Operators
  template <class __Derived>
  friend inline std::ostream& operator<<( std::ostream &os, const VectorOstreamWrapper<__Derived> &wrapper ) noexcept;

 protected:

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  CRTP_DERIVED(_Derived);
#endif  // DOXYGEN_SHOULD_SKIP_THIS

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_BASE_VECTOR_OSTREAM_WRAPPER_HH_
