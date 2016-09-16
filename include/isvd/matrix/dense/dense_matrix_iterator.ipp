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
template <typename _Scalar, Layout _layout, class _Matrix>
DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::DenseMatrixIteratorBase() noexcept
  : rowidx_(0),
    colidx_(0),
    matrix_(nullptr) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given matrix.
///
template <typename _Scalar, Layout _layout, class _Matrix>
DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::DenseMatrixIteratorBase(
    _Matrix *matrix
) noexcept
  : rowidx_(0),
    colidx_(0),
    matrix_(matrix) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given matrix.
///
template <typename _Scalar, Layout _layout, class _Matrix>
DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::DenseMatrixIteratorBase(
    _Matrix *matrix,
    const index_t rowidx,
    const index_t colidx
) noexcept
  : rowidx_(rowidx),
    colidx_(colidx),
    matrix_(matrix) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
template <typename _Scalar, Layout _layout, class _Matrix>
DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::DenseMatrixIteratorBase(
    const DenseMatrixIteratorBase &other
) noexcept
  : rowidx_(other.rowidx_),
    colidx_(other.colidx_),
    matrix_(other.matrix_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
template <typename _Scalar, Layout _layout, class _Matrix>
DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>& DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::operator=(
    const DenseMatrixIteratorBase &other
) noexcept {
  rowidx_ = other.rowidx_;
  colidx_ = other.colidx_;
  matrix_ = other.matrix_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Equal-to operator.
///
template <typename _Scalar, Layout _layout, class _Matrix>
bool DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::operator==(
    const DenseMatrixIteratorBase &other
) const noexcept {
  if ( this == &other ) {
    return true;
  } else {
    return &(getValue()) == &(other.getValue());
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Not-equal-to operator.
///
template <typename _Scalar, Layout _layout, class _Matrix>
bool DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::operator!=(
    const DenseMatrixIteratorBase &other
) const noexcept {
  return !(*this == other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Prefix increment operator.
///
template <typename _Scalar, Layout _layout, class _Matrix>
DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>&
    DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::operator++() noexcept {
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
template <typename _Scalar, Layout _layout, class _Matrix>
DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>
    DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::operator++( int ) noexcept {
  auto retval(*this);
  ++(*this);
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value.
///
/// @attention  Never call this when the iterator is at the end.
///
template <typename _Scalar, Layout _layout, class _Matrix>
_Scalar& DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::getValue() noexcept {
  return matrix_->getValue()[getPos()];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar, Layout _layout, class _Matrix>
const _Scalar& DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::getValue() const noexcept {
  return matrix_->getValue()[getPos()];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index tuple.
///
template <typename _Scalar, Layout _layout, class _Matrix>
typename DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::IdxTupleType
    DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::getIdxs() const noexcept {
  return makeIdxTuple(idx1_, idx2_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the row index.
///
template <typename _Scalar, Layout _layout, class _Matrix>
index_t DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::getRowIdx() const noexcept {
  return rowidx_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the column index.
///
template <typename _Scalar, Layout _layout, class _Matrix>
index_t DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::getColIdx() const noexcept {
  return colidx_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the leading index.
///
template <typename _Scalar, Layout _layout, class _Matrix>
index_t DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::getIdx1() const noexcept {
  return idx1_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the second index.
///
template <typename _Scalar, Layout _layout, class _Matrix>
index_t DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::getIdx2() const noexcept {
  return idx2_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position.
///
template <typename _Scalar, Layout _layout, class _Matrix>
index_t DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::getPos() const noexcept {
  return matrix_->getPos(colidx_, rowidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the iterator to beginning.
///
template <typename _Scalar, Layout _layout, class _Matrix>
DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>& DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::setBegin() noexcept {
  idx1_ = 0;
  idx2_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the iterator to end.
///
template <typename _Scalar, Layout _layout, class _Matrix>
DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>& DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::setEnd() noexcept {
  idx1_ = 0;
  idx2_ = (matrix_ != nullptr) ? matrix_->getSize2() : 0;
  return *this;
}

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_IPP_
