////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_vector_iterator.hpp
/// @brief   The dense vector iterator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_ITERATOR_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_ITERATOR_HPP_

#include <mcnla/core/matrix/dense/dense_vector_iterator.hh>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Output to stream.
///
template <typename __Scalar, class __Vector>
std::ostream& operator<< (
    std::ostream &os,
    const DenseVectorIteratorBase<__Scalar, __Vector> &iterator
) {
  const index_t width = log10(iterator.container_->length())+1;
  return os << "(" << std::setw(width) << iterator.idx() << ")  " << std::setw(ios_width) << iterator.value();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the value.
///
/// @attention  Never call this when the iterator is at the end.
///
template <typename _Scalar, class _Vector>
_Scalar& DenseVectorIteratorBase<_Scalar, _Vector>::value() const noexcept {
  mcnla_assert_gelt(itidx_, 0, container_->nelem());
  return container_->valuePtr()[pos()];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index.
///
template <typename _Scalar, class _Vector>
index_t DenseVectorIteratorBase<_Scalar, _Vector>::idx() const noexcept {
  return itidx_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position.
///
/// @attention  Never call this when the iterator is at the end.
///
template <typename _Scalar, class _Vector>
index_t DenseVectorIteratorBase<_Scalar, _Vector>::pos() const noexcept {
  return container_->pos(itidx_);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_ITERATOR_HPP_
