////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_cube_iterator.ipp
/// @brief   The implementation of COO cube iterator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_CUBE_ITERATOR_IPP_
#define MCNLA_CORE_MATRIX_COO_COO_CUBE_ITERATOR_IPP_

#include <mcnla/core/matrix/coo/coo_cube_iterator.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Print to stream.
///
template <typename __Scalar, typename __Index, Layout __layout, class __Cube>
std::ostream& operator<< ( std::ostream &out, const CooCubeIteratorBase<__Scalar, __Index, __layout, __Cube> &iterator ) {
  const index_t width_r = log10(iterator.container_->getNrow())+1;
  const index_t width_c = log10(iterator.container_->getNcol())+1;
  const index_t width_p = log10(iterator.container_->getNpage())+1;
  const index_t width   = std::max(std::max(width_r, width_c), width_p);
  return out << "(" << std::setw(width)     << iterator.getRowIdx()  << ", "
                    << std::setw(width)     << iterator.getColIdx()  << ", "
                    << std::setw(width)     << iterator.getPageIdx() << ")  "
                    << std::setw(ios_width) << iterator.getValue()   << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the row index.
///
template <typename _Scalar, typename _Index, Layout _layout, class _Cube>
typename CooCubeIteratorBase<_Scalar, _Index, _layout, _Cube>::IndexType&
    CooCubeIteratorBase<_Scalar, _Index, _layout, _Cube>::getRowIdx() const noexcept {
  return BaseType::template getIdx<isColMajor(_layout) ? 0 : 1>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the column index.
///
template <typename _Scalar, typename _Index, Layout _layout, class _Cube>
typename CooCubeIteratorBase<_Scalar, _Index, _layout, _Cube>::IndexType&
    CooCubeIteratorBase<_Scalar, _Index, _layout, _Cube>::getColIdx() const noexcept {
  return BaseType::template getIdx<isColMajor(_layout) ? 1 : 0>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the page index.
///
template <typename _Scalar, typename _Index, Layout _layout, class _Cube>
typename CooCubeIteratorBase<_Scalar, _Index, _layout, _Cube>::IndexType&
    CooCubeIteratorBase<_Scalar, _Index, _layout, _Cube>::getPageIdx() const noexcept {
  return BaseType::template getIdx<2>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position.
///
template <typename _Scalar, typename _Index, Layout _layout, class _Cube>
index_t CooCubeIteratorBase<_Scalar, _Index, _layout, _Cube>::getPos() const noexcept {
  return this->getItIdx();
}

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_CUBE_ITERATOR_IPP_
