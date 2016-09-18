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
template <class __Derived>
std::ostream& operator<< ( std::ostream &out, const CooVectorIteratorBase<__Derived> &iterator ) {
  const index_t witdh = log10(iterator.container_->getLength())+1;
  return out << "(" << std::setw(witdh) << iterator.getIdx() << ")  "
                    << std::setw(ios_width) << iterator.getValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value.
///
/// @attention  Never call this when the iterator is at the end.
///
template <class _Derived>
typename CooVectorIteratorBase<_Derived>::ScalarType& CooVectorIteratorBase<_Derived>::getValue() noexcept {
  return container_->getValue()[itidx_];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <class _Derived>
const typename CooVectorIteratorBase<_Derived>::ScalarType& CooVectorIteratorBase<_Derived>::getValue() const noexcept {
  return container_->getValue()[itidx_];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index.
///
template <class _Derived>
typename CooVectorIteratorBase<_Derived>::IndexType& CooVectorIteratorBase<_Derived>::getIdx() noexcept {
  return container_->getIdx()[itidx_];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index.
///
template <class _Derived>
const typename CooVectorIteratorBase<_Derived>::IndexType& CooVectorIteratorBase<_Derived>::getIdx() const noexcept {
  return container_->getIdx()[itidx_];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position.
///
template <class _Derived>
index_t CooVectorIteratorBase<_Derived>::getPos() const noexcept {
  return itidx_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the iterator to beginning.
///
template <class _Derived>
_Derived& CooVectorIteratorBase<_Derived>::setBegin() noexcept {
  itidx_ = 0;
  return this->derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the iterator to end.
///
template <class _Derived>
_Derived& CooVectorIteratorBase<_Derived>::setEnd() noexcept {
  itidx_ = (container_ != nullptr) ? container_->getNnz() : 0;
  return this->derived();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index tuple.
///
template <class _Derived>
typename CooVectorIteratorBase<_Derived>::IdxTupleType CooVectorIteratorBase<_Derived>::getIdxs() noexcept {
  return makeIdxTuple(&getIdx());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getIdxs
///
template <class _Derived>
typename CooVectorIteratorBase<_Derived>::ConstIdxTupleType CooVectorIteratorBase<_Derived>::getIdxs() const noexcept {
  return makeIdxTuple(&getIdx());
}

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_COO_COO_VECTOR_ITERATOR_IPP_
