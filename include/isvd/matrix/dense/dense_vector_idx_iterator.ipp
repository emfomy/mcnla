////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense/dense_vector_idx_iterator.ipp
/// @brief   The implementation of dense vector iterator.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DENSE_VECTOR_IDX_ITERATOR_IPP_
#define ISVD_MATRIX_DENSE_DENSE_VECTOR_IDX_ITERATOR_IPP_

#include <isvd/matrix/dense/dense_vector_idx_iterator.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index tuple.
///
/// @attention  Never call this when the iterator is at the end.
///
template <typename _Scalar, class _Vector>
typename DenseVectorIdxIteratorBase<_Scalar, _Vector>::IdxTupleType
    DenseVectorIdxIteratorBase<_Scalar, _Vector>::operator*() const noexcept {
  return IdxTupleType({this->idx_});
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  internal::DenseVectorIteratorBase::setBegin
///
template <typename _Scalar, class _Vector>
DenseVectorIdxIteratorBase<_Scalar, _Vector>& DenseVectorIdxIteratorBase<_Scalar, _Vector>::setBegin() noexcept {
  DenseVectorIteratorBase<_Scalar, _Vector>::setBegin(); return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  internal::DenseVectorIteratorBase::setEnd
///
template <typename _Scalar, class _Vector>
DenseVectorIdxIteratorBase<_Scalar, _Vector>& DenseVectorIdxIteratorBase<_Scalar, _Vector>::setEnd() noexcept {
  DenseVectorIteratorBase<_Scalar, _Vector>::setEnd(); return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value iterator.
///
template <typename _Scalar, class _Vector>
DenseVectorIteratorBase<_Scalar, _Vector>& DenseVectorIdxIteratorBase<_Scalar, _Vector>::getValueIterator() noexcept {
  return static_cast<DenseVectorIteratorBase<_Scalar, _Vector>&>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  internal::DenseVectorIteratorBase::getBegin
///
template <typename _Scalar, class _Vector>
DenseVectorIdxIteratorBase<_Scalar, _Vector>
    DenseVectorIdxIteratorBase<_Scalar, _Vector>::getBegin( _Vector *vector ) noexcept {
  return DenseVectorIdxIteratorBase(vector).setBegin();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  internal::DenseVectorIdxIteratorBase::getEnd
///
template <typename _Scalar, class _Vector>
DenseVectorIdxIteratorBase<_Scalar, _Vector>
    DenseVectorIdxIteratorBase<_Scalar, _Vector>::getEnd( _Vector *vector ) noexcept {
  return DenseVectorIdxIteratorBase(vector).setEnd();
}

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_VECTOR_IDX_ITERATOR_IPP_
