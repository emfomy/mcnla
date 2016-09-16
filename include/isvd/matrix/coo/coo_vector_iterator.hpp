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

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar> class CooVector;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) vector iterator.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar, typename _Index, class _Vector>
class CooVectorIteratorBase : public std::iterator<std::forward_iterator_tag, _Scalar> {

 protected:

  /// The iterator index.
  index_t itidx_;

  /// The vector.
  _Vector *container_;

 public:

  // Constructors
  inline CooVectorIteratorBase() noexcept;
  inline CooVectorIteratorBase( _Vector *vector, const index_t pos = 0 ) noexcept;
  inline CooVectorIteratorBase( const CooVectorIteratorBase &other ) noexcept;

  // Operators
  inline CooVectorIteratorBase& operator=( const CooVectorIteratorBase &other ) noexcept;
  inline bool operator==( const CooVectorIteratorBase &other ) const noexcept;
  inline bool operator!=( const CooVectorIteratorBase &other ) const noexcept;
  inline CooVectorIteratorBase& operator++() noexcept;
  inline CooVectorIteratorBase  operator++( int ) noexcept;
  inline       _Scalar& operator*() noexcept;
  inline const _Scalar& operator*() const noexcept;
  inline       _Scalar* operator->() noexcept;
  inline const _Scalar* operator->() const noexcept;

  // Gets value
  inline       _Scalar& getValue() noexcept;
  inline const _Scalar& getValue() const noexcept;
  inline       _Index& getIdx() noexcept;
  inline const _Index& getIdx() const noexcept;
  inline       index_t getPos() const noexcept;

  // Sets to begin/end
  inline CooVectorIteratorBase& setBegin() noexcept;
  inline CooVectorIteratorBase& setEnd() noexcept;

  // Gets the begin/end iterator
  static inline CooVectorIteratorBase getBegin( _Vector *vector ) noexcept;
  static inline CooVectorIteratorBase getEnd( _Vector *vector ) noexcept;

};

}  // namespace internal

template <typename _Scalar>
using CooVectorIterator = internal::CooVectorIteratorBase<_Scalar, index_t, CooVector<_Scalar>>;

template <typename _Scalar>
using CooVectorConstIterator = internal::CooVectorIteratorBase<const _Scalar, const index_t, const CooVector<_Scalar>>;

}  // namespace isvd

#endif  // ISVD_MATRIX_COO_COO_VECTOR_ITERATOR_HPP_
