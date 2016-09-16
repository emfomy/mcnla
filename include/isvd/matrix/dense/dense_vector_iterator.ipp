////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense/dense_vector_iterator.ipp
/// @brief   The implementation of dense vector iterator.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DENSE_VECTOR_ITERATOR_IPP_
#define ISVD_MATRIX_DENSE_DENSE_VECTOR_ITERATOR_IPP_

#include <isvd/matrix/dense/dense_vector_iterator.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Print to stream.
///
template <typename __Scalar, class __Vector>
std::ostream& operator<< ( std::ostream &out, const DenseVectorIteratorBase<__Scalar, __Vector> &iterator ) {
  const index_t witdh = log10(iterator.container_->getLength())+1;
  return out << "(" << std::setw(witdh) << iterator.getIdx() << ")  "
                    << std::setw(ios_width) << iterator.getValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value.
///
/// @attention  Never call this when the iterator is at the end.
///
template <typename _Scalar, class _Vector>
_Scalar& DenseVectorIteratorBase<_Scalar, _Vector>::getValue() noexcept {
  return container_->getValue()[getPos()];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar, class _Vector>
const _Scalar& DenseVectorIteratorBase<_Scalar, _Vector>::getValue() const noexcept {
  return container_->getValue()[getPos()];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index tuple.
///
template <typename _Scalar, class _Vector>
IdxTuple<1> DenseVectorIteratorBase<_Scalar, _Vector>::getIdxs() const noexcept {
  return makeIdxTuple(getIdx());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index.
///
template <typename _Scalar, class _Vector>
index_t DenseVectorIteratorBase<_Scalar, _Vector>::getIdx() const noexcept {
  return itidx_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position.
///
template <typename _Scalar, class _Vector>
index_t DenseVectorIteratorBase<_Scalar, _Vector>::getPos() const noexcept {
  return container_->getPos(getIdx());
}

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_VECTOR_ITERATOR_IPP_
