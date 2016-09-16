////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense/dense_matrix_iterator.hpp
/// @brief   The dense matrix iterator class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_HPP_
#define ISVD_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_HPP_

#include <isvd/isvd.hpp>
#include <isvd/matrix/base/iterator_base.hpp>
#include <isvd/matrix/dense/dense_matrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Layout _layout> class DenseMatrix;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

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
struct Traits<DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>> {
  using ScalarType        = _Scalar;
  using IdxTupleType      = IdxTuple<2>;
  using ContainerType     = _Matrix;
  using BaseType          = DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>;
  using ValueIteratorType = DenseMatrixValueIteratorBase<_Scalar, _layout, _Matrix>;
  using IdxIteratorType   = DenseMatrixIdxIteratorBase<_Scalar, _layout, _Matrix>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix value iterator traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
/// @tparam  _Matrix  The matrix type.
///
template <typename _Scalar, Layout _layout, class _Matrix>
struct Traits<DenseMatrixValueIteratorBase<_Scalar, _layout, _Matrix>>
  : Traits<DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>> {
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix index iterator traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
/// @tparam  _Matrix  The matrix type.
///
template <typename _Scalar, Layout _layout, class _Matrix>
struct Traits<DenseMatrixIdxIteratorBase<_Scalar, _layout, _Matrix>>
  : Traits<DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>> {
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix iterator.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
/// @tparam  _Matrix  The matrix type.
///
template <typename _Scalar, Layout _layout, class _Matrix>
class DenseMatrixIteratorBase {

 public:

  using ValueIteratorType = DenseMatrixValueIteratorBase<_Scalar, _layout, _Matrix>;
  using IdxIteratorType   = DenseMatrixIdxIteratorBase<_Scalar, _layout, _Matrix>;

 protected:

  /// The row index.
  index_t rowidx_;

  /// The column index.
  index_t colidx_;

  /// The leading index.
  index_t &idx1_ = isColMajor(_layout) ? rowidx_ : colidx_;

  /// The second index.
  index_t &idx2_ = isColMajor(_layout) ? colidx_ : rowidx_;

  /// The matrix.
  _Matrix *container_;

 public:

  // Constructors
  inline DenseMatrixIteratorBase() noexcept;
  inline DenseMatrixIteratorBase( _Matrix *matrix ) noexcept;
  inline DenseMatrixIteratorBase( _Matrix *matrix, const index_t rowidx, const index_t colidx ) noexcept;
  inline DenseMatrixIteratorBase( const DenseMatrixIteratorBase &other ) noexcept;

  // Operators
  inline DenseMatrixIteratorBase& operator=( const DenseMatrixIteratorBase &other ) noexcept;
  inline bool operator==( const DenseMatrixIteratorBase &other ) const noexcept;
  inline bool operator!=( const DenseMatrixIteratorBase &other ) const noexcept;
  inline DenseMatrixIteratorBase& operator++() noexcept;
  inline DenseMatrixIteratorBase  operator++( int ) noexcept;

  // Gets value
  inline       _Scalar& getValue() noexcept;
  inline const _Scalar& getValue() const noexcept;
  inline       IdxTuple<2> getIdxs() const noexcept;
  inline       index_t getRowIdx() const noexcept;
  inline       index_t getColIdx() const noexcept;
  inline       index_t getIdx1() const noexcept;
  inline       index_t getIdx2() const noexcept;
  inline       index_t getPos() const noexcept;

  // Sets to begin/end
  inline DenseMatrixIteratorBase& setBegin() noexcept;
  inline DenseMatrixIteratorBase& setEnd() noexcept;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix value iterator.
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
/// The dense matrix value iterator.
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

}  // namespace internal

template <typename _Scalar, Layout _layout>
using DenseMatrixIterator =
    internal::DenseMatrixValueIteratorBase<_Scalar, _layout, DenseMatrix<_Scalar, _layout>>;

template <typename _Scalar, Layout _layout>
using DenseMatrixConstIterator =
    internal::DenseMatrixValueIteratorBase<const _Scalar, _layout, const DenseMatrix<_Scalar, _layout>>;

template <typename _Scalar, Layout _layout>
using DenseMatrixIdxIterator =
    internal::DenseMatrixIdxIteratorBase<_Scalar, _layout, DenseMatrix<_Scalar, _layout>>;

template <typename _Scalar, Layout _layout>
using DenseMatrixConstIdxIterator =
    internal::DenseMatrixIdxIteratorBase<const _Scalar, _layout, const DenseMatrix<_Scalar, _layout>>;

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_HPP_
