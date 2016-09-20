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
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace.
//
namespace detail {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Layout _layout, class _Cube> class DenseCubeIteratorBase;
template <typename _Scalar, Layout _layout, class _Cube> class DenseCubeValueIteratorBase;
template <typename _Scalar, Layout _layout, class _Cube> class DenseCubeIdxIteratorBase;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix iterator traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
/// @tparam  _Cube    The cube type.
///
template <typename _Scalar, Layout _layout, class _Cube>
struct Traits<DenseCubeIteratorBase<_Scalar, _layout, _Cube>>
  : Traits<IteratorBase<DenseCubeIteratorBase<_Scalar, _layout, _Cube>>> {
  using ScalarType        = _Scalar;
  using IdxTupleType      = IdxTuple<3>;
  using ContainerType     = _Cube;
  using BaseType          = DenseCubeIteratorBase<_Scalar, _layout, _Cube>;
  using ValueIteratorType = DenseCubeValueIteratorBase<_Scalar, _layout, _Cube>;
  using IdxIteratorType   = DenseCubeIdxIteratorBase<_Scalar, _layout, _Cube>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix iterator traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
/// @tparam  _Cube    The cube type.
///
template <typename _Scalar, Layout _layout, class _Cube>
struct Traits<DenseCubeValueIteratorBase<_Scalar, _layout, _Cube>> : Traits<DenseCubeIteratorBase<_Scalar, _layout, _Cube>> {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix index iterator traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
/// @tparam  _Cube    The cube type.
///
template <typename _Scalar, Layout _layout, class _Cube>
struct Traits<DenseCubeIdxIteratorBase<_Scalar, _layout, _Cube>> : Traits<DenseCubeIteratorBase<_Scalar, _layout, _Cube>> {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense cube iterator.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
/// @tparam  _Cube    The cube type.
///
template <typename _Scalar, Layout _layout, class _Cube>
class DenseCubeIteratorBase : public IteratorBase<DenseCubeIteratorBase<_Scalar, _layout, _Cube>> {

 protected:

  using IteratorBase<DenseCubeIteratorBase<_Scalar, _layout, _Cube>>::itidx_;
  using IteratorBase<DenseCubeIteratorBase<_Scalar, _layout, _Cube>>::container_;

 public:

  using IteratorBase<DenseCubeIteratorBase<_Scalar, _layout, _Cube>>::IteratorBase;

  // Operators
  template <typename __Scalar, Layout __layout, class __Cube>
  friend inline std::ostream& operator<<( std::ostream &out,
                                          const DenseCubeIteratorBase<__Scalar, __layout, __Cube> &iterator );

  // Gets value
  inline       _Scalar&    getValue() noexcept;
  inline const _Scalar&    getValue() const noexcept;
  inline       IdxTuple<3> getIdxs() const noexcept;
  inline       index_t     getRowIdx() const noexcept;
  inline       index_t     getColIdx() const noexcept;
  inline       index_t     getPageIdx() const noexcept;
  inline       index_t     getIdx1() const noexcept;
  inline       index_t     getIdx2() const noexcept;
  inline       index_t     getIdx3() const noexcept;
  inline       index_t     getPos() const noexcept;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense cube iterator.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
/// @tparam  _Cube    The cube type.
///
template <typename _Scalar, Layout _layout, class _Cube>
class DenseCubeValueIteratorBase
  : public DenseCubeIteratorBase<_Scalar, _layout, _Cube>,
    public ValueIteratorBase<DenseCubeValueIteratorBase<_Scalar, _layout, _Cube>> {

 public:

  using DenseCubeIteratorBase<_Scalar, _layout, _Cube>::DenseCubeIteratorBase;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense cube iterator.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
/// @tparam  _Cube    The cube type.
///
template <typename _Scalar, Layout _layout, class _Cube>
class DenseCubeIdxIteratorBase
  : public DenseCubeIteratorBase<_Scalar, _layout, _Cube>,
    public IdxIteratorBase<DenseCubeIdxIteratorBase<_Scalar, _layout, _Cube>> {

 public:

  using DenseCubeIteratorBase<_Scalar, _layout, _Cube>::DenseCubeIteratorBase;

};

}  // namespace detail

template <typename _Scalar, Layout _layout>
using DenseCubeIterator = detail::DenseCubeValueIteratorBase<_Scalar, _layout, DenseCube<_Scalar, _layout>>;

template <typename _Scalar, Layout _layout>
using DenseCubeConstIterator = detail::DenseCubeValueIteratorBase<const _Scalar, _layout, const DenseCube<_Scalar, _layout>>;

template <typename _Scalar, Layout _layout>
using DenseCubeIdxIterator = detail::DenseCubeIdxIteratorBase<_Scalar, _layout, DenseCube<_Scalar, _layout>>;

template <typename _Scalar, Layout _layout>
using DenseCubeConstIdxIterator = detail::DenseCubeIdxIteratorBase<const _Scalar, _layout, const DenseCube<_Scalar, _layout>>;

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_CUBE_ITERATOR_HPP_
