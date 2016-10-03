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
    const index_t capability
) noexcept
  : BaseType(new std::valarray<_Type>(capability)),
    offset_(0) {}

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
  assert(offset_ >= 0 && offset_ <= this->getCapability());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <typename _Type>
Array<_Type>::Array( const Array &other ) noexcept
  : BaseType(other),
    offset_(other.offset_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Type>
Array<_Type>::Array( Array &&other ) noexcept
  : BaseType(std::move(other)),
    offset_(other.offset_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <typename _Type>
Array<_Type>& Array<_Type>::operator=( const Array &other ) noexcept {
  BaseType::operator=(other); offset_ = other.offset_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Type>
Array<_Type>& Array<_Type>::operator=( Array &&other ) noexcept {
  BaseType::operator=(std::move(other)); offset_ = other.offset_; other.offset_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Right-shift the offset.
///
template <typename _Type>
void Array<_Type>::operator>>=( const index_t offset ) noexcept {
  offset_ += offset;
  assert(offset_ >= 0 && offset_ <= this->getCapability());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Left-shift the offset.
///
template <typename _Type>
void Array<_Type>::operator<<=( const index_t offset ) noexcept {
  offset_ -= offset;
  assert(offset_ >= 0 && offset_ <= this->getCapability());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Right-shift the offset.
///
template <typename _Type>
Array<_Type> Array<_Type>::operator>>( const index_t offset ) noexcept {
  Array retval = *this; retval >>= offset; return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Right-shift the offset.
///
template <typename _Type>
const Array<_Type> Array<_Type>::operator>>( const index_t offset ) const noexcept {
  Array retval = *this; retval >>= offset; return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Left-shift the offset.
///
template <typename _Type>
Array<_Type> Array<_Type>::operator<<( const index_t offset ) noexcept {
  Array retval = *this; retval <<= offset; return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Left-shift the offset.
///
template <typename _Type>
const Array<_Type> Array<_Type>::operator<<( const index_t offset ) const noexcept {
  Array retval = *this; retval <<= offset; return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the length of valarray.
///
template <typename _Type>
index_t Array<_Type>::getCapability() const noexcept {
  return this->getValarray().size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the offset.
///
template <typename _Type>
index_t Array<_Type>::getOffset() const noexcept {
  return offset_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the data pointer.
///
template <typename _Type>
_Type* Array<_Type>::operator*() noexcept {
  return &(this->getValarray()[offset_]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the data pointer.
///
template <typename _Type>
const _Type* Array<_Type>::operator*() const noexcept {
  return &(this->getValarray()[offset_]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the data of given index.
///
template <typename _Type>
_Type& Array<_Type>::operator[]( const index_t idx ) noexcept {
  return this->getValarray()[idx+offset_];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the data of given index.
///
template <typename _Type>
const _Type& Array<_Type>::operator[]( const index_t idx ) const noexcept {
  return this->getValarray()[idx+offset_];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the valarray.
///
template <typename _Type>
std::valarray<_Type>& Array<_Type>::getValarray() noexcept {
  return *(this->get());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the valarray.
///
template <typename _Type>
const std::valarray<_Type>& Array<_Type>::getValarray() const noexcept {
  return *(this->get());
}

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_KIT_ARRAY_IPP_
