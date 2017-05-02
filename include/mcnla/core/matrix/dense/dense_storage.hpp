////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_storage.hpp
/// @brief   The dense storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_STORAGE_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_STORAGE_HPP_

#include <mcnla/core/matrix/dense/dense_storage.hh>

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
template <typename _Val, template <typename> class _Array>
DenseStorage<_Val, _Array>::DenseStorage() noexcept
  : val_() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, template <typename> class _Array>
DenseStorage<_Val, _Array>::DenseStorage(
    const index_t capacity
) noexcept
  : val_(capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Val, template <typename> class _Array>
DenseStorage<_Val, _Array>::DenseStorage(
    const ValArrayType &val
) noexcept
  : val_(val) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <typename _Val, template <typename> class _Array>
DenseStorage<_Val, _Array>::DenseStorage(
    const DenseStorage &other
) noexcept
  : val_(other.val_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy (creates an alias). For deep copy, uses mcnla::la::copy.
///
template <typename _Val, template <typename> class _Array>
DenseStorage<_Val, _Array>& DenseStorage<_Val, _Array>::operator=(
    const DenseStorage &other
) noexcept {
  val_ = other.val_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the memory size is zero.
///
template <typename _Val, template <typename> class _Array>
bool DenseStorage<_Val, _Array>::isEmpty() const noexcept {
  return val_.isEmpty();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the capacity of the value array.
///
template <typename _Val, template <typename> class _Array>
index_t DenseStorage<_Val, _Array>::capacity() const noexcept {
  return val_.capacity();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the offset of the value array.
///
template <typename _Val, template <typename> class _Array>
index_t DenseStorage<_Val, _Array>::offset() const noexcept {
  return val_.offset();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value array.
///
template <typename _Val, template <typename> class _Array>
typename DenseStorage<_Val, _Array>::ValArrayType& DenseStorage<_Val, _Array>::val() noexcept {
  return val_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  val
///
template <typename _Val, template <typename> class _Array>
const typename DenseStorage<_Val, _Array>::ValArrayType& DenseStorage<_Val, _Array>::val() const noexcept {
  return val_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw value pointer.
///
template <typename _Val, template <typename> class _Array>
_Val* DenseStorage<_Val, _Array>::valPtr() noexcept {
  return *val_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  valPtr
///
template <typename _Val, template <typename> class _Array>
const _Val* DenseStorage<_Val, _Array>::valPtr() const noexcept {
  return *val_;
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_STORAGE_HPP_
