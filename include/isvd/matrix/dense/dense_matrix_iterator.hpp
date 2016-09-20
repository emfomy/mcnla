////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense/dense_matrix_iterator.hpp
/// @brief   The dense matrix iterator class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_HPP_
#define ISVD_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_HPP_

#include <isvd/isvd.hpp>
#include <isvd/matrix/dense/dense_matrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Layout _layout> class DenseMatrix;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace.
//
namespace detail {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Layout _layout, class _Matrix> class DenseMatrixIteratorBase;
template <typename _Scalar, Layout _layout, class _Matrix> class DenseMatrixValueIteratorBase;
template <typename _Scalar, Layout _layout, class _Matrix> class DenseMatrixIdxIteratorBase;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix iterator traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
/// @tparam  _Matrix  The matrix type.
///
template <typename _Scalar, Layout _layout, class _Matrix>
struct Traits<DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>>
  : Traits<IteratorBase<DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>>> {
  using ScalarType        = _Scalar;
  using IdxTupleType      = IdxTuple<2>;
  using ContainerType     = _Matrix;
  using BaseType          = DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>;
  using ValueIteratorType = DenseMatrixValueIteratorBase<_Scalar, _layout, _Matrix>;
  using IdxIteratorType   = DenseMatrixIdxIteratorBase<_Scalar, _layout, _Matrix>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix iterator traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
/// @tparam  _Matrix  The matrix type.
///
template <typename _Scalar, Layout _layout, class _Matrix>
struct Traits<DenseMatrixValueIteratorBase<_Scalar, _layout, _Matrix>>
  : Traits<DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>> {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix index iterator traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
/// @tparam  _Matrix  The matrix type.
///
template <typename _Scalar, Layout _layout, class _Matrix>
struct Traits<DenseMatrixIdxIteratorBase<_Scalar, _layout, _Matrix>>
  : Traits<DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>> {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix iterator.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
/// @tparam  _Matrix  The matrix type.
///
template <typename _Scalar, Layout _layout, class _Matrix>
class DenseMatrixIteratorBase : public IteratorBase<DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>> {

 protected:

  using IteratorBase<DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>>::itidx_;
  using IteratorBase<DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>>::container_;

 public:

  using IteratorBase<DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>>::IteratorBase;

  // Operators
  template <typename __Scalar, Layout __layout, class __Matrix>
  friend inline std::ostream& operator<<( std::ostream &out,
                                          const DenseMatrixIteratorBase<__Scalar, __layout, __Matrix> &iterator );

  // Gets value
  inline       _Scalar&    getValue() noexcept;
  inline const _Scalar&    getValue() const noexcept;
  inline       IdxTuple<2> getIdxs() const noexcept;
  inline       index_t     getRowIdx() const noexcept;
  inline       index_t     getColIdx() const noexcept;
  inline       index_t     getIdx1() const noexcept;
  inline       index_t     getIdx2() const noexcept;
  inline       index_t     getPos() const noexcept;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix iterator.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
/// @tparam  _Matrix  The matrix type.
///
template <typename _Scalar, Layout _layout, class _Matrix>
class DenseMatrixValueIteratorBase
  : public DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>,
    public ValueIteratorBase<DenseMatrixValueIteratorBase<_Scalar, _layout, _Matrix>> {

 public:

  using DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::DenseMatrixIteratorBase;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix iterator.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
/// @tparam  _Matrix  The matrix type.
///
template <typename _Scalar, Layout _layout, class _Matrix>
class DenseMatrixIdxIteratorBase
  : public DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>,
    public IdxIteratorBase<DenseMatrixIdxIteratorBase<_Scalar, _layout, _Matrix>> {

 public:

  using DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::DenseMatrixIteratorBase;

};

}  // namespace detail

template <typename _Scalar, Layout _layout>
using DenseMatrixIterator =
    detail::DenseMatrixValueIteratorBase<_Scalar, _layout, DenseMatrix<_Scalar, _layout>>;

template <typename _Scalar, Layout _layout>
using DenseMatrixConstIterator =
    detail::DenseMatrixValueIteratorBase<const _Scalar, _layout, const DenseMatrix<_Scalar, _layout>>;

template <typename _Scalar, Layout _layout>
using DenseMatrixIdxIterator =
    detail::DenseMatrixIdxIteratorBase<_Scalar, _layout, DenseMatrix<_Scalar, _layout>>;

template <typename _Scalar, Layout _layout>
using DenseMatrixConstIdxIterator =
    detail::DenseMatrixIdxIteratorBase<const _Scalar, _layout, const DenseMatrix<_Scalar, _layout>>;

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_HPP_
