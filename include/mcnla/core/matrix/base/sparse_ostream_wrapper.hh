////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/base/sparse_ostream_wrapper.hh
/// @brief   The definition of sparse container output-stream wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_BASE_SPARSE_OSTREAM_WRAPPER_HH_
#define MCNLA_CORE_MATRIX_BASE_SPARSE_OSTREAM_WRAPPER_HH_

#include <mcnla/core/matrix/def.hpp>
#include <iostream>
#include <mcnla/core/utility/crtp.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The sparse container output-stream wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class SparseOstreamWrapper {

 protected:

  // Constructors
  inline SparseOstreamWrapper() noexcept = default;

 public:

  // Operators
  template <class __Derived>
  friend inline std::ostream& operator<<( std::ostream &os, const SparseOstreamWrapper<__Derived> &wrapper ) noexcept;

 protected:

  MCNLA_CRTP_DERIVED(_Derived)

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_BASE_SPARSE_OSTREAM_WRAPPER_HH_
