////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/base/vector_base.ipp
/// @brief   The implementation of vector interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_BASE_VECTOR_BASE_IPP_
#define ISVD_MATRIX_BASE_VECTOR_BASE_IPP_

#include <isvd/matrix/base/vector_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <class _Derived>
VectorBase<_Derived>::VectorBase() noexcept
  : length_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Derived>
VectorBase<_Derived>::VectorBase(
    const index_t length
) noexcept
  : length_(length) {
  assert(length_ >= 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
template <class _Derived>
VectorBase<_Derived>::VectorBase( const VectorBase &other ) noexcept
  : length_(other.length_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <class _Derived>
VectorBase<_Derived>::VectorBase( VectorBase &&other ) noexcept
  : length_(other.length_) {
  other.length_ = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses isvd::blas::copy.
///
template <class _Derived>
VectorBase<_Derived>& VectorBase<_Derived>::operator=( const VectorBase &other ) noexcept {
  length_ = other.length_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <class _Derived>
VectorBase<_Derived>& VectorBase<_Derived>::operator=( VectorBase &&other ) noexcept {
  length_ = other.length_; other.length_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the length.
///
template <class _Derived>
index_t VectorBase<_Derived>::getLength() const noexcept { return length_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size.
///
template <class _Derived> template <index_t _dim>
index_t VectorBase<_Derived>::getSize() const noexcept {
  static_assert(_dim == 0, "Invalid dimension!");
  return length_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of elements.
///
template <class _Derived>
index_t VectorBase<_Derived>::getNelem() const noexcept { return length_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the sizes.
///
template <class _Derived>
index_t VectorBase<_Derived>::getSizes() const noexcept { return length_; }

}  // namespace isvd

#endif  // ISVD_MATRIX_BASE_VECTOR_BASE_IPP_
