////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/matrix_base.ipp
/// @brief   The implementation of matrix interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_MATRIX_BASE_IPP_
#define ISVD_MATRIX_MATRIX_BASE_IPP_

#include <isvd/matrix/matrix_base.hpp>

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
  assert(nrow_ > 0 && ncol_ > 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of rows.
///
template <class _Derived> template <TransOption _trans>
index_t MatrixBase<_Derived>::getNrow() const noexcept {
  return !isTranspose(_trans) ? nrow_ : ncol_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of columns.
///
template <class _Derived> template <TransOption _trans>
index_t MatrixBase<_Derived>::getNcol() const noexcept {
  return !isTranspose(_trans) ? ncol_ : nrow_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size.
///
template <class _Derived>
index_t MatrixBase<_Derived>::getSize() const noexcept { return nrow_ * ncol_; }

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_MATRIX_BASE_IPP_
