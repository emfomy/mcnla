////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_base.ipp
/// @brief   The implementation of dense container interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_BASE_IPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_BASE_IPP_

#include <mcnla/core/matrix/dense/dense_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <class _Derived>
DenseBase<_Derived>::DenseBase() noexcept
  : offset_(0),
    data_() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Derived>
DenseBase<_Derived>::DenseBase(
    const index_t capability,
    const index_t offset
) noexcept
  : offset_(offset),
    data_(capability) {
  assert(offset_ >= 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <class _Derived>
DenseBase<_Derived>::DenseBase(
    const ValuePtrType &value,
    const index_t offset
) noexcept
  : offset_(offset),
    data_(value) {
  assert(offset_ >= 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct from data storage.
///
template <class _Derived>
DenseBase<_Derived>::DenseBase(
    const DataType &data,
    const index_t offset
) noexcept
  : offset_(offset),
    data_(data) {
  assert(offset_ >= 0 && offset_ <= data_.getCapability());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <class _Derived>
DenseBase<_Derived>::DenseBase( const DenseBase &other ) noexcept
  : offset_(other.offset_),
    data_(other.data_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <class _Derived>
DenseBase<_Derived>::DenseBase( DenseBase &&other ) noexcept
  : offset_(other.offset_),
    data_(std::move(other.data_)) {
  other.offset_ = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <class _Derived>
DenseBase<_Derived>& DenseBase<_Derived>::operator=( const DenseBase &other ) noexcept {
  offset_ = other.offset_; data_ = other.data_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <class _Derived>
DenseBase<_Derived>& DenseBase<_Derived>::operator=( DenseBase &&other ) noexcept {
  offset_ = other.offset_; data_ = std::move(other.data_); other.offset_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the length of value array.
///
template <class _Derived>
index_t DenseBase<_Derived>::getCapability() const noexcept { return getData().getCapability(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the offset of starting position.
///
template <class _Derived>
index_t DenseBase<_Derived>::getOffset() const noexcept { return offset_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the data storage.
///
template <class _Derived>
typename DenseBase<_Derived>::DataType& DenseBase<_Derived>::getData() noexcept { return data_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getData
///
template <class _Derived>
const typename DenseBase<_Derived>::DataType& DenseBase<_Derived>::getData() const noexcept { return data_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value array.
///
template <class _Derived>
typename DenseBase<_Derived>::ScalarType* DenseBase<_Derived>::getValue() noexcept {
  return getData().getValue() + getOffset();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <class _Derived>
const typename DenseBase<_Derived>::ScalarType* DenseBase<_Derived>::getValue() const noexcept {
  return getData().getValue() + getOffset();
}

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_BASE_IPP_
