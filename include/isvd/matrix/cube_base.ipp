////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/cube_base.ipp
/// @brief   The implementation of cube interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_CUBE_BASE_IPP_
#define ISVD_MATRIX_CUBE_BASE_IPP_

#include <isvd/matrix/cube_base.hpp>

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
index_t CubeBase<_Derived>::getNrow() const noexcept {
  return !isTranspose(_trans) ?this->derived().getNrowImpl() : this->derived().getNcolImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of columns.
///
template <class _Derived> template <TransOption _trans>
index_t CubeBase<_Derived>::getNcol() const noexcept {
  return !isTranspose(_trans) ?this->derived().getNcolImpl() : this->derived().getNrowImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element.
///
template <class _Derived>
typename CubeBase<_Derived>::ScalarType& CubeBase<_Derived>::getElement(
    const index_t rowidx,
    const index_t colidx,
    const index_t pageidx
) noexcept { return this->derived().getElementImpl(rowidx, colidx, pageidx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElement
///
template <class _Derived>
const typename CubeBase<_Derived>::ScalarType& CubeBase<_Derived>::getElement(
    const index_t rowidx,
    const index_t colidx,
    const index_t pageidx
) const noexcept { return this->derived().getElementImpl(rowidx, colidx, pageidx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElement
///
template <class _Derived>
typename CubeBase<_Derived>::ScalarType& CubeBase<_Derived>::operator()(
    const index_t rowidx,
    const index_t colidx,
    const index_t pageidx
) noexcept { return getElement(rowidx, colidx, pageidx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElement
///
template <class _Derived>
const typename CubeBase<_Derived>::ScalarType& CubeBase<_Derived>::operator()(
    const index_t rowidx,
    const index_t colidx,
    const index_t pageidx
) const noexcept { return getElement(rowidx, colidx, pageidx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of pages.
///
template <class _Derived>
index_t CubeBase<_Derived>::getNpage() const noexcept { return this->derived().getNpageImpl(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size.
///
template <class _Derived>
index_t CubeBase<_Derived>::getSize() const noexcept { return getNrow() * getNcol() * getNpage(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Resize the cube
///
template <class _Derived>
void CubeBase<_Derived>::resize(
    const index_t nrow,
    const index_t ncol,
    const index_t npage
) noexcept { return this->derived().resizeImpl(nrow, ncol, npage); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Converts the index range.
///
template <class _Derived>
IndexRange CubeBase<_Derived>::convertRowRange(
    const IndexRange range
) const noexcept { return range.convert(getNrow()); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Converts the index range.
///
template <class _Derived>
IndexRange CubeBase<_Derived>::convertColRange(
    const IndexRange range
) const noexcept { return range.convert(getNcol()); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Converts the index range.
///
template <class _Derived>
IndexRange CubeBase<_Derived>::convertPageRange(
    const IndexRange range
) const noexcept { return range.convert(getNpage()); }

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_CUBE_BASE_IPP_
