////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/base/iterator_base.ipp
/// @brief   The implementation of iterator interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_BASE_ITERATOR_BASE_IPP_
#define ISVD_MATRIX_BASE_ITERATOR_BASE_IPP_

#include <isvd/matrix/base/iterator_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <class _Derived>
IteratorBase<_Derived>::IteratorBase() noexcept
  : itidx_(0),
    container_(nullptr) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given container.
///
template <class _Derived>
IteratorBase<_Derived>::IteratorBase(
    ContainerType *container,
    const index_t itidx
) noexcept
  : itidx_(itidx),
    container_(container) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
template <class _Derived>
IteratorBase<_Derived>::IteratorBase(
    const IteratorBase &other
) noexcept
  : itidx_(other.itidx_),
    container_(other.container_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
template <class _Derived>
_Derived& IteratorBase<_Derived>::operator=(
    const IteratorBase &other
) noexcept {
  itidx_ = other.itidx_; container_ = other.container_;
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Equal-to operator.
///
template <class _Derived>
bool IteratorBase<_Derived>::operator==(
    const IteratorBase &other
) const noexcept {
  assert(container_ == other.container_);
  return (container_ == other.container_) && (itidx_ == other.itidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Not-equal-to operator.
///
template <class _Derived>
bool IteratorBase<_Derived>::operator!=(
    const IteratorBase &other
) const noexcept {
  return !(*this == other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Greater-than operator.
///
template <class _Derived>
bool IteratorBase<_Derived>::operator>(
    const IteratorBase &other
) const noexcept {
  assert(container_ == other.container_);
  return (itidx_ > other.itidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Less-than operator.
///
template <class _Derived>
bool IteratorBase<_Derived>::operator<(
    const IteratorBase &other
) const noexcept {
  assert(container_ == other.container_);
  return (itidx_ < other.itidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Less-than or equal-to operator.
///
template <class _Derived>
bool IteratorBase<_Derived>::operator<=(
    const IteratorBase &other
) const noexcept {
  return !(*this > other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Greater-than or equal-to operator.
///
template <class _Derived>
bool IteratorBase<_Derived>::operator>=(
    const IteratorBase &other
) const noexcept {
  return !(*this < other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Prefix increment operator.
///
template <class _Derived>
_Derived& IteratorBase<_Derived>::operator++() noexcept {
  assert(container_ != nullptr);

  const auto nelem = container_->getNelem();
  if ( ++itidx_ >= nelem ) {
    itidx_ = nelem;
  }
  return static_cast<_Derived&>(static_cast<typename Traits<_Derived>::BaseType&>(*this));
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Prefix decrement operator.
///
template <class _Derived>
_Derived& IteratorBase<_Derived>::operator--() noexcept {
  assert(container_ != nullptr);

  const auto nelem = container_->getNelem();
  if ( --itidx_ >= nelem ) {
    itidx_ = nelem;
  }
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Postfix increment operator.
///
template <class _Derived>
_Derived IteratorBase<_Derived>::operator++( int ) noexcept {
  auto retval(*this);
  ++(*this);
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Postfix decrement operator.
///
template <class _Derived>
_Derived IteratorBase<_Derived>::operator--( int ) noexcept {
  auto retval(*this);
  --(*this);
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Addition operator.
///
template <class _Derived>
_Derived& IteratorBase<_Derived>::operator+=( const index_t num ) noexcept {
  assert(container_ != nullptr);

  const auto nelem = container_->getNelem();
  if ( (itidx_+=num) >= nelem ) {
    itidx_ = nelem;
  }
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Subtraction operator.
///
template <class _Derived>
_Derived& IteratorBase<_Derived>::operator-=( const index_t num ) noexcept {
  assert(container_ != nullptr);

  const auto nelem = container_->getNelem();
  if ( (itidx_-=num) >= nelem ) {
    itidx_ = nelem;
  }
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Addition assignment operator.
///
template <class _Derived>
_Derived IteratorBase<_Derived>::operator+( const index_t num ) const noexcept {
  auto retval(*this);
  return (retval += num);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Subtraction assignment operator.
///
template <class _Derived>
_Derived IteratorBase<_Derived>::operator-( const index_t num ) const noexcept {
  auto retval(*this);
  return (retval -= num);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Subtraction assignment operator.
///
template <class _Derived>
index_t IteratorBase<_Derived>::operator-( const IteratorBase &other ) const noexcept {
  assert(container_ != nullptr);
  return (this->itidx_ - other.itidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Addition assignment operator.
///
template <class __Derived>
__Derived operator+(
    const index_t num,
    const IteratorBase<__Derived> &iterator
) noexcept {
  return iterator + num;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the iterator index.
///
template <class _Derived>
index_t IteratorBase<_Derived>::getItIdx() const noexcept {
  return itidx_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the container.
///
template <class _Derived>
typename IteratorBase<_Derived>::ContainerType* IteratorBase<_Derived>::getContainer() const noexcept {
  return container_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the to beginning iterator.
///
template <class _Derived>
_Derived IteratorBase<_Derived>::getBegin( ContainerType *container ) noexcept {
  _Derived retval(container); retval.setBegin(); return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the to end iterator.
///
template <class _Derived>
_Derived IteratorBase<_Derived>::getEnd( ContainerType *container ) noexcept {
  _Derived retval(container); retval.setEnd(); return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Change to derived class.
///
template <class _Derived>
_Derived& IteratorBase<_Derived>::derived() noexcept {
  return static_cast<_Derived&>(static_cast<BaseIteratorType&>(*this));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  derived
///
template <class _Derived>
const _Derived& IteratorBase<_Derived>::derived() const noexcept {
  return static_cast<const _Derived&>(static_cast<const BaseIteratorType&>(*this));
}

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_BASE_ITERATOR_BASE_IPP_
