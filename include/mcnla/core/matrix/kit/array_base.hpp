////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/kit/array_base.hpp
/// @brief   The base array.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_KIT_ARRAY_BASE_HPP_
#define MCNLA_CORE_MATRIX_KIT_ARRAY_BASE_HPP_

#include <mcnla/core/matrix/kit/array_base.hh>

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
template <class _Core, typename _Val>
ArrayBase<_Core, _Val>::ArrayBase() noexcept
  : BaseType(),
    size_(0),
    offset_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <class _Core, typename _Val>
ArrayBase<_Core, _Val>::ArrayBase(
    const BaseType &ptr,
    const index_t size,
    const index_t offset
) noexcept
  : BaseType(ptr),
    size_(size),
    offset_(offset) {
  mcnla_assert_gele(offset_, 0, size_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy (creates an alias).
///
template <class _Core, typename _Val>
ArrayBase<_Core, _Val>::ArrayBase(
    const DerivedType &other
) noexcept
  : BaseType(other),
    size_(other.size_),
    offset_(other.offset_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy (creates an alias).
///
template <class _Core, typename _Val>
ArrS<_Core, _Val>& ArrayBase<_Core, _Val>::operator=(
    const DerivedType &other
) noexcept {
  BaseType::operator=(other);
  size_   = other.size_;
  offset_ = other.offset_;
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Right-shift the offset.
/// Add @a offset to @ref offset_.
///
template <class _Core, typename _Val>
ArrS<_Core, _Val>& ArrayBase<_Core, _Val>::operator>>=(
    const index_t offset
) noexcept {
  offset_ += offset;
  mcnla_assert_gele(offset_, 0, size_);
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Left-shift the offset.
/// Subtract @ref offset_ by @a offset.
///
template <class _Core, typename _Val>
ArrS<_Core, _Val>& ArrayBase<_Core, _Val>::operator<<=(
    const index_t offset
) noexcept {
  offset_ -= offset;
  mcnla_assert_gele(offset_, 0, size_);
  return derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator>>=
///
template <class _Core, typename _Val>
ArrS<_Core, _Val> ArrayBase<_Core, _Val>::operator>>(
    const index_t offset
) noexcept {
  auto retval = derived();
  retval >>= offset;
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator>>=
///
template <class _Core, typename _Val>
const ArrS<_Core, _Val> ArrayBase<_Core, _Val>::operator>>(
    const index_t offset
) const noexcept {
  auto retval = derived();
  retval >>= offset;
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator<<=
///
template <class _Core, typename _Val>
ArrS<_Core, _Val> ArrayBase<_Core, _Val>::operator<<(
    const index_t offset
) noexcept {
  auto retval = derived();
  retval <<= offset;
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator<<=
///
template <class _Core, typename _Val>
const ArrS<_Core, _Val> ArrayBase<_Core, _Val>::operator<<(
    const index_t offset
) const noexcept {
  auto retval = derived();
  retval <<= offset;
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the memory size is zero.
///
template <class _Core, typename _Val>
bool ArrayBase<_Core, _Val>::isEmpty() const noexcept {
  return (size_ == 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the memory size.
///
/// @note  #capacity + #offset = #size.
///
template <class _Core, typename _Val>
index_t ArrayBase<_Core, _Val>::size() const noexcept {
  return size_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the capacity.
///
/// @note  #capacity + #offset = #size.
///
template <class _Core, typename _Val>
index_t ArrayBase<_Core, _Val>::capacity() const noexcept {
  return size_ - offset_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the offset.
///
/// @note  #capacity + #offset = #size.
///
template <class _Core, typename _Val>
index_t ArrayBase<_Core, _Val>::offset() const noexcept {
  return offset_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the data pointer.
///
template <class _Core, typename _Val>
_Val* ArrayBase<_Core, _Val>::operator*() noexcept {
  return &(this->get()[offset_]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the data pointer.
///
template <class _Core, typename _Val>
const _Val* ArrayBase<_Core, _Val>::operator*() const noexcept {
  return &(this->get()[offset_]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the data of given index.
///
template <class _Core, typename _Val>
_Val& ArrayBase<_Core, _Val>::operator[](
    const index_t idx
) noexcept {
  return this->get()[idx+offset_];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the data of given index.
///
template <class _Core, typename _Val>
const _Val& ArrayBase<_Core, _Val>::operator[](
    const index_t idx
) const noexcept {
  return this->get()[idx+offset_];
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_KIT_ARRAY_BASE_HPP_
