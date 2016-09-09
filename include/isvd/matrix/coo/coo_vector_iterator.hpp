////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/coo/coo_vector_iterator.hpp
/// @brief   The COO vector iterator class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_COO_COO_VECTOR_ITERATOR_HPP_
#define ISVD_MATRIX_COO_COO_VECTOR_ITERATOR_HPP_

#include <isvd/isvd.hpp>
#include <iterator>
#include <isvd/matrix/coo/coo_vector.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

template <typename _Scalar> class CooVector;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) vector iterator.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
class CooVectorIterator : public std::iterator<std::forward_iterator_tag, _Scalar> {

 protected:

  /// The internal position.
  index_t pos_;

  /// The vector.
  CooVector<_Scalar> *vector_;

 public:

  // Constructors
  CooVectorIterator() noexcept;
  CooVectorIterator( CooVector<_Scalar> *vector ) noexcept;
  CooVectorIterator( const CooVectorIterator &other ) noexcept;

  // Operators
  inline CooVectorIterator& operator=( const CooVectorIterator &other ) noexcept;
  inline bool operator==( const CooVectorIterator &other ) const noexcept;
  inline bool operator!=( const CooVectorIterator &other ) const noexcept;
  inline CooVectorIterator& operator++() noexcept;
  inline CooVectorIterator& operator++( int ) noexcept;
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
  inline CooVectorIterator& setBegin() noexcept;
  inline CooVectorIterator& setEnd() noexcept;

  // Gets the begin/end iterator
  static inline       CooVectorIterator begin( CooVector<_Scalar> *vector ) noexcept;
  static inline const CooVectorIterator begin( const CooVector<_Scalar> *vector ) noexcept;
  static inline       CooVectorIterator end( CooVector<_Scalar> *vector ) noexcept;
  static inline const CooVectorIterator end( const CooVector<_Scalar> *vector ) noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_COO_COO_VECTOR_ITERATOR_HPP_
