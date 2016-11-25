////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/set/matrix_set_base.hpp
/// @brief   The matrix set interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_SET_MATRIX_SET_BASE_HPP_
#define MCNLA_CORE_MATRIX_SET_MATRIX_SET_BASE_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/utility/traits.hpp>
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
/// @ingroup  matrix_set_module
/// The interface of matrix set.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class MatrixSetBase : public utility::CrtpBase<_Derived, MatrixSetBase<_Derived>> {

 private:

  using MatrixType = typename traits::Traits<_Derived>::MatrixType;

 protected:

  // Constructors
  inline MatrixSetBase() noexcept;

 public:

  // Gets information
  inline index_t getNrow() const noexcept;
  inline index_t getNcol() const noexcept;
  inline index_t getNmat() const noexcept;
  inline std::tuple<index_t, index_t, index_t> getSizes() const noexcept;

  // Gets matrix
  inline       MatrixType getMatrix( const index_t idx ) noexcept;
  inline const MatrixType getMatrix( const index_t idx ) const noexcept;
  inline       MatrixType operator()( const index_t idx ) noexcept;
  inline const MatrixType operator()( const index_t idx ) const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_SET_MATRIX_SET_BASE_HPP_
