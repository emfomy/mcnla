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
/// @brief  Print to stream.
///
template <typename __Scalar, typename __Index, class __Vector>
std::ostream& operator<< ( std::ostream &out, const CooVectorIteratorBase<__Scalar, __Index, __Vector> &iterator ) {
  const index_t witdh = log10(iterator.container_->getLength())+1;
  return out << "(" << std::setw(witdh) << iterator.getIdx() << ")  "
                    << std::setw(ios_width) << iterator.getValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index.
///
template <typename _Scalar, typename _Index, class _Vector> template <index_t _dim>
typename CooVectorIteratorBase<_Scalar, _Index, _Vector>::IndexType&
    CooVectorIteratorBase<_Scalar, _Index, _Vector>::getIdx() const noexcept {
  return BaseType::template getIdx<_dim>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position.
///
template <typename _Scalar, typename _Index, class _Vector>
index_t CooVectorIteratorBase<_Scalar, _Index, _Vector>::getPos() const noexcept {
  return this->getItIdx();
}

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_COO_COO_VECTOR_ITERATOR_IPP_
