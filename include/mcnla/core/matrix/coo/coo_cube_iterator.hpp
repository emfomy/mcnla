////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_cube_iterator.hpp
/// @brief   The COO cube iterator class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_CUBE_ITERATOR_HPP_
#define MCNLA_CORE_MATRIX_COO_COO_CUBE_ITERATOR_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/matrix/coo/coo_iterator_base.hpp>
#include <mcnla/core/matrix/coo/coo_cube.hpp>
#include <mcnla/core/matrix/coo/coo_tuple.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Layout _layout> class CooCube;
template <typename _Scalar, typename _Index, Layout _layout, class _Cube> class CooCubeIteratorBase;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) cube iterator traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Index   The index type.
/// @tparam  _Cube    The cube type.
///
template <typename _Scalar, typename _Index, Layout _layout, class _Cube>
struct Traits<matrix::CooCubeIteratorBase<_Scalar, _Index, _layout, _Cube>> {
  static constexpr index_t ndim = 3;
  using ScalarType    = _Scalar;
  using IndexType     = _Index;
  using ContainerType = _Cube;
};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_coo_module
/// The coordinate list (COO) cube iterator.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Index   The index type.
/// @tparam  _Cube    The cube type.
///
/// @see  CooCubeIterator, CooCubeConstIterator
///
template <typename _Scalar, typename _Index, Layout _layout, class _Cube>
class CooCubeIteratorBase : public CooIteratorBase<CooCubeIteratorBase<_Scalar, _Index, _layout, _Cube>> {

 private:

  static constexpr index_t ndim = 3;
  using ScalarType    = _Scalar;
  using IndexType     = _Index;
  using ContainerType = _Cube;

  using BaseType      = CooIteratorBase<CooCubeIteratorBase<_Scalar, _Index, _layout, _Cube>>;

 protected:

  using BaseType::itidx_;
  using BaseType::container_;

 public:

  using BaseType::CooIteratorBase;
  using BaseType::operator=;

  // Operators
  template <typename __Scalar, typename __Index, Layout __layout, class __Cube>
  friend inline std::ostream& operator<<( std::ostream &out,
                                          const CooCubeIteratorBase<__Scalar, __Index, __layout, __Cube> &iterator );

  // Gets value
  inline IndexType& getRowIdx() const noexcept;
  inline IndexType& getColIdx() const noexcept;
  inline IndexType& getPageIdx() const noexcept;
  inline index_t    getPos() const noexcept;

};

/// @ingroup  matrix_coo_module
template <typename _Scalar, Layout _layout>
using CooCubeIterator = mcnla::matrix::CooCubeIteratorBase<_Scalar, index_t, _layout, CooCube<_Scalar, _layout>>;

/// @ingroup  matrix_coo_module
template <typename _Scalar, Layout _layout>
using CooCubeConstIterator = mcnla::matrix::CooCubeIteratorBase<const _Scalar, const index_t, _layout, const CooCube<_Scalar, _layout>>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_CUBE_ITERATOR_HPP_
