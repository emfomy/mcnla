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
//  The implementation namespace.
//
namespace impl {

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
/// @brief  Gets the offset of starting position.
///
template <class _Derived>
index_t DenseMatrixBase<_Derived>::getOffset() const noexcept { return this->derived().getOffsetImpl(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value of given index.
///
template <class _Derived>
typename DenseMatrixBase<_Derived>::ScalarType& DenseMatrixBase<_Derived>::getValue(
    const index_t rowidx,
    const index_t colidx
) noexcept { return this->derived().getValueImpl(rowidx, colidx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value of given index.
///
template <class _Derived>
const typename DenseMatrixBase<_Derived>::ScalarType& DenseMatrixBase<_Derived>::getValue(
    const index_t rowidx,
    const index_t colidx
) const noexcept { return this->derived().getValueImpl(rowidx, colidx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a matrix block.
///
template <class _Derived>
_Derived DenseMatrixBase<_Derived>::getBlock(
    const index_t rowidx,
    const index_t colidx,
    const index_t nrow,
    const index_t ncol
) noexcept { return this->derived().getBlockImpl(rowidx, colidx, nrow, ncol); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a matrix block.
///
template <class _Derived>
_Derived DenseMatrixBase<_Derived>::getRows(
    const index_t rowidx,
    const index_t nrow
) noexcept { return this->derived().getRowsImpl(rowidx, nrow); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a matrix block.
///
template <class _Derived>
_Derived DenseMatrixBase<_Derived>::getCols(
    const index_t colidx,
    const index_t ncol
) noexcept { return this->derived().getRowsImpl(colidx, ncol); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <class _Derived>
typename DenseMatrixBase<_Derived>::VectorType DenseMatrixBase<_Derived>::getRow(
    const index_t rowidx
) noexcept { return this->derived().getRowImpl(rowidx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <class _Derived>
typename DenseMatrixBase<_Derived>::VectorType DenseMatrixBase<_Derived>::getRow(
    const index_t rowidx,
    const index_t colidx,
    const index_t ncol
) noexcept { return this->derived().getRowImpl(rowidx, colidx, ncol); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <class _Derived>
typename DenseMatrixBase<_Derived>::VectorType DenseMatrixBase<_Derived>::getCol(
    const index_t colidx
) noexcept { return this->derived().getRowImpl(colidx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
template <class _Derived>
typename DenseMatrixBase<_Derived>::VectorType DenseMatrixBase<_Derived>::getCol(
    const index_t colidx,
    const index_t rowidx,
    const index_t nrow
) noexcept { return this->derived().getRowImpl(colidx, rowidx, nrow); }

}  // namespace impl

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_MATRIX_BASE_IPP_
