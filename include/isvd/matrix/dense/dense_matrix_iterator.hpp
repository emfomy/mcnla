////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense/dense_matrix_iterator.hpp
/// @brief   The dense matrix iterator class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_HPP_
#define ISVD_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_HPP_

#include <isvd/isvd.hpp>
#include <iterator>
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix iterator.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
///
template <typename _Scalar, Layout _layout, class _Matrix>
class DenseMatrixIteratorBase : public std::iterator<std::forward_iterator_tag, _Scalar> {

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
  _Matrix *matrix_;

 public:

  // Constructors
  DenseMatrixIteratorBase() noexcept;
  DenseMatrixIteratorBase( _Matrix *matrix ) noexcept;
  DenseMatrixIteratorBase( _Matrix *matrix, const index_t rowidx, const index_t colidx ) noexcept;
  DenseMatrixIteratorBase( const DenseMatrixIteratorBase &other ) noexcept;

  // Operators
  inline DenseMatrixIteratorBase& operator=( const DenseMatrixIteratorBase &other ) noexcept;
  inline bool operator==( const DenseMatrixIteratorBase &other ) const noexcept;
  inline bool operator!=( const DenseMatrixIteratorBase &other ) const noexcept;
  inline DenseMatrixIteratorBase& operator++() noexcept;
  inline DenseMatrixIteratorBase  operator++( int ) noexcept;
  inline       _Scalar& operator*() noexcept;
  inline const _Scalar& operator*() const noexcept;
  inline       _Scalar* operator->() noexcept;
  inline const _Scalar* operator->() const noexcept;

  // Gets value
  inline       _Scalar& getValue() noexcept;
  inline const _Scalar& getValue() const noexcept;
  inline       index_t getRowIdx() const noexcept;
  inline       index_t getColIdx() const noexcept;
  inline       index_t getIdx1() const noexcept;
  inline       index_t getIdx2() const noexcept;
  inline       index_t getPos() const noexcept;

  // Sets to begin/end
  inline DenseMatrixIteratorBase& setBegin() noexcept;
  inline DenseMatrixIteratorBase& setEnd() noexcept;

  // Gets the begin/end iterator
  static inline DenseMatrixIteratorBase getBegin( _Matrix *matrix ) noexcept;
  static inline DenseMatrixIteratorBase getEnd( _Matrix *matrix ) noexcept;

};

}  // namespace internal

template <typename _Scalar, Layout _layout>
using DenseMatrixIterator = internal::DenseMatrixIteratorBase<_Scalar, _layout, DenseMatrix<_Scalar, _layout>>;

template <typename _Scalar, Layout _layout>
using DenseMatrixConstIterator = internal::DenseMatrixIteratorBase<const _Scalar, _layout, const DenseMatrix<_Scalar, _layout>>;

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_HPP_
