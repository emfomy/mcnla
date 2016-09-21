////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense/dense_cube_iterator.hpp
/// @brief   The dense cube iterator class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DENSE_CUBE_ITERATOR_HPP_
#define ISVD_MATRIX_DENSE_DENSE_CUBE_ITERATOR_HPP_

#include <isvd/isvd.hpp>
#include <isvd/matrix/dense/dense_cube.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Layout _layout> class DenseCube;
template <typename _Scalar, Layout _layout, class _Cube> class DenseCubeIteratorBase;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace.
//
namespace detail {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix iterator traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
/// @tparam  _Cube    The cube type.
///
template <typename _Scalar, Layout _layout, class _Cube>
struct Traits<DenseCubeIteratorBase<_Scalar, _layout, _Cube>> {
  static constexpr index_t ndim = 3;
  using ScalarType    = _Scalar;
  using ContainerType = _Cube;
};

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense cube iterator.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
/// @tparam  _Cube    The cube type.
///
template <typename _Scalar, Layout _layout, class _Cube>
class DenseCubeIteratorBase : public DenseIteratorBase<DenseCubeIteratorBase<_Scalar, _layout, _Cube>> {

 private:

  static constexpr index_t ndim = 3;
  using ScalarType    = _Scalar;
  using ContainerType = _Cube;

  using BaseType      = DenseIteratorBase<DenseCubeIteratorBase<_Scalar, _layout, _Cube>>;

 protected:

  using BaseType::itidx_;
  using BaseType::container_;

 public:

  using BaseType::DenseIteratorBase;
  using BaseType::operator=;

  // Operators
  template <typename __Scalar, Layout __layout, class __Cube>
  friend inline std::ostream& operator<<( std::ostream &out,
                                          const DenseCubeIteratorBase<__Scalar, __layout, __Cube> &iterator );

  // Gets value
  inline ScalarType& getValue() const noexcept;
  inline index_t     getRowIdx() const noexcept;
  inline index_t     getColIdx() const noexcept;
  inline index_t     getPageIdx() const noexcept;
  inline index_t     getIdx1() const noexcept;
  inline index_t     getIdx2() const noexcept;
  inline index_t     getIdx3() const noexcept;
  inline index_t     getPos() const noexcept;

};

template <typename _Scalar, Layout _layout>
using DenseCubeIterator = DenseCubeIteratorBase<_Scalar, _layout, DenseCube<_Scalar, _layout>>;

template <typename _Scalar, Layout _layout>
using DenseCubeConstIterator = DenseCubeIteratorBase<const _Scalar, _layout, const DenseCube<_Scalar, _layout>>;

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_CUBE_ITERATOR_HPP_
