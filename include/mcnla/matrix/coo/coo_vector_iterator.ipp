////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/matrix/coo/coo_vector_iterator.ipp
/// @brief   The implementation of COO vector iterator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_MATRIX_COO_COO_VECTOR_ITERATOR_IPP_
#define MCNLA_MATRIX_COO_COO_VECTOR_ITERATOR_IPP_

#include <mcnla/matrix/coo/coo_vector_iterator.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Print to stream.
///
template <typename __Scalar, typename __Index, class __Vector>
std::ostream& operator<< ( std::ostream &out, const CooVectorIteratorBase<__Scalar, __Index, __Vector> &iterator ) {
  const index_t width = log10(iterator.container_->getLength())+1;
  return out << "(" << std::setw(width)     << iterator.getIdx()   << ")  "
                    << std::setw(ios_width) << iterator.getValue() << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index.
///
template <typename _Scalar, typename _Index, class _Vector>
typename CooVectorIteratorBase<_Scalar, _Index, _Vector>::IndexType&
    CooVectorIteratorBase<_Scalar, _Index, _Vector>::getIdx() const noexcept {
  return BaseType::template getIdx<0>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position.
///
template <typename _Scalar, typename _Index, class _Vector>
index_t CooVectorIteratorBase<_Scalar, _Index, _Vector>::getPos() const noexcept {
  return this->getItIdx();
}

}  // namespace mcnla

#endif  // MCNLA_MATRIX_COO_COO_VECTOR_ITERATOR_IPP_
