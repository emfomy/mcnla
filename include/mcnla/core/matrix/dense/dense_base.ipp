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
  : data_() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Derived>
DenseBase<_Derived>::DenseBase(
    const index_t capability
) noexcept
  : data_(capability) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <class _Derived>
DenseBase<_Derived>::DenseBase(
    const ValueArrayType &value
) noexcept
  : data_(value) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct from data storage.
///
template <class _Derived>
DenseBase<_Derived>::DenseBase(
    const DataType &data
) noexcept
  : data_(data) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <class _Derived>
DenseBase<_Derived>::DenseBase( const DenseBase &other ) noexcept
  : data_(other.data_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <class _Derived>
DenseBase<_Derived>::DenseBase( DenseBase &&other ) noexcept
  : data_(std::move(other.data_)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <class _Derived>
DenseBase<_Derived>& DenseBase<_Derived>::operator=( const DenseBase &other ) noexcept {
  data_ = other.data_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <class _Derived>
DenseBase<_Derived>& DenseBase<_Derived>::operator=( DenseBase &&other ) noexcept {
  data_ = std::move(other.data_);
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
index_t DenseBase<_Derived>::getOffset() const noexcept { return getData().getOffset(); }

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
/// @brief  Gets the raw value array.
///
template <class _Derived>
typename DenseBase<_Derived>::ScalarType* DenseBase<_Derived>::getValue() noexcept { return getData().getValue(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <class _Derived>
const typename DenseBase<_Derived>::ScalarType* DenseBase<_Derived>::getValue() const noexcept { return getData().getValue(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value valarray.
///
template <class _Derived>
typename DenseBase<_Derived>::ValueValarrayType& DenseBase<_Derived>::getValueValarray() noexcept {
  return getData().getValueValarray();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValueValarray
///
template <class _Derived>
const typename DenseBase<_Derived>::ValueValarrayType& DenseBase<_Derived>::getValueValarray() const noexcept {
  return getData().getValueValarray();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Change to derived class.
///
template <class _Derived>
_Derived& DenseBase<_Derived>::derived() noexcept {
  return static_cast<_Derived&>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  derived
///
template <class _Derived>
const _Derived& DenseBase<_Derived>::derived() const noexcept {
  return static_cast<const _Derived&>(*this);
}

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_BASE_IPP_
