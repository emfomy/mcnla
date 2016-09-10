////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense/dense_vector_iterator.hpp
/// @brief   The dense vector iterator class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DENSE_VECTOR_ITERATOR_HPP_
#define ISVD_MATRIX_DENSE_DENSE_VECTOR_ITERATOR_HPP_

#include <isvd/isvd.hpp>
#include <iterator>
#include <isvd/matrix/dense/dense_vector.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

template <typename _Scalar> class DenseVector;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector iterator.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar, class _Vector>
class DenseVectorIteratorBase : public std::iterator<std::forward_iterator_tag, _Scalar> {

 protected:

  /// The index.
  index_t idx_;

  /// The vector.
  _Vector *vector_;

 public:

  // Constructors
  DenseVectorIteratorBase() noexcept;
  DenseVectorIteratorBase( _Vector *vector, const index_t idx = 0 ) noexcept;
  DenseVectorIteratorBase( const DenseVectorIteratorBase &other ) noexcept;

  // Operators
  inline DenseVectorIteratorBase& operator=( const DenseVectorIteratorBase &other ) noexcept;
  inline bool operator==( const DenseVectorIteratorBase &other ) const noexcept;
  inline bool operator!=( const DenseVectorIteratorBase &other ) const noexcept;
  inline DenseVectorIteratorBase& operator++() noexcept;
  inline DenseVectorIteratorBase  operator++( int ) noexcept;
  inline       _Scalar& operator*() noexcept;
  inline const _Scalar& operator*() const noexcept;
  inline       _Scalar* operator->() noexcept;
  inline const _Scalar* operator->() const noexcept;

  // Gets value
  inline       _Scalar& getValue() noexcept;
  inline const _Scalar& getValue() const noexcept;
  inline       index_t getIdx() const noexcept;
  inline       index_t getPos() const noexcept;

  // Sets to begin/end
  inline DenseVectorIteratorBase& setBegin() noexcept;
  inline DenseVectorIteratorBase& setEnd() noexcept;

  // Gets the begin/end iterator
  static inline DenseVectorIteratorBase getBegin( _Vector *vector ) noexcept;
  static inline DenseVectorIteratorBase getEnd( _Vector *vector ) noexcept;

};

}  // namespace internal

template <typename _Scalar>
using DenseVectorIterator = internal::DenseVectorIteratorBase<_Scalar, DenseVector<_Scalar>>;

template <typename _Scalar>
using DenseVectorConstIterator = internal::DenseVectorIteratorBase<const _Scalar, const DenseVector<_Scalar>>;

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_VECTOR_ITERATOR_HPP_
