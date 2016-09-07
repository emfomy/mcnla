////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_vector_iterator.ipp
/// @brief   The implementation of dense vector iterator.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_VECTOR_ITERATOR_IPP_
#define ISVD_MATRIX_DENSE_VECTOR_ITERATOR_IPP_

#include <isvd/matrix/dense_vector_iterator.hpp>

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
template <typename _Scalar>
DenseVectorIterator<_Scalar>::DenseVectorIterator() noexcept
  : idx_(0),
    vector_(nullptr) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given vector.
///
template <typename _Scalar>
DenseVectorIterator<_Scalar>::DenseVectorIterator(
    DenseVector<_Scalar> *vector
) noexcept
  : idx_(0),
    vector_(vector) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
template <typename _Scalar>
DenseVectorIterator<_Scalar>::DenseVectorIterator(
    const DenseVectorIterator &other
) noexcept
  : idx_(other.idx_),
    vector_(other.vector_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
template <typename _Scalar>
DenseVectorIterator<_Scalar>& DenseVectorIterator<_Scalar>::operator=(
    const DenseVectorIterator &other
) noexcept {
  idx_ = other.idx_;
  vector_ = other.vector_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Equal-to operator.
///
template <typename _Scalar>
bool DenseVectorIterator<_Scalar>::operator==(
    const DenseVectorIterator &other
) const noexcept {
  if ( this == &other ) {
    return true;
  } else if ( *(vector_->getData()) != *(other.vector_->getData()) ) {
    return false;
  } else {
    return idx_ == other.idx_;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Not-equal-to operator.
///
template <typename _Scalar>
bool DenseVectorIterator<_Scalar>::operator!=(
    const DenseVectorIterator &other
) const noexcept {
  return !(*this == other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Prefix increment operator.
///
template <typename _Scalar>
DenseVectorIterator<_Scalar>& DenseVectorIterator<_Scalar>::operator++() noexcept {
  assert(vector_ != nullptr);

  const auto length = vector_->getLength();
  if ( ++idx_ >= length ) {
    idx_ = length;
  }
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Postfix increment operator.
///
template <typename _Scalar>
DenseVectorIterator<_Scalar>& DenseVectorIterator<_Scalar>::operator++( int ) noexcept {
  auto retval(*this);
  (*this)++;
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar>
_Scalar& DenseVectorIterator<_Scalar>::operator*() noexcept {
  return getValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar>
const _Scalar& DenseVectorIterator<_Scalar>::operator*() const noexcept {
  return getValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar>
_Scalar* DenseVectorIterator<_Scalar>::operator->() noexcept {
  return &getValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar>
const _Scalar* DenseVectorIterator<_Scalar>::operator->() const noexcept {
  return &getValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value.
///
/// @attention  Never call this when the iterator is at the end.
///
template <typename _Scalar>
_Scalar& DenseVectorIterator<_Scalar>::getValue() noexcept {
  return (*vector_)(idx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar>
const _Scalar& DenseVectorIterator<_Scalar>::getValue() const noexcept {
  return (*vector_)(idx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index.
///
template <typename _Scalar>
index_t DenseVectorIterator<_Scalar>::getIdx() noexcept {
  return idx_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the iterator to beginning.
///
template <typename _Scalar>
DenseVectorIterator<_Scalar>& DenseVectorIterator<_Scalar>::setBegin() noexcept {
  idx_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the iterator to end.
///
template <typename _Scalar>
DenseVectorIterator<_Scalar>& DenseVectorIterator<_Scalar>::setEnd() noexcept {
  idx_ = (vector_ != nullptr) ? vector_->getLength() : 0;
  return *this;
}

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_VECTOR_ITERATOR_IPP_
