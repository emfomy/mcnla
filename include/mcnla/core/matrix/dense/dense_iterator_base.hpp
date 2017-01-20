////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_iterator_base.hpp
/// @brief   The dense iterator interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_ITERATOR_BASE_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_ITERATOR_BASE_HPP_

#include <mcnla/core/matrix/dense/dense_iterator_base.hh>

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
template <class _Derived>
DenseIteratorBase<_Derived>::DenseIteratorBase() noexcept
  : container_(nullptr),
    itidx_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given container.
///
template <class _Derived>
DenseIteratorBase<_Derived>::DenseIteratorBase(
    ContainerType *container,
    const index_t itidx
) noexcept
  : container_(container),
    itidx_(itidx) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
template <class _Derived>
DenseIteratorBase<_Derived>::DenseIteratorBase(
    const DenseIteratorBase &other
) noexcept
  : container_(other.container_),
    itidx_(other.itidx_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
template <class _Derived>
_Derived& DenseIteratorBase<_Derived>::operator=(
    const DenseIteratorBase &other
) noexcept {
  container_ = other.container_; itidx_ = other.itidx_;
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Indirection operator
///
/// @attention  Never call this when the iterator is at the end.
///
template <class _Derived>
ScalarT<_Derived>& DenseIteratorBase<_Derived>::operator*() const noexcept {
  return derived().value();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Indirection operator
///
/// @attention  Never call this when the iterator is at the end.
///
template <class _Derived>
ScalarT<_Derived>* DenseIteratorBase<_Derived>::operator->() const noexcept {
  return &(derived().value());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Equal-to operator.
///
template <class _Derived>
bool DenseIteratorBase<_Derived>::operator==(
    const DenseIteratorBase &other
) const noexcept {
  mcnla_assert_eq(container_, other.container_);
  return (itidx_ == other.itidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Not-equal-to operator.
///
template <class _Derived>
bool DenseIteratorBase<_Derived>::operator!=(
    const DenseIteratorBase &other
) const noexcept {
  return !(*this == other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Greater-than operator.
///
template <class _Derived>
bool DenseIteratorBase<_Derived>::operator>(
    const DenseIteratorBase &other
) const noexcept {
  mcnla_assert_eq(container_, other.container_);
  return (itidx_ > other.itidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Less-than operator.
///
template <class _Derived>
bool DenseIteratorBase<_Derived>::operator<(
    const DenseIteratorBase &other
) const noexcept {
  mcnla_assert_eq(container_, other.container_);
  return (itidx_ < other.itidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Less-than or equal-to operator.
///
template <class _Derived>
bool DenseIteratorBase<_Derived>::operator<=(
    const DenseIteratorBase &other
) const noexcept {
  return !(*this > other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Greater-than or equal-to operator.
///
template <class _Derived>
bool DenseIteratorBase<_Derived>::operator>=(
    const DenseIteratorBase &other
) const noexcept {
  return !(*this < other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Prefix increment operator.
///
template <class _Derived>
_Derived& DenseIteratorBase<_Derived>::operator++() noexcept {
  mcnla_assert_ne(container_, nullptr);

  const auto nidx = container_->nidx();
  if ( ++itidx_ > nidx ) {
    itidx_ = nidx;
  }
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Prefix decrement operator.
///
template <class _Derived>
_Derived& DenseIteratorBase<_Derived>::operator--() noexcept {
  mcnla_assert_ne(container_, nullptr);

  if ( --itidx_ < 0 ) {
    itidx_ = 0;
  }
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Postfix increment operator.
///
template <class _Derived>
_Derived DenseIteratorBase<_Derived>::operator++( int ) noexcept {
  auto retval(*this);
  ++(*this);
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Postfix decrement operator.
///
template <class _Derived>
_Derived DenseIteratorBase<_Derived>::operator--( int ) noexcept {
  auto retval(*this);
  --(*this);
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Addition operator.
///
template <class _Derived>
_Derived& DenseIteratorBase<_Derived>::operator+=(
    const index_t num
) noexcept {
  mcnla_assert_ne(container_, nullptr);
  mcnla_assert_ge(num, 0);

  const auto nidx = container_->nidx();
  if ( (itidx_+=num) > nidx ) {
    itidx_ = nidx;
  }
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Subtraction operator.
///
template <class _Derived>
_Derived& DenseIteratorBase<_Derived>::operator-=(
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
template <class _Derived>
_Derived DenseIteratorBase<_Derived>::operator+(
    const index_t num
) const noexcept {
  auto retval(*this);
  return (retval += num);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Subtraction assignment operator.
///
template <class _Derived>
_Derived DenseIteratorBase<_Derived>::operator-(
    const index_t num
) const noexcept {
  auto retval(*this);
  return (retval -= num);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Subtraction assignment operator.
///
template <class _Derived>
index_t DenseIteratorBase<_Derived>::operator-(
    const DenseIteratorBase &other
) const noexcept {
  mcnla_assert_ne(container_, nullptr);
  return (this->itidx_ - other.itidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Addition assignment operator.
///
template <class __Derived>
__Derived operator+(
    const index_t num,
    const DenseIteratorBase<__Derived> &iterator
) noexcept {
  return iterator + num;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the iterator index.
///
template <class _Derived>
index_t DenseIteratorBase<_Derived>::itidx() const noexcept {
  return itidx_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the container.
///
template <class _Derived>
ContainerT<_Derived>* DenseIteratorBase<_Derived>::container() const noexcept {
  return container_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the iterator to beginning.
///
template <class _Derived>
_Derived& DenseIteratorBase<_Derived>::setBegin() noexcept {
  itidx_ = 0;
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the iterator to end.
///
template <class _Derived>
_Derived& DenseIteratorBase<_Derived>::setEnd() noexcept {
  itidx_ = (container_ != nullptr) ? container_->nidx() : 0;
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the to beginning iterator.
///
template <class _Derived>
_Derived DenseIteratorBase<_Derived>::beginImpl(
    ContainerType *container
) noexcept {
  _Derived retval(container); retval.setBegin(); return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the to end iterator.
///
template <class _Derived>
_Derived DenseIteratorBase<_Derived>::endImpl(
    ContainerType *container
) noexcept {
  _Derived retval(container); retval.setEnd(); return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert to derived class.
///
template <class _Derived>
_Derived& DenseIteratorBase<_Derived>::derived() noexcept {
  return static_cast<_Derived&>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  derived
///
template <class _Derived>
const _Derived& DenseIteratorBase<_Derived>::derived() const noexcept {
  return static_cast<const _Derived&>(*this);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_ITERATOR_BASE_HPP_
