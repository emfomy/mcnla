////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_vector_base.ipp
/// @brief   The implementation of dense vector interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_VECTOR_BASE_IPP_
#define ISVD_MATRIX_DENSE_VECTOR_BASE_IPP_

#include <isvd/matrix/dense_vector_base.hpp>

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
inline index_t DenseVectorBase<_Derived, _Scalar>::getIncrement() const noexcept { return this->derived().getIncrementImpl(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the offset of starting position.
///
template <class _Derived, typename _Scalar>
inline index_t DenseVectorBase<_Derived, _Scalar>::getOffset() const noexcept { return this->derived().getOffsetImpl(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value of given index.
///
template <class _Derived, typename _Scalar>
inline _Scalar& DenseVectorBase<_Derived, _Scalar>::getValue(
    const index_t idx
) noexcept { return this->derived().getValueImpl(idx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value of given index.
///
template <class _Derived, typename _Scalar>
inline const _Scalar& DenseVectorBase<_Derived, _Scalar>::getValue(
    const index_t idx
) const noexcept { return this->derived().getValueImpl(idx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a block matrix.
///
template <class _Derived, typename _Scalar>
_Derived DenseVectorBase<_Derived, _Scalar>::getSegment(
    const index_t idx,
    const index_t length
) noexcept { return this->derived().getSegmentImpl(idx, length); }

}  // namespace impl

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_VECTOR_BASE_IPP_
