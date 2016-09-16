////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/coo/coo_vector_iterator.ipp
/// @brief   The implementation of COO vector iterator.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_COO_COO_VECTOR_ITERATOR_IPP_
#define ISVD_MATRIX_COO_COO_VECTOR_ITERATOR_IPP_

#include <isvd/matrix/coo/coo_vector_iterator.hpp>

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
template <typename __Scalar, typename __Index, class __Vector>
std::ostream& operator<< ( std::ostream &out, const CooVectorIteratorBase<__Scalar, __Index, __Vector> &iterator ) {
  const index_t witdh = log10(iterator.container_->getLength())+1;
  return out << "(" << std::setw(witdh) << iterator.getIdx() << ")  "
                    << std::setw(ios_width) << iterator.getValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value.
///
/// @attention  Never call this when the iterator is at the end.
///
template <typename _Scalar, typename _Index, class _Vector>
_Scalar& CooVectorIteratorBase<_Scalar, _Index, _Vector>::getValue() noexcept {
  return container_->getValue()[itidx_];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value.
///
/// @attention  Never call this when the iterator is at the end.
///
template <typename _Scalar, typename _Index, class _Vector>
const _Scalar& CooVectorIteratorBase<_Scalar, _Index, _Vector>::getValue() const noexcept {
  return container_->getValue()[itidx_];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index tuple.
///
template <typename _Scalar, typename _Index, class _Vector>
IdxTuple<1> CooVectorIteratorBase<_Scalar, _Index, _Vector>::getIdxs() const noexcept {
  return makeIdxTuple(getIdx());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index.
///
template <typename _Scalar, typename _Index, class _Vector>
_Index& CooVectorIteratorBase<_Scalar, _Index, _Vector>::getIdx() noexcept {
  return container_->getIdx()[itidx_];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index.
///
template <typename _Scalar, typename _Index, class _Vector>
const _Index& CooVectorIteratorBase<_Scalar, _Index, _Vector>::getIdx() const noexcept {
  return container_->getIdx()[itidx_];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position.
///
template <typename _Scalar, typename _Index, class _Vector>
index_t CooVectorIteratorBase<_Scalar, _Index, _Vector>::getPos() const noexcept {
  return itidx_;
}

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_COO_COO_VECTOR_ITERATOR_IPP_
