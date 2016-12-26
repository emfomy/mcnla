////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/kit/array.ipp
/// @brief   The implementation of array.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_KIT_ARRAY_IPP_
#define MCNLA_CORE_MATRIX_KIT_ARRAY_IPP_

#include <mcnla/core/matrix/kit/array.hpp>

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
template <typename _Type>
Array<_Type>::Array() noexcept
  : BaseType(kNullPtr),
    offset_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Type>
Array<_Type>::Array(
    const index_t capacity,
    const index_t offset
) noexcept
  : BaseType(new std::valarray<_Type>(capacity)),
    offset_(offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Type>
Array<_Type>::Array(
    const BaseType &value,
    const index_t offset
) noexcept
  : BaseType(value),
    offset_(offset) {
  mcnla_assert_gele(offset_, 0, size());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <typename _Type>
Array<_Type>::Array(
    const Array &other
) noexcept
  : BaseType(other),
    offset_(other.offset_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Type>
Array<_Type>::Array(
    Array &&other
) noexcept
  : BaseType(std::move(other)),
    offset_(other.offset_) {
  static_cast<BaseType&>(other) = kNullPtr;
  other.offset_ = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <typename _Type>
Array<_Type>& Array<_Type>::operator=(
    const Array &other
) noexcept {
  BaseType::operator=(other);
  offset_ = other.offset_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Type>
Array<_Type>& Array<_Type>::operator=(
    Array &&other
) noexcept {
  BaseType::operator=(std::move(other)); static_cast<BaseType&>(other) = kNullPtr;
  offset_ = other.offset_; other.offset_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Right-shift the offset.
/// Add the #offset_ to @a offset.
///
template <typename _Type>
void Array<_Type>::operator>>=(
    const index_t offset
) noexcept {
  offset_ += offset;
  mcnla_assert_gele(offset_, 0, size());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Left-shift the offset.
/// Subtract #offset_ from @a offset.
///
template <typename _Type>
void Array<_Type>::operator<<=(
    const index_t offset
) noexcept {
  offset_ -= offset;
  mcnla_assert_gele(offset_, 0, size());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Right-shift the offset.
/// Add the #offset_ to @a offset.
///
template <typename _Type>
Array<_Type> Array<_Type>::operator>>(
    const index_t offset
) noexcept {
  Array retval = *this;
  retval >>= offset;
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Right-shift the offset.
/// Add the #offset_ to @a offset.
///
template <typename _Type>
const Array<_Type> Array<_Type>::operator>>(
    const index_t offset
) const noexcept {
  Array retval = *this;
  retval >>= offset;
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Left-shift the offset.
/// Subtract #offset_ from @a offset.
///
template <typename _Type>
Array<_Type> Array<_Type>::operator<<(
    const index_t offset
) noexcept {
  Array retval = *this;
  retval <<= offset;
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Left-shift the offset.
/// Subtract #offset_ from @a offset.
///
template <typename _Type>
const Array<_Type> Array<_Type>::operator<<(
    const index_t offset
) const noexcept {
  Array retval = *this;
  retval <<= offset;
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the memory size is zero.
///
template <typename _Type>
bool Array<_Type>::isEmpty() const noexcept {
  return (size() == 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the memory size.
///
/// @note  @link capacity() capacity@endlink + @link offset() offset@endlink = @link size() memory size@endlink.
///
template <typename _Type>
index_t Array<_Type>::size() const noexcept {
  return this->valarray().size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the capacity.
///
/// @note  @link capacity() capacity@endlink + @link offset() offset@endlink = @link size() memory size@endlink.
///
template <typename _Type>
index_t Array<_Type>::capacity() const noexcept {
  return size() - offset();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the offset.
///
/// @note  @link capacity() capacity@endlink + @link offset() offset@endlink = @link size() memory size@endlink.
///
template <typename _Type>
index_t Array<_Type>::offset() const noexcept {
  return offset_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the data pointer.
///
template <typename _Type>
_Type* Array<_Type>::operator*() noexcept {
  return &(this->valarray()[offset_]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the data pointer.
///
template <typename _Type>
const _Type* Array<_Type>::operator*() const noexcept {
  return &(this->valarray()[offset_]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the data of given index.
///
template <typename _Type>
_Type& Array<_Type>::operator[](
    const index_t idx
) noexcept {
  return this->valarray()[idx+offset_];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the data of given index.
///
template <typename _Type>
const _Type& Array<_Type>::operator[](
    const index_t idx
) const noexcept {
  return this->valarray()[idx+offset_];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the valarray.
///
template <typename _Type>
std::valarray<_Type>& Array<_Type>::valarray() noexcept {
  return *(this->get());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the valarray.
///
template <typename _Type>
const std::valarray<_Type>& Array<_Type>::valarray() const noexcept {
  return *(this->get());
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_KIT_ARRAY_IPP_
