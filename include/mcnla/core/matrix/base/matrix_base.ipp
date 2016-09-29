////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/base/matrix_base.ipp
/// @brief   The implementation of matrix interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_BASE_MATRIX_BASE_IPP_
#define MCNLA_CORE_MATRIX_BASE_MATRIX_BASE_IPP_

#include <mcnla/core/matrix/base/matrix_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <class _Derived>
MatrixBase<_Derived>::MatrixBase() noexcept
  : nrow_(0),
    ncol_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Derived>
MatrixBase<_Derived>::MatrixBase(
    const index_t nrow,
    const index_t ncol
) noexcept
  : nrow_(nrow),
    ncol_(ncol) {
  assert(nrow_ >= 0 && ncol_ >= 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Derived>
MatrixBase<_Derived>::MatrixBase(
    const std::pair<index_t, index_t> sizes
) noexcept
  : MatrixBase(sizes.first, sizes.second) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <class _Derived>
MatrixBase<_Derived>::MatrixBase( const MatrixBase &other ) noexcept
  : nrow_(other.nrow_),
    ncol_(other.ncol_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <class _Derived>
MatrixBase<_Derived>::MatrixBase( MatrixBase &&other ) noexcept
  : nrow_(other.nrow_),
    ncol_(other.ncol_) {
  other.nrow_ = 0;
  other.ncol_ = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <class _Derived>
MatrixBase<_Derived>& MatrixBase<_Derived>::operator=( const MatrixBase &other ) noexcept {
  nrow_ = other.nrow_; ncol_ = other.ncol_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <class _Derived>
MatrixBase<_Derived>& MatrixBase<_Derived>::operator=( MatrixBase &&other ) noexcept {
  nrow_ = other.nrow_; ncol_ = other.ncol_;
  other.nrow_ = 0;     other.ncol_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of rows.
///
template <class _Derived> template <TransOption _trans>
index_t MatrixBase<_Derived>::getNrow() const noexcept { return !isTranspose(_trans) ? nrow_ : ncol_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of columns.
///
template <class _Derived> template <TransOption _trans>
index_t MatrixBase<_Derived>::getNcol() const noexcept { return !isTranspose(_trans) ? ncol_ : nrow_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size.
///
template <class _Derived> template <index_t _dim>
index_t MatrixBase<_Derived>::getSize() const noexcept {
  static_assert(_dim >= 0 && _dim < 2, "Invalid dimension!");
  return (_dim == 0) ? size0_ : size1_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of elements.
///
template <class _Derived>
index_t MatrixBase<_Derived>::getNelem() const noexcept { return size0_ * size1_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the sizes.
///
template <class _Derived>
std::pair<index_t, index_t> MatrixBase<_Derived>::getSizes() const noexcept { return std::make_pair(nrow_, ncol_); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Change to derived class.
///
template <class _Derived>
_Derived& MatrixBase<_Derived>::derived() noexcept {
  return static_cast<_Derived&>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  derived
///
template <class _Derived>
const _Derived& MatrixBase<_Derived>::derived() const noexcept {
  return static_cast<const _Derived&>(*this);
}

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_BASE_MATRIX_BASE_IPP_
