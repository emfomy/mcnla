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
template <class _Derived, typename _Scalar>
inline Layout DenseMatrixBase<_Derived, _Scalar>::getLayout() const noexcept { return this->derived().getLayoutImpl(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the leading dimension.
///
template <class _Derived, typename _Scalar>
inline index_t DenseMatrixBase<_Derived, _Scalar>::getPitch() const noexcept { return this->derived().getPitchImpl(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the offset of starting position.
///
template <class _Derived, typename _Scalar>
inline index_t DenseMatrixBase<_Derived, _Scalar>::getOffset() const noexcept { return this->derived().getOffsetImpl(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value of given index.
///
template <class _Derived, typename _Scalar>
inline _Scalar& DenseMatrixBase<_Derived, _Scalar>::getValue(
    const index_t rowidx,
    const index_t colidx
) noexcept { return this->derived().getValueImpl(rowidx, colidx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value of given index.
///
template <class _Derived, typename _Scalar>
inline const _Scalar& DenseMatrixBase<_Derived, _Scalar>::getValue(
    const index_t rowidx,
    const index_t colidx
) const noexcept { return this->derived().getValueImpl(rowidx, colidx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a block matrix.
///
template <class _Derived, typename _Scalar>
_Derived DenseMatrixBase<_Derived, _Scalar>::getBlock(
    const index_t rowidx,
    const index_t colidx,
    const index_t nrow,
    const index_t ncol
) noexcept { return this->derived().getBlockImpl(rowidx, colidx, nrow, ncol); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a block matrix.
///
template <class _Derived, typename _Scalar>
_Derived DenseMatrixBase<_Derived, _Scalar>::getRows(
    const index_t rowidx,
    const index_t nrow
) noexcept { return this->derived().getRowsImpl(rowidx, nrow); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a block matrix.
///
template <class _Derived, typename _Scalar>
_Derived DenseMatrixBase<_Derived, _Scalar>::getCols(
    const index_t colidx,
    const index_t ncol
) noexcept { return this->derived().getRowsImpl(colidx, ncol); }

}  // namespace impl

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_MATRIX_BASE_IPP_
