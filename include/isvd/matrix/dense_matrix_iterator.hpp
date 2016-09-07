////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_matrix_iterator.hpp
/// @brief   The dense matrix iterator class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_MATRIX_ITERATOR_HPP_
#define ISVD_MATRIX_DENSE_MATRIX_ITERATOR_HPP_

#include <iterator>
#include <isvd/isvd.hpp>
#include <isvd/matrix/dense_matrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

template <typename _Scalar, Layout _layout> class DenseMatrix;

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
template <typename _Scalar, Layout _layout>
class DenseMatrixIterator : public std::iterator<std::forward_iterator_tag, _Scalar> {

 protected:

  /// The leading index.
  index_t idx1_;

  /// The second index.
  index_t idx2_;

  /// The row index.
  index_t &rowidx_ = isColMajor(_layout) ? idx1_ : idx2_;

  /// The column index.
  index_t &colidx_ = isColMajor(_layout) ? idx2_ : idx1_;

  /// The matrix.
  DenseMatrix<_Scalar, _layout> *matrix_;

 public:

  // Constructors
  DenseMatrixIterator() noexcept;
  DenseMatrixIterator( DenseMatrix<_Scalar, _layout> *matrix ) noexcept;
  DenseMatrixIterator( const DenseMatrixIterator &other ) noexcept;

  // Operators
  inline DenseMatrixIterator& operator=( const DenseMatrixIterator &other ) noexcept;
  inline bool operator==( const DenseMatrixIterator &other ) const noexcept;
  inline bool operator!=( const DenseMatrixIterator &other ) const noexcept;
  inline DenseMatrixIterator& operator++() noexcept;
  inline DenseMatrixIterator& operator++( int ) noexcept;
  inline       _Scalar& operator*() noexcept;
  inline const _Scalar& operator*() const noexcept;
  inline       _Scalar* operator->() noexcept;
  inline const _Scalar* operator->() const noexcept;

  // Gets value
  inline       _Scalar& getValue() noexcept;
  inline const _Scalar& getValue() const noexcept;
  inline       index_t getRowIdx() noexcept;
  inline       index_t getColIdx() noexcept;
  inline       index_t getIdx1() noexcept;
  inline       index_t getIdx2() noexcept;

  // Sets to begin & end
  inline DenseMatrixIterator& setBegin() noexcept;
  inline DenseMatrixIterator& setEnd() noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_MATRIX_ITERATOR_HPP_
