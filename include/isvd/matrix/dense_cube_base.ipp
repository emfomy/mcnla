////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_cube_base.ipp
/// @brief   The implementation of dense cube interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_CUBE_BASE_IPP_
#define ISVD_MATRIX_DENSE_CUBE_BASE_IPP_

#include <isvd/matrix/dense_cube_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element.
///
template <class _Derived>
typename DenseCubeBase<_Derived>::ScalarType& DenseCubeBase<_Derived>::operator()(
    const index_t rowidx,
    const index_t colidx,
    const index_t pageidx
) noexcept { return this->derived().getElementImpl(rowidx, colidx, pageidx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element.
///
template <class _Derived>
const typename DenseCubeBase<_Derived>::ScalarType& DenseCubeBase<_Derived>::operator()(
    const index_t rowidx,
    const index_t colidx,
    const index_t pageidx
) const noexcept { return this->derived().getElementImpl(rowidx, colidx, pageidx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the storage layout.
///
template <class _Derived>
Layout DenseCubeBase<_Derived>::getLayout() const noexcept { return this->derived().getLayoutImpl(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the leading dimension.
///
template <class _Derived>
index_t DenseCubeBase<_Derived>::getPitch() const noexcept { return this->derived().getPitchImpl(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the page dimension.
///
template <class _Derived>
index_t DenseCubeBase<_Derived>::getPagePitch() const noexcept { return this->derived().getPagePitchImpl(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a cube block.
///
template <class _Derived>
_Derived DenseCubeBase<_Derived>::getBlock(
    const IndexRange rowrange,
    const IndexRange colrange,
    const IndexRange pagerange
) noexcept {return this->derived().getBlockImpl(
    this->convertRowRange(rowrange), this->convertColRange(colrange), this->convertPageRange(pagerange)); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a matrix block.
///
template <class _Derived>
typename DenseCubeBase<_Derived>::MatrixType DenseCubeBase<_Derived>::getPage(
    const index_t pageidx,
    const IndexRange rowrange,
    const IndexRange colrange
) noexcept { return this->derived().getPageImpl(pageidx, this->convertRowRange(rowrange), this->convertColRange(colrange)); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <class _Derived>
typename DenseCubeBase<_Derived>::VectorType DenseCubeBase<_Derived>::getRow(
    const index_t rowidx,
    const index_t pageidx,
    const IndexRange colrange
) noexcept { return this->derived().getRowImpl(rowidx, pageidx, this->convertColRange(colrange)); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <class _Derived>
typename DenseCubeBase<_Derived>::VectorType DenseCubeBase<_Derived>::getCol(
    const index_t colidx,
    const index_t pageidx,
    const IndexRange rowrange
) noexcept { return this->derived().getColImpl(colidx, pageidx, this->convertRowRange(rowrange)); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <class _Derived>
typename DenseCubeBase<_Derived>::VectorType DenseCubeBase<_Derived>::getTube(
    const index_t rowidx,
    const index_t colidx,
    const IndexRange pagerange
) noexcept { return this->derived().getTubeImpl(rowidx, colidx, this->convertPageRange(pagerange)); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a diagonal vector.
///
template <class _Derived>
typename DenseCubeBase<_Derived>::VectorType DenseCubeBase<_Derived>::getDiagonal(
    const index_t pageidx,
    const index_t idx
) noexcept { return this->derived().getDiagonalImpl(pageidx, idx); }

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_CUBE_BASE_IPP_
