////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_matrix_iterator.ipp
/// @brief   The implementation of COO matrix iterator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_MATRIX_ITERATOR_IPP_
#define MCNLA_CORE_MATRIX_COO_COO_MATRIX_ITERATOR_IPP_

#include <mcnla/core/matrix/coo/coo_matrix_iterator.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Print to stream.
///
template <typename __Scalar, typename __Index, Layout __layout, class __Matrix>
std::ostream& operator<< ( std::ostream &out, const CooMatrixIteratorBase<__Scalar, __Index, __layout, __Matrix> &iterator ) {
  const index_t width_r = log10(iterator.container_->getNrow())+1;
  const index_t width_c = log10(iterator.container_->getNcol())+1;
  const index_t width   = std::max(width_r, width_c);
  return out << "(" << std::setw(width)     << iterator.getRowIdx() << ", "
                    << std::setw(width)     << iterator.getColIdx() << ")  "
                    << std::setw(ios_width) << iterator.getValue()  << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the row index.
///
template <typename _Scalar, typename _Index, Layout _layout, class _Matrix>
typename CooMatrixIteratorBase<_Scalar, _Index, _layout, _Matrix>::IndexType&
    CooMatrixIteratorBase<_Scalar, _Index, _layout, _Matrix>::getRowIdx() const noexcept {
  return BaseType::template getIdx<isColMajor(_layout) ? 0 : 1>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the column index.
///
template <typename _Scalar, typename _Index, Layout _layout, class _Matrix>
typename CooMatrixIteratorBase<_Scalar, _Index, _layout, _Matrix>::IndexType&
    CooMatrixIteratorBase<_Scalar, _Index, _layout, _Matrix>::getColIdx() const noexcept {
  return BaseType::template getIdx<isColMajor(_layout) ? 1 : 0>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position.
///
template <typename _Scalar, typename _Index, Layout _layout, class _Matrix>
index_t CooMatrixIteratorBase<_Scalar, _Index, _layout, _Matrix>::getPos() const noexcept {
  return this->getItIdx();
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_MATRIX_ITERATOR_IPP_
