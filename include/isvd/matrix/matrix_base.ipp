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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of rows.
///
template <class _Derived> template <TransOption _trans>
index_t MatrixBase<_Derived>::getNrow() const noexcept {
  return !isTranspose(_trans) ?this->derived().getNrowImpl() : this->derived().getNcolImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of columns.
///
template <class _Derived> template <TransOption _trans>
index_t MatrixBase<_Derived>::getNcol() const noexcept {
  return !isTranspose(_trans) ?this->derived().getNcolImpl() : this->derived().getNrowImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element.
///
template <class _Derived>
typename MatrixBase<_Derived>::ScalarType& MatrixBase<_Derived>::getElement(
    const index_t rowidx,
    const index_t colidx
) noexcept { return this->derived().getElementImpl(rowidx, colidx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElement
///
template <class _Derived>
const typename MatrixBase<_Derived>::ScalarType& MatrixBase<_Derived>::getElement(
    const index_t rowidx,
    const index_t colidx
) const noexcept { return this->derived().getElementImpl(rowidx, colidx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElement
///
template <class _Derived>
typename MatrixBase<_Derived>::ScalarType& MatrixBase<_Derived>::operator()(
    const index_t rowidx,
    const index_t colidx
) noexcept { return getElement(rowidx, colidx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElement
///
template <class _Derived>
const typename MatrixBase<_Derived>::ScalarType& MatrixBase<_Derived>::operator()(
    const index_t rowidx,
    const index_t colidx
) const noexcept { return getElement(rowidx, colidx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size.
///
template <class _Derived>
index_t MatrixBase<_Derived>::getSize() const noexcept { return getNrow() * getNcol(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Resize the matrix.
///
template <class _Derived>
void MatrixBase<_Derived>::resize(
    const index_t nrow,
    const index_t ncol
) noexcept { return this->derived().resizeImpl(nrow, ncol); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Converts the index range.
///
template <class _Derived>
IndexRange MatrixBase<_Derived>::convertRowRange(
    const IndexRange range
) const noexcept { return range.convert(getNrow()); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Converts the index range.
///
template <class _Derived>
IndexRange MatrixBase<_Derived>::convertColRange(
    const IndexRange range
) const noexcept { return range.convert(getNcol()); }

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_MATRIX_BASE_IPP_
