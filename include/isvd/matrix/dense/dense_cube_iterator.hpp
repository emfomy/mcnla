////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense/dense_cube_iterator.hpp
/// @brief   The dense cube iterator class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DENSE_CUBE_ITERATOR_HPP_
#define ISVD_MATRIX_DENSE_DENSE_CUBE_ITERATOR_HPP_

#include <isvd/isvd.hpp>
#include <isvd/matrix/base/iterator_base.hpp>
#include <isvd/matrix/base/value_iterator_base.hpp>
#include <isvd/matrix/base/idx_iterator_base.hpp>
#include <isvd/matrix/dense/dense_cube.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Layout _layout> class DenseCube;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

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
struct Traits<DenseCubeIteratorBase<_Scalar, _layout, _Cube>> : Traits<IteratorBase<_Cube>> {
  using ScalarType        = _Scalar;
  using IdxTupleType      = IdxTuple<3>;
  using BaseType          = DenseCubeIteratorBase<_Scalar, _layout, _Cube>;
  using ValueIteratorType = DenseCubeValueIteratorBase<_Scalar, _layout, _Cube>;
  using IdxIteratorType   = DenseCubeIdxIteratorBase<_Scalar, _layout, _Cube>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix value iterator traits.
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
class DenseCubeIteratorBase : public IteratorBase<_Cube> {

 protected:

  using IteratorBase<_Cube>::itidx_;
  using IteratorBase<_Cube>::container_;

 public:

  using IteratorBase<_Cube>::IteratorBase;

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
/// The dense cube value iterator.
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
/// The dense cube value iterator.
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

}  // namespace internal

template <typename _Scalar, Layout _layout>
using DenseCubeIterator = internal::DenseCubeValueIteratorBase<_Scalar, _layout, DenseCube<_Scalar, _layout>>;

template <typename _Scalar, Layout _layout>
using DenseCubeConstIterator = internal::DenseCubeValueIteratorBase<const _Scalar, _layout, const DenseCube<_Scalar, _layout>>;

template <typename _Scalar, Layout _layout>
using DenseCubeIdxIterator = internal::DenseCubeIdxIteratorBase<_Scalar, _layout, DenseCube<_Scalar, _layout>>;

template <typename _Scalar, Layout _layout>
using DenseCubeConstIdxIterator = internal::DenseCubeIdxIteratorBase<const _Scalar, _layout, const DenseCube<_Scalar, _layout>>;

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_CUBE_ITERATOR_HPP_
