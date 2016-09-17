////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/base/idx_iterator_base.hpp
/// @brief   The index iterator interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_BASE_IDX_ITERATOR_BASE_HPP_
#define ISVD_MATRIX_BASE_IDX_ITERATOR_BASE_HPP_

#include <isvd/isvd.hpp>
#include <iterator>
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
/// The interface of index iterator.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class IdxIteratorBase
  : public std::iterator<typename Traits<_Derived>::IteratorTag, typename Traits<_Derived>::IdxTupleType> {

 private:

  using IdxTupleType      = typename Traits<_Derived>::IdxTupleType;
  using ValueIteratorType = typename Traits<_Derived>::ValueIteratorType;

 protected:

  // Constructors
  IdxIteratorBase() noexcept {};

 public:

  // Operators
  inline IdxTupleType operator*() const noexcept;

  // Gets the value iterator
  inline       ValueIteratorType toValueIterator() noexcept;
  inline const ValueIteratorType toValueIterator() const noexcept;

 protected:

  // Gets derived class
  inline       _Derived& derived() noexcept;
  inline const _Derived& derived() const noexcept;

 private:

  // Operators
  inline void operator->() const noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_BASE_IDX_ITERATOR_BASE_HPP_
