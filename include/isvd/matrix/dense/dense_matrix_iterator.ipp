////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense/dense_matrix_iterator.ipp
/// @brief   The implementation of dense matrix iterator.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_IPP_
#define ISVD_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_IPP_

#include <isvd/matrix/dense/dense_matrix_iterator.hpp>

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
template <typename _Scalar, Layout _layout>
DenseMatrixIterator<_Scalar, _layout>::DenseMatrixIterator() noexcept
  : idx1_(0),
    idx2_(0),
    matrix_(nullptr) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given matrix.
///
template <typename _Scalar, Layout _layout>
DenseMatrixIterator<_Scalar, _layout>::DenseMatrixIterator(
    DenseMatrix<_Scalar, _layout> *matrix
) noexcept
  : idx1_(0),
    idx2_(0),
    matrix_(matrix) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
template <typename _Scalar, Layout _layout>
DenseMatrixIterator<_Scalar, _layout>::DenseMatrixIterator(
    const DenseMatrixIterator &other
) noexcept
  : idx1_(other.idx1_),
    idx2_(other.idx2_),
    matrix_(other.matrix_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
template <typename _Scalar, Layout _layout>
DenseMatrixIterator<_Scalar, _layout>& DenseMatrixIterator<_Scalar, _layout>::operator=(
    const DenseMatrixIterator &other
) noexcept {
  idx1_ = other.idx1_;
  idx2_ = other.idx2_;
  matrix_ = other.matrix_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Equal-to operator.
///
template <typename _Scalar, Layout _layout>
bool DenseMatrixIterator<_Scalar, _layout>::operator==(
    const DenseMatrixIterator &other
) const noexcept {
  if ( this == &other ) {
    return true;
  } else if ( *(matrix_->getData()) != *(other.matrix_->getData()) ) {
    return false;
  } else {
    return (idx1_ == other.idx1_) && (idx2_ == other.idx2_);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Not-equal-to operator.
///
template <typename _Scalar, Layout _layout>
bool DenseMatrixIterator<_Scalar, _layout>::operator!=(
    const DenseMatrixIterator &other
) const noexcept {
  return !(*this == other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Prefix increment operator.
///
template <typename _Scalar, Layout _layout>
DenseMatrixIterator<_Scalar, _layout>& DenseMatrixIterator<_Scalar, _layout>::operator++() noexcept {
  assert(matrix_ != nullptr);

  const auto size1 = matrix_->getSize1();
  const auto size2 = matrix_->getSize2();
  if ( ++idx1_ >= size1 ) {
    idx1_ = 0;
    if ( ++idx2_ >= size2 ) {
      idx2_ = size2;
    }
  }
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Postfix increment operator.
///
template <typename _Scalar, Layout _layout>
DenseMatrixIterator<_Scalar, _layout>& DenseMatrixIterator<_Scalar, _layout>::operator++( int ) noexcept {
  auto retval(*this);
  (*this)++;
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar, Layout _layout>
_Scalar& DenseMatrixIterator<_Scalar, _layout>::operator*() noexcept {
  return getValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar, Layout _layout>
const _Scalar& DenseMatrixIterator<_Scalar, _layout>::operator*() const noexcept {
  return getValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar, Layout _layout>
_Scalar* DenseMatrixIterator<_Scalar, _layout>::operator->() noexcept {
  return &getValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar, Layout _layout>
const _Scalar* DenseMatrixIterator<_Scalar, _layout>::operator->() const noexcept {
  return &getValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value.
///
/// @attention  Never call this when the iterator is at the end.
///
template <typename _Scalar, Layout _layout>
_Scalar& DenseMatrixIterator<_Scalar, _layout>::getValue() noexcept {
  return (*matrix_)(rowidx_, colidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar, Layout _layout>
const _Scalar& DenseMatrixIterator<_Scalar, _layout>::getValue() const noexcept {
  return (*matrix_)(rowidx_, colidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the row index.
///
template <typename _Scalar, Layout _layout>
index_t DenseMatrixIterator<_Scalar, _layout>::getRowIdx() noexcept {
  return rowidx_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the column index.
///
template <typename _Scalar, Layout _layout>
index_t DenseMatrixIterator<_Scalar, _layout>::getColIdx() noexcept {
  return colidx_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the leading index.
///
template <typename _Scalar, Layout _layout>
index_t DenseMatrixIterator<_Scalar, _layout>::getIdx1() noexcept {
  return idx1_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the second index.
///
template <typename _Scalar, Layout _layout>
index_t DenseMatrixIterator<_Scalar, _layout>::getIdx2() noexcept {
  return idx2_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the iterator to beginning.
///
template <typename _Scalar, Layout _layout>
DenseMatrixIterator<_Scalar, _layout>& DenseMatrixIterator<_Scalar, _layout>::setBegin() noexcept {
  idx1_ = 0;
  idx2_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the iterator to end.
///
template <typename _Scalar, Layout _layout>
DenseMatrixIterator<_Scalar, _layout>& DenseMatrixIterator<_Scalar, _layout>::setEnd() noexcept {
  idx1_ = 0;
  idx2_ = (matrix_ != nullptr) ? matrix_->getSize2() : 0;
  return *this;
}

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_IPP_
