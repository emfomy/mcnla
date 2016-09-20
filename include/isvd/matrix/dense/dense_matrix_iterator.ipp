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
//  The detail namespace.
//
namespace detail {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Print to stream.
///
template <typename __Scalar, Layout __layout, class __Matrix>
std::ostream& operator<< ( std::ostream &out, const DenseMatrixIteratorBase<__Scalar, __layout, __Matrix> &iterator ) {
  const index_t witdh_r = log10(iterator.container_->getNrow())+1;
  const index_t witdh_c = log10(iterator.container_->getNcol())+1;
  return out << "(" << std::setw(witdh_r) << iterator.getRowIdx() << ", "
                    << std::setw(witdh_c) << iterator.getColIdx() << ")  "
                    << std::setw(ios_width) << iterator.getValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value.
///
/// @attention  Never call this when the iterator is at the end.
///
template <typename _Scalar, Layout _layout, class _Matrix>
_Scalar& DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::getValue() noexcept {
  return container_->getValue()[getPos()];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getValue
///
template <typename _Scalar, Layout _layout, class _Matrix>
const _Scalar& DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::getValue() const noexcept {
  return container_->getValue()[getPos()];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index tuple.
///
template <typename _Scalar, Layout _layout, class _Matrix>
IdxTuple<2> DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::getIdxs() const noexcept {
  return makeIdxTuple(&getIdx1(), &getIdx2());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the row index.
///
template <typename _Scalar, Layout _layout, class _Matrix>
index_t DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::getRowIdx() const noexcept {
  return isColMajor(_layout) ? getIdx1() : getIdx2();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the column index.
///
template <typename _Scalar, Layout _layout, class _Matrix>
index_t DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::getColIdx() const noexcept {
  return isColMajor(_layout) ? getIdx2() : getIdx1();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the leading index.
///
template <typename _Scalar, Layout _layout, class _Matrix>
index_t DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::getIdx1() const noexcept {
  return itidx_ % container_->getSize1();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the second index.
///
template <typename _Scalar, Layout _layout, class _Matrix>
index_t DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::getIdx2() const noexcept {
  return itidx_ / container_->getSize1();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position.
///
template <typename _Scalar, Layout _layout, class _Matrix>
index_t DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>::getPos() const noexcept {
  return container_->getPos(getRowIdx(), getColIdx());
}

}  // namespace detail

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_IPP_
