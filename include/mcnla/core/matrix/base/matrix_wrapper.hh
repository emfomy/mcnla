////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/base/matrix_wrapper.hh
/// @brief   The definition of matrix wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_BASE_MATRIX_WRAPPER_HH_
#define MCNLA_CORE_MATRIX_BASE_MATRIX_WRAPPER_HH_

#include <mcnla/core/matrix/def.hpp>
#include <iostream>
#include <tuple>
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
/// The matrix wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class MatrixWrapper : public utility::CrtpBase<_Derived, MatrixWrapper<_Derived>> {

 private:

  using SizesType = std::tuple<index_t, index_t>;

 protected:

  // Constructors
  inline MatrixWrapper() noexcept = default;

 public:

  // Operators
  template <class __Derived>
  friend inline std::ostream& operator<<( std::ostream &os, const MatrixWrapper<__Derived> &wrapper );

  // Gets information
  inline index_t   nrow() const noexcept;
  inline index_t   ncol() const noexcept;
  inline index_t   nelem() const noexcept;
  inline SizesType sizes() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_BASE_MATRIX_WRAPPER_HH_
