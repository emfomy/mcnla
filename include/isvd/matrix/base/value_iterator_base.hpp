////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/base/value_iterator_base.hpp
/// @brief   The value iterator interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_BASE_VALUE_ITERATOR_BASE_HPP_
#define ISVD_MATRIX_BASE_VALUE_ITERATOR_BASE_HPP_

#include <isvd/isvd.hpp>
#include <iterator>
#include <isvd/utility/crtp.hpp>
#include <isvd/utility/traits.hpp>

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
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class ValueIteratorBase
  : protected CrtpBase<_Derived, ValueIteratorBase<_Derived>>,
    public std::iterator<typename Traits<_Derived>::IteratorTag, typename Traits<_Derived>::ScalarType> {

 private:

  using ScalarType        = typename Traits<_Derived>::ScalarType;
  using ContainerType     = typename Traits<_Derived>::ContainerType;
  using ValueIteratorType = _Derived;
  using BaseIteratorType  = typename Traits<_Derived>::BaseType;
  using IdxIteratorType   = typename Traits<_Derived>::IdxIteratorType;

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
  inline IdxIteratorType& toIdxIterator() noexcept;

  // Gets the begin/end iterator
  static inline ValueIteratorType getBegin( ContainerType *container ) noexcept;
  static inline ValueIteratorType getEnd( ContainerType *container ) noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_BASE_VALUE_ITERATOR_BASE_HPP_
