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
/// @brief  Default constructor.
///
template <typename _Scalar, typename _Index, class _Vector>
CooVectorIteratorBase<_Scalar, _Index, _Vector>::CooVectorIteratorBase() noexcept
  : itidx_(0),
    container_(nullptr) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given vector.
///
template <typename _Scalar, typename _Index, class _Vector>
CooVectorIteratorBase<_Scalar, _Index, _Vector>::CooVectorIteratorBase(
    _Vector *vector,
    const index_t pos
) noexcept
  : itidx_(pos),
    container_(vector) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
template <typename _Scalar, typename _Index, class _Vector>
CooVectorIteratorBase<_Scalar, _Index, _Vector>::CooVectorIteratorBase(
    const CooVectorIteratorBase &other
) noexcept
  : itidx_(other.itidx_),
    container_(other.container_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
template <typename _Scalar, typename _Index, class _Vector>
CooVectorIteratorBase<_Scalar, _Index, _Vector>& CooVectorIteratorBase<_Scalar, _Index, _Vector>::operator=(
    const CooVectorIteratorBase &other
) noexcept {
  itidx_ = other.itidx_;
  container_ = other.container_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Equal-to operator.
///
template <typename _Scalar, typename _Index, class _Vector>
bool CooVectorIteratorBase<_Scalar, _Index, _Vector>::operator==(
    const CooVectorIteratorBase &other
) const noexcept {
  return (container_ == other.container_) && (itidx_ == other.itidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Not-equal-to operator.
///
template <typename _Scalar, typename _Index, class _Vector>
bool CooVectorIteratorBase<_Scalar, _Index, _Vector>::operator!=(
    const CooVectorIteratorBase &other
) const noexcept {
  return !(*this == other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Prefix increment operator.
///
template <typename _Scalar, typename _Index, class _Vector>
CooVectorIteratorBase<_Scalar, _Index, _Vector>& CooVectorIteratorBase<_Scalar, _Index, _Vector>::operator++() noexcept {
  assert(container_ != nullptr);

  const auto nnz = container_->getNnz();
  if ( ++itidx_ >= nnz ) {
    itidx_ = nnz;
  }
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Postfix increment operator.
///
template <typename _Scalar, typename _Index, class _Vector>
CooVectorIteratorBase<_Scalar, _Index, _Vector> CooVectorIteratorBase<_Scalar, _Index, _Vector>::operator++( int ) noexcept {
  auto retval(*this);
  ++(*this);
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar, typename _Index, class _Vector>
_Scalar& CooVectorIteratorBase<_Scalar, _Index, _Vector>::operator*() noexcept {
  return getValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar, typename _Index, class _Vector>
const _Scalar& CooVectorIteratorBase<_Scalar, _Index, _Vector>::operator*() const noexcept {
  return getValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar, typename _Index, class _Vector>
_Scalar* CooVectorIteratorBase<_Scalar, _Index, _Vector>::operator->() noexcept {
  return &getValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar, typename _Index, class _Vector>
const _Scalar* CooVectorIteratorBase<_Scalar, _Index, _Vector>::operator->() const noexcept {
  return &getValue();
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the iterator to beginning.
///
template <typename _Scalar, typename _Index, class _Vector>
CooVectorIteratorBase<_Scalar, _Index, _Vector>& CooVectorIteratorBase<_Scalar, _Index, _Vector>::setBegin() noexcept {
  itidx_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the iterator to end.
///
template <typename _Scalar, typename _Index, class _Vector>
CooVectorIteratorBase<_Scalar, _Index, _Vector>& CooVectorIteratorBase<_Scalar, _Index, _Vector>::setEnd() noexcept {
  itidx_ = (container_ != nullptr) ? container_->getNnz() : 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the to beginning iterator.
///
template <typename _Scalar, typename _Index, class _Vector>
CooVectorIteratorBase<_Scalar, _Index, _Vector>
  CooVectorIteratorBase<_Scalar, _Index, _Vector>::getBegin( _Vector *vector ) noexcept {
  return CooVectorIteratorBase(vector).setBegin();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the to end iterator.
///
template <typename _Scalar, typename _Index, class _Vector>
CooVectorIteratorBase<_Scalar, _Index, _Vector>
  CooVectorIteratorBase<_Scalar, _Index, _Vector>::getEnd( _Vector *vector ) noexcept {
  return CooVectorIteratorBase(vector).setEnd();
}

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_COO_COO_VECTOR_ITERATOR_IPP_
