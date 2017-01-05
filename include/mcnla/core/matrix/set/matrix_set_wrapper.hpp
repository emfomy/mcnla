////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/set/matrix_set_wrapper.hpp
/// @brief   The matrix set wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_SET_MATRIX_SET_WRAPPER_HPP_
#define MCNLA_CORE_MATRIX_SET_MATRIX_SET_WRAPPER_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
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
/// @ingroup  matrix_set_module
/// The matrix set wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class MatrixSetWrapper : public utility::CrtpBase<_Derived, MatrixSetWrapper<_Derived>> {

 private:

  using MatrixType = MatrixT<_Derived>;

 protected:

  // Constructors
  inline MatrixSetWrapper() noexcept;

 public:

  // Gets information
  inline index_t nrow() const noexcept;
  inline index_t ncol() const noexcept;
  inline index_t nmat() const noexcept;
  inline std::tuple<index_t, index_t, index_t> sizes() const noexcept;

  // Gets matrix
  inline       MatrixType operator()( const index_t idx ) noexcept;
  inline const MatrixType operator()( const index_t idx ) const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_SET_MATRIX_SET_WRAPPER_HPP_
