////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/base/sparse_wrapper.hh
/// @brief   The definition of sparse container wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_BASE_SPARSE_WRAPPER_HH_
#define MCNLA_CORE_MATRIX_BASE_SPARSE_WRAPPER_HH_

#include <mcnla/core/matrix/def.hpp>
#include <iostream>
#include <mcnla/core/utility/crtp.hpp>
#include <mcnla/core/utility/traits.hpp>

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
/// The sparse container wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class SparseWrapper : public utility::CrtpBase<_Derived, SparseWrapper<_Derived>> {

 protected:

  // Constructors
  inline SparseWrapper() noexcept = default;

 public:

  // Operators
  template <class __Derived>
  friend inline std::ostream& operator<<( std::ostream &os, const SparseWrapper<__Derived> &wrapper ) noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_BASE_SPARSE_WRAPPER_HH_
