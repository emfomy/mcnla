////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/base/cube_base.hpp
/// @brief   The cube interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_BASE_CUBE_BASE_HPP_
#define MCNLA_CORE_MATRIX_BASE_CUBE_BASE_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <tuple>
#include <mcnla/core/utility/traits.hpp>
#include <mcnla/core/matrix/base/tensor_base.hpp>
#include <mcnla/core/matrix/kit/idx_range.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of cube type.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class CubeBase : public TensorBase<_Derived> {

 private:

  static constexpr Layout layout = traits::Traits<_Derived>::layout;

 protected:

  /// The number of rows.
  index_t nrow_;

  /// The number of columns.
  index_t ncol_;

  /// The number of pages.
  index_t npage_;

  /// The leading size.
  index_t &size0_ = isColMajor(layout) ? nrow_ : ncol_;

  /// The second size.
  index_t &size1_ = isColMajor(layout) ? ncol_ : nrow_;

  /// The third size.
  index_t &size2_ = npage_;

 protected:

  // Constructors
  inline CubeBase() noexcept;
  inline CubeBase( const index_t nrow, const index_t ncol, const index_t npage ) noexcept;
  inline CubeBase( const std::tuple<index_t, index_t, index_t> sizes ) noexcept;
  inline CubeBase( const CubeBase &other ) noexcept;
  inline CubeBase( CubeBase &&other ) noexcept;

  // Operators
  inline CubeBase& operator=( const CubeBase &other ) noexcept;
  inline CubeBase& operator=( CubeBase &&other ) noexcept;

 public:

  // Gets information
  template <TransOption _trans = TransOption::NORMAL> inline index_t getNrow() const noexcept;
  template <TransOption _trans = TransOption::NORMAL> inline index_t getNcol() const noexcept;
  template <index_t _dim> inline index_t getSize() const noexcept;
  inline index_t getNpage() const noexcept;
  inline index_t getNelem() const noexcept;
  inline std::tuple<index_t, index_t, index_t> getSizes() const noexcept;

  // Gets derived class
  inline       _Derived& derived() noexcept;
  inline const _Derived& derived() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_BASE_CUBE_BASE_HPP_
