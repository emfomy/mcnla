////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/base/iterator_base.hpp
/// @brief   The iterator interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_BASE_ITERATOR_BASE_HPP_
#define MCNLA_CORE_MATRIX_BASE_ITERATOR_BASE_HPP_

#include <mcnla/core/matrix/base/iterator_base.hh>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <class _Derived, class _Container, typename _Elem, typename _ElemRef, typename _ElemPtr>
IteratorBase<_Derived, _Container, _Elem, _ElemRef, _ElemPtr>::IteratorBase() noexcept
  : container_(nullptr),
    itidx_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given container.
///
template <class _Derived, class _Container, typename _Elem, typename _ElemRef, typename _ElemPtr>
IteratorBase<_Derived, _Container, _Elem, _ElemRef, _ElemPtr>::IteratorBase(
    _Container *container,
    const index_t itidx
) noexcept
  : container_(container),
    itidx_(itidx) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
template <class _Derived, class _Container, typename _Elem, typename _ElemRef, typename _ElemPtr>
IteratorBase<_Derived, _Container, _Elem, _ElemRef, _ElemPtr>::IteratorBase(
    const IteratorBase &other
) noexcept
  : container_(other.container_),
    itidx_(other.itidx_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
template <class _Derived, class _Container, typename _Elem, typename _ElemRef, typename _ElemPtr>
_Derived& IteratorBase<_Derived, _Container, _Elem, _ElemRef, _ElemPtr>::operator=(
    const IteratorBase &other
) noexcept {
  container_ = other.container_; itidx_ = other.itidx_;
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Indirection operator
///
/// @attention  Never call this method when the iterator is at the end.
///
template <class _Derived, class _Container, typename _Elem, typename _ElemRef, typename _ElemPtr>
_ElemRef IteratorBase<_Derived, _Container, _Elem, _ElemRef, _ElemPtr>::operator*() const noexcept {
  return derived().elemRef();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Indirection operator
///
/// @attention  Never call this method when the iterator is at the end.
///
template <class _Derived, class _Container, typename _Elem, typename _ElemRef, typename _ElemPtr>
_ElemPtr IteratorBase<_Derived, _Container, _Elem, _ElemRef, _ElemPtr>::operator->() const noexcept {
  return derived().elemPtr();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Equal-to operator.
///
template <class _Derived, class _Container, typename _Elem, typename _ElemRef, typename _ElemPtr>
bool IteratorBase<_Derived, _Container, _Elem, _ElemRef, _ElemPtr>::operator==(
    const IteratorBase &other
) const noexcept {
  mcnla_assert_eq(container_, other.container_);
  return (itidx_ == other.itidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Not-equal-to operator.
///
template <class _Derived, class _Container, typename _Elem, typename _ElemRef, typename _ElemPtr>
bool IteratorBase<_Derived, _Container, _Elem, _ElemRef, _ElemPtr>::operator!=(
    const IteratorBase &other
) const noexcept {
  return !(*this == other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Greater-than operator.
///
template <class _Derived, class _Container, typename _Elem, typename _ElemRef, typename _ElemPtr>
bool IteratorBase<_Derived, _Container, _Elem, _ElemRef, _ElemPtr>::operator>(
    const IteratorBase &other
) const noexcept {
  mcnla_assert_eq(container_, other.container_);
  return (itidx_ > other.itidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Less-than operator.
///
template <class _Derived, class _Container, typename _Elem, typename _ElemRef, typename _ElemPtr>
bool IteratorBase<_Derived, _Container, _Elem, _ElemRef, _ElemPtr>::operator<(
    const IteratorBase &other
) const noexcept {
  mcnla_assert_eq(container_, other.container_);
  return (itidx_ < other.itidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Less-than or equal-to operator.
///
template <class _Derived, class _Container, typename _Elem, typename _ElemRef, typename _ElemPtr>
bool IteratorBase<_Derived, _Container, _Elem, _ElemRef, _ElemPtr>::operator<=(
    const IteratorBase &other
) const noexcept {
  return !(*this > other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Greater-than or equal-to operator.
///
template <class _Derived, class _Container, typename _Elem, typename _ElemRef, typename _ElemPtr>
bool IteratorBase<_Derived, _Container, _Elem, _ElemRef, _ElemPtr>::operator>=(
    const IteratorBase &other
) const noexcept {
  return !(*this < other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Prefix increment operator.
///
template <class _Derived, class _Container, typename _Elem, typename _ElemRef, typename _ElemPtr>
_Derived& IteratorBase<_Derived, _Container, _Elem, _ElemRef, _ElemPtr>::operator++() noexcept {
  mcnla_assert_ne(container_, nullptr);

  const auto nnz = container_->nnz();
  if ( ++itidx_ > nnz ) {
    itidx_ = nnz;
  }
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Prefix decrement operator.
///
template <class _Derived, class _Container, typename _Elem, typename _ElemRef, typename _ElemPtr>
_Derived& IteratorBase<_Derived, _Container, _Elem, _ElemRef, _ElemPtr>::operator--() noexcept {
  mcnla_assert_ne(container_, nullptr);

  if ( --itidx_ < 0 ) {
    itidx_ = 0;
  }
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Postfix increment operator.
///
template <class _Derived, class _Container, typename _Elem, typename _ElemRef, typename _ElemPtr>
_Derived IteratorBase<_Derived, _Container, _Elem, _ElemRef, _ElemPtr>::operator++( int ) noexcept {
  auto retval(*this);
  ++(*this);
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Postfix decrement operator.
///
template <class _Derived, class _Container, typename _Elem, typename _ElemRef, typename _ElemPtr>
_Derived IteratorBase<_Derived, _Container, _Elem, _ElemRef, _ElemPtr>::operator--( int ) noexcept {
  auto retval(*this);
  --(*this);
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Addition operator.
///
template <class _Derived, class _Container, typename _Elem, typename _ElemRef, typename _ElemPtr>
_Derived& IteratorBase<_Derived, _Container, _Elem, _ElemRef, _ElemPtr>::operator+=(
    const index_t num
) noexcept {
  mcnla_assert_ne(container_, nullptr);
  mcnla_assert_ge(num, 0);

  const auto nnz = container_->nnz();
  if ( (itidx_+=num) > nnz ) {
    itidx_ = nnz;
  }
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Subtraction operator.
///
template <class _Derived, class _Container, typename _Elem, typename _ElemRef, typename _ElemPtr>
_Derived& IteratorBase<_Derived, _Container, _Elem, _ElemRef, _ElemPtr>::operator-=(
    const index_t num
) noexcept {
  mcnla_assert_ne(container_, nullptr);
  mcnla_assert_ge(num, 0);

  if ( (itidx_-=num) < 0 ) {
    itidx_ = 0;
  }
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Addition assignment operator.
///
template <class _Derived, class _Container, typename _Elem, typename _ElemRef, typename _ElemPtr>
_Derived IteratorBase<_Derived, _Container, _Elem, _ElemRef, _ElemPtr>::operator+(
    const index_t num
) const noexcept {
  auto retval(*this);
  return (retval += num);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Subtraction assignment operator.
///
template <class _Derived, class _Container, typename _Elem, typename _ElemRef, typename _ElemPtr>
_Derived IteratorBase<_Derived, _Container, _Elem, _ElemRef, _ElemPtr>::operator-(
    const index_t num
) const noexcept {
  auto retval(*this);
  return (retval -= num);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Subtraction assignment operator.
///
template <class _Derived, class _Container, typename _Elem, typename _ElemRef, typename _ElemPtr>
index_t IteratorBase<_Derived, _Container, _Elem, _ElemRef, _ElemPtr>::operator-(
    const IteratorBase &other
) const noexcept {
  mcnla_assert_ne(container_, nullptr);
  return (this->itidx_ - other.itidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Addition assignment operator.
///
template <class __Derived, typename ...__Args>
__Derived operator+(
    const index_t num,
    const IteratorBase<__Derived, __Args...> &it
) noexcept {
  return (it + num);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the iterator index.
///
template <class _Derived, class _Container, typename _Elem, typename _ElemRef, typename _ElemPtr>
index_t IteratorBase<_Derived, _Container, _Elem, _ElemRef, _ElemPtr>::itidx() const noexcept {
  return itidx_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the container.
///
template <class _Derived, class _Container, typename _Elem, typename _ElemRef, typename _ElemPtr>
_Container* IteratorBase<_Derived, _Container, _Elem, _ElemRef, _ElemPtr>::container() const noexcept {
  return container_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the iterator to beginning.
///
template <class _Derived, class _Container, typename _Elem, typename _ElemRef, typename _ElemPtr>
_Derived& IteratorBase<_Derived, _Container, _Elem, _ElemRef, _ElemPtr>::setBegin() noexcept {
  itidx_ = 0;
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the iterator to end.
///
template <class _Derived, class _Container, typename _Elem, typename _ElemRef, typename _ElemPtr>
_Derived& IteratorBase<_Derived, _Container, _Elem, _ElemRef, _ElemPtr>::setEnd() noexcept {
  itidx_ = (container_ != nullptr) ? container_->nnz() : 0;
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the to beginning iterator.
///
template <class _Derived, class _Container, typename _Elem, typename _ElemRef, typename _ElemPtr>
_Derived IteratorBase<_Derived, _Container, _Elem, _ElemRef, _ElemPtr>::beginImpl(
    _Container *container
) noexcept {
  _Derived retval(container); retval.setBegin(); return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the to end iterator.
///
template <class _Derived, class _Container, typename _Elem, typename _ElemRef, typename _ElemPtr>
_Derived IteratorBase<_Derived, _Container, _Elem, _ElemRef, _ElemPtr>::endImpl(
    _Container *container
) noexcept {
  _Derived retval(container); retval.setEnd(); return retval;
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_BASE_ITERATOR_BASE_HPP_
