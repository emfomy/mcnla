////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/base/invertible_wrapper.hh
/// @brief   The definition of invertible wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_BASE_INVERTIBLE_WRAPPER_HH_
#define MCNLA_CORE_MATRIX_BASE_INVERTIBLE_WRAPPER_HH_

#include <mcnla/core/matrix/def.hpp>
#include <mcnla/core/utility/crtp.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {


#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Base> class InverseView;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_base_module
/// The invertible container wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class InvertibleWrapper {

 public:

  // Constructors
  inline InvertibleWrapper() noexcept = default;

  // Change view
  inline       InverseView<_Derived>& inv() noexcept;
  inline const InverseView<_Derived>& inv() const noexcept;

 protected:

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  CRTP_DERIVED(_Derived);
#endif  // DOXYGEN_SHOULD_SKIP_THIS

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_base_module
/// The inverse view.
///
/// @tparam  _Base  The base type.
///
template <class _Base>
class InverseView : private _Base {

  friend InvertibleWrapper<_Base>;

 public:

  // Constructors
  inline InverseView() noexcept = delete;

  // Change view
  inline       _Base& inv() noexcept;
  inline const _Base& inv() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_BASE_INVERTIBLE_WRAPPER_HH_
