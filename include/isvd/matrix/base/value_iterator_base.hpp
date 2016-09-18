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
  : public std::iterator<typename Traits<_Derived>::IteratorTag, typename Traits<_Derived>::ScalarType> {

 private:

  using ScalarType      = typename Traits<_Derived>::ScalarType;
  using IdxIteratorType = typename Traits<_Derived>::IdxIteratorType;

 protected:

  // Constructors
  inline ValueIteratorBase() noexcept {};

 public:

  // Operators
  inline ScalarType& operator*() const noexcept;
  inline ScalarType* operator->() const noexcept;

  // Gets the index iterator
  inline       IdxIteratorType toIdxIterator() noexcept;
  inline const IdxIteratorType toIdxIterator() const noexcept;

 protected:

  // Gets derived class
  inline       _Derived& derived() noexcept;
  inline const _Derived& derived() const noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_BASE_VALUE_ITERATOR_BASE_HPP_
