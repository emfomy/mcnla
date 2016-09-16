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
template <class _Container>
IteratorBase<_Container>::IteratorBase() noexcept
  : itidx_(0),
    container_(nullptr) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given container.
///
template <class _Container>
IteratorBase<_Container>::IteratorBase(
    _Container *container
) noexcept
  : itidx_(0),
    container_(container) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
template <class _Container>
IteratorBase<_Container>::IteratorBase(
    const IteratorBase &other
) noexcept
  : itidx_(other.itidx_),
    container_(other.container_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
template <class _Container>
IteratorBase<_Container>& IteratorBase<_Container>::operator=(
    const IteratorBase &other
) noexcept {
  itidx_ = other.itidx_; container_ = other.container_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Equal-to operator.
///
template <class _Container>
bool IteratorBase<_Container>::operator==(
    const IteratorBase &other
) const noexcept {
  assert(container_ == other.container_);
  return (container_ == other.container_) && (itidx_ == other.itidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Not-equal-to operator.
///
template <class _Container>
bool IteratorBase<_Container>::operator!=(
    const IteratorBase &other
) const noexcept {
  return !(*this == other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Greater-than operator.
///
template <class _Container>
bool IteratorBase<_Container>::operator>(
    const IteratorBase &other
) const noexcept {
  assert(container_ == other.container_);
  return (itidx_ > other.itidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Less-than operator.
///
template <class _Container>
bool IteratorBase<_Container>::operator<(
    const IteratorBase &other
) const noexcept {
  assert(container_ == other.container_);
  return (itidx_ < other.itidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Less-than or equal-to operator.
///
template <class _Container>
bool IteratorBase<_Container>::operator<=(
    const IteratorBase &other
) const noexcept {
  return !(*this > other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Greater-than or equal-to operator.
///
template <class _Container>
bool IteratorBase<_Container>::operator>=(
    const IteratorBase &other
) const noexcept {
  return !(*this < other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Prefix increment operator.
///
template <class _Container>
IteratorBase<_Container>& IteratorBase<_Container>::operator++() noexcept {
  assert(container_ != nullptr);

  const auto nelem = container_->getNelem();
  if ( ++itidx_ >= nelem ) {
    itidx_ = nelem;
  }
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Prefix decrement operator.
///
template <class _Container>
IteratorBase<_Container>& IteratorBase<_Container>::operator--() noexcept {
  assert(container_ != nullptr);

  const auto nelem = container_->getNelem();
  if ( --itidx_ >= nelem ) {
    itidx_ = nelem;
  }
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Postfix increment operator.
///
template <class _Container>
IteratorBase<_Container> IteratorBase<_Container>::operator++( int ) noexcept {
  auto retval(*this);
  ++(*this);
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Postfix decrement operator.
///
template <class _Container>
IteratorBase<_Container> IteratorBase<_Container>::operator--( int ) noexcept {
  auto retval(*this);
  --(*this);
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Addition operator.
///
template <class _Container>
IteratorBase<_Container>& IteratorBase<_Container>::operator+=( const index_t num ) noexcept {
  assert(container_ != nullptr);

  const auto nelem = container_->getNelem();
  if ( (itidx_+=num) >= nelem ) {
    itidx_ = nelem;
  }
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Subtraction operator.
///
template <class _Container>
IteratorBase<_Container>& IteratorBase<_Container>::operator-=( const index_t num ) noexcept {
  assert(container_ != nullptr);

  const auto nelem = container_->getNelem();
  if ( (itidx_-=num) >= nelem ) {
    itidx_ = nelem;
  }
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Addition assignment operator.
///
template <class _Container>
IteratorBase<_Container> IteratorBase<_Container>::operator+( const index_t num ) const noexcept {
  auto retval(*this);
  return (retval += num);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Subtraction assignment operator.
///
template <class _Container>
IteratorBase<_Container> IteratorBase<_Container>::operator-( const index_t num ) const noexcept {
  auto retval(*this);
  return (retval -= num);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Subtraction assignment operator.
///
template <class _Container>
index_t IteratorBase<_Container>::operator-( const IteratorBase &other ) const noexcept {
  assert(container_ != nullptr);
  return (this->itidx_ - other.itidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Addition assignment operator.
///
template <class __Container>
IteratorBase<__Container> operator+(
    const index_t num,
    const IteratorBase<__Container> &iterator
) noexcept {
  return iterator + num;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the iterator to beginning.
///
template <class _Container>
IteratorBase<_Container>& IteratorBase<_Container>::setBegin() noexcept {
  itidx_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the iterator to end.
///
template <class _Container>
IteratorBase<_Container>& IteratorBase<_Container>::setEnd() noexcept {
  itidx_ = (container_ != nullptr) ? container_->getNelem() : 0;
  return *this;
}

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_BASE_ITERATOR_BASE_IPP_
