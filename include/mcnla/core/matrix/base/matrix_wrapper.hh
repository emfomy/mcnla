////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/base/matrix_wrapper.hh
/// @brief   The definition of matrix wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_BASE_MATRIX_WRAPPER_HH_
#define MCNLA_CORE_MATRIX_BASE_MATRIX_WRAPPER_HH_

#include <mcnla/core/matrix/def.hpp>
#include <tuple>
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
/// The matrix wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class MatrixWrapper {

 public:

  static constexpr index_t ndim = 2;

 private:

  using SizesType = std::tuple<index_t, index_t>;

 protected:

  // Constructors
  inline MatrixWrapper() noexcept = default;

 public:

  // Gets information
  inline index_t   nrow() const noexcept;
  inline index_t   ncol() const noexcept;
  inline index_t   nelem() const noexcept;
  inline SizesType sizes() const noexcept;

 protected:

  MCNLA_CRTP_DERIVED(_Derived)

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_BASE_MATRIX_WRAPPER_HH_
