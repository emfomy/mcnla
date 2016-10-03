////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_iterator_base.ipp
/// @brief   The implementation of COO iterator interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_ITERATOR_BASE_IPP_
#define MCNLA_CORE_MATRIX_COO_COO_ITERATOR_BASE_IPP_

#include <mcnla/core/matrix/coo/coo_iterator_base.hpp>

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
CooIteratorBase<_Derived>::CooIteratorBase() noexcept
  : container_(nullptr),
    itidx_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given container.
///
template <class _Derived>
CooIteratorBase<_Derived>::CooIteratorBase(
    ContainerType *container,
    const index_t itidx
) noexcept
  : container_(container),
    itidx_(itidx) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
template <class _Derived>
CooIteratorBase<_Derived>::CooIteratorBase(
    const CooIteratorBase &other
) noexcept
  : container_(other.container_),
    itidx_(other.itidx_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
template <class _Derived>
_Derived& CooIteratorBase<_Derived>::operator=(
    const CooIteratorBase &other
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
typename CooIteratorBase<_Derived>::TupleType CooIteratorBase<_Derived>::operator*() const noexcept {
  return getTuple();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Equal-to operator.
///
template <class _Derived>
bool CooIteratorBase<_Derived>::operator==(
    const CooIteratorBase &other
) const noexcept {
  assert(container_ == other.container_);
  return (itidx_ == other.itidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Not-equal-to operator.
///
template <class _Derived>
bool CooIteratorBase<_Derived>::operator!=(
    const CooIteratorBase &other
) const noexcept {
  return !(*this == other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Greater-than operator.
///
template <class _Derived>
bool CooIteratorBase<_Derived>::operator>(
    const CooIteratorBase &other
) const noexcept {
  assert(container_ == other.container_);
  return (itidx_ > other.itidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Less-than operator.
///
template <class _Derived>
bool CooIteratorBase<_Derived>::operator<(
    const CooIteratorBase &other
) const noexcept {
  assert(container_ == other.container_);
  return (itidx_ < other.itidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Less-than or equal-to operator.
///
template <class _Derived>
bool CooIteratorBase<_Derived>::operator<=(
    const CooIteratorBase &other
) const noexcept {
  return !(*this > other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Greater-than or equal-to operator.
///
template <class _Derived>
bool CooIteratorBase<_Derived>::operator>=(
    const CooIteratorBase &other
) const noexcept {
  return !(*this < other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Prefix increment operator.
///
template <class _Derived>
_Derived& CooIteratorBase<_Derived>::operator++() noexcept {
  assert(container_ != nullptr);

  const auto nnz = container_->getNnz();
  if ( ++itidx_ > nnz ) {
    itidx_ = nnz;
  }
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Prefix decrement operator.
///
template <class _Derived>
_Derived& CooIteratorBase<_Derived>::operator--() noexcept {
  assert(container_ != nullptr);

  if ( --itidx_ < 0 ) {
    itidx_ = 0;
  }
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Postfix increment operator.
///
template <class _Derived>
_Derived CooIteratorBase<_Derived>::operator++( int ) noexcept {
  auto retval(*this);
  ++(*this);
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Postfix decrement operator.
///
template <class _Derived>
_Derived CooIteratorBase<_Derived>::operator--( int ) noexcept {
  auto retval(*this);
  --(*this);
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Addition operator.
///
template <class _Derived>
_Derived& CooIteratorBase<_Derived>::operator+=( const index_t num ) noexcept {
  assert(container_ != nullptr);
  assert(num >= 0);

  const auto nnz = container_->getNnz();
  if ( (itidx_+=num) > nnz ) {
    itidx_ = nnz;
  }
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Subtraction operator.
///
template <class _Derived>
_Derived& CooIteratorBase<_Derived>::operator-=( const index_t num ) noexcept {
  assert(container_ != nullptr);
  assert(num >= 0);

  if ( (itidx_-=num) < 0 ) {
    itidx_ = 0;
  }
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Addition assignment operator.
///
template <class _Derived>
_Derived CooIteratorBase<_Derived>::operator+( const index_t num ) const noexcept {
  auto retval(*this);
  return (retval += num);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Subtraction assignment operator.
///
template <class _Derived>
_Derived CooIteratorBase<_Derived>::operator-( const index_t num ) const noexcept {
  auto retval(*this);
  return (retval -= num);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Subtraction assignment operator.
///
template <class _Derived>
index_t CooIteratorBase<_Derived>::operator-( const CooIteratorBase &other ) const noexcept {
  assert(container_ != nullptr);
  return (this->itidx_ - other.itidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Addition assignment operator.
///
template <class __Derived>
__Derived operator+(
    const index_t num,
    const CooIteratorBase<__Derived> &iterator
) noexcept {
  return iterator + num;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the iterator index.
///
template <class _Derived>
index_t CooIteratorBase<_Derived>::getItIdx() const noexcept {
  return itidx_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value.
///
/// @attention  Never call this when the iterator is at the end.
///
template <class _Derived>
typename CooIteratorBase<_Derived>::ScalarType& CooIteratorBase<_Derived>::getValue() const noexcept {
  assert(itidx_ >= 0 && itidx_ < container_->getNnz());
  return container_->getValue()[itidx_];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index.
///
/// @attention  Never call this when the iterator is at the end.
///
template <class _Derived> template <index_t _dim>
typename CooIteratorBase<_Derived>::IndexType& CooIteratorBase<_Derived>::getIdx() const noexcept {
  assert(itidx_ >= 0 && itidx_ < container_->getNnz());
  return container_->getIdx<_dim>()[itidx_];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the tuple.
///
/// @attention  Never call this when the iterator is at the end.
///
template <class _Derived>
typename CooIteratorBase<_Derived>::TupleType CooIteratorBase<_Derived>::getTuple() const noexcept {
  assert(itidx_ >= 0 && itidx_ < container_->getNnz());
  return container_->getTuple(itidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the container.
///
template <class _Derived>
typename CooIteratorBase<_Derived>::ContainerType* CooIteratorBase<_Derived>::getContainer() const noexcept {
  return container_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the iterator to beginning.
///
template <class _Derived>
_Derived& CooIteratorBase<_Derived>::setBegin() noexcept {
  itidx_ = 0;
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the iterator to end.
///
template <class _Derived>
_Derived& CooIteratorBase<_Derived>::setEnd() noexcept {
  itidx_ = (container_ != nullptr) ? container_->getNnz() : 0;
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the to beginning iterator.
///
template <class _Derived>
_Derived CooIteratorBase<_Derived>::getBegin( ContainerType *container ) noexcept {
  _Derived retval(container); retval.setBegin(); return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the to end iterator.
///
template <class _Derived>
_Derived CooIteratorBase<_Derived>::getEnd( ContainerType *container ) noexcept {
  _Derived retval(container); retval.setEnd(); return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Change to derived class.
///
template <class _Derived>
_Derived& CooIteratorBase<_Derived>::derived() noexcept {
  return static_cast<_Derived&>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  derived
///
template <class _Derived>
const _Derived& CooIteratorBase<_Derived>::derived() const noexcept {
  return static_cast<const _Derived&>(*this);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_ITERATOR_BASE_IPP_
