////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_matrix_base.ipp
/// @brief   The implementation of dense matrix interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_MATRIX_BASE_IPP_
#define ISVD_MATRIX_DENSE_MATRIX_BASE_IPP_

#include <isvd/matrix/dense_matrix_base.hpp>

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
typename DenseMatrixBase<_Derived>::ScalarType& DenseMatrixBase<_Derived>::operator()(
    const index_t rowidx,
    const index_t colidx
) noexcept { return this->derived().getElementImpl(rowidx, colidx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element.
///
template <class _Derived>
const typename DenseMatrixBase<_Derived>::ScalarType& DenseMatrixBase<_Derived>::operator()(
    const index_t rowidx,
    const index_t colidx
) const noexcept { return this->derived().getElementImpl(rowidx, colidx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the storage layout.
///
template <class _Derived>
Layout DenseMatrixBase<_Derived>::getLayout() const noexcept { return this->derived().getLayoutImpl(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the leading dimension.
///
template <class _Derived>
index_t DenseMatrixBase<_Derived>::getPitch() const noexcept { return this->derived().getPitchImpl(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a matrix block.
///
template <class _Derived>
_Derived DenseMatrixBase<_Derived>::getBlock(
    const IndexRange rowrange,
    const IndexRange colrange
) noexcept { return this->derived().getBlockImpl(this->convertRowRange(rowrange), this->convertColRange(colrange)); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <class _Derived>
typename DenseMatrixBase<_Derived>::VectorType DenseMatrixBase<_Derived>::getCol(
    const index_t colidx,
    const IndexRange rowrange
) noexcept { return this->derived().getRowImpl(colidx, this->convertRowRange(rowrange)); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <class _Derived>
typename DenseMatrixBase<_Derived>::VectorType DenseMatrixBase<_Derived>::getRow(
    const index_t rowidx,
    const IndexRange colrange
) noexcept { return this->derived().getRowImpl(rowidx, this->convertColRange(colrange)); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a diagonal vector.
///
template <class _Derived>
typename DenseMatrixBase<_Derived>::VectorType DenseMatrixBase<_Derived>::getDiagonal(
    const index_t idx
) noexcept { return this->derived().getDiagonalImpl(idx); }

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_MATRIX_BASE_IPP_
