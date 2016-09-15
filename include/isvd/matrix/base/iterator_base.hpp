////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/base/iterator_base.hpp
/// @brief   The iterator interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_ITERATOR_BASE_HPP_
#define ISVD_MATRIX_ITERATOR_BASE_HPP_

#include <isvd/isvd.hpp>
#include <iterator>
#include <isvd/utility/crtp.hpp>
#include <isvd/utility/traits.hpp>
#include <isvd/matrix/kit/idx_tuple.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of value iterator.
///
/// @tparam  _Derived  The implementation type.
///
template <class _Derived>
class ValueIteratorBase :
    protected CrtpBase<_Derived, ValueIteratorBase<_Derived>>,
    public std::iterator<std::random_access_iterator_tag, typename Traits<_Derived>::ScalarType> {

 private:

  using ScalarType        = typename Traits<_Derived>::ScalarType;
  using ContainerType     = typename Traits<_Derived>::ContainerType;
  using ValueIteratorType = _Derived;
  using BaseIteratorType  = typename Traits<_Derived>::BaseType;
  using IdxIteratorType   = typename Traits<_Derived>::BaseType::IdxIteratorType;

 protected:

  // Constructors
  inline ValueIteratorBase() noexcept {};

 public:

  // Operators
  inline       ScalarType& operator*() noexcept;
  inline const ScalarType& operator*() const noexcept;
  inline       ScalarType* operator->() noexcept;
  inline const ScalarType* operator->() const noexcept;

  // Gets the index iterator
  inline IdxIteratorType& getIdxIterator() noexcept;

  // Gets the begin/end iterator
  static inline ValueIteratorType getBegin( ContainerType *container ) noexcept;
  static inline ValueIteratorType getEnd( ContainerType *container ) noexcept;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of index iterator.
///
/// @tparam  _Derived  The implementation type.
///
template <class _Derived>
class IdxIteratorBase :
    protected CrtpBase<_Derived, IdxIteratorBase<_Derived>>,
    public std::iterator<std::random_access_iterator_tag, typename Traits<_Derived>::IdxTupleType> {

 private:

  using IdxTupleType      = typename Traits<_Derived>::IdxTupleType;
  using ContainerType     = typename Traits<_Derived>::ContainerType;
  using IdxIteratorType   = _Derived;
  using BaseIteratorType  = typename Traits<_Derived>::BaseType;
  using ValueIteratorType = typename Traits<_Derived>::BaseType::ValueIteratorType;

 protected:

  // Constructors
  IdxIteratorBase() noexcept {};

 public:

  // Operators
  inline IdxTupleType operator*() const noexcept;

  // Gets the value iterator
  inline ValueIteratorType& getValueIterator() noexcept;

  // Gets the begin/end iterator
  static inline IdxIteratorType getBegin( ContainerType *container ) noexcept;
  static inline IdxIteratorType getEnd( ContainerType *container ) noexcept;

 private:

  // Operators
  inline void operator->() const noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_ITERATOR_BASE_HPP_
