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
/// The interface of index iterator.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class IdxIteratorBase
  : protected CrtpBase<_Derived, IdxIteratorBase<_Derived>>,
    public std::iterator<typename Traits<_Derived>::IteratorTag, typename Traits<_Derived>::IdxTupleType> {

 private:

  using IdxTupleType      = typename Traits<_Derived>::IdxTupleType;
  using ContainerType     = typename Traits<_Derived>::ContainerType;
  using IdxIteratorType   = _Derived;
  using BaseIteratorType  = typename Traits<_Derived>::BaseType;
  using ValueIteratorType = typename Traits<_Derived>::ValueIteratorType;

 protected:

  // Constructors
  IdxIteratorBase() noexcept {};

 public:

  // Operators
  inline IdxTupleType operator*() const noexcept;

  // Gets the value iterator
  inline ValueIteratorType& toValueIterator() noexcept;

  // Gets the begin/end iterator
  static inline IdxIteratorType getBegin( ContainerType *container ) noexcept;
  static inline IdxIteratorType getEnd( ContainerType *container ) noexcept;

 private:

  // Operators
  inline void operator->() const noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_BASE_IDX_ITERATOR_BASE_HPP_
