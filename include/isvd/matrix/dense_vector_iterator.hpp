////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_vector_iterator.hpp
/// @brief   The dense vector iterator class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_VECTOR_ITERATOR_HPP_
#define ISVD_MATRIX_DENSE_VECTOR_ITERATOR_HPP_

#include <iterator>
#include <isvd/isvd.hpp>

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
template <typename _Scalar>
class DenseVectorIterator : public std::iterator<std::forward_iterator_tag, _Scalar> {

 protected:

  /// The offset of starting position.
  index_t idx_;

  DenseVector<_Scalar> *vector_;

 public:

  // Constructors
  DenseVectorIterator() noexcept;
  DenseVectorIterator( DenseVector<_Scalar> *vector ) noexcept;
  DenseVectorIterator( const DenseVectorIterator &other ) noexcept;

  // Operators
  inline DenseVectorIterator& operator=( const DenseVectorIterator &other ) noexcept;
  inline bool operator==( const DenseVectorIterator &other ) const noexcept;
  inline bool operator!=( const DenseVectorIterator &other ) const noexcept;
  inline DenseVectorIterator& operator++() noexcept;
  inline DenseVectorIterator& operator++( int ) noexcept;
  inline       _Scalar& operator*() noexcept;
  inline const _Scalar& operator*() const noexcept;
  inline       _Scalar* operator->() noexcept;
  inline const _Scalar* operator->() const noexcept;

  // Gets value
  inline       _Scalar& getValue() noexcept;
  inline const _Scalar& getValue() const noexcept;
  inline       index_t getIdx() noexcept;

  // Sets to begin & end
  inline DenseVectorIterator& setBegin() noexcept;
  inline DenseVectorIterator& setEnd() noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_VECTOR_ITERATOR_HPP_
