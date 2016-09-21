////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/coo/coo_matrix_iterator.ipp
/// @brief   The implementation of COO matrix iterator.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_COO_COO_MATRIX_ITERATOR_IPP_
#define ISVD_MATRIX_COO_COO_MATRIX_ITERATOR_IPP_

#include <isvd/matrix/coo/coo_matrix_iterator.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Print to stream.
///
template <typename __Scalar, typename __Index, Layout __layout, class __Matrix>
std::ostream& operator<< ( std::ostream &out, const CooMatrixIteratorBase<__Scalar, __Index, __layout, __Matrix> &iterator ) {
  const index_t width_r = log10(iterator.container_->getNrow())+1;
  const index_t width_c = log10(iterator.container_->getNcol())+1;
  return out << "(" << std::setw(width_r) << iterator.getRowIdx() << ", "
                    << std::setw(width_c) << iterator.getColIdx() << ")  "
                    << std::setw(ios_width) << iterator.getValue() << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the row index.
///
template <typename _Scalar, typename _Index, Layout _layout, class _Matrix>
typename CooMatrixIteratorBase<_Scalar, _Index, _layout, _Matrix>::IndexType&
    CooMatrixIteratorBase<_Scalar, _Index, _layout, _Matrix>::getRowIdx() const noexcept {
  return isColMajor(_layout) ? getIdx1() : getIdx2();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the column index.
///
template <typename _Scalar, typename _Index, Layout _layout, class _Matrix>
typename CooMatrixIteratorBase<_Scalar, _Index, _layout, _Matrix>::IndexType&
    CooMatrixIteratorBase<_Scalar, _Index, _layout, _Matrix>::getColIdx() const noexcept {
  return isColMajor(_layout) ? getIdx2() : getIdx1();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the first index.
///
template <typename _Scalar, typename _Index, Layout _layout, class _Matrix>
typename CooMatrixIteratorBase<_Scalar, _Index, _layout, _Matrix>::IndexType&
    CooMatrixIteratorBase<_Scalar, _Index, _layout, _Matrix>::getIdx1() const noexcept {
  return BaseType::template getIdx<0>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the second index.
///
template <typename _Scalar, typename _Index, Layout _layout, class _Matrix>
typename CooMatrixIteratorBase<_Scalar, _Index, _layout, _Matrix>::IndexType&
    CooMatrixIteratorBase<_Scalar, _Index, _layout, _Matrix>::getIdx2() const noexcept {
  return BaseType::template getIdx<1>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position.
///
template <typename _Scalar, typename _Index, Layout _layout, class _Matrix>
index_t CooMatrixIteratorBase<_Scalar, _Index, _layout, _Matrix>::getPos() const noexcept {
  return this->getItIdx();
}

}  // namespace isvd

#endif  // ISVD_MATRIX_COO_COO_MATRIX_ITERATOR_IPP_
