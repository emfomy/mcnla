////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/base/dense_matrix_wrapper.hh
/// @brief   The definition of dense matrix wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_BASE_DENSE_MATRIX_WRAPPER_HH_
#define MCNLA_CORE_MATRIX_BASE_DENSE_MATRIX_WRAPPER_HH_

#include <mcnla/core/matrix/def.hpp>
#include <tuple>
#include <mcnla/core/matrix/base/matrix_wrapper.hpp>
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
/// The dense matrix wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class DenseMatrixWrapper : public MatrixWrapper<_Derived> {

 private:

  using SizesType = std::tuple<index_t, index_t>;

 protected:

  // Constructors
  inline DenseMatrixWrapper() noexcept = default;

 public:

  // Gets information
  inline index_t   mrow() const noexcept;
  inline index_t   mcol() const noexcept;
  inline index_t   melem() const noexcept;
  inline SizesType msizes() const noexcept;

 protected:

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  CRTP_DERIVED(_Derived);
#endif  // DOXYGEN_SHOULD_SKIP_THIS

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_BASE_DENSE_MATRIX_WRAPPER_HH_
