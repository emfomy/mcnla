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
/// @brief  Default constructor.
///
template <typename _Scalar, class _Vector>
DenseVectorIteratorBase<_Scalar, _Vector>::DenseVectorIteratorBase() noexcept
  : idx_(0),
    container_(nullptr) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given vector.
///
template <typename _Scalar, class _Vector>
DenseVectorIteratorBase<_Scalar, _Vector>::DenseVectorIteratorBase(
    _Vector *vector,
    const index_t idx
) noexcept
  : idx_(idx),
    container_(vector) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
template <typename _Scalar, class _Vector>
DenseVectorIteratorBase<_Scalar, _Vector>::DenseVectorIteratorBase(
    const DenseVectorIteratorBase &other
) noexcept
  : idx_(other.idx_),
    container_(other.container_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
template <typename _Scalar, class _Vector>
DenseVectorIteratorBase<_Scalar, _Vector>& DenseVectorIteratorBase<_Scalar, _Vector>::operator=(
    const DenseVectorIteratorBase &other
) noexcept {
  idx_ = other.idx_;
  container_ = other.container_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Equal-to operator.
///
template <typename _Scalar, class _Vector>
bool DenseVectorIteratorBase<_Scalar, _Vector>::operator==(
    const DenseVectorIteratorBase &other
) const noexcept {
  return (container_ == other.container_) && (idx_ == other.idx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Not-equal-to operator.
///
template <typename _Scalar, class _Vector>
bool DenseVectorIteratorBase<_Scalar, _Vector>::operator!=(
    const DenseVectorIteratorBase &other
) const noexcept {
  return !(*this == other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Prefix increment operator.
///
template <typename _Scalar, class _Vector>
DenseVectorIteratorBase<_Scalar, _Vector>& DenseVectorIteratorBase<_Scalar, _Vector>::operator++() noexcept {
  assert(container_ != nullptr);

  const auto length = container_->getLength();
  if ( ++idx_ >= length ) {
    idx_ = length;
  }
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Postfix increment operator.
///
template <typename _Scalar, class _Vector>
DenseVectorIteratorBase<_Scalar, _Vector> DenseVectorIteratorBase<_Scalar, _Vector>::operator++( int ) noexcept {
  auto retval(*this);
  ++(*this);
  return retval;
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
  return makeIdxTuple(idx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index.
///
template <typename _Scalar, class _Vector>
index_t DenseVectorIteratorBase<_Scalar, _Vector>::getIdx() const noexcept {
  return idx_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position.
///
template <typename _Scalar, class _Vector>
index_t DenseVectorIteratorBase<_Scalar, _Vector>::getPos() const noexcept {
  return container_->getPos(idx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the iterator to beginning.
///
template <typename _Scalar, class _Vector>
DenseVectorIteratorBase<_Scalar, _Vector>& DenseVectorIteratorBase<_Scalar, _Vector>::setBegin() noexcept {
  idx_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the iterator to end.
///
template <typename _Scalar, class _Vector>
DenseVectorIteratorBase<_Scalar, _Vector>& DenseVectorIteratorBase<_Scalar, _Vector>::setEnd() noexcept {
  idx_ = (container_ != nullptr) ? container_->getLength() : 0;
  return *this;
}

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_VECTOR_ITERATOR_IPP_
