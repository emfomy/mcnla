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
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element.
///
template <class _Derived>
typename DenseVectorBase<_Derived>::ScalarType& DenseVectorBase<_Derived>::operator()(
    const index_t idx
) noexcept { return this->derived().getElementImpl(idx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element.
///
template <class _Derived>
const typename DenseVectorBase<_Derived>::ScalarType& DenseVectorBase<_Derived>::operator()(
    const index_t idx
) const noexcept { return this->derived().getElementImpl(idx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the storage layout.
///
template <class _Derived>
index_t DenseVectorBase<_Derived>::getIncrement() const noexcept { return this->derived().getIncrementImpl(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a matrix block.
///
template <class _Derived>
_Derived DenseVectorBase<_Derived>::getSegment(
    const IndexRange range
) noexcept { return this->derived().getSegmentImpl(this->convertRange(range)); }

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_VECTOR_BASE_IPP_